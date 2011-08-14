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

CXXFLAGS=-std=c++0x

PKG_CHECK_EXISTS([gl],
               [BACKEND_PC_FILES="$BACKEND_PC_FILES gl"],
               # if a pkg-config file isn't found just add -lGL
               # and hope for the best.
               [FLAVOUR_LIBS="$FLAVOUR_LIBS -lGL"])

AC_SUBST([GL_CFLAGS])
AC_SUBST([GL_LIBS])

AC_CHECK_HEADERS([GL/glx.h],
                 [],
                 [AC_MSG_ERROR([Unable to locate required GLX headers])])

AC_CHECK_LIB(GL, [glXCreateContext],
             [HAVE_LIBGLX=yes],
             [AC_MSG_ERROR([Required GLX library not found])])

AC_MSG_CHECKING([for X11])
PKG_CHECK_EXISTS([x11], [have_x11=yes], [have_x11=no])

AC_SUBST([X11_CFLAGS])
AC_SUBST([X11_LIBS])

AC_CONFIG_FILES([
	Makefile
])

AC_OUTPUT
