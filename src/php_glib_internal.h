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

#ifndef PHP_GLIB_INTERNAL_H
#define PHP_GLIB_INTERNAL_H

#include <php.h>
#include <zend_exceptions.h>

/* We already need a compat header for php 7 stuff :( */
#include "compat.h"

/* use this to check if our struct item is initialized in a generic manner */
#define GLIB_CHECK_INITIALIZED(member, class_name) \
	if(!(member)) { \
		zend_throw_exception(zend_ce_type_error, "The " #class_name " object has not been correctly initialized by its constructor", 0); \
		return; \
	}

/* main_context is used in main_loop, provide the class entry and macro here */
typedef struct _glib_main_context_object {
	GMainContext *main_context;
	zend_object std;
} glib_main_context_object;

extern zend_class_entry *glib_ce_main_context;
extern zend_class_entry *glib_ce_source;
extern zend_object_handlers glib_source_object_handlers;

static inline glib_main_context_object *glib_main_context_fetch_object(zend_object *object)
{
	return (glib_main_context_object *) ((char*)(object) - XtOffsetOf(glib_main_context_object, std));
}
#define Z_GLIB_MAIN_CONTEXT_P(zv) glib_main_context_fetch_object(Z_OBJ_P(zv))

typedef struct _GPhpSource {
	GSource source;
	zval    source_zval;
} GPhpSource;

typedef struct _GPhpTimeoutSource {
	GSource  source;
	guint    interval;
	gboolean seconds;
	zval     source_zval;
} GPhpTimeoutSource;

typedef struct _glib_source_object {
	GSource *source;
  zend_bool is_php_source;
	zend_object std;
} glib_source_object;

GSourceFuncs php_glib_source_funcs;

static inline glib_source_object *glib_source_fetch_object(zend_object *object)
{
	return (glib_source_object *) ((char*)(object) - XtOffsetOf(glib_source_object, std));
}
#define Z_GLIB_SOURCE_P(zv) glib_source_fetch_object(Z_OBJ_P(zv))

/* Glib functions and classes to register */
extern const zend_function_entry php_glib_functions[];
PHP_MINIT_FUNCTION(glib_main_context);
PHP_MINIT_FUNCTION(glib_main_loop);
PHP_MINIT_FUNCTION(glib_source);
PHP_MINIT_FUNCTION(glib_source_timeout);
PHP_MINIT_FUNCTION(glib_timer);

#endif /* PHP_GLIB_INTERNAL_H */
