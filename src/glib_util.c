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

/* $Id: glib.c 24 2009-05-14 19:45:06Z auroraeosrose $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_glib.h"

zend_class_entry *glib_ce_glib;

ZEND_BEGIN_ARG_INFO_EX(glib_checkVersion_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, major)
	ZEND_ARG_INFO(0, minor)
	ZEND_ARG_INFO(0, micro)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(glib_string_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(glib_userSpecialDir_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, user_dir_type)
ZEND_END_ARG_INFO()

/* {{{ proto string Glib::checkRuntimeVersion()
	 Returns NULL if the GLib library is compatible with the given version, or a string describing the version mismatch.
	 Compatibility is defined by two things: first the version of the running library is newer than the version
	 major.minor.micro. Second the running library must be binary compatible with the version
	 majore.minor.micro (same major version.)
   */
PHP_METHOD(Glib, checkRuntimeVersion)
{
	long major = 0, micro = 0, minor = 0;
	const char * version_error;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l|ll", &major, &minor, &micro) == FAILURE) {
		return;
	}

	version_error = glib_check_version(major, minor, micro);
	if (version_error == NULL) {
		return;
	} else {
		RETURN_STRING(version_error, 1);
	}
}
/* }}} */

/* {{{ proto boolean Glib::checkVersion()
	   Checks the version of the GLib library the extension was compiled against.
	   Returns TRUE if the version of the GLib header files compiled against are the same as or newer than the passed-in version. 
   */
PHP_METHOD(Glib, checkVersion)
{
	long major = 0, micro = 0, minor = 0;
	const char * version_error;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l|ll", &major, &minor, &micro) == FAILURE) {
		return;
	}

	RETURN_BOOL(GLIB_CHECK_VERSION(major, minor, micro));
}
/* }}} */

/* {{{ proto string Glib::localeToUtf8(string text)
	   Converts a string which is in the encoding used for strings in the current locale into a UTF-8 string. 
   */
PHP_METHOD(Glib, localeToUtf8)
{
	char *str_utf8, *locale;
	int length;
	GError *error = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &locale, &length) == FAILURE) {
		return;
	}

	str_utf8 = g_locale_to_utf8((const gchar*)locale, length, NULL, NULL, &error);
	if (php_glib_handle_gerror(&error TSRMLS_CC)) {
		return;
	}
	RETURN_STRING(str_utf8, 1);
}
/* }}} */

/* {{{ proto string Glib::localeFromUtf8(string text)
	   Converts a string from UTF-8 into the encoding used for strings in the current locale. 
   */
PHP_METHOD(Glib, localeFromUtf8)
{
	char *str_utf8, *locale;
	int length;
	GError *error = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &locale, &length) == FAILURE) {
		return;
	}

	str_utf8 = g_locale_from_utf8((const gchar*)locale, length, NULL, NULL, &error);
	if (php_glib_handle_gerror(&error TSRMLS_CC)) {
		return;
	}
	RETURN_STRING(str_utf8, 1);
}
/* }}} */

/* {{{ proto array Glib::getLanguageNames()
	   Checks the version of the GLib library the extension was compiled against.
	   Returns TRUE if the version of the GLib header files compiled against are the same as or newer than the passed-in version. 
   */
PHP_METHOD(Glib, getLanguageNames)
{
	const gchar* const *langs;
	int i;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	langs = g_get_language_names();

	array_init(return_value);
	for (i = 0; langs[i]; i++) {
		add_next_index_string(return_value, (char *)langs[i], 1);
	}
}
/* }}} */

/* {{{ proto string Glib::displayName(string filename)
       Converts a filename into a valid UTF-8 string. 
      */
PHP_METHOD(Glib, displayName)
{
	char *filename, *display_name;
	int length;
	GError *error = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &filename, &length) == FAILURE) {
		return;
	}

	display_name = g_filename_display_name((const gchar*)filename);
	if (php_glib_handle_gerror(&error TSRMLS_CC)) {
		return;
	}
	RETURN_STRING(display_name, 1);
}
/* }}} */

/* {{{ proto string Glib::displayBasename(string filename)
	   Returns the display basename for the particular filename, guaranteed to be valid UTF-8.
      */
PHP_METHOD(Glib, displayBasename)
{
	char *filename, *display_name;
	int length;
	GError *error = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &filename, &length) == FAILURE) {
		return;
	}

	display_name = g_filename_display_basename((const gchar*)filename);
	if (php_glib_handle_gerror(&error TSRMLS_CC)) {
		return;
	}
	RETURN_STRING(display_name, 1);
}
/* }}} */

