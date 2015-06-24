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
  | Authors: Elizabeth Smith <auroraeosrose@php.net>                     |
  |          Michael Maclean <mgdm@php.net>                              |
  +----------------------------------------------------------------------+
*/

/* $Id: $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_glib.h"

zend_class_entry *glib_ce_optionentry;
zend_class_entry *glib_ce_optionarg;
zend_class_entry *glib_ce_optionflag;
zend_class_entry *glib_ce_optioncontext;

/* for extended classes, make sure internal object exists properly */
static inline glib_optionentry_object* glib_optionentry_object_get(zval *zobj TSRMLS_DC)
{
	glib_optionentry_object *pobj = zend_object_store_get_object(zobj TSRMLS_CC);
	if(pobj->optionentry == NULL) {
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Internal object missing in %s class, you must call parent::__construct in extended classes", Z_OBJCE_P(zobj)->name);
	}
	return pobj;
}

void glib_optionentry_free_storage(glib_optionentry_object *intern TSRMLS_DC)
{
	if(intern->optionentry) {	
		efree(intern->optionentry);
	}

	if (intern->std.guards) {
		zend_hash_destroy(intern->std.guards);
		FREE_HASHTABLE(intern->std.guards);
	}

	if (intern->std.properties) {
		zend_hash_destroy(intern->std.properties);
		FREE_HASHTABLE(intern->std.properties);
	}
	efree(intern);
}

zend_object_value glib_optionentry_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	glib_optionentry_object *object;
	zval *tmp;

	object = ecalloc(1, sizeof(glib_optionentry_object));
	object->std.ce = ce;
	object->std.guards = NULL;
	object->optionentry = NULL;
	
	ALLOC_HASHTABLE(object->std.properties);
	zend_hash_init(object->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
	zend_hash_copy(object->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

	retval.handle = zend_objects_store_put(object, (zend_objects_store_dtor_t)zend_objects_destroy_object, (zend_objects_free_object_storage_t) glib_optionentry_free_storage, NULL TSRMLS_CC);
	retval.handlers = zend_get_std_object_handlers();
	return retval;

}

PHP_METHOD(Glib_OptionEntry, __construct)
{
	gchar *long_name, short_name, *desc, *arg_desc;
	long long_name_len, short_name_len, desc_len, arg_desc_len;
	gint arg_type, flags;

	glib_optionentry_object *option_entry = (glib_optionentry_object *)zend_objects_get_address(getThis() TSRMLS_CC);

	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ssllss", 
				&long_name, &long_name_len, 
				&short_name, &short_name_len,
				&arg_type, &flags, 
				&desc, &desc_len, 
				&arg_desc, &arg_desc_len) == FAILURE) 
	{
		return;
	}

	option_entry->optionentry = ecalloc(1, sizeof(GOptionEntry));
	option_entry->optionentry->long_name = g_strdup(long_name);
	option_entry->optionentry->short_name = short_name,
	option_entry->optionentry->arg = (int)arg_type;
	option_entry->optionentry->flags = flags;
	option_entry->optionentry->description = g_strdup(desc);
	option_entry->optionentry->arg_description = g_strdup(arg_desc);
}

/* {{{ glib_optionentry_methods[] */
const zend_function_entry glib_optionentry_methods[] = {
	PHP_ME(Glib_OptionEntry, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	{ NULL, NULL, NULL }
};
/* }}} */


zend_class_entry *glib_ce_optioncontext;

ZEND_BEGIN_ARG_INFO_EX(glib_OptionContext_addMainEntries_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, entries)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(glib_OptionContext_parse_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, arguments)
ZEND_END_ARG_INFO()

/* for extended classes, make sure internal object exists properly */
static inline glib_optioncontext_object* glib_optioncontext_object_get(zval *zobj TSRMLS_DC)
{
	glib_optioncontext_object *pobj = zend_object_store_get_object(zobj TSRMLS_CC);
	if(pobj->optioncontext == NULL) 
	{
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Internal object missing in %s class, you must call parent::__construct in extended classes", Z_OBJCE_P(zobj)->name);
	}
	return pobj;
}

void glib_optioncontext_free_storage(glib_optioncontext_object *intern TSRMLS_DC)
{
	if(intern->optioncontext) {
		g_option_context_free(intern->optioncontext);
	}

	if (intern->std.guards) {
		zend_hash_destroy(intern->std.guards);
		FREE_HASHTABLE(intern->std.guards);
	}

	if (intern->std.properties) {
		zend_hash_destroy(intern->std.properties);
		FREE_HASHTABLE(intern->std.properties);
	}
	efree(intern);
}

zend_object_value glib_optioncontext_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	glib_optioncontext_object *object;
	zval *tmp;

	object = emalloc(sizeof(glib_optioncontext_object));
	object->std.ce = ce;
	object->std.guards = NULL;
	object->optioncontext = NULL;
	
	ALLOC_HASHTABLE(object->std.properties);
	zend_hash_init(object->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
	zend_hash_copy(object->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

	retval.handle = zend_objects_store_put(object, (zend_objects_store_dtor_t)zend_objects_destroy_object, (zend_objects_free_object_storage_t) glib_optioncontext_free_storage, NULL TSRMLS_CC);
	retval.handlers = zend_get_std_object_handlers();
	return retval;

}

PHP_METHOD(Glib_OptionContext, __construct)
{
	const gchar *desc;
	long desc_len;	

	glib_optioncontext_object *option_context = (glib_optioncontext_object *)zend_objects_get_address(getThis() TSRMLS_CC);

	if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &desc, &desc_len) == FAILURE)
	{
		return;
	}

	option_context->optioncontext = g_option_context_new(desc);
}

