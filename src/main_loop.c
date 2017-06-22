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

zend_class_entry *ce_glib_main_loop;
static zend_object_handlers glib_main_loop_object_handlers;

typedef struct _glib_main_loop_object {
	GMainLoop 	*main_loop;
	zval 		context_zval;
	zend_object 	std;
} glib_main_loop_object;

static inline glib_main_loop_object *glib_main_loop_fetch_object(zend_object *object)
{
	return (glib_main_loop_object *) ((char*)(object) - XtOffsetOf(glib_main_loop_object, std));
}
#define Z_GLIB_MAIN_LOOP_P(zv) glib_main_loop_fetch_object(Z_OBJ_P(zv))


/* ----------------------------------------------------------------
    Glib\Main\Loop class API
------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO(Loop___construct_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, context, Glib\\Main\\Context, 0)
	ZEND_ARG_TYPE_INFO(0, is_running, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

/* {{{ proto void \Glib\Main\Loop->__construct(Context $context, bool $is_running)
        Creates a new main loop inside the context that is sent
   */
PHP_METHOD(GlibMainLoop, __construct)
{
	zval *context_zval = NULL;
	zend_bool is_running;
	glib_main_context_object *context_object;
	glib_main_loop_object *loop_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "Ob", &context_zval, glib_ce_main_context, &is_running) == FAILURE) {
		return;
	}
	
	if(context_zval == NULL) {
		zend_throw_exception(spl_ce_InvalidArgumentException, "Invalid context sent", 0);
		return;
	}
	
	context_object = Z_GLIB_MAIN_CONTEXT_P(context_zval);
	loop_object = Z_GLIB_MAIN_LOOP_P(getThis());

	loop_object->main_loop = g_main_loop_new(context_object->main_context, is_running);
	loop_object->main_loop = g_main_loop_ref(loop_object->main_loop);
	// add a ref to our context too
	context_object->main_context = g_main_context_ref(context_object->main_context);

	// copy our zval into our internal struct, return with getContext
	ZVAL_COPY(&loop_object->context_zval, context_zval);
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Loop_run_args, IS_VOID, 0)
ZEND_END_ARG_INFO()

/* {{{ proto bool \Glib\Main\Loop->run()
	runs a main loop until quit is called on the loop
  */ 
PHP_METHOD(GlibMainLoop, run)
{
	glib_main_loop_object *loop_object;

	if (zend_parse_parameters_none_throw() == FAILURE) {
		return;
	}

	loop_object = Z_GLIB_MAIN_LOOP_P(getThis());
	GLIB_CHECK_INITIALIZED(loop_object->main_loop, Glib\\Main\\Loop)

	g_main_loop_run(loop_object->main_loop);
}

/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Loop_quit_args, IS_VOID, 0)
ZEND_END_ARG_INFO()

/* {{{ proto bool \Glib\Main\Loop->quit()
	stops a main loop from running
  */ 
