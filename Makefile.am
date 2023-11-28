ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = liblitejson.la
liblitejson_la_SOURCES = src/litejson.cpp \
	src/jsonvalue.cpp
liblitejson_la_CXXFLAGS = -I$(srcdir)/include -pedantic

include_HEADERS = include/litejson.h \
	include/jsonvalue.h

LIBTOOL_DEPS = @LIBTOOL_DEPS@
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status libtool

dist_noinst_DATA = tests/t_array \
	tests/t_false \
	tests/t_null \
	tests/t_number \
	tests/t_object \
	tests/t_string \
	tests/t_true \
	tests/t_string_invalid \
	tests/t_number_invalid \
	tests/t_literal_invalid \
	tests/t_array_invalid \
	tests/t_object_invalid \
	autogen.sh

TESTS = tests/t_array \
	tests/t_false \
	tests/t_null \
	tests/t_number \
	tests/t_object \
	tests/t_string \
	tests/t_true \
	tests/t_string_invalid \
	tests/t_number_invalid \
	tests/t_literal_invalid \
	tests/t_array_invalid \
	tests/t_object_invalid

XFAIL_TESTS = tests/t_string_invalid \
	tests/t_number_invalid \
	tests/t_literal_invalid \
	tests/t_array_invalid \
	tests/t_object_invalid

check_PROGRAMS = tests/validate

tests_validate_SOURCES = tests/validate.cpp
tests_validate_CXXFLAGS = -I$(srcdir)/include
tests_validate_LDADD = -llitejson