/* {{{ proto void Glib\OptionContext->addMainEntries(array entries)
	   A convenience function which creates a main group if it doesn't exist, and adds the entries to it.
	   TODO: handle translation domains
	   */

PHP_METHOD(Glib_OptionContext, addMainEntries)
{
	zval *entries, **data;
	HashTable *myht;
	HashPosition pos;
	GOptionEntry **mainentries;
	glib_optionentry_object *optionentry;
	glib_optioncontext_object *optioncontext;
	int count, i = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &entries) == FAILURE)
	{
		return;
	}
	
	myht = Z_ARRVAL_P(entries);
	if (zend_hash_num_elements(myht) == 0) 
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "At least one GOptionEntry is required");
		return;
	}
	
	optioncontext = (glib_optioncontext_object *) glib_optioncontext_object_get(getThis() TSRMLS_CC);
	count = zend_hash_num_elements(myht);
	mainentries = (GOptionEntry **)ecalloc(count, sizeof(GOptionEntry));

	zend_hash_internal_pointer_reset_ex(myht, &pos);
	for(zend_hash_internal_pointer_reset_ex(myht, &pos);
			zend_hash_get_current_data_ex(myht, (void **)&data, &pos) == SUCCESS;
			zend_hash_move_forward_ex(myht, &pos)) {
		if ((Z_TYPE_PP(data) == IS_OBJECT) && strcmp(Z_OBJCE_PP(data)->name, ZEND_NS_NAME(GLIB_NAMESPACE, "OptionEntry")) == 0 )
		{
			optionentry = (glib_optionentry_object *)glib_optionentry_object_get(*data TSRMLS_CC);
			mainentries[i] = optionentry->optionentry;
			i++;
		} else {
			php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Ignored item of type %d", Z_TYPE_PP(data));
		}
	}
/*
	if(i < count) {
		for(i = count + 1; i <= count; i++) {
			mainentries[i] = NULL;
		}
	}
*/
	g_option_context_add_main_entries(optioncontext->optioncontext, (GOptionEntry *) mainentries, NULL);
}

/* }}} */

/* {{{ proto boolean Glib\OptionContext->parse(array arguments)
	   Parses the command line arguments, recognizing options which have been added to context.
	   */
PHP_METHOD(Glib_OptionContext, parse)
{
	zval *arguments, **data;
	gchar **args;
	int argc, i = 0;
	HashTable *myht;
	HashPosition pos;
	glib_optioncontext_object *optioncontext;
	GError *error = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &arguments ) == FAILURE)
	{
		return;
	}	
	
	myht = Z_ARRVAL_P(arguments);
	argc = zend_hash_num_elements(myht);
	args = ecalloc(argc, sizeof(gchar *));
	
	optioncontext = (glib_optioncontext_object *) glib_optioncontext_object_get(getThis() TSRMLS_CC);

	for(zend_hash_internal_pointer_reset_ex(myht, &pos);
			zend_hash_get_current_data_ex(myht, (void **)&data, &pos) == SUCCESS;
			zend_hash_move_forward_ex(myht, &pos)) {
		if (Z_TYPE_PP(data) == IS_STRING)
		{
			args[i] = g_strdup(Z_STRVAL_PP(data));
			i++;
		}
	}
	args[argc] = NULL;

	g_option_context_parse(optioncontext->optioncontext, (int *)&argc, &args, &error);
	if (php_glib_handle_gerror(&error TSRMLS_CC)) {
		return;
	}

	RETURN_TRUE;
}

/* }}} */

