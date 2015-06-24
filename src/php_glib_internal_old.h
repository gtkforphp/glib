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

/* $Id: php_glib.h 23 2009-05-12 13:20:38Z auroraeosrose $ */

#ifndef PHP_GLIB_H
#define PHP_GLIB_H

#define PHP_GLIB_VERSION "0.1.0-dev"

#define GLIB_NAMESPACE "Glib"

extern zend_module_entry glib_module_entry;
#define phpext_glib_ptr &glib_module_entry

#ifdef PHP_WIN32
#	define PHP_GLIB_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_GLIB_API __attribute__ ((visibility("default")))
#else
#	define PHP_GLIB_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#include <glib.h>

typedef struct _glib_maincontext_object {
	zend_object std;
	GMainContext *maincontext;
} glib_maincontext_object;

typedef struct _glib_source_object {
	zend_object std;
	GSource *source;
} glib_source_object;

typedef struct _glib_timer_object {
	zend_object std;
	GTimer *timer;
	zend_bool active;
} glib_timer_object;

typedef struct _glib_bookmarkfile_object {
	zend_object std;
	GBookmarkFile *bookmarkfile;
} glib_bookmarkfile_object;

typedef struct _glib_optionentry_object {
	zend_object std;
	GOptionEntry *optionentry;
} glib_optionentry_object;

typedef struct _glib_optioncontext_object {
	zend_object std;
	GOptionContext *optioncontext;
} glib_optioncontext_object;

PHP_GLIB_API zend_bool php_glib_handle_gerror(GError **error TSRMLS_DC);

PHP_MINIT_FUNCTION(glib);
PHP_MINFO_FUNCTION(glib);

PHP_MINIT_FUNCTION(glib_exception);
PHP_MINIT_FUNCTION(glib_main);
PHP_MINIT_FUNCTION(glib_maincontext);
PHP_MINIT_FUNCTION(glib_source);
PHP_MINIT_FUNCTION(glib_timer);
PHP_MINIT_FUNCTION(glib_bookmarkfile);
PHP_MINIT_FUNCTION(glib_option);

extern zend_class_entry *glib_ce_exception;

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
