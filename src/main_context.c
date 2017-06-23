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

zend_class_entry *glib_ce_main_context;
static zend_object_handlers glib_main_context_object_handlers;
static zend_object* glib_main_context_get_default_object(zend_class_entry *ce, zend_bool get_default);

/* ----------------------------------------------------------------
    Glib\Main\Context class API
------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO(Context___construct_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto void \Glib\Main\Context->__construct()
        Creates a new main context object, holding a list of sources to be handled in a main loop
		generally you will want to call \Glib\Main\Context::getDefault(); instead
   */
PHP_METHOD(GlibMainContext, __construct)
{
	if (zend_parse_parameters_none_throw() == FAILURE) {
		return;
	}
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Context_iteration_args, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, may_block, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

/* {{{ proto bool \Glib\Main\Context->iteration(boolean may_block)
		Runs a single iteration for the given main loop. This involves checking to see if any event sources
		are ready to be processed, then if no events sources are ready and may_block is TRUE, waiting for a
		source to become ready, then dispatching the highest priority events sources that are ready. Otherwise,
		if may_block is FALSE sources are not waited to become ready, only those highest priority events sources
		will be dispatched (if any), that are ready at this given moment without further waiting.
  */ 
PHP_METHOD(GlibMainContext, iteration)
{
	glib_main_context_object *context_object;
	zend_bool may_block = FALSE;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "b", &may_block) == FAILURE) {
		return;
	}

	context_object = Z_GLIB_MAIN_CONTEXT_P(getThis());

	RETURN_BOOL(g_main_context_iteration(context_object->main_context, may_block));
}

/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Context_pending_args, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

/* {{{ proto bool \Glib\Main\Context->pending()
		Checks if any sources have pending events for the given context.
 */ 
PHP_METHOD(GlibMainContext, pending)
{
	glib_main_context_object *context_object;

	if (zend_parse_parameters_none_throw() == FAILURE) {
		return;
	}

	context_object = Z_GLIB_MAIN_CONTEXT_P(getThis());

	RETURN_BOOL(g_main_context_pending(context_object->main_context));
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Context_wakeup_args, IS_VOID, 0)
ZEND_END_ARG_INFO()

/* {{{ proto void \Glib\Main\Context->wakeup()
		If context is currently waiting in a poll(), interrupt the poll(), and continue the iteration process.
   */
