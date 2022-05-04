ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = liblitejson.la
liblitejson_la_SOURCES = src/litejson.cpp \
	src/json_value.cpp \
	src/json_object.cpp
	src/int_json_object.cpp \
	src/int_json_object.h
liblitejson_la_CXXFLAGS = -I$(srcdir)/include -pedantic

include_HERADERS = include/litejson.h \
	include/json_value.h \
	include/json_object.h

LIBTOOL_DEPS = @LIBTOOL_DEPS@
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status libtool
