cmake_minimum_required(VERSION 3.18)

project(
  litejson
  VERSION 0.2.1.1
  DESCRIPTION "Lite JSON loader"
  HOMEPAGE_URL "https://gitverse.ru/DimaO87/liblitejson"
  LANGUAGES CXX
)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# Compile options
set(CMAKE_CXX_STANDARD 17)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-pedantic)
endif()

# Sources and headers
set(SOURCES
  src/litejson.cpp
	src/jsonvalue.cpp
  src/jsonarrayvalue.cpp
  src/jsonbooleanvalue.cpp
  src/jsonnumbervalue.cpp
  src/jsonobjectvalue.cpp
  src/jsonstringvalue.cpp
)

set(INTERFACE_HEADERS
  include/litejson/litejson.h
	include/litejson/jsonvalue.h
)

set(HEADERS
  src/jsonarrayvalue.cpp
  src/jsonbooleanvalue.cpp
  src/jsonnumbervalue.cpp
  src/jsonobjectvalue.cpp
  src/jsonstringvalue.cpp
)

# Library
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

add_library(
  litejson SHARED
  ${SOURCES}
)
target_include_directories(
  litejson PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
  $<INSTALL_INTERFACE:include/litejson>
)
set_target_properties(litejson PROPERTIES
  PUBLIC_HEADER "${INTERFACE_HEADERS}"
)

# Configuration
set(INCLUDE_INSTALL_DIR include/ CACHE PATH "Headers install directory")
set(LIB_INSTALL_DIR lib/ CACHE PATH "Libraries install directory")
set(SYSCONFIG_INSTALL_DIR etc/litejson/ CACHE PATH "System Configuration install directory")
configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/litejsonConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/litejsonConfig.cmake
  INSTALL_DESTINATION ${LIB_INSTALL_DIR}/litejson/cmake
  PATH_VARS INCLUDE_INSTALL_DIR SYSCONFIG_INSTALL_DIR
)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/litejsonConfigVersion.cmake
  VERSION 0.2.0
  COMPATIBILITY SameMajorVersion
)

# Install
install(
  TARGETS litejson
  EXPORT litejson-targets
  PUBLIC_HEADER DESTINATION include/litejson
)

install(
  FILES
  ${CMAKE_CURRENT_BINARY_DIR}/litejsonConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/litejsonConfigVersion.cmake
  DESTINATION ${LIB_INSTALL_DIR}/cmake/litejson
)

# Tests
add_subdirectory(tests)

# Config file
set(PACKAGE ${PROJECT_NAME})
set(VERSION ${PROJECT_VERSION})
configure_file(
  ${CMAKE_SOURCE_DIR}/config.h.in
  ${CMAKE_BINARY_DIR}/config.h
  @ONLY
)
target_compile_definitions(
  litejson PRIVATE
  "-DHAVE_CONFIG_H"
)

# Documentation
find_program(
  MAKEINFO
  makeinfo
)

if(MAKEINFO)
  add_subdirectory(doc)
  install(
    FILES ${CMAKE_BINARY_DIR}/doc/litejson.pdf
    TYPE DOC
  )
else()
  message(WARNING "makeinfo not found. Skip document building.")
endif()
