/*
  +----------------------------------------------------------------------+
  | For PHP Version 7                                                    |
  +----------------------------------------------------------------------+
  | Copyright (c) 2017 Elizabeth M Smith                                 |
  +----------------------------------------------------------------------+
  | http://www.opensource.org/licenses/mit-license.php  MIT License      |
  | Also available in LICENSE                                            |
  +----------------------------------------------------------------------+
  | Author: Elizabeth M Smith <auroraeosrose@gmail.com>                  |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#	include "config.h"
#endif

#include <php.h>
#include <zend_exceptions.h>
#include <ext/spl/spl_exceptions.h>

#include <glib.h>

#include "php_glib.h"
#include "php_glib_internal.h"

zend_class_entry *ce_glib_timer;
static zend_object_handlers glib_timer_object_handlers;

typedef struct _glib_timer_object {
	GTimer *timer;
	zend_bool active;
	zend_object std;
} glib_timer_object;

static inline glib_timer_object *glib_timer_fetch_object(zend_object *object)
{
	return (glib_timer_object *) ((char*)(object) - XtOffsetOf(glib_timer_object, std));
}
#define Z_GLIB_TIMER_P(zv) glib_timer_fetch_object(Z_OBJ_P(zv))

/* ----------------------------------------------------------------
    Glib\Timer class API
------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO(Timer___construct_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto void \Glib\Timer->__construct()
        Creates a new timer and implicitly calls start on it, so you don't have to call start
   */
PHP_METHOD(GlibTimer, __construct)
{
	if (zend_parse_parameters_none_throw() == FAILURE) {
		return;
	}
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Timer_start_args, IS_VOID, 1)
ZEND_END_ARG_INFO()

/* {{{ proto void \Glib\Timer->start()
        Starts or restarts the timer - really a reset call
	If used after stop call the total time will be started over, not added to
   */
PHP_METHOD(GlibTimer, start)
{
	glib_timer_object *timer_object;

	if (zend_parse_parameters_none_throw() == FAILURE) {
		return;
	}

	timer_object = Z_GLIB_TIMER_P(getThis());

	g_timer_start(timer_object->timer);
	timer_object->active = TRUE;
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Timer_stop_args, IS_VOID, 1)
ZEND_END_ARG_INFO()

/* {{{ proto void \Glib\Timer->stop()
         stops the timer, already elapsed time will not be erased
         really more like a "marker" then stopping the timer
   */
PHP_METHOD(GlibTimer, stop)
{
	glib_timer_object *timer_object;

	if (zend_parse_parameters_none_throw() == FAILURE) {
		return;
	}

	timer_object = Z_GLIB_TIMER_P(getThis());

	g_timer_stop(timer_object->timer);
	timer_object->active = FALSE;
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Timer_continue_args, IS_VOID, 1)
ZEND_END_ARG_INFO()

/* {{{ proto void \Glib\Timer->continue()
        continues timing after a stop call, MUST have stop called before this can be called
		if called without a stop call first a warning is thrown
   */
PHP_METHOD(GlibTimer, continue)
{
	glib_timer_object *timer_object;

	if (zend_parse_parameters_none_throw() == FAILURE) {
		return;
	}

	timer_object = Z_GLIB_TIMER_P(getThis());

	if (timer_object->active == TRUE) {
		zend_throw_exception(spl_ce_BadMethodCallException, "Cannot call continue on a timer that has not been stopped", 0);
		return;
	}

	g_timer_continue(timer_object->timer);
	timer_object->active = TRUE;
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Timer_elapsed_args, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()

/* {{{ proto float \Glib\Timer->elapsed()
         returns the total elapsed time from the last start call
	or the difference between the start and last stop (mark) call
   */
PHP_METHOD(GlibTimer, elapsed)
{
	glib_timer_object *timer_object;

	if (zend_parse_parameters_none_throw() == FAILURE) {
		return;
	}

	timer_object = Z_GLIB_TIMER_P(getThis());

	RETURN_DOUBLE(g_timer_elapsed(timer_object->timer, NULL));
}
/* }}} */

/* ----------------------------------------------------------------
    Glib\Timer Object management
------------------------------------------------------------------*/

/* Custom Object Destruction - calls g_timer_destroy() */
void glib_timer_free_obj(zend_object *object)
{
	glib_timer_object *intern = glib_timer_fetch_object(object);

	if(!intern) {
		return;
	}
	if(intern->timer) {
		g_timer_destroy(intern->timer);
	}
	intern->timer = NULL;
	intern->active = FALSE;

	zend_object_std_dtor(&intern->std);
}

/* Custom object creation - calls g_timer_new() */
static zend_object* glib_timer_create_object(zend_class_entry *ce)
{
	glib_timer_object *intern = NULL;

	intern = ecalloc(1, sizeof(glib_timer_object) + zend_object_properties_size(ce));
	intern->timer = g_timer_new();
	intern->active = TRUE;

	zend_object_std_init(&(intern->std), ce);
	object_properties_init(&(intern->std), ce);
	intern->std.handlers = &glib_timer_object_handlers;
	return &(intern->std);
}

/* ----------------------------------------------------------------
    Glib\Timer Class Definition and Registration
------------------------------------------------------------------*/

static const zend_function_entry glib_timer_methods[] = {
	PHP_ME(GlibTimer, __construct, Timer___construct_args, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(GlibTimer, start, Timer_start_args, ZEND_ACC_PUBLIC)
	PHP_ME(GlibTimer, stop, Timer_stop_args, ZEND_ACC_PUBLIC)
	PHP_ME(GlibTimer, continue, Timer_continue_args, ZEND_ACC_PUBLIC)
	PHP_ME(GlibTimer, elapsed, Timer_elapsed_args, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

PHP_MINIT_FUNCTION(glib_timer)
{
	zend_class_entry ce;

	memcpy(&glib_timer_object_handlers, zend_get_std_object_handlers(),
		sizeof(zend_object_handlers));
	glib_timer_object_handlers.offset = XtOffsetOf(glib_timer_object, std);
	glib_timer_object_handlers.clone_obj = NULL;
	glib_timer_object_handlers.free_obj = glib_timer_free_obj;

	INIT_NS_CLASS_ENTRY(ce, GLIB_NAMESPACE, "Timer", glib_timer_methods);
	ce.create_object = glib_timer_create_object;
	ce_glib_timer = zend_register_internal_class(&ce);

	return SUCCESS;
}

