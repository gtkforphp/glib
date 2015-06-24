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

/* $Id: glib_bookmarkfile.c 10 2009-04-29 16:30:59Z auroraeosrose $ */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_glib.h"

#if GLIB_CHECK_VERSION (2, 12, 0)
zend_class_entry *glib_ce_bookmarkfile;

/* for extended classes, make sure internal object exists properly */
static inline glib_bookmarkfile_object* glib_bookmarkfile_object_get(zval *zobj TSRMLS_DC)
{
	glib_bookmarkfile_object *pobj = zend_object_store_get_object(zobj TSRMLS_CC);
	if (pobj->bookmarkfile == NULL) {
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Internal object missing in %s class, you must call parent::__construct in extended classes", Z_OBJCE_P(zobj)->name);
	}
	return pobj;
}

/* {{{ glib_bookmarkfile_free_storage
       calls free on the bookmarkfile */
void glib_bookmarkfile_free_storage(glib_bookmarkfile_object *intern TSRMLS_DC)
{
	if(intern->bookmarkfile) {
		g_bookmark_file_free (intern->bookmarkfile);
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

/* {{{ glib_bookmarkfile_object_new
       sets up the glib_bookmarkfile_object struct and other internal class junk */
zend_object_value glib_bookmarkfile_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	glib_bookmarkfile_object *object;
	zval *tmp;

	object = emalloc(sizeof(glib_bookmarkfile_object));
	object->std.ce = ce;
	object->std.guards = NULL;
	object->bookmarkfile = NULL;

	ALLOC_HASHTABLE(object->std.properties);
	zend_hash_init(object->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
	zend_hash_copy(object->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

	retval.handle = zend_objects_store_put(object, (zend_objects_store_dtor_t)zend_objects_destroy_object, (zend_objects_free_object_storage_t) glib_bookmarkfile_free_storage, NULL TSRMLS_CC);
	retval.handlers = zend_get_std_object_handlers();
	return retval;
}
/* }}} */

/* {{{ proto void \Glib\Bookmarkfile->__construct()
        Creates a new empty bookmarkfile
   */
PHP_METHOD(Glib_Bookmarkfile, __construct)
{
	glib_bookmarkfile_object *bookmark_object = (glib_bookmarkfile_object *)zend_objects_get_address(getThis() TSRMLS_CC);

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	bookmark_object->bookmarkfile = g_bookmark_file_new();
}
/* }}} */

/* {{{ proto string \Glib\Bookmarkfile->__toString()
        Outputs the current contents of the bookmarkfile as xml to a string
   */
PHP_METHOD(Glib_Bookmarkfile, __toString)
{
	gchar *buffer;
	gsize length;
	GError **error = NULL;

	glib_bookmarkfile_object *bookmark_object = (glib_bookmarkfile_object *)glib_bookmarkfile_object_get(getThis() TSRMLS_CC);

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	buffer = g_bookmark_file_to_data(bookmark_object->bookmarkfile, &length, error);

	if (php_glib_handle_gerror(error TSRMLS_CC)) {
		return;
	}
	RETURN_STRINGL(buffer, length, 1);
}
/* }}} */

/* {{{ glib_bookmarkfile_methods[] */
const zend_function_entry glib_bookmarkfile_methods[] = {
	PHP_ME(Glib_Bookmarkfile, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Glib_Bookmarkfile, __toString, NULL, ZEND_ACC_PUBLIC)
	//PHP_ME(Glib_Bookmarkfile, hasItem, NULL, ZEND_ACC_PUBLIC)
	//PHP_ME(Glib_Bookmarkfile, hasGroup, NULL, ZEND_ACC_PUBLIC)
	//PHP_ME(Glib_Bookmarkfile, hasApplication, NULL, ZEND_ACC_PUBLIC)
	//PHP_ME(Glib_Bookmarkfile, count, NULL, ZEND_ACC_PUBLIC)
	//PHP_ME(Glib_Bookmarkfile, getUris, NULL, ZEND_ACC_PUBLIC)
	//PHP_ME(Glib_Bookmarkfile, getTitle, NULL, ZEND_ACC_PUBLIC)
	//PHP_ME(Glib_Bookmarkfile, getDescription, NULL, ZEND_ACC_PUBLIC)
	//PHP_ME(Glib_Bookmarkfile, getMimeType, NULL, ZEND_ACC_PUBLIC)
	//PHP_ME(Glib_Bookmarkfile, getIsPrivate, NULL, ZEND_ACC_PUBLIC)
	//PHP_ME(Glib_Bookmarkfile, getIcon, NULL, ZEND_ACC_PUBLIC)
	//PHP_ME(Glib_Bookmarkfile, getAdded, NULL, ZEND_ACC_PUBLIC)
	//PHP_ME(Glib_Bookmarkfile, getModified, NULL, ZEND_ACC_PUBLIC)
	//PHP_ME(Glib_Bookmarkfile, getVisited, NULL, ZEND_ACC_PUBLIC)
	//PHP_ME(Glib_Bookmarkfile, getGroups, NULL, ZEND_ACC_PUBLIC)
	//PHP_ME(Glib_Bookmarkfile, getApplications, NULL, ZEND_ACC_PUBLIC)
	//PHP_ME(Glib_Bookmarkfile, getAppInfo, NULL, ZEND_ACC_PUBLIC)
	//PHP_ME(Glib_Bookmarkfile, setTitle, NULL, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};
/* }}} */

#endif

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(glib_bookmarkfile)
{
#if GLIB_CHECK_VERSION (2, 12, 0)
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, GLIB_NAMESPACE, "Bookmarkfile", glib_bookmarkfile_methods);
	glib_ce_bookmarkfile = zend_register_internal_class(&ce TSRMLS_CC);
	glib_ce_bookmarkfile->create_object  = glib_bookmarkfile_object_new;
#endif
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