/* {{{ proto string Glib::filenameFromUri(string filename)
	   Converts an escaped ASCII-encoded URI to a local filename in the encoding used for filenames.
      */
PHP_METHOD(Glib, filenameFromUri)
{
	char *filename, *uri;
	int length;
	GError *error = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &uri, &length) == FAILURE) {
		return;
	}

	filename = g_filename_from_uri((const gchar*)uri, NULL, &error);
	if (php_glib_handle_gerror(&error TSRMLS_CC)) {
		return;
	}
	RETURN_STRING(filename, 1);
}
/* }}} */

/* {{{ proto string Glib::filenameToUri(string filename)
	   Converts an escaped ASCII-encoded URI to a local filename in the encoding used for filenames.
      */
PHP_METHOD(Glib, filenameToUri)
{
	char *filename, *uri;
	int length;
	GError *error = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &filename, &length) == FAILURE) {
		return;
	}

	uri = g_filename_to_uri((const gchar*)filename, NULL, &error);
	if (php_glib_handle_gerror(&error TSRMLS_CC)) {
		return;
	}
	RETURN_STRING(uri, 1);
}
/* }}} */

/* {{{ proto array Glib::filenameGetCharsets()
	   Determines the preferred character sets used for filenames. 
	   Returns an array. The first element is a boolean indicating if the filename encoding
	   is UTF-8. The second element is the filename encoding.
	   The final element is an array of character sets used when trying to generate a
	   displayable representation of a filename.
	   */
PHP_METHOD(Glib, filenameGetCharsets)
{
	const gchar **charsets;
	gboolean utf8;
	zval *charset_array;
	int i;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	array_init(return_value);
	MAKE_STD_ZVAL(charset_array);
	array_init(charset_array);

	utf8 = g_get_filename_charsets(&charsets);
	add_next_index_bool(return_value, utf8);
	add_next_index_string(return_value, (char *)charsets[0], 1);
	for (i = 1; charsets[i]; i++) {
		add_next_index_string(charset_array, (char *)charsets[i], 1);
	}
	add_next_index_zval(return_value, charset_array);
}

/* }}} */

/* {{{ proto array Glib::getCharset()
	   Obtains the character set for the current locale.
	   Returns an array, the first element of which is a boolean indicating if the
	   current charset is UTF-8. The remaining element is the charset.
	   */
PHP_METHOD(Glib, getCharset)
{
	gboolean status;
	const gchar *charset;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	status = g_get_charset(&charset);
	array_init(return_value);
	add_next_index_bool(return_value, status);
	add_next_index_string(return_value, (char *)charset, 1);
}

/* }}} */

/* {{{ proto string Glib::shellQuote(string unquoted_string)
	   Quotes a string so that the shell (/bin/sh) will interpret the quoted string to mean unquoted_string
      */
PHP_METHOD(Glib, shellQuote)
{
	char *string, *quoted_string;
	int length;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &string, &length) == FAILURE) {
		return;
	}

	quoted_string = g_shell_quote((const gchar*)string);
	RETURN_STRING(quoted_string, 1);
}
/* }}} */

/* {{{ proto string Glib::shellUnquote(string ununquoted_string)
	   Unquotes a string as the shell (/bin/sh) would. Only handles quotes; if
	   a string contains file globs, arithmetic operators, variables,
	   backticks, redirections, or other special-to-the-shell features, the
	   result will be different from the result a real shell would produce (the
	   variables, backticks, etc. will be passed through literally instead of
	   being expanded).
      */
PHP_METHOD(Glib, shellUnquote)
{
	char *string, *unquoted_string;
	int length;
	GError *error = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &string, &length) == FAILURE) {
		return;
	}

	unquoted_string = g_shell_unquote((const gchar*)string, &error);
	if (php_glib_handle_gerror(&error TSRMLS_CC)) {
		return;
	}
	RETURN_STRING(unquoted_string, 1);
}
/* }}} */

/* {{{ proto string Glib::shellUnquote(string ununquoted_string)
	   Locates the first executable named program in the user's path, in the same way that execvp() 
	   would locate it. Returns an allocated string with the absolute path name, or NULL if the 
	   program is not found in the path.
*/
PHP_METHOD(Glib, findProgram)
{
	char *string;
	int length;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &string, &length) == FAILURE) {
		return;
	}

	char *name = g_find_program_in_path(string);

	if (NULL == name) {
		RETURN_NULL();
	}

	RETURN_STRING(name, 1);
}
/* }}} */

