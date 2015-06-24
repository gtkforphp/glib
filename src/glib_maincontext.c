/*
  +----------------------------------------------------------------------+
  | Glib PHP Extension                                                   |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2009 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Elizabeth Smith <auroraeosrose@php.net>                      |
  +----------------------------------------------------------------------+
*/

/* $Id: glib_maincontext.c 15 2009-05-01 12:15:36Z auroraeosrose $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_glib.h"

zend_class_entry *glib_ce_maincontext;

ZEND_BEGIN_ARG_INFO_EX(Glib_Main_Context_iteration_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
	ZEND_ARG_INFO(0, may_block)
ZEND_END_ARG_INFO()

/* for extended classes, make sure internal object exists properly */
static inline glib_maincontext_object* glib_maincontext_object_get(zval *zobj TSRMLS_DC)
{
	glib_maincontext_object *pobj = zend_object_store_get_object(zobj TSRMLS_CC);
	if (pobj->maincontext == NULL) {
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Internal object missing in %s class, you must call parent::__construct in extended classes", Z_OBJCE_P(zobj)->name);
	}
	return pobj;
}

/* {{{ glib_maincontext_free_storage
      unrefs the main context */
void glib_maincontext_free_storage(glib_maincontext_object *intern TSRMLS_DC)
{
	if(intern->maincontext) {
		g_main_context_unref(intern->maincontext);
	}

	if (intern->std.guards) {
		zend_hash_destroy(intern->std.guards);
		FREE_HASHTABLE(intern->std.guards);		
	}
	
	if (intern->std.properties) {
		zend_hash_destroy(intern->std.properties);
		FREE_HASHTABLE(intern->std.properties);
	}
	efree(intern);
}

/* }}} */

/* {{{ glib_maincontext_object_new
       sets up the glib_maincontext_object struct and other internal class junk */
zend_object_value glib_maincontext_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	glib_maincontext_object *object;
	zval *tmp;

	object = emalloc(sizeof(glib_maincontext_object));
	object->std.ce = ce;
	object->std.guards = NULL;
	object->maincontext = NULL;

	ALLOC_HASHTABLE(object->std.properties);
	zend_hash_init(object->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
	zend_hash_copy(object->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

	retval.handle = zend_objects_store_put(object, (zend_objects_store_dtor_t)zend_objects_destroy_object, (zend_objects_free_object_storage_t) glib_maincontext_free_storage, NULL TSRMLS_CC);
	retval.handlers = zend_get_std_object_handlers();
	return retval;
}
/* }}} */

/* {{{ proto void \Glib\Main\Context->__construct()
        Creates a new main context object, holding a list of sources to be handled in a main loop
		generally you will want to call \Glib\Main\Context::getDefault(); instead
   */
PHP_METHOD(Glib_Main_Context, __construct)
{
	glib_maincontext_object *context_object = (glib_maincontext_object *)zend_objects_get_address(getThis() TSRMLS_CC);

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	context_object->maincontext = g_main_context_new();
	g_main_context_ref(context_object->maincontext);
}
/* }}} */

/* {{{ proto \Glib\Main\Context object \Glib\Main\Context::getDefault();
        Returns the default main context. This is the main context used for
		main loop functions when a main loop is not explicitly specified.
   */
PHP_METHOD(Glib_Main_Context, getDefault)
{
	glib_maincontext_object *context_object;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	object_init_ex(return_value, glib_ce_maincontext);
	context_object = (glib_maincontext_object *)zend_objects_get_address(return_value TSRMLS_CC);
	context_object->maincontext = g_main_context_new();
	g_main_context_ref(context_object->maincontext);
}
/* }}} */

/* {{{ proto bool \Glib\Main\Context->iteration([boolean may_block])
		Runs a single iteration for the given main loop. This involves checking to see if any event sources
		are ready to be processed, then if no events sources are ready and may_block is TRUE, waiting for a
		source to become ready, then dispatching the highest priority events sources that are ready. Otherwise,
		if may_block is FALSE sources are not waited to become ready, only those highest priority events sources
		will be dispatched (if any), that are ready at this given moment without further waiting.
   */
PHP_METHOD(Glib_Main_Context, iteration)
{
	zend_bool may_block = FALSE;
	glib_maincontext_object *context_object = (glib_maincontext_object *)glib_maincontext_object_get(getThis() TSRMLS_CC);

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|b", &may_block) == FAILURE) {
		return;
	}

	RETURN_BOOL(g_main_context_iteration(context_object->maincontext, may_block));
}
/* }}} */

/* {{{ proto bool \Glib\Main\Context->pending()
		Checks if any sources have pending events for the given context.
   */
PHP_METHOD(Glib_Main_Context, pending)
{
	glib_maincontext_object *context_object = (glib_maincontext_object *)glib_maincontext_object_get(getThis() TSRMLS_CC);

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	RETURN_BOOL(g_main_context_pending(context_object->maincontext));
}
/* }}} */

/* {{{ proto void \Glib\Main\Context->wakeup()
		If context is currently waiting in a poll(), interrupt the poll(), and continue the iteration process.
   */
PHP_METHOD(Glib_Main_Context, wakeup)
{
	glib_maincontext_object *context_object = (glib_maincontext_object *)glib_maincontext_object_get(getThis() TSRMLS_CC);

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	g_main_context_wakeup(context_object->maincontext);
}
/* }}} */

/* {{{ proto array(boolean, int) \Glib\Main\Context->prepare()
		Checks if any sources have pending events for the given context.
		Returns an array of status (true if some source is ready to be dispatched prior to polling)
		and integer priority (priority of highest priority source already ready)
   */
PHP_METHOD(Glib_Main_Context, prepare)
{
	gint priority;
	gboolean status;
	glib_maincontext_object *context_object = (glib_maincontext_object *)glib_maincontext_object_get(getThis() TSRMLS_CC);

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	status = g_main_context_prepare(context_object->maincontext, &priority);
	array_init(return_value);
	add_next_index_bool(return_value, status);
	add_next_index_long(return_value, priority);
}
/* }}} */

/* {{{ proto void \Glib\Main\Context->dispatch()
		Dispatches all pending sources
   */
PHP_METHOD(Glib_Main_Context, dispatch)
{
	glib_maincontext_object *context_object = (glib_maincontext_object *)glib_maincontext_object_get(getThis() TSRMLS_CC);

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	g_main_context_dispatch(context_object->maincontext);
}
/* }}} */

/* {{{ glib_maincontext_methods[] */
const zend_function_entry glib_maincontext_methods[] = {
	PHP_ME(Glib_Main_Context, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Glib_Main_Context, getDefault, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glib_Main_Context, iteration, Glib_Main_Context_iteration_args, ZEND_ACC_PUBLIC)
	PHP_ME(Glib_Main_Context, pending, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Glib_Main_Context, wakeup, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Glib_Main_Context, prepare, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Glib_Main_Context, dispatch, NULL, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(glib_maincontext)
{
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, GLIB_NAMESPACE, ZEND_NS_NAME("Main", "Context"), glib_maincontext_methods);
	glib_ce_maincontext = zend_register_internal_class(&ce TSRMLS_CC);
	glib_ce_maincontext->create_object  = glib_maincontext_object_new;

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
