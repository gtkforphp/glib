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

/* $Id: glib_exception.c 10 2009-04-29 16:30:59Z auroraeosrose $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "zend_exceptions.h"
#include "php_glib.h"

zend_class_entry *glib_ce_exception;

/* {{{ exported function to take a gerror, throw an exception, and clear the error */
PHP_GLIB_API zend_bool php_glib_handle_gerror(GError **error TSRMLS_DC)
{
	zval *exception;

	if (error == NULL || *error == NULL) {
		return FALSE;
	}

	MAKE_STD_ZVAL(exception);
	object_init_ex(exception, glib_ce_exception);
	if ((*error)->message) {
		zend_update_property_string(glib_ce_exception, exception, "message", sizeof("message")-1, (char *)(*error)->message TSRMLS_CC);
	}
	zend_update_property_string(glib_ce_exception, exception, "domain", sizeof("domain")-1, (char *)g_quark_to_string((*error)->domain) TSRMLS_CC);
	zend_update_property_long(glib_ce_exception, exception, "code", sizeof("code")-1, (*error)->code TSRMLS_CC);

	zend_throw_exception_object(exception TSRMLS_CC);

	g_clear_error(error);

	return TRUE;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(glib_exception)
{
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, GLIB_NAMESPACE, "Exception", NULL);
	glib_ce_exception = zend_register_internal_class_ex(&ce, zend_exception_get_default(TSRMLS_C), "Exception" TSRMLS_CC);
	glib_ce_exception->ce_flags |= ZEND_ACC_FINAL;
	glib_ce_exception->constructor->common.fn_flags |= ZEND_ACC_PROTECTED;
	zend_declare_property_string(glib_ce_exception, "domain", sizeof("domain")-1, "", ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_string(glib_ce_exception, "message", sizeof("message")-1, "", ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_string(glib_ce_exception, "code", sizeof("code")-1, "", ZEND_ACC_PUBLIC TSRMLS_CC);

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
