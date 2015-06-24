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

/* $Id: glib_main.c 15 2009-05-01 12:15:36Z auroraeosrose $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_glib.h"

zend_class_entry *glib_ce_main;

ZEND_BEGIN_ARG_INFO_EX(Glib_Main_iteration_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
	ZEND_ARG_INFO(0, may_block)
ZEND_END_ARG_INFO()

/* {{{ proto bool \Glib\Main::iteration([boolean may_block])
		Runs a single iteration on the default context
		see \Glib\Main\Context->iteration();
   */
PHP_METHOD(Glib_Main, iteration)
{
	zend_bool may_block = FALSE;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|b", &may_block) == FAILURE) {
		return;
	}

	RETURN_BOOL(g_main_context_iteration(NULL, may_block));
}
/* }}} */

/* {{{ proto bool \Glib\Main::pending()
		Runs a single iteration on the default context
		see \Glib\Main\Context->pending();
   */
PHP_METHOD(Glib_Main, pending)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	RETURN_BOOL(g_main_context_pending(NULL));
}
/* }}} */

/* {{{ proto int \Glib\Main::depth()
		Returns the depth of the stack of calls to \Glib\Main\Context->dispatch() on any context in the current thread.
   */
PHP_METHOD(Glib_Main, depth)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	RETURN_LONG(g_main_depth());
}
/* }}} */

/* {{{ glib_main_methods[] */
const zend_function_entry glib_main_methods[] = {
	PHP_ME(Glib_Main, iteration, Glib_Main_iteration_args, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glib_Main, pending, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glib_Main, depth, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	{NULL, NULL, NULL}
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(glib_main)
{
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, GLIB_NAMESPACE, "Main", glib_main_methods);
	glib_ce_main = zend_register_internal_class(&ce TSRMLS_CC);

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
