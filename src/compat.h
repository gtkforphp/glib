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

#ifndef PHP_GLIB_COMPAT_H
#define PHP_GLIB_COMPAT_H

#include <php.h>

/**
 * These compat macros are designed for OLD php versions
 * So our extension uses the new calls/definitions but still
 * compiles and runs on older versions
 */

/**
 * Macros before 7.2 were messed up for return type info
 */

#if PHP_VERSION_ID < 70200

#undef ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX
#undef ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO

#undef ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX
#undef ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO

#define ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(name, return_reference, required_num_args, class_name, allow_null) \
	static const zend_internal_arg_info name[] = { \
		{ (const char*)(zend_uintptr_t)(required_num_args), class_name, IS_OBJECT, return_reference, allow_null, 0 },
#define ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(name, class_name, allow_null) \
	ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(name, 0, -1, class_name, allow_null)

#define ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(name, return_reference, required_num_args, type, allow_null) \
	static const zend_internal_arg_info name[] = { \
	   	{ (const char*)(zend_uintptr_t)(required_num_args), NULL, type, return_reference, allow_null, 0 },
#define ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(name, type, allow_null) \
	ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(name, 0, -1, type, allow_null)

#else

/**
 * there's currently a PHP 7.2 bug in this macro
 * see https://github.com/php/php-src/pull/2523
 */
#undef ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO

#define ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(name, class_name, allow_null) \
	ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(name, 0, -1, class_name, allow_null)
#endif

/**
 * zend_parse_parameters_none_throw didn't exist before 7.2
 */
#if PHP_VERSION_ID < 70200
#define zend_parse_parameters_none_throw() \
	(EXPECTED(ZEND_NUM_ARGS() == 0) ? SUCCESS : zend_parse_parameters_throw(ZEND_NUM_ARGS(), ""))
#endif

/**
 * PHP 7.0 has no void return types
 * This effectively turns anything return typehinted as "void"
 * to return typehinted as "null" in 7.0
 */
#ifndef IS_VOID
#define IS_VOID IS_NULL
#endif

#endif /* PHP_GLIB_COMPAT_H */
