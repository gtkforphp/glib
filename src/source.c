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

zend_class_entry *glib_ce_source;
static zend_object_handlers glib_source_object_handlers;

typedef struct _glib_source_object {
	GSource *source;
	zend_object std;
} glib_source_object;

static inline glib_source_object *glib_source_fetch_object(zend_object *object)
{
	return (glib_source_object *) ((char*)(object) - XtOffsetOf(glib_source_object, std));
}
#define Z_GLIB_SOURCE_P(zv) glib_source_fetch_object(Z_OBJ_P(zv))

/* ----------------------------------------------------------------
    Glib\Source class API
------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO(Source___construct_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto void \Glib\Source->__construct()
        Creates a new source and implicitly calls start on it, so you don't have to call start
   */
PHP_METHOD(GlibSource, __construct)
{
	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}
}
/* }}} */

ZEND_BEGIN_ARG_INFO(Source_start_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto void \Glib\Source->start()
        Starts or restarts the source - identical to reset call
		If used after stop call the total time will be started over, not added to
   */
PHP_METHOD(GlibSource, start)
{
	glib_source_object *source_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}

	source_object = Z_GLIB_TIMER_P(getThis());

	g_source_start(source_object->source);
	source_object->active = TRUE;
}
/* }}} */

ZEND_BEGIN_ARG_INFO(Source_stop_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto void \Glib\Source->stop()
         stops the source, already elapsed time will not be erased
   */
PHP_METHOD(GlibSource, stop)
{
	glib_source_object *source_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}
	source_object = Z_GLIB_TIMER_P(getThis());

	g_source_stop(source_object->source);
	source_object->active = FALSE;
}
/* }}} */

ZEND_BEGIN_ARG_INFO(Source_continue_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto void \Glib\Source->continue()
        continues timing after a stop call, MUST have stop called before this can be called
		if called without a stop call first a warning is thrown
   */
PHP_METHOD(GlibSource, continue)
{
	glib_source_object *source_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}
	source_object = Z_GLIB_TIMER_P(getThis());

	if (source_object->active == TRUE) {
		zend_throw_exception(spl_ce_BadMethodCallException, "Cannot call continue on a source that has not been stopped", 0);
		return;
	}

	g_source_continue(source_object->source);
	source_object->active = TRUE;
}
/* }}} */

ZEND_BEGIN_ARG_INFO(Source_elapsed_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto float \Glib\Source->elapsed()
         returns the total elapsed time from the last start/reset call
   */
PHP_METHOD(GlibSource, elapsed)
{
	glib_source_object *source_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "") == FAILURE) {
		return;
	}
	source_object = Z_GLIB_TIMER_P(getThis());

	RETURN_DOUBLE(g_source_elapsed(source_object->source, NULL));
}
/* }}} */

/* ----------------------------------------------------------------
    Glib\Source Object management
------------------------------------------------------------------*/

/* Custom Object Destruction - calls g_source_destroy() */
void glib_source_free_obj(zend_object *object)
{
	glib_source_object *intern = glib_source_fetch_object(object);

	if(!intern) {
		return;
	}
	if(intern->source) {
		g_source_destroy(intern->source);
	}
	intern->source = NULL;
	intern->active = FALSE;

	zend_object_std_dtor(&intern->std);
}

/* Custom object creation - calls g_source_new() */
static zend_object* glib_source_create_object(zend_class_entry *ce)
{
	glib_source_object *intern = NULL;

	intern = ecalloc(1, sizeof(glib_source_object) + zend_object_properties_size(ce));
	intern->source = g_source_new();
	intern->active = TRUE;

	zend_object_std_init(&(intern->std), ce);
	object_properties_init(&(intern->std), ce);
	intern->std.handlers = &glib_source_object_handlers;
	return &(intern->std);
}

/* ----------------------------------------------------------------
    Glib\Source Class Definition and Registration
------------------------------------------------------------------*/

static const zend_function_entry glib_source_methods[] = {
	PHP_ME(GlibSource, __construct, Source___construct_args, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(GlibSource, start, Source_start_args, ZEND_ACC_PUBLIC)
	PHP_ME(GlibSource, stop, Source_stop_args, ZEND_ACC_PUBLIC)
	PHP_ME(GlibSource, continue, Source_continue_args, ZEND_ACC_PUBLIC)
	PHP_ME(GlibSource, elapsed, Source_elapsed_args, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

PHP_MINIT_FUNCTION(glib_source)
{
	zend_class_entry ce;

	memcpy(&glib_source_object_handlers, zend_get_std_object_handlers(),
		sizeof(zend_object_handlers));
	glib_source_object_handlers.offset = XtOffsetOf(glib_source_object, std);
	// TODO: clone?
	glib_source_object_handlers.clone_obj = NULL;
	glib_source_object_handlers.free_obj = glib_source_free_obj;

	INIT_NS_CLASS_ENTRY(ce, GLIB_NAMESPACE, "Source", glib_source_methods);
	ce.create_object = glib_source_create_object;
	glib_ce_source = zend_register_internal_class(&ce);

	return SUCCESS;
}

