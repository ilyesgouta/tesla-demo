AC_PREREQ([2.63])

#http://www.pouet.net/prod.php?which=33

AC_INIT([tesla-demo],
        [1.0],
        [tesla-demo],
        [tesla-demo],
        [tesla-demo])

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])

AC_PROG_LIBTOOL
AC_PROG_CXX
AM_PROG_CC_C_O

AM_INIT_AUTOMAKE([1.11])

# Checks for header files.
AC_HEADER_STDC

EGL_REQUIRED_VERSION=2.1
PKG_CHECK_MODULES([EGL], [egl >= $EGL_REQUIRED_VERSION])
AC_SUBST([EGL_CFLAGS])
AC_SUBST([EGL_LIBS])

AC_CHECK_HEADERS([GLES/gl.h], [], AC_MSG_ERROR([OpenGL ES 1.1 headers not found]))

EGL_LIBS="$EGL_LIBS -lGLESv1_CM"

PKG_CHECK_MODULES(directfb, directfb, [have_directfb=yes], [have_directfb=no])
AC_SUBST([directfb_CFLAGS])
AC_SUBST([directfb_LIBS])

PKG_CHECK_MODULES(libmpg123, libmpg123, [have_libmpg123=yes], [have_libmpg123=no])
AC_SUBST([libmpg123_CFLAGS])
AC_SUBST([libmpg123_LIBS])

PKG_CHECK_MODULES(alsa, alsa, [have_alsa=yes], [have_alsa=no])
AC_SUBST([alsa_CFLAGS])
AC_SUBST([alsa_LIBS])

PKG_CHECK_MODULES(lib3ds, lib3ds, [have_lib3ds=yes], [have_lib3ds=no])
AC_SUBST([lib3ds_CFLAGS])
AC_SUBST([lib3ds_LIBS])

PKG_CHECK_MODULES(libpng, libpng, [have_libpng=yes], [have_libpng=no])
AC_SUBST([libpng_CFLAGS])
AC_SUBST([libpng_LIBS])

AC_CHECK_LIB(jpeg, jpeg_destroy_decompress,
                   have_libjpeg=yes, have_libjpeg=no
                   AC_MSG_ERROR([JPEG library (libjpeg) not found]))
if test "$have_libjpeg" = yes; then
   AC_MSG_CHECKING([for jpeglib])
   AC_TRY_CPP(
[#include <stdio.h>
#undef PACKAGE
#undef VERSION
#undef HAVE_STDLIB_H
#include <jpeglib.h>],
         have_libjpeg=yes,
         have_libjpeg=no)
   AC_MSG_RESULT($jpeg_ok)
   if test "$have_libjpeg" = yes; then
      jpeg_LIBS="-ljpeg"
   else
      AC_MSG_ERROR([JPEG library (libjpeg) not found])
   fi
fi
AC_SUBST([jpeg_LIBS])

AC_CONFIG_FILES([
	Makefile
])

AC_OUTPUT