/* {{{ proto string Glib::userName()
	   Gets the user name of the current user
*/
PHP_METHOD(Glib, userName)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	const char *name = g_get_user_name();
	RETURN_STRING(name, 1);
}
/* }}} */

/* {{{ proto string Glib::userRealName()
	   Gets the real name of the user
*/
PHP_METHOD(Glib, userRealName)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	const char *name = g_get_real_name();
	RETURN_STRING(name, 1);
}
/* }}} */

/* {{{ proto array Glib::systemDataDirs()
	   Returns an ordered list of base directories in which to access system-wide application data.
*/
PHP_METHOD(Glib, systemDataDirs)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	const gchar* const *dir = g_get_system_data_dirs();

	array_init(return_value);

	while (*dir != NULL) {
		add_next_index_string(return_value, *dir, 1);
		dir++;
	}
}
/* }}} */

/* {{{ proto array Glib::systemConfigDirs()
	   Returns an ordered list of base directories in which to access system-wide configuration information.
*/
PHP_METHOD(Glib, systemConfigDirs)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	const gchar* const *dir = g_get_system_config_dirs();

	array_init(return_value);

	while (*dir != NULL) {
		add_next_index_string(return_value, *dir, 1);
		dir++;
	}
}
/* }}} */

/* {{{ proto string Glib::userCacheDir()
	   Returns a base directory in which to store non-essential, cached data specific to particular user.
*/
PHP_METHOD(Glib, userCacheDir)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	const char *name = g_get_user_cache_dir();
	RETURN_STRING(name, 1);
}
/* }}} */

/* {{{ proto string Glib::userConfigDir()
	   Returns a base directory in which to store user-specific application configuration 
	   information such as user preferences and settings.
*/
PHP_METHOD(Glib, userConfigDir)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	const char *name = g_get_user_config_dir();
	RETURN_STRING(name, 1);
}
/* }}} */

/* {{{ proto string Glib::userDataDir()
	   Returns a base directory in which to access application data such as icons that is 
	   customized for a particular user
*/
PHP_METHOD(Glib, userDataDir)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	const char *name = g_get_user_data_dir();
	RETURN_STRING(name, 1);
}
/* }}} */

/* {{{ proto string Glib::userHomeDir()
	   Gets the current user's home directory as defined in the password database.
*/
PHP_METHOD(Glib, userHomeDir)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	const char *name = g_get_home_dir();
	RETURN_STRING(name, 1);
}
/* }}} */


/* {{{ proto string Glib::userSpecialDir(int user_dir_type)
	   Returns the full path of a special directory using its logical id.
	   One of Glib::USER_DIRECTORY_* constants is supposed to be used as parameter
*/
PHP_METHOD(Glib, userSpecialDir)
{
	long dir_type;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &dir_type) == FAILURE) {
		return;
	}

	if (dir_type < 0 || dir_type >= G_USER_N_DIRECTORIES) {
		zval *exception;

		MAKE_STD_ZVAL(exception);
		object_init_ex(exception, glib_ce_exception);
		zend_update_property_string(glib_ce_exception, exception, "message", sizeof("message")-1, "invalid user-directory type" TSRMLS_CC);
		zend_throw_exception_object(exception TSRMLS_CC);

		return;
	}

	const char *retval = g_get_user_special_dir(dir_type);

	if (NULL == retval) {
		RETURN_NULL();
	}

	RETURN_STRING(retval, 1);
}
/* }}} */

/* {{{ glib_class_functions[] */
const zend_function_entry glib_methods[] = {
	PHP_ME(Glib, checkVersion,        glib_checkVersion_args,    ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glib, checkRuntimeVersion, glib_checkVersion_args,    ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glib, localeToUtf8,        glib_string_args,          ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glib, localeFromUtf8,      glib_string_args,          ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glib, getLanguageNames,    NULL,                      ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glib, displayName,         glib_string_args,          ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glib, displayBasename,     glib_string_args,          ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glib, filenameFromUri,     glib_string_args,          ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glib, filenameToUri,       glib_string_args,          ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glib, filenameGetCharsets, NULL,                      ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glib, getCharset,          NULL,                      ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glib, shellQuote,          glib_string_args,          ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glib, shellUnquote,        glib_string_args,          ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glib, findProgram,         glib_string_args,          ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)

	PHP_ME(Glib, userName,            NULL,                      ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glib, userRealName,        NULL,                      ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)

	// Directories
	PHP_ME(Glib, systemDataDirs,      NULL,                      ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glib, systemConfigDirs,    NULL,                      ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glib, userCacheDir,        NULL,                      ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glib, userConfigDir,       NULL,                      ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glib, userDataDir,         NULL,                      ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glib, userHomeDir,         NULL,                      ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Glib, userSpecialDir,      glib_userSpecialDir_args,  ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)

	{NULL, NULL, NULL}
};
/* }}} */

