#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([liblitejson], [0.1.0.0], [dimao8@yandex.ru])
AC_CONFIG_SRCDIR([src/litejson.cpp])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([1.10 foreign subdir-objects silent-rules])

LT_PREREQ([2.4.6])
LT_INIT([dlopen win32-dll])
AC_SUBST([LIBTOOL_DEPS])

CXXFLAGS="-std=gnu++11 "
AC_PROG_CXX([clang++ llwm-g++ g++])

AC_ARG_ENABLE([debug],
              [
                AS_HELP_STRING([--enable-debug], [Set to build debug version])
              ])

AS_IF([test "x$enable_debug" = "xyes"],
      [CXXFLAGS+="-O0 -g -DDEBUG"],
      [CXXFLAGS+="-O2 -DNDEBUG"])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
