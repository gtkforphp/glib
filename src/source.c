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
zend_object_handlers glib_source_object_handlers;

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
	if (zend_parse_parameters_none_throw() == FAILURE) {
		return;
	}

	// we put the zval in the php_glib_source and shake it all up
	glib_source_object * source_object = Z_GLIB_SOURCE_P(getThis());
	source_object->source = g_source_new(&php_glib_source_funcs, sizeof(GPhpSource));
	source_object->source = g_source_ref(source_object->source);
	source_object->is_php_source = TRUE;

	GPhpSource *gsource = (GPhpSource *)source_object->source;

	// copy our zval into our internal struct, return with getContext
	ZVAL_COPY(&gsource->source_zval, getThis());
	zval_add_ref(&gsource->source_zval);
	zval_add_ref(&gsource->source_zval);
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Source_attach_args, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, context, Glib\\Main\\Context, 0)
ZEND_END_ARG_INFO()

/* {{{ proto void \Glib\Source->attach(Context $context)
        attaches a source to a main context
   */
PHP_METHOD(GlibSource, attach)
{
	zval *context_zval = NULL;
	glib_main_context_object *context_object;
	glib_source_object *source_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "O", &context_zval, glib_ce_main_context) == FAILURE) {
		return;
	}

	if(context_zval == NULL) {
		zend_throw_exception(spl_ce_InvalidArgumentException, "Invalid context sent", 0);
		return;
	}

	context_object = Z_GLIB_MAIN_CONTEXT_P(context_zval);
	source_object = Z_GLIB_SOURCE_P(getThis());
	GLIB_CHECK_INITIALIZED(source_object->source, Glib\\Source)
	
	if(g_source_is_destroyed(source_object->source)) {
		zend_throw_exception(spl_ce_RuntimeException, "Source has been destroyed", 0);
		return;
	}

	RETURN_LONG(g_source_attach(source_object->source, context_object->main_context));
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Source_destroy_args, IS_VOID, 0)
ZEND_END_ARG_INFO()

/* {{{ proto void \Glib\Source->destroy()
        removes a source from a main context and marks it as destroyed
   */
PHP_METHOD(GlibSource, destroy)
{
	glib_source_object *source_object;

	if (zend_parse_parameters_none_throw() == FAILURE) {
		return;
	}

	source_object = Z_GLIB_SOURCE_P(getThis());
	GLIB_CHECK_INITIALIZED(source_object->source, Glib\\Source)

	g_source_destroy(source_object->source);
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Source_isDestroyed_args, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

/* {{{ proto bool \Glib\Source->isDestroyed()
        removes a source from a main context and marks it as destroyed
   */
PHP_METHOD(GlibSource, isDestroyed)
{
	glib_source_object *source_object;

	if (zend_parse_parameters_none_throw() == FAILURE) {
		return;
	}

	source_object = Z_GLIB_SOURCE_P(getThis());
	GLIB_CHECK_INITIALIZED(source_object->source, Glib\\Source)

	RETURN_BOOL(g_source_is_destroyed(source_object->source));
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Source_setPriority_args, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, priority, IS_LONG, 0)
ZEND_END_ARG_INFO()

/* {{{ proto void \Glib\Source->setPriority(int priority)
        sets the priority of a source
   */
PHP_METHOD(GlibSource, setPriority)
{
	zend_long priority;
	gint set_priority;
	glib_source_object *source_object;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "l", &priority) == FAILURE) {
		return;
	}

	source_object = Z_GLIB_SOURCE_P(getThis());
	GLIB_CHECK_INITIALIZED(source_object->source, Glib\\Source)
	set_priority = priority;

	g_source_set_priority(source_object->source, priority);
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Source_getPriority_args, IS_LONG, 0)
ZEND_END_ARG_INFO()

/* {{{ proto int \Glib\Source->getPriority()
        sets the priority of a source
   */
PHP_METHOD(GlibSource, getPriority)
{
	glib_source_object *source_object;

	if (zend_parse_parameters_none_throw() == FAILURE) {
		return;
	}

	source_object = Z_GLIB_SOURCE_P(getThis());
	GLIB_CHECK_INITIALIZED(source_object->source, Glib\\Source)

	RETURN_LONG(g_source_get_priority(source_object->source));
}
/* }}} */

// somehow figure out how to wrap the existing sources  - gtimeout and friends
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Source_prepare_args, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Source_check_args, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

