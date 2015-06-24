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

#ifndef PHP_GLIB_PUBLIC_H
#define PHP_GLIB_PUBLIC_H

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef ZTS
# include "TSRM.h"
#endif

#include <php.h>

#ifdef PHP_WIN32
#  ifdef GLIB_EXPORTS
#    define PHP_GLIB_API __declspec(dllexport)
#  elif defined(COMPILE_DL_GLIB)
#    define PHP_GLIB_API __declspec(dllimport)
#  else
#    define PHP_GLIB_API /* nothing special */
#  endif
#elif defined(__GNUC__) && __GNUC__ >= 4
#  define PHP_GLIB_API __attribute__ ((visibility("default")))
#else
#  define PHP_GLIB_API
#endif

#define PHP_GLIB_VERSION "0.1.0-dev"
#define GLIB_NAMESPACE "G"

extern PHP_GLIB_API zend_class_entry *ce_glib_enum;
extern PHP_GLIB_API zend_class_entry *ce_glib_struct;
extern PHP_GLIB_API zend_class_entry *ce_glib_exception;
extern PHP_GLIB_API zend_class_entry *ce_glib_string;
extern PHP_GLIB_API zend_class_entry *ce_glib_unicode;

/* so we don't have to include glib.h for one define */
typedef struct _GError GError;

extern PHP_GLIB_API zend_bool php_glib_handle_gerror(GError **error TSRMLS_DC);
extern PHP_GLIB_API long php_g_get_enum_value(zval** enumclass TSRMLS_DC);
extern PHP_GLIB_API void php_g_set_enum_value(zval** enumclass, long value TSRMLS_DC);

#endif /* PHP_GLIB_PUBLIC_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
