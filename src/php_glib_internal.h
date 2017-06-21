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

/* We already need a compat header for php 7 stuff :( */
#include "compat.h"

/* Glib Classes to register */
PHP_MINIT_FUNCTION(glib_main_context);
PHP_MINIT_FUNCTION(glib_timer);

#endif /* PHP_GLIB_INTERNAL_H */