PHP_METHOD(GlibMainContext, wakeup)
{
	glib_main_context_object *context_object;

	if (zend_parse_parameters_none_throw() == FAILURE) {
		return;
	}

	context_object = Z_GLIB_MAIN_CONTEXT_P(getThis());

	g_main_context_wakeup(context_object->main_context);
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Context_isOwner_args, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

/* {{{ proto void \Glib\Main\Context->isOwner()
		does the thread hold recursive ownership of this context
   */
PHP_METHOD(GlibMainContext, isOwner)
{
	glib_main_context_object *context_object;

	if (zend_parse_parameters_none_throw() == FAILURE) {
		return;
	}

	context_object = Z_GLIB_MAIN_CONTEXT_P(getThis());

	RETURN_BOOL(g_main_context_is_owner(context_object->main_context));
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Context_prepare_args, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

/* {{{ proto array(boolean, int) \Glib\Main\Context->prepare()
		Checks if any sources have pending events for the given context.
		Returns an array of status (true if some source is ready to be dispatched prior to polling)
		and integer priority (priority of highest priority source already ready)
  */ 
PHP_METHOD(GlibMainContext, prepare)
{
	gint priority;
	gboolean status;
	gboolean acquire;
	glib_main_context_object *context_object;

	if (zend_parse_parameters_none_throw() == FAILURE) {
		return;
	}

	context_object = Z_GLIB_MAIN_CONTEXT_P(getThis());
	
	/* we must aquire first */
	acquire = g_main_context_acquire(context_object->main_context);

	if(!acquire) {
		zend_throw_exception(spl_ce_RuntimeException, "Could not acquire the specified context", 0);
		return;
	}

	status = g_main_context_prepare(context_object->main_context, &priority);

	array_init(return_value);
	add_next_index_bool(return_value, status);
	add_next_index_long(return_value, priority);
	
	g_main_context_release(context_object->main_context);
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Context_dispatch_args, IS_VOID, 0)
ZEND_END_ARG_INFO()

/* {{{ proto void \Glib\Main\Context->dispatch()
		Dispatches all pending sources
   */
PHP_METHOD(GlibMainContext, dispatch)
{
	glib_main_context_object *context_object;
	gboolean acquire;

	if (zend_parse_parameters_none_throw() == FAILURE) {
		return;
	}

	context_object = Z_GLIB_MAIN_CONTEXT_P(getThis());
	
	/* we must aquire first */
	acquire = g_main_context_acquire(context_object->main_context);

	if(!acquire) {
		zend_throw_exception(spl_ce_RuntimeException, "Could not aquire the specified context", 0);
		return;
	}

	g_main_context_dispatch(context_object->main_context);
	g_main_context_release(context_object->main_context);
}
/* }}} */


ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(Context_getDefault_args, "Glib\\Main\\Context", 0)
ZEND_END_ARG_INFO()

/* {{{ proto \Glib\Main\Context object \Glib\Main\Context::getDefault();
        Returns the default main context. This is the main context used for
		main loop functions when a main loop is not explicitly specified.
   */
PHP_METHOD(GlibMainContext, getDefault)
{
	if (zend_parse_parameters_none_throw() == FAILURE) {
		return;
	}

	ZVAL_OBJ(return_value, glib_main_context_get_default_object(glib_ce_main_context, TRUE));
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(Context_getThreadDefault_args, "Glib\\Main\\Context", 0)
ZEND_END_ARG_INFO()

/* {{{ proto \Glib\Main\Context object \Glib\Main\Context::getThreadDefault();
        Returns the default main context. This is the main context used for
		main loop functions when a main loop is not explicitly specified.
   */
PHP_METHOD(GlibMainContext, getThreadDefault)
{
	if (zend_parse_parameters_none_throw() == FAILURE) {
		return;
	}

	ZVAL_OBJ(return_value, glib_main_context_get_default_object(glib_ce_main_context, FALSE));
}

/* }}} */

/* ----------------------------------------------------------------
    Glib\Main\Context Object management
------------------------------------------------------------------*/

/* Custom Object Destruction - unrefs our context */
void glib_main_context_free_obj(zend_object *object)
{
	glib_main_context_object *intern = glib_main_context_fetch_object(object);

	if(!intern) {
		return;
	}
	if(intern->main_context) {
		g_main_context_unref(intern->main_context);
	}
	intern->main_context = NULL;

	zend_object_std_dtor(&intern->std);
}

/* Custom object creation - calls g_main_context_new and ref */
static zend_object* glib_main_context_create_object(zend_class_entry *ce)
{
	glib_main_context_object *intern = NULL;

	intern = ecalloc(1, sizeof(glib_main_context_object) + zend_object_properties_size(ce));
	intern->main_context = g_main_context_new();
	intern->main_context = g_main_context_ref(intern->main_context);

	zend_object_std_init(&(intern->std), ce);
	object_properties_init(&(intern->std), ce);
	intern->std.handlers = &glib_main_context_object_handlers;
	return &(intern->std);
}

/* Custom object creation - for our specialty getDefault and getDefaultThread */
static zend_object* glib_main_context_get_default_object(zend_class_entry *ce, zend_bool get_default)
{
	glib_main_context_object *intern = NULL;

	intern = ecalloc(1, sizeof(glib_main_context_object) + zend_object_properties_size(ce));

	if(get_default) {
		intern->main_context = g_main_context_default();
		intern->main_context = g_main_context_ref(intern->main_context);
	} else {
		intern->main_context = g_main_context_ref_thread_default();
	}
	
	zend_object_std_init(&(intern->std), ce);
	object_properties_init(&(intern->std), ce);
	intern->std.handlers = &glib_main_context_object_handlers;
	return &(intern->std);
}

/* ----------------------------------------------------------------
    Glib\MainContext Class Definition and Registration
------------------------------------------------------------------*/

static const zend_function_entry glib_main_context_methods[] = {
	PHP_ME(GlibMainContext, __construct, Context___construct_args, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(GlibMainContext, iteration, Context_iteration_args, ZEND_ACC_PUBLIC)
	PHP_ME(GlibMainContext, pending, Context_pending_args, ZEND_ACC_PUBLIC)
	PHP_ME(GlibMainContext, wakeup, Context_wakeup_args, ZEND_ACC_PUBLIC)
	PHP_ME(GlibMainContext, isOwner, Context_isOwner_args, ZEND_ACC_PUBLIC)
	PHP_ME(GlibMainContext, prepare, Context_prepare_args, ZEND_ACC_PUBLIC)
	PHP_ME(GlibMainContext, dispatch, Context_dispatch_args, ZEND_ACC_PUBLIC)
	PHP_ME(GlibMainContext, getDefault, Context_getDefault_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(GlibMainContext, getThreadDefault, Context_getThreadDefault_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

PHP_MINIT_FUNCTION(glib_main_context)
{
	zend_class_entry ce;

	memcpy(&glib_main_context_object_handlers, zend_get_std_object_handlers(),
		sizeof(zend_object_handlers));
	glib_main_context_object_handlers.offset = XtOffsetOf(glib_main_context_object, std);
	glib_main_context_object_handlers.clone_obj = NULL;
	glib_main_context_object_handlers.free_obj = glib_main_context_free_obj;

	INIT_NS_CLASS_ENTRY(ce, GLIB_NAMESPACE, ZEND_NS_NAME("Main", "Context"), glib_main_context_methods);
	ce.create_object = glib_main_context_create_object;
	glib_ce_main_context = zend_register_internal_class(&ce);

	return SUCCESS;
}