/* {{{ glib_module_entry
 */
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
/* }}} */

#ifdef COMPILE_DL_GLIB
ZEND_GET_MODULE(glib)
#endif

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(glib)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, GLIB_NAMESPACE, glib_methods);
	glib_ce_glib = zend_register_internal_class(&ce TSRMLS_CC);
	glib_ce_glib->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS|ZEND_ACC_FINAL_CLASS;

	zend_declare_class_constant_long(glib_ce_glib, "MAJOR_VERSION", sizeof("MAJOR_VERSION")-1, GLIB_MAJOR_VERSION TSRMLS_CC);
	zend_declare_class_constant_long(glib_ce_glib, "MINOR_VERSION", sizeof("MINOR_VERSION")-1, GLIB_MINOR_VERSION TSRMLS_CC);
	zend_declare_class_constant_long(glib_ce_glib, "MICRO_VERSION", sizeof("MICRO_VERSION")-1, GLIB_MICRO_VERSION TSRMLS_CC);

	zend_declare_class_constant_long(glib_ce_glib, "major_version", sizeof("major_version")-1, glib_major_version TSRMLS_CC);
	zend_declare_class_constant_long(glib_ce_glib, "minor_version", sizeof("minor_version")-1, glib_minor_version TSRMLS_CC);
	zend_declare_class_constant_long(glib_ce_glib, "micro_version", sizeof("micro_version")-1, glib_micro_version TSRMLS_CC);

	zend_declare_class_constant_long(glib_ce_glib, "USER_DIRECTORY_DESKTOP",      sizeof("USER_DIRECTORY_DESKTOP")-1,      G_USER_DIRECTORY_DESKTOP TSRMLS_CC);
	zend_declare_class_constant_long(glib_ce_glib, "USER_DIRECTORY_DOCUMENTS",    sizeof("USER_DIRECTORY_DOCUMENTS")-1,    G_USER_DIRECTORY_DOCUMENTS TSRMLS_CC);
	zend_declare_class_constant_long(glib_ce_glib, "USER_DIRECTORY_DOWNLOAD",     sizeof("USER_DIRECTORY_DOWNLOAD")-1,     G_USER_DIRECTORY_DOWNLOAD TSRMLS_CC);
	zend_declare_class_constant_long(glib_ce_glib, "USER_DIRECTORY_MUSIC",        sizeof("USER_DIRECTORY_MUSIC")-1,        G_USER_DIRECTORY_MUSIC TSRMLS_CC);
	zend_declare_class_constant_long(glib_ce_glib, "USER_DIRECTORY_PICTURES",     sizeof("USER_DIRECTORY_PICTURES")-1,     G_USER_DIRECTORY_PICTURES TSRMLS_CC);
	zend_declare_class_constant_long(glib_ce_glib, "USER_DIRECTORY_PUBLIC_SHARE", sizeof("USER_DIRECTORY_PUBLIC_SHARE")-1, G_USER_DIRECTORY_PUBLIC_SHARE TSRMLS_CC);
	zend_declare_class_constant_long(glib_ce_glib, "USER_DIRECTORY_TEMPLATES",    sizeof("USER_DIRECTORY_TEMPLATES")-1,    G_USER_DIRECTORY_TEMPLATES TSRMLS_CC);
	zend_declare_class_constant_long(glib_ce_glib, "USER_DIRECTORY_VIDEOS",       sizeof("USER_DIRECTORY_VIDEOS")-1,       G_USER_DIRECTORY_VIDEOS TSRMLS_CC);

	PHP_MINIT(glib_exception)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(glib_main)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(glib_maincontext)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(glib_timer)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(glib_bookmarkfile)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(glib_option)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(glib_source)(INIT_FUNC_ARGS_PASSTHRU);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION(glib)
 */
PHP_MINFO_FUNCTION(glib)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "glib library wrapper", "enabled");
	php_info_print_table_end();
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
