ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = liblitejson.la
liblitejson_la_SOURCES = src/litejson.cpp \
	src/json_value.cpp
liblitejson_la_CXXFLAGS = -I$(srcdir)/include -pedantic

include_HERADERS = include/litejson.h \
	include/json_value.h

LIBTOOL_DEPS = @LIBTOOL_DEPS@
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status libtool

TESTS = tests/t_test1 \
	tests/t_test2

XFAIL_TESTS = tests/t_test2

check_PROGRAMS = tests/test1

tests_test1_SOURCES = tests/test1.cpp
tests_test1_CXXFLAGS = -I$(srcdir)/include
tests_test1_LDADD = -L$(builddir) liblitejson.la
