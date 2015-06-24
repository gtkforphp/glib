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

/* $Id: glib_source.c 24 2009-05-14 19:45:06Z auroraeosrose $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_glib.h"

zend_class_entry *glib_ce_source;

/* for extended classes, make sure internal object exists properly */
static inline glib_source_object* glib_source_object_get(zval *zobj TSRMLS_DC)
{
	glib_source_object *pobj = zend_object_store_get_object(zobj TSRMLS_CC);
	if (pobj->source == NULL) {
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Internal object missing in %s class, you must call parent::__construct in extended classes", Z_OBJCE_P(zobj)->name);
	}
	return pobj;
}

/* {{{ glib_source_free_storage
      unrefs the source */
void glib_source_free_storage(glib_source_object *intern TSRMLS_DC)
{
	if(intern->source) {
		g_source_unref(intern->source);
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

/* {{{ glib_source_object_new
       sets up the glib_source_object struct and other internal class junk */
zend_object_value glib_source_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	glib_source_object *object;
	zval *tmp;

	object = emalloc(sizeof(glib_source_object));
	object->std.ce = ce;
	object->std.guards = NULL;
	object->source = NULL;

	ALLOC_HASHTABLE(object->std.properties);
	zend_hash_init(object->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
	zend_hash_copy(object->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

	retval.handle = zend_objects_store_put(object, (zend_objects_store_dtor_t)zend_objects_destroy_object, (zend_objects_free_object_storage_t) glib_source_free_storage, NULL TSRMLS_CC);
	retval.handlers = zend_get_std_object_handlers();
	return retval;
}
/* }}} */

/* {{{ proto void \Glib\Source->__construct()
        Creates a new main context object, holding a list of sources to be handled in a main loop
		generally you will want to call \Glib\Main\Context::getDefault(); instead
   */
PHP_METHOD(Glib_Source, __construct)
{
	glib_maincontext_object *context_object = (glib_maincontext_object *)zend_objects_get_address(getThis() TSRMLS_CC);

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	context_object->maincontext = g_main_context_new();
	g_main_context_ref(context_object->maincontext);
}
/* }}} */

/* {{{ glib_source_methods[] */
const zend_function_entry glib_source_methods[] = {
	PHP_ME(Glib_Source, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	//PHP_ME(Glib_Source, getDefault, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	//PHP_ME(Glib_Source, iteration, Glib_Main_Context_iteration_args, ZEND_ACC_PUBLIC)
	//PHP_ME(Glib_Source, pending, NULL, ZEND_ACC_PUBLIC)
	//PHP_ME(Glib_Source, wakeup, NULL, ZEND_ACC_PUBLIC)
	//PHP_ME(Glib_Source, prepare, NULL, ZEND_ACC_PUBLIC)
	//PHP_ME(Glib_Source, dispatch, NULL, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(glib_source)
{
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, GLIB_NAMESPACE, "Source", glib_source_methods);
	glib_ce_source = zend_register_internal_class(&ce TSRMLS_CC);
	glib_ce_source->create_object  = glib_source_object_new;
	glib_ce_source->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;

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
