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

/* ----------------------------------------------------------------
    Glib namespaced functions
------------------------------------------------------------------*/

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(check_version_args, 0, 1, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, major, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, minor, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, micro, IS_LONG, 0)
ZEND_END_ARG_INFO()

/* {{{ proto string \Glib\check_version(int major[ , int minor [, int micro ] ])
         checks the glib library in use is compatible with the given
         version information
   */
PHP_FUNCTION(check_version)
{
    long major = 0, micro = 0, minor = 0;
    const char * version_error;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "l|ll", &major, &minor, &micro) == FAILURE) {
		return;
	}

	version_error = glib_check_version(major, minor, micro);
	if (version_error == NULL) {
		return;
	} else {
		RETURN_STRING(version_error);
	}
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(check_compiled_version_args, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, major, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, minor, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, micro, IS_LONG, 0)
ZEND_END_ARG_INFO()

/* {{{ proto boolean Glib\check_compiled_version(int major[ , int minor [, int micro ] ])
	   Checks the version of the GLib library the extension was compiled against.
	   Returns TRUE if the version of the GLib header files compiled against are the same as or newer than the passed-in version. 
   */
PHP_FUNCTION(check_compiled_version)
{
	long major = 0, micro = 0, minor = 0;

	if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "l|ll", &major, &minor, &micro) == FAILURE) {
		return;
	}

	RETURN_BOOL(GLIB_CHECK_VERSION(major, minor, micro));
}
/* }}} */

/* ----------------------------------------------------------------
    Glib Namespaced Functions Registration
------------------------------------------------------------------*/

const zend_function_entry php_glib_functions[] = {
	ZEND_NS_FE(GLIB_NAMESPACE, check_version, check_version_args)
    ZEND_NS_FE(GLIB_NAMESPACE, check_compiled_version, check_compiled_version_args)
	ZEND_FE_END
};