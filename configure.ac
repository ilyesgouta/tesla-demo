AC_PREREQ([2.63])
AM_INIT_AUTOMAKE([1.11])

AC_INIT([tesla-demo],
        [1.0],
        [http://www.pouet.net/prod.php?which=33],
        [tesla-demo],
        [http://www.pouet.net/prod.php?which=33])

AC_CONFIG_HEADERS([config.h])

# Checks for header files.
AC_HEADER_STDC

# required versions for dependencies
m4_define([glib_req_version],           [2.26.0])

AC_SUBST([GLIB_REQ_VERSION], [glib_req_version])

AM_PATH_GLIB_2_0([glib_req_version],
                 [],
                 [AC_MSG_ERROR([glib-2.0 is required])],
                 [gobject])

PKG_CHECK_EXISTS([gl],
               [BACKEND_PC_FILES="$BACKEND_PC_FILES gl"],
               # if a pkg-config file isn't found just add -lGL
               # and hope for the best.
               [FLAVOUR_LIBS="$FLAVOUR_LIBS -lGL"])

PKG_CHECK_EXISTS([libdrm],
               [
                 AC_DEFINE([HAVE_DRM], [1], [Have libdrm support])
                 BACKEND_PC_FILES="$BACKEND_PC_FILES libdrm"
               ],
               [])

AC_DEFINE([HAVE_TESLA_GLX], [1], [Have the GLX backend])

AC_CHECK_HEADERS([GL/glx.h],
                 [],
                 [AC_MSG_ERROR([Unable to locate required GLX headers])])

AC_CHECK_LIB(GL, [glXCreateContext],
             [HAVE_LIBGLX=yes],
             [AC_MSG_ERROR([Required GLX library not found])])

# base X11 includes and libraries
AC_MSG_CHECKING([for X11])

# start with pkg-config
PKG_CHECK_EXISTS([x11], [have_x11=yes], [have_x11=no])
AS_IF([test "x$have_x11" = "xyes"],
      [
        X11_PC_FILES="x11"

        # we actually need to ask for CFLAGS and LIBS
        X11_CFLAGS=`$PKG_CONFIG --cflags $X11_PC_FILES`
        X11_LIBS=`$PKG_CONFIG --libs $X11_PC_FILES`

        AC_MSG_RESULT([found])
      ])


AC_CONFIG_FILES([
	Makefile
])
