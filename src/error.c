/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2012 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Elizabeth M Smith <auroraeosrose@php.net>                    |
  +----------------------------------------------------------------------+
*/

#include "php_glib.h"

zend_class_entry *ce_glib_exception;

/* ----------------------------------------------------------------
    G\Exception C API
------------------------------------------------------------------*/

/* {{{ exported function to take a gerror, throw an exception, and clear the error */
PHP_GLIB_API zend_bool php_glib_handle_gerror(GError **error TSRMLS_DC)
{
	zval *exception;

	if (error == NULL || *error == NULL) {
		return FALSE;
	}

	MAKE_STD_ZVAL(exception);
	object_init_ex(exception, ce_glib_exception);
	if ((*error)->message) {
		zend_update_property_string(ce_glib_exception, exception, "message", sizeof("message")-1, (char *)(*error)->message TSRMLS_CC);
	}
	zend_update_property_string(ce_glib_exception, exception, "domain", sizeof("domain")-1, (char *)g_quark_to_string((*error)->domain) TSRMLS_CC);
	zend_update_property_long(ce_glib_exception, exception, "code", sizeof("code")-1, (*error)->code TSRMLS_CC);

	zend_throw_exception_object(exception TSRMLS_CC);

	g_clear_error(error);

	return TRUE;
}
/* }}} */

/* ----------------------------------------------------------------
    G\Exception class API
------------------------------------------------------------------*/

/* {{{ proto string G\Exception->getDomain()
                    returns the string domain of the gerror */
PHP_METHOD(Exception, getDomain)
{
	zval *value;

	PHP_GLIB_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GLIB_RESTORE_ERRORS

	value = zend_read_property(ce_glib_exception, getThis(), "domain", sizeof("domain")-1, 0 TSRMLS_CC);
	*return_value = *value;
	zval_copy_ctor(return_value);
	INIT_PZVAL(return_value);
}
/* }}} */

/* ----------------------------------------------------------------
    G\Exception Definition and registration
------------------------------------------------------------------*/

/* {{{ class methods */
static const zend_function_entry glib_exception_methods[] = {
	ZEND_ME(Exception, getDomain, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	ZEND_FE_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(glib_Error)
{
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, GLIB_NAMESPACE, "Exception", glib_exception_methods);
	ce_glib_exception = zend_register_internal_class_ex(&ce, spl_ce_RuntimeException, NULL TSRMLS_CC);
	ce_glib_exception->ce_flags |= ZEND_ACC_FINAL;
	zend_declare_property_string(ce_glib_exception, "domain", sizeof("domain")-1, "", ZEND_ACC_PROTECTED TSRMLS_CC);

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