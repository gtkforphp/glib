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

#include <glib.h>

#include "php_glib.h"
#include "php_glib_internal.h"

zend_class_entry *glib_ce_source_timeout;

/* ----------------------------------------------------------------
    Glib\Source\Timeout class API
------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO(Timeout___construct_args, ZEND_SEND_BY_VAL)
    ZEND_ARG_TYPE_INFO(0, timeout, IS_LONG, 0)
ZEND_END_ARG_INFO()

/* {{{ proto void \Glib\Source->__construct()
        Creates a new source and implicitly calls start on it, so you don't have to call start
   */
PHP_METHOD(GlibSourceTimeout, __construct)
{
    guint interval;
    zend_long php_interval = -1;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "l", &php_interval) == FAILURE) {
		return;
	}

    interval = php_interval;

	glib_source_object * source_object = Z_GLIB_SOURCE_P(getThis());

    // get our GTimeoutSource created
    source_object->source = g_timeout_source_new(interval);
    // reallocate it to get enough room for our cache zval
    source_object->source = g_try_realloc(source_object->source, sizeof(GPhpTimeoutSource));
    source_object->source = g_source_ref((GSource *)source_object->source);
    
    GPhpTimeoutSource *psource = (GPhpTimeoutSource *)source_object->source;
    
    // copy our zval into our internal struct, return with getContext
	ZVAL_COPY(&psource->source_zval, getThis());
	zval_add_ref(&psource->source_zval);
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Timeout_prepare_args, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

/* {{{ proto int \Glib\Source\Timeout->prepare()
        this is actually a null callback so FUN
   */
PHP_METHOD(GlibSourceTimeout, prepare)
{
	glib_source_object *source_object;

	if (zend_parse_parameters_none_throw() == FAILURE) {
		return;
	}

	source_object = Z_GLIB_SOURCE_P(getThis());
    GLIB_CHECK_INITIALIZED(source_object->source, Glib\\Source\\Timeout)
    array_init(return_value);

    gboolean result = FALSE;
    gint source_timeout = -1;
    gboolean(* prepare) (GSource *source, gint *timeout);

    /* although this should never happen... */
    prepare = source_object->source->source_funcs->prepare;

	if(prepare) {
        result = (*prepare) (source_object->source, &source_timeout);
    }

    add_index_bool(return_value, 0, result);
    add_index_long(return_value, 1, source_timeout);
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Timeout_check_args, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

/* {{{ proto int \Glib\Source\Timeout->check()
        this is actually a null callback so FUN
   */
PHP_METHOD(GlibSourceTimeout, check)
{
	glib_source_object *source_object;

	if (zend_parse_parameters_none_throw() == FAILURE) {
		return;
	}

	source_object = Z_GLIB_SOURCE_P(getThis());
    GLIB_CHECK_INITIALIZED(source_object->source, Glib\\Source\\Timeout)

    gboolean result = FALSE;
    gboolean(* check) (GSource *source);

    /* although this should never happen... */
    check = source_object->source->source_funcs->check;

	if(check) {
        result = (*check) (source_object->source);
    }

    RETURN_BOOL(result);
}
/* }}} */

/* These arguments are optional and nullable which makes PHP 7 unhappy */
#if PHP_VERSION_ID < 70100
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Timeout_dispatch_args, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(0, args)
ZEND_END_ARG_INFO()
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Timeout_dispatch_args, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, callback, IS_CALLABLE, 1)
	ZEND_ARG_TYPE_INFO(0, args, IS_ARRAY, 1)
ZEND_END_ARG_INFO()
#endif

/* {{{ proto int \Glib\Source\Timeout->dispatch()
        this is actually a null callback so FUN
   */
PHP_METHOD(GlibSourceTimeout, dispatch)
{
	glib_source_object *source_object;
    zend_fcall_info fci;
    zend_fcall_info_cache fci_cache;
    zval *args;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "f!a!/", &fci, &fci_cache, &args) == FAILURE) {
		return;
	}

/*  how to use the stuff to do the call 
    zend_fcall_info_args(&fci, args);
    zval *retval;
    fci.retval = &retval;
    if(zend_call_function(&fci, &fci_cache) == SUCCESS && Z_TYPE(retval) != IS_UNDEF) {
        ZVAL_COPY_VALUE(return_value, &retval);
    }
    zend_fcall_info_args_clear(&fci, 1);
*/

	source_object = Z_GLIB_SOURCE_P(getThis());
    GLIB_CHECK_INITIALIZED(source_object->source, Glib\\Source\\Timeout)

    gboolean result = FALSE;
    gboolean (*dispatch) (GSource *, GSourceFunc, gpointer);

    dispatch = source_object->source->source_funcs->dispatch;

	if(dispatch) {
        php_printf("build a GSourceFunc from args sent\n");
        //result = (*dispatch) (source_object->source);
    }

    RETURN_BOOL(result);
}
/* }}} */

/* If you actually typehint null we can't define this in 7.0 */
#if PHP_VERSION_ID < 70100
ZEND_BEGIN_ARG_INFO(Timeout_finalize_args, ZEND_SEND_BY_VAL)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(Timeout_finalize_args, IS_VOID, 0)
#endif
ZEND_END_ARG_INFO()

/* {{{ proto int \Glib\Source\Timeout->finalize()
        this is actually a null callback so FUN
   */
PHP_METHOD(GlibSourceTimeout, finalize)
{
	glib_source_object *source_object;

	if (zend_parse_parameters_none_throw() == FAILURE) {
		return;
	}

	source_object = Z_GLIB_SOURCE_P(getThis());
    GLIB_CHECK_INITIALIZED(source_object->source, Glib\\Source\\Timeout)

    void (* finalize) (GSource *source);

    /* although this should never happen... */
    finalize = source_object->source->source_funcs->finalize;

	if(finalize) {
        (*finalize) (source_object->source);
    }
}
/* }}} */

/* ----------------------------------------------------------------
    Glib\Source Object management
------------------------------------------------------------------*/

/* Custom object creation - calls g_source_new() */
static zend_object* glib_source_timeout_create_object(zend_class_entry *ce)
{
	glib_source_object *intern = NULL;

	intern = ecalloc(1, sizeof(glib_source_object) + zend_object_properties_size(ce));

    intern->source = NULL;

	zend_object_std_init(&(intern->std), ce);
	object_properties_init(&(intern->std), ce);
	intern->std.handlers = &glib_source_object_handlers;
	return &(intern->std);
}

/* ----------------------------------------------------------------
    Glib\Source\Timeout Class Definition and Registration
------------------------------------------------------------------*/

static const zend_function_entry glib_source_timeout_methods[] = {
    PHP_ME(GlibSourceTimeout, __construct, Timeout___construct_args, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(GlibSourceTimeout, prepare, Timeout_prepare_args, ZEND_ACC_PUBLIC)
	PHP_ME(GlibSourceTimeout, dispatch, Timeout_dispatch_args, ZEND_ACC_PUBLIC)
	PHP_ME(GlibSourceTimeout, check, Timeout_check_args, ZEND_ACC_PUBLIC)
	PHP_ME(GlibSourceTimeout, finalize, Timeout_finalize_args, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

PHP_MINIT_FUNCTION(glib_source_timeout)
{
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, GLIB_NAMESPACE, ZEND_NS_NAME("Source", "Timeout"), glib_source_timeout_methods);
	ce.create_object = glib_source_timeout_create_object;
	glib_ce_source_timeout = zend_register_internal_class_ex(&ce, glib_ce_source);

	return SUCCESS;
}

