dnl
dnl Glib wrapper
dnl

PHP_ARG_WITH(glib, for glib support,
[  --with-glib             Enable glib support], yes)

if test "$PHP_GLIB" != "no"; then

  PHP_SUBST(GLIB_SHARED_LIBADD)
  AC_DEFINE(HAVE_GLIB, 1, [ ])

  PHP_NEW_EXTENSION(glib, \
    src/glib.c \
    src/timer.c \
    src/main_context.c \
  , $ext_shared)

  EXT_GLIB_HEADERS="php_glib_api.h"

  ifdef([PHP_INSTALL_HEADERS], [
    PHP_INSTALL_HEADERS(ext/glib, $EXT_GLIB_HEADERS)
  ])

  AC_MSG_CHECKING(for pkg-config)

  if test ! -f "$PKG_CONFIG"; then
    PKG_CONFIG=`which pkg-config`
  fi

  if test -f "$PKG_CONFIG"; then
    AC_MSG_RESULT(found)
    AC_MSG_CHECKING(for glib)
    
    if $PKG_CONFIG --exists glib-2.0; then
        glib_version_full=`$PKG_CONFIG --modversion glib-2.0`
        AC_MSG_RESULT([found $glib_version_full])
        GLIB_LIBS="$LDFLAGS `$PKG_CONFIG --libs glib-2.0`"
        GLIB_INCS="$CFLAGS `$PKG_CONFIG --cflags-only-I glib-2.0`"
        PHP_EVAL_INCLINE($GLIB_INCS)
        PHP_EVAL_LIBLINE($GLIB_LIBS, GLIB_SHARED_LIBADD)
        AC_DEFINE(HAVE_GLIB, 1, [whther glib exists in the system])
    else
        AC_MSG_RESULT(not found)
        AC_MSG_ERROR(Ooops ! no glib detected in the system)
    fi
  else
    AC_MSG_RESULT(not found)
    AC_MSG_ERROR(Ooops ! no pkg-config found .... )
  fi
fi

