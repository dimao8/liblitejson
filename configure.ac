#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([liblitejson], [0.2.0.1dev], [dimao8@yandex.ru])
AC_CONFIG_SRCDIR([src/litejson.cpp])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([1.10 foreign subdir-objects silent-rules])
AM_SILENT_RULES([yes])
AC_CONFIG_MACRO_DIR([m4])
AC_LANG([C++])

LT_PREREQ([2.4.6])
LT_INIT([dlopen win32-dll])
LT_LANG([C++])
AC_SUBST([LIBTOOL_DEPS])

CXXFLAGS="-std=gnu++17"
AC_PROG_CXX([clang++ llwm-g++ g++])

AC_ARG_ENABLE([debug],
              [
                AS_HELP_STRING([--enable-debug], [Set to build debug version])
              ])

AS_IF([test "x$enable_debug" = "xyes"],
      [CXXFLAGS+=" -O0 -g -DDEBUG"],
      [CXXFLAGS+=" -O2 -DNDEBUG"])

AC_CONFIG_LINKS([tests/array.json:tests/array.json
  tests/error.json:tests/error.json
  tests/false.json:tests/false.json
  tests/null.json:tests/null.json
  tests/number.json:tests/number.json
  tests/object.json:tests/object.json
  tests/string.json:tests/string.json
  tests/true.json:tests/true.json
  tests/string_invalid.json:tests/string_invalid.json
  tests/number_invalid.json:tests/number_invalid.json
  tests/literal_invalid.json:tests/literal_invalid.json])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
