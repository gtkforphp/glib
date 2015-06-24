/*
  +----------------------------------------------------------------------+
  | For PHP Version 7                                                    |
  +----------------------------------------------------------------------+
  | Copyright (c) 2015 Elizabeth M Smith                                 |
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
#include <glib.h>

#include "php_glib.h"

zend_class_entry *ce_glib_timer;
static zend_object_handlers glib_timer_object_handlers;

typedef struct _glib_timer_object {
	GTimer *timer;
	zend_bool active;
	zend_object std;
} glib_timer_object;

#define GLIB_TIMER_FETCH_OBJ(zv) ((glib_timer_object*) (((char*)Z_OBJ_P(zv)) - XtOffsetOf(glib_timer_object, std)))

/* {{{ proto void \Glib\Timer->__construct()
        Creates a new timer and implicitly calls start on it, so you don't have to call start
   */
PHP_METHOD(Glib_Timer, __construct)
{
	glib_timer_object *timer_object = GLIB_TIMER_FETCH_OBJ(getThis());

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	timer_object->timer = g_timer_new();
	timer_object->active = TRUE;
}
/* }}} */

/* {{{ proto void \Glib\Timer->start()
    Starts or restarts the timer - identical to reset call
    If used after stop call the total time will be started over, not added to
   */
PHP_METHOD(Glib_Timer, start)
{
	glib_timer_object *timer_object = GLIB_TIMER_FETCH_OBJ(getThis());

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	g_timer_start(timer_object->timer);
	timer_object->active = TRUE;
}
/* }}} */

/* {{{ proto void \Glib\Timer->stop()
         stops the timer, already elapsed time will not be erased
   */
PHP_METHOD(Glib_Timer, stop)
{
	glib_timer_object *timer_object = GLIB_TIMER_FETCH_OBJ(getThis());

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	g_timer_stop(timer_object->timer);
	timer_object->active = FALSE;
}
/* }}} */

/* {{{ proto void \Glib\Timer->continue()
        continues timing after a stop call, MUST have stop called before this can be called
		if called without a stop call first a warning is thrown
   */
PHP_METHOD(Glib_Timer, continue)
{
	glib_timer_object *timer_object = GLIB_TIMER_FETCH_OBJ(getThis());

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	if (timer_object->active == TRUE) {
		// TODO replace this with other exception type
		zend_throw_exception(zend_exception_get_default(), "Cannot continue a Timer that has not been stopped");
		return;
	}
	g_timer_continue(timer_object->timer);
	timer_object->active = TRUE;
}
/* }}} */

/* {{{ proto void \Glib\Timer->reset()
         identical to start, sets the timer total back to zero
   */
PHP_METHOD(Glib_Timer, reset)
{
	glib_timer_object *timer_object = GLIB_TIMER_FETCH_OBJ(getThis());

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	g_timer_reset(timer_object->timer);
	timer_object->active = TRUE;
}
/* }}} */

/* {{{ proto float \Glib\Timer->elapsed()
         returns the total elapsed time from the last start/reset call
   */
PHP_METHOD(Glib_Timer, elapsed)
{
	glib_timer_object *timer_object = GLIB_TIMER_FETCH_OBJ(getThis());

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	RETURN_DOUBLE(g_timer_elapsed(timer_object->timer, NULL));
}
/* }}} */

/* {{{ arginfo */
ZEND_BEGIN_ARG_INFO(arginfo_glib_timer_void, 0)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ */
const zend_function_entry glib_timer_methods[] = {
	PHP_ME(Glib_Timer, __construct, arginfo_glib_timer_void, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Glib_Timer, start, arginfo_glib_timer_void, ZEND_ACC_PUBLIC)
	PHP_ME(Glib_Timer, stop, arginfo_glib_timer_void, ZEND_ACC_PUBLIC)
	PHP_ME(Glib_Timer, continue, arginfo_glib_timer_void, ZEND_ACC_PUBLIC)
	PHP_ME(Glib_Timer, reset, arginfo_glib_timer_void, ZEND_ACC_PUBLIC)
	PHP_ME(Glib_Timer, elapsed, arginfo_glib_timer_void, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
/* }}} */

/* {{{ */
static inline void glib_timer_free_storage(zend_object *object)
{
	glib_timer_object *intern = (glib_timer_object*) ((char*)object - XtOffsetOf(glib_timer_object, std));

	if(!intern) {
		return;
	}

	if(intern->timer) {
		g_timer_destroy(intern->timer);
	}
	intern->timer = NULL;

	zend_object_std_dtor(&intern->std);
}
/* }}} */

/* {{{ */
static inline zend_object* glib_timer_object_new(zend_class_entry *ce)
{
	glib_timer_object *object = ecalloc(1, sizeof(glib_timer_object) + zend_object_properties_size(ce));
	object->active = FALSE;

	zend_object_std_init(&object->std, ce);
	object_properties_init(&object->std, ce);
	object->std.handlers = &glib_timer_object_handlers;
	return &object->std;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(glib_timer)
{
	zend_class_entry ce;

	memcpy(&glib_timer_object_handlers,
		   zend_get_std_object_handlers(),
		   sizeof(zend_object_handlers));

	glib_timer_object_handlers.offset = XtOffsetOf(glib_timer_object, std);
	glib_timer_object_handlers.free_obj = glib_timer_free_storage;
	glib_timer_object_handlers.clone_obj = NULL;

	INIT_NS_CLASS_ENTRY(ce, GLIB_NAMESPACE, "Timer", glib_timer_methods);
	ce.create_object = glib_timer_object_new;
	ce_glib_timer = zend_register_internal_class(&ce);

	return SUCCESS;
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
