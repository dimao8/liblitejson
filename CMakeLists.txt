cmake_minimum_required(VERSION 3.10)

project(
  liblitejson
  VERSION 0.2.0.5
  DESCRIPTION "Lite JSON loader"
  HOMEPAGE_URL "https://gitverse.ru/DimaO87/liblitejson"
  LANGUAGES CXX
)

# Compile options
set(CMAKE_CXX_STANDARD 17)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-pedantic)
endif()

# Sources and headers
set(SOURCES
  src/litejson.cpp
	src/jsonvalue.cpp
)

set(HEADERS
  include/litejson.h
	include/jsonvalue.h
)

# Library
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

add_library(
  litejson
  ${SOURCES}
  ${HEADERS}
)
target_include_directories(
  litejson PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_BINARY_DIR}
)
target_compile_definitions(
  litejson PRIVATE
  "-DHAVE_CONFIG_H"
)
# set_target_properties(
#   litejson PROPERTIES
#   PUBLIC_HEADER ${HEADERS}
# )

# Testing
option(DISABLE_TESTING "Disable test routine" OFF)
if(NOT DISABLE_TESTING)
  add_subdirectory(tests)
else()
  message(NOTICE "Testing is disabled. ``check'' is unavailable")
endif()

# Config file
set(PACKAGE ${PROJECT_NAME})
set(VERSION ${PROJECT_VERSION})
configure_file(
  ${CMAKE_SOURCE_DIR}/config.h.in
  ${CMAKE_BINARY_DIR}/config.h
  @ONLY
)

# Copy compile_commands.json
file(
  CREATE_LINK
  ${CMAKE_BINARY_DIR}/compile_commands.json
  ${CMAKE_SOURCE_DIR}/compile_commands.json
  COPY_ON_ERROR
  SYMBOLIC
)
