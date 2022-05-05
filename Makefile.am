ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = liblitejson.la
liblitejson_la_SOURCES = src/litejson.cpp \
	src/json_value.cpp \
	src/json_object.cpp
	src/int_json_object.cpp \
	src/int_json_object.h \
	src/int_json_array.cpp \
	src/int_json_array.h \
	src/json_array.cpp
liblitejson_la_CXXFLAGS = -I$(srcdir)/include -pedantic

include_HERADERS = include/litejson.h \
	include/json_value.h \
	include/json_object.h \
	include/json_array.h

LIBTOOL_DEPS = @LIBTOOL_DEPS@
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status libtool