PHP_METHOD(GlibMainLoop, quit)
{
	glib_main_loop_object *loop_object;

	if (zend_parse_parameters_none_throw() == FAILURE) {
		return;
	}

	loop_object = Z_GLIB_MAIN_LOOP_P(getThis());
	GLIB_CHECK_INITIALIZED(loop_object->main_loop, Glib\\Main\\Loop)

	g_main_loop_quit(loop_object->main_loop);
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Loop_isRunning_args, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

/* {{{ proto void \Glib\Main\Loop->isRunning()
		check to see if a loop is running
   */
PHP_METHOD(GlibMainLoop, isRunning)
{
	glib_main_loop_object *loop_object;

	if (zend_parse_parameters_none_throw() == FAILURE) {
		return;
	}

	loop_object = Z_GLIB_MAIN_LOOP_P(getThis());
	GLIB_CHECK_INITIALIZED(loop_object->main_loop, Glib\\Main\\Loop)

	RETURN_BOOL(g_main_loop_is_running(loop_object->main_loop));
}
/* }}} */


ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(Loop_getContext_args, "Glib\\Main\\Context", 0)
ZEND_END_ARG_INFO()

/* {{{ proto \Glib\Main\Context object \Glib\Main\Loop->getContext();
        Returns the context used when the loop was created
   */
PHP_METHOD(GlibMainLoop, getContext)
{
	glib_main_loop_object *loop_object;
	glib_main_context_object *context_object;
	
	if (zend_parse_parameters_none_throw() == FAILURE) {
		return;
	}

	loop_object = Z_GLIB_MAIN_LOOP_P(getThis());
	GLIB_CHECK_INITIALIZED(loop_object->main_loop, Glib\\Main\\Loop)

	if(!Z_ISNULL(loop_object->context_zval) &&
	   !Z_ISUNDEF(loop_object->context_zval) &&
            Z_REFCOUNT(loop_object->context_zval) > 0) {

		context_object = Z_GLIB_MAIN_CONTEXT_P(&loop_object->context_zval);
		if(g_main_loop_get_context(loop_object->main_loop) == context_object->main_context) {
			zval_ptr_dtor(return_value);
			ZVAL_COPY(return_value, &loop_object->context_zval);
			return;
		}
	}

	object_init_ex(return_value, glib_ce_main_context);
	context_object = Z_GLIB_MAIN_CONTEXT_P(return_value);
	context_object->main_context = g_main_loop_get_context(loop_object->main_loop);
	context_object->main_context = g_main_context_ref(context_object->main_context);

	// copy our zval into our internal struct for with getContext
	ZVAL_COPY(&loop_object->context_zval, return_value);
}
/* }}} */

/* ----------------------------------------------------------------
    Glib\Main\Loop Object management
------------------------------------------------------------------*/

/* Custom Object Destruction - unrefs our context */
void glib_main_loop_free_obj(zend_object *object)
{
	glib_main_loop_object *intern = glib_main_loop_fetch_object(object);

	if(!intern) {
		return;
	}

	if(!Z_ISNULL(intern->context_zval) &&
		!Z_ISUNDEF(intern->context_zval)) {

		glib_main_context_object *context_object = Z_GLIB_MAIN_CONTEXT_P(&intern->context_zval);
		g_main_context_unref(context_object->main_context);

		Z_TRY_DELREF_P(&intern->context_zval);
		ZVAL_UNDEF(&intern->context_zval);
	}
	if(intern->main_loop) {
		g_main_loop_unref(intern->main_loop);
	}
	intern->main_loop = NULL;

	zend_object_std_dtor(&intern->std);
}

/* Custom object creation - doesn't actually create this */
static zend_object* glib_main_loop_create_object(zend_class_entry *ce)
{
	glib_main_loop_object *intern = NULL;

	intern = ecalloc(1, sizeof(glib_main_loop_object) + zend_object_properties_size(ce));
	ZVAL_UNDEF(&intern->context_zval);
	intern->main_loop = NULL;

	zend_object_std_init(&(intern->std), ce);
	object_properties_init(&(intern->std), ce);
	intern->std.handlers = &glib_main_loop_object_handlers;
	return &(intern->std);
}

/* ----------------------------------------------------------------
    Glib\Main\Loop Class Definition and Registration
------------------------------------------------------------------*/

static const zend_function_entry glib_main_loop_methods[] = {
	PHP_ME(GlibMainLoop, __construct, Loop___construct_args, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(GlibMainLoop, run, Loop_run_args, ZEND_ACC_PUBLIC)
	PHP_ME(GlibMainLoop, quit, Loop_quit_args, ZEND_ACC_PUBLIC)
	PHP_ME(GlibMainLoop, isRunning, Loop_isRunning_args, ZEND_ACC_PUBLIC)
	PHP_ME(GlibMainLoop, getContext, Loop_getContext_args, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

PHP_MINIT_FUNCTION(glib_main_loop)
{
	zend_class_entry ce;

	memcpy(&glib_main_loop_object_handlers, zend_get_std_object_handlers(),
		sizeof(zend_object_handlers));
	glib_main_loop_object_handlers.offset = XtOffsetOf(glib_main_loop_object, std);
	glib_main_loop_object_handlers.clone_obj = NULL;
	glib_main_loop_object_handlers.free_obj = glib_main_loop_free_obj;

	INIT_NS_CLASS_ENTRY(ce, GLIB_NAMESPACE, ZEND_NS_NAME("Main", "Loop"), glib_main_loop_methods);
	ce.create_object = glib_main_loop_create_object;
	ce_glib_main_loop = zend_register_internal_class(&ce);

	return SUCCESS;
}

