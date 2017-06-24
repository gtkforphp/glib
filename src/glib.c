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

#include "ext/standard/info.h"

#include "php_glib.h"
#include "php_glib_internal.h"

PHP_MINIT_FUNCTION(glib)
{
	/* Register namespace constants */
	REGISTER_NS_LONG_CONSTANT(GLIB_NAMESPACE, "major_version", glib_major_version, CONST_CS | CONST_PERSISTENT);
	REGISTER_NS_LONG_CONSTANT(GLIB_NAMESPACE, "minor_version", glib_minor_version, CONST_CS | CONST_PERSISTENT);
	REGISTER_NS_LONG_CONSTANT(GLIB_NAMESPACE, "micro_version", glib_micro_version, CONST_CS | CONST_PERSISTENT);
	REGISTER_NS_LONG_CONSTANT(GLIB_NAMESPACE, "binary_age", glib_binary_age, CONST_CS | CONST_PERSISTENT);
	REGISTER_NS_LONG_CONSTANT(GLIB_NAMESPACE, "interface_age", glib_interface_age, CONST_CS | CONST_PERSISTENT);
	REGISTER_NS_LONG_CONSTANT(GLIB_NAMESPACE, "MAJOR_VERSION", GLIB_MAJOR_VERSION, CONST_CS | CONST_PERSISTENT);
	REGISTER_NS_LONG_CONSTANT(GLIB_NAMESPACE, "MINOR_VERSION", GLIB_MINOR_VERSION, CONST_CS | CONST_PERSISTENT);
	REGISTER_NS_LONG_CONSTANT(GLIB_NAMESPACE, "MICRO_VERSION", GLIB_MICRO_VERSION, CONST_CS | CONST_PERSISTENT);

#ifdef G_OS_WIN32
	REGISTER_NS_BOOL_CONSTANT(GLIB_NAMESPACE, "OS_WIN32", 1, CONST_CS | CONST_PERSISTENT);
#endif

#ifdef G_OS_UNIX
	REGISTER_NS_BOOL_CONSTANT(GLIB_NAMESPACE, "OS_UNIX", 1, CONST_CS | CONST_PERSISTENT);
#endif

	/* Register our Core application support classes */ 
	PHP_MINIT(glib_main_context)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(glib_main_loop)(INIT_FUNC_ARGS_PASSTHRU);

	/* Register our utitilty classes */
	PHP_MINIT(glib_timer)(INIT_FUNC_ARGS_PASSTHRU);

	/* Register our datatype classes */

	return SUCCESS;
}

#define GLIB_VERSION_STRINGIZE_(major, minor, micro) \
	#major"."#minor"."#micro
#define GLIB_VERSION_STRINGIZE(major, minor, micro) \
	GLIB_VERSION_STRINGIZE_(major, minor, micro)

PHP_MINFO_FUNCTION(glib)
{
	char output_buf[58];
	snprintf(output_buf, sizeof(output_buf), "%d.%d.%d", glib_major_version, glib_minor_version, glib_micro_version);

	php_info_print_table_start();
	php_info_print_table_header(2, "GLib extension", "enabled");
	php_info_print_table_row(2, "Runtime Glib Library Version", output_buf);
	php_info_print_table_row(2, "Compiled Glib Library Version", GLIB_VERSION_STRINGIZE(GLIB_MAJOR_VERSION, GLIB_MINOR_VERSION, GLIB_MICRO_VERSION));
	php_info_print_table_row(2, "Extension Version", PHP_GLIB_VERSION);
	php_info_print_table_end();
}

#undef GLIB_VERSION_STRINGIZE
#undef GLIB_VERSION_STRINGIZE_

zend_module_entry glib_module_entry = {
	STANDARD_MODULE_HEADER,
	"glib",
	php_glib_functions,
	PHP_MINIT(glib),
	NULL,
	NULL,
	NULL,
	PHP_MINFO(glib),
	PHP_GLIB_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_GLIB
	ZEND_GET_MODULE(glib)
#endif