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
	PHP_MINIT(glib_timer)(INIT_FUNC_ARGS_PASSTHRU);

	PHP_MINIT(glib_main_context)(INIT_FUNC_ARGS_PASSTHRU);
	return SUCCESS;
}

PHP_MINFO_FUNCTION(glib)
{
	char output_buf[58];
	snprintf(output_buf, sizeof(output_buf), "%d.%d.%d", glib_major_version, glib_minor_version, glib_micro_version);

	php_info_print_table_start();
	php_info_print_table_header(2, "GLib extension", "enabled");
	php_info_print_table_row(2, "Glib Library Version", output_buf);
	php_info_print_table_row(2, "Extension Version", PHP_GLIB_VERSION);
	php_info_print_table_end();
}

zend_module_entry glib_module_entry = {
	STANDARD_MODULE_HEADER,
	"glib",
	NULL,
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