/* These arguments are optional and nullable which makes PHP 7 unhappy */
#if PHP_VERSION_ID < 70100
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Source_dispatch_args, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(0, args)
ZEND_END_ARG_INFO()
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Source_dispatch_args, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, callback, IS_CALLABLE, 1)
	ZEND_ARG_TYPE_INFO(0, args, IS_ARRAY, 1)
ZEND_END_ARG_INFO()
#endif

/* If you actually typehint null we can't define this in 7.0 */
#if PHP_VERSION_ID < 70100
ZEND_BEGIN_ARG_INFO(Source_finalize_args, ZEND_SEND_BY_VAL)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Source_finalize_args, IS_VOID, 0)
#endif
ZEND_END_ARG_INFO()

/* ----------------------------------------------------------------
    Glib\Source GSourceFuncs handlers
------------------------------------------------------------------*/

static void
glib_source_callback_helper(zval *retval, zval *source_zval, const char *name, zval *params, uint32_t param_count)
{
	zend_fcall_info fci;
	zend_fcall_info_cache fci_cache;
	zval caller;

	array_init(&caller);
	add_index_zval(&caller, 0, source_zval);
	add_index_string(&caller, 1, name);

	char * callback_error;
	if(FAILURE == zend_fcall_info_init(&caller, IS_CALLABLE_STRICT, &fci, &fci_cache, NULL, &callback_error))
	{
		zend_throw_exception_ex(spl_ce_BadMethodCallException, 0,
			"Could not call %s source handler, %s", name, callback_error);
		zval_dtor(&caller);
		return;
	}

	/* Handle arguments if necessary */
	fci.param_count = param_count;
	if(param_count > 0) {
		fci.params = params;
	}

	fci.retval = retval;
	if(FAILURE == zend_call_function(&fci, &fci_cache)) {
		zend_throw_exception_ex(spl_ce_BadFunctionCallException, 0,
			"Could not call %s source handler", name);
	}
	zval_dtor(&caller);
}

static gboolean
php_glib_source_prepare(GSource *source, gint *timeout)
{
	gboolean retval = FALSE;
	zend_long php_timeout = -1;
	zval php_retval;
	GPhpSource *glib_source = (GPhpSource*) source;

	glib_source_callback_helper(&php_retval, &glib_source->source_zval, "prepare", NULL, 0);

	/* Our return must be array [retval, timeout]
	   we can cast those values if they're not bool, long
	   but we must have that format ...
	   TODO: return struct instead? */
	if(Z_ISUNDEF(php_retval)
	    || Z_TYPE(php_retval) != IS_ARRAY
		|| zend_array_count(Z_ARRVAL(php_retval)) < 2
		|| zend_hash_index_exists(Z_ARRVAL(php_retval), 0) == FALSE
		|| zend_hash_index_exists(Z_ARRVAL(php_retval), 1) == FALSE) {
		zend_throw_exception(spl_ce_BadFunctionCallException,
			"Prepare must return an array with bool return at [0] and int timeout at [1]", 0);
		if(!Z_ISUNDEF(php_retval)) {
			zval_ptr_dtor(&php_retval);
		}
		return FALSE;
	}

	php_timeout = Z_LVAL_P(zend_hash_index_find(Z_ARRVAL(php_retval), 1));
	*timeout = php_timeout;
	if(Z_TYPE_P(zend_hash_index_find(Z_ARRVAL(php_retval), 0)) == IS_TRUE) {
		retval = TRUE;
	}
	zval_ptr_dtor(&php_retval);
	return retval;
}

static gboolean
php_glib_source_check(GSource *source)
{
	gboolean retval = FALSE;
	zval php_retval;
	GPhpSource *glib_source = (GPhpSource*)source;

	glib_source_callback_helper(&php_retval, &glib_source->source_zval, "check", NULL, 0);

	/* we are expecting a boolean return value
		return typehints will error on exception */
	if(Z_ISUNDEF(php_retval)) {
		return FALSE;
	}

	if(Z_TYPE(php_retval) == IS_TRUE) {
		retval = TRUE;
	}

	zval_ptr_dtor(&php_retval);
	return retval;
}

static gboolean
php_glib_source_dispatch(GSource *source, GSourceFunc callback, gpointer userdata)
{
	gboolean retval = FALSE;
	zval php_retval;
	GPhpSource *glib_source = (GPhpSource*)source;

	// TODO: make this work properly?
	// for now send nulls
	zval args[2];

	ZVAL_NULL(&args[0]);
	ZVAL_NULL(&args[1]);
	

	glib_source_callback_helper(&php_retval, &glib_source->source_zval, "dispatch", (zval *)args, 2);

	/* we are expecting a boolean return value
		return typehints will error on exception */
	if(Z_ISUNDEF(php_retval)) {
		return FALSE;
	}

	if(Z_TYPE(php_retval) == IS_TRUE) {
		retval = TRUE;
	}

	zval_ptr_dtor(&php_retval);
	return retval;
}

static void
php_glib_source_finalize(GSource *source)
{
	gboolean retval = FALSE;
	zval php_retval;
	GPhpSource *glib_source = (GPhpSource*)source;

	glib_source_callback_helper(&php_retval, &glib_source->source_zval, "finalize", NULL, 0);

	/* void is fine, just don't ptr_dtor if we don't have a zval */
	if(Z_ISUNDEF(php_retval)) {
		return;
	}

	zval_ptr_dtor(&php_retval);
}

GSourceFuncs php_glib_source_funcs = 
{
	php_glib_source_prepare,
	php_glib_source_check,
	php_glib_source_dispatch,
	php_glib_source_finalize
};

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

	GSource *source = (GSource *)intern->source;

	/* this will make finalize call, we MUST do this before freeing the source zval */
	if(intern->source != NULL) {
		g_source_destroy(source);
		g_source_unref(source);

		if(intern->is_php_source) {
			GPhpSource *psource = (GPhpSource *)intern->source;
			if(!Z_ISNULL(psource->source_zval) &&
				!Z_ISUNDEF(psource->source_zval)) {

				Z_TRY_DELREF_P(&psource->source_zval);
				ZVAL_UNDEF(&psource->source_zval);
			}
		}
	}

	zend_object_std_dtor(&intern->std);
}

/* Custom object creation - calls g_source_new() */
static zend_object* glib_source_create_object(zend_class_entry *ce)
{
	glib_source_object *intern = NULL;

	intern = ecalloc(1, sizeof(glib_source_object) + zend_object_properties_size(ce));

	intern->is_php_source = FALSE;
	intern->source = NULL;

	zend_object_std_init(&(intern->std), ce);
	object_properties_init(&(intern->std), ce);
	intern->std.handlers = &glib_source_object_handlers;
	return &(intern->std);
}

/* ----------------------------------------------------------------
    Glib\Source Interface Definition and Registration
------------------------------------------------------------------*/

static const zend_function_entry glib_source_methods[] = {
	PHP_ME(GlibSource, __construct, Source___construct_args, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(GlibSource, attach, Source_attach_args, ZEND_ACC_PUBLIC)
	PHP_ME(GlibSource, destroy, Source_destroy_args, ZEND_ACC_PUBLIC)
	PHP_ME(GlibSource, isDestroyed, Source_isDestroyed_args, ZEND_ACC_PUBLIC)
	PHP_ME(GlibSource, getPriority, Source_getPriority_args, ZEND_ACC_PUBLIC)
	PHP_ME(GlibSource, setPriority, Source_setPriority_args, ZEND_ACC_PUBLIC)
	PHP_ABSTRACT_ME(GlibSource, prepare, Source_prepare_args)
	PHP_ABSTRACT_ME(GlibSource, check, Source_check_args)
	PHP_ABSTRACT_ME(GlibSource, dispatch, Source_dispatch_args)
	PHP_ABSTRACT_ME(GlibSource, finalize, Source_finalize_args)
	ZEND_FE_END
};

PHP_MINIT_FUNCTION(glib_source)
{
	zend_class_entry ce;

	memcpy(&glib_source_object_handlers, zend_get_std_object_handlers(),
		sizeof(zend_object_handlers));
	glib_source_object_handlers.offset = XtOffsetOf(glib_source_object, std);
	glib_source_object_handlers.clone_obj = NULL;
	glib_source_object_handlers.free_obj = glib_source_free_obj;

	INIT_NS_CLASS_ENTRY(ce, GLIB_NAMESPACE, "Source", glib_source_methods);
	ce.create_object = glib_source_create_object;
	glib_ce_source = zend_register_internal_class(&ce);
	glib_ce_source->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;

	return SUCCESS;
}