/* {{{ glib_optioncontext_methods[] */
const zend_function_entry glib_optioncontext_methods[] = {
	PHP_ME(Glib_OptionContext, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Glib_OptionContext, addMainEntries, glib_OptionContext_addMainEntries_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Glib_OptionContext, parse, glib_OptionContext_parse_args, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	{ NULL, NULL, NULL }
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(glib_option)
{
	zend_class_entry optionentry_ce;
	zend_class_entry optionarg_ce;
	zend_class_entry optionflag_ce;
	zend_class_entry optioncontext_ce;

	INIT_NS_CLASS_ENTRY(optionarg_ce, GLIB_NAMESPACE, "OptionArg", NULL);
	glib_ce_optionarg = zend_register_internal_class(&optionarg_ce TSRMLS_CC);
	glib_ce_optionarg->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;
	
	zend_declare_class_constant_long(glib_ce_optionarg, "NONE", sizeof("NONE")-1, G_OPTION_ARG_NONE TSRMLS_CC);
	zend_declare_class_constant_long(glib_ce_optionarg, "STRING", sizeof("STRING")-1, G_OPTION_ARG_STRING TSRMLS_CC);
	zend_declare_class_constant_long(glib_ce_optionarg, "INT", sizeof("INT")-1, G_OPTION_ARG_INT TSRMLS_CC);
	zend_declare_class_constant_long(glib_ce_optionarg, "CALLBACK", sizeof("CALLBACK")-1, G_OPTION_ARG_CALLBACK TSRMLS_CC);
	zend_declare_class_constant_long(glib_ce_optionarg, "FILENAME", sizeof("FILENAME")-1, G_OPTION_ARG_FILENAME TSRMLS_CC);
	zend_declare_class_constant_long(glib_ce_optionarg, "STRING_ARRAY", sizeof("STRING_ARRAY")-1, G_OPTION_ARG_STRING_ARRAY TSRMLS_CC);
	zend_declare_class_constant_long(glib_ce_optionarg, "FILENAME_ARRAY", sizeof("FILENAME_ARRAY")-1, G_OPTION_ARG_FILENAME_ARRAY TSRMLS_CC);
	zend_declare_class_constant_long(glib_ce_optionarg, "DOUBLE", sizeof("DOUBLE")-1, G_OPTION_ARG_DOUBLE TSRMLS_CC);
	zend_declare_class_constant_long(glib_ce_optionarg, "INT64", sizeof("INT64")-1, G_OPTION_ARG_INT64 TSRMLS_CC);

	INIT_NS_CLASS_ENTRY(optionflag_ce, GLIB_NAMESPACE, "OptionFlag", NULL);
	glib_ce_optionflag = zend_register_internal_class(&optionflag_ce TSRMLS_CC);
	glib_ce_optionflag->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS | ZEND_ACC_FINAL_CLASS;
	
	zend_declare_class_constant_long(glib_ce_optionflag, "HIDDEN", sizeof("HIDDEN")-1, G_OPTION_FLAG_HIDDEN TSRMLS_CC);
	zend_declare_class_constant_long(glib_ce_optionflag, "IN_MAIN", sizeof("IN_MAIN")-1, G_OPTION_FLAG_IN_MAIN TSRMLS_CC);
	zend_declare_class_constant_long(glib_ce_optionflag, "REVERSE", sizeof("REVERSE")-1, G_OPTION_FLAG_REVERSE TSRMLS_CC);
	zend_declare_class_constant_long(glib_ce_optionflag, "NO_ARG", sizeof("NO_ARG")-1, G_OPTION_FLAG_NO_ARG TSRMLS_CC);
	zend_declare_class_constant_long(glib_ce_optionflag, "FILENAME", sizeof("FILENAME")-1, G_OPTION_FLAG_FILENAME TSRMLS_CC);
	zend_declare_class_constant_long(glib_ce_optionflag, "OPTIONAL_ARG", sizeof("OPTIONAL_ARG")-1, G_OPTION_FLAG_OPTIONAL_ARG TSRMLS_CC);
	zend_declare_class_constant_long(glib_ce_optionflag, "NOALIAS", sizeof("NOALIAS")-1, G_OPTION_FLAG_NOALIAS TSRMLS_CC);

	INIT_NS_CLASS_ENTRY(optionentry_ce, GLIB_NAMESPACE, "OptionEntry", glib_optionentry_methods);
	glib_ce_optionentry = zend_register_internal_class(&optionentry_ce TSRMLS_CC);
	glib_ce_optionentry->create_object = glib_optionentry_object_new;

	INIT_NS_CLASS_ENTRY(optioncontext_ce, GLIB_NAMESPACE, "OptionContext", glib_optioncontext_methods);
	glib_ce_optioncontext = zend_register_internal_class(&optioncontext_ce TSRMLS_CC);
	glib_ce_optioncontext->create_object = glib_optioncontext_object_new;

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
