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

PKG_CHECK_MODULES(EGL, egl, [have_egl=yes], [have_egl=no])
AC_SUBST([EGL_CFLAGS])
AC_SUBST([EGL_LIBS])

PKG_CHECK_MODULES(GLESV1_CM, glesv1_cm, [have_gles11=yes], [have_gles11=no])
AC_SUBST([GLESV1_CM_CFLAGS])
AC_SUBST([GLESV1_CM_LIBS])

PKG_CHECK_MODULES(X11, x11, [have_x11=yes], [have_x11=no])
AC_SUBST([X11_CFLAGS])
AC_SUBST([X11_LIBS])

PKG_CHECK_MODULES(libmpg123, libmpg123, [have_libmpg123=yes], [have_libmpg123=no])
AC_SUBST([libmpg123_CFLAGS])
AC_SUBST([libmpg123_LIBS])

PKG_CHECK_MODULES(alsa, alsa, [have_alsa=yes], [have_alsa=no])
AC_SUBST([alsa_CFLAGS])
AC_SUBST([alsa_LIBS])

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
