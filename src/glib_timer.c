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

/* $Id: glib_timer.c 10 2009-04-29 16:30:59Z auroraeosrose $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_glib.h"

zend_class_entry *glib_ce_timer;

/* for extended classes, make sure internal object exists properly */
static inline glib_timer_object* glib_timer_object_get(zval *zobj TSRMLS_DC)
{
	glib_timer_object *pobj = zend_object_store_get_object(zobj TSRMLS_CC);
	if (pobj->timer == NULL) {
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Internal object missing in %s class, you must call parent::__construct in extended classes", Z_OBJCE_P(zobj)->name);
	}
	return pobj;
}

/* {{{ glib_timer_free_storage
       calls destroy on the GTimer */
void glib_timer_free_storage(glib_timer_object *intern TSRMLS_DC)
{
	if(intern->timer) {
		g_timer_destroy(intern->timer);
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

/* }}} */

/* {{{ glib_timer_object_new
       sets up the glib_timer_object struct and other internal class junk */
zend_object_value glib_timer_object_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	glib_timer_object *object;
	zval *tmp;

	object = emalloc(sizeof(glib_timer_object));
	object->std.ce = ce;
	object->std.guards = NULL;
	object->timer = NULL;
	object->active = FALSE;

	ALLOC_HASHTABLE(object->std.properties);
	zend_hash_init(object->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
	zend_hash_copy(object->std.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

	retval.handle = zend_objects_store_put(object, (zend_objects_store_dtor_t)zend_objects_destroy_object, (zend_objects_free_object_storage_t) glib_timer_free_storage, NULL TSRMLS_CC);
	retval.handlers = zend_get_std_object_handlers();
	return retval;
}
/* }}} */

/* {{{ proto void \Glib\Timer->__construct()
        Creates a new timer and implicitly calls start on it, so you don't have to call start
   */
PHP_METHOD(Glib_Timer, __construct)
{
	glib_timer_object *timer_object = (glib_timer_object *)zend_objects_get_address(getThis() TSRMLS_CC);

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	timer_object->timer = g_timer_new();
	timer_object->active = TRUE;
}
/* }}} */

/* {{{ proto void \Glib\Timer->start()
        Starts or restarts the timer - identical to reset call
		If used after stop call the total time will be started over, not added to
   */
PHP_METHOD(Glib_Timer, start)
{
	glib_timer_object *timer_object = (glib_timer_object *)glib_timer_object_get(getThis() TSRMLS_CC);

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	g_timer_start(timer_object->timer);
	timer_object->active = TRUE;
}
/* }}} */

/* {{{ proto void \Glib\Timer->stop()
         stops the timer, already elapsed time will not be erased
   */
PHP_METHOD(Glib_Timer, stop)
{
	glib_timer_object *timer_object = (glib_timer_object *)glib_timer_object_get(getThis() TSRMLS_CC);

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	g_timer_stop(timer_object->timer);
	timer_object->active = FALSE;
}
/* }}} */

/* {{{ proto void \Glib\Timer->continue()
        continues timing after a stop call, MUST have stop called before this can be called
		if called without a stop call first a warning is thrown
   */
PHP_METHOD(Glib_Timer, continue)
{
	glib_timer_object *timer_object = (glib_timer_object *)glib_timer_object_get(getThis() TSRMLS_CC);

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	if (timer_object->active == TRUE) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Cannot continue a Timer that has not been stopped");
		return;
	}
	g_timer_continue(timer_object->timer);
	timer_object->active = TRUE;
}
/* }}} */

/* {{{ proto void \Glib\Timer->reset()
         identical to start, sets the timer total back to zero
   */
PHP_METHOD(Glib_Timer, reset)
{
	glib_timer_object *timer_object = (glib_timer_object *)glib_timer_object_get(getThis() TSRMLS_CC);

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	g_timer_reset(timer_object->timer);
	timer_object->active = TRUE;
}
/* }}} */

/* {{{ proto float \Glib\Timer->elapsed()
         returns the total elapsed time from the last start/reset call
   */
PHP_METHOD(Glib_Timer, elapsed)
{
	glib_timer_object *timer_object = (glib_timer_object *)glib_timer_object_get(getThis() TSRMLS_CC);

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	RETURN_DOUBLE(g_timer_elapsed(timer_object->timer, NULL));
}
/* }}} */

/* {{{ glib_timer_methods[] */
const zend_function_entry glib_timer_methods[] = {
	PHP_ME(Glib_Timer, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Glib_Timer, start, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Glib_Timer, stop, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Glib_Timer, continue, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Glib_Timer, reset, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Glib_Timer, elapsed, NULL, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(glib_timer)
{
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, GLIB_NAMESPACE, "Timer", glib_timer_methods);
	glib_ce_timer = zend_register_internal_class(&ce TSRMLS_CC);
	glib_ce_timer->create_object  = glib_timer_object_new;

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
