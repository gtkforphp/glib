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

#ifndef PHP_GLIB_EXT_H
#define PHP_GLIB_EXT_H

#include <php.h>

extern zend_module_entry glib_module_entry;
#define phpext_glib_ptr &glib_module_entry

#define PHP_GLIB_VERSION "0.1.0-dev"
#define GLIB_NAMESPACE "Glib"

#endif /* PHP_GLIB_EXT_H */
