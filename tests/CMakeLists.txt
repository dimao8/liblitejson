enable_testing()

set(TESTS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TESTS_BIN_DIR ${CMAKE_CURRENT_BINARY_DIR})

# validate
add_executable(
  validate
  ${TESTS_SRC_DIR}/validate.cpp
)
target_include_directories(validate PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(
  validate PRIVATE
  $<TARGET_FILE:litejson>
)

# export_compare
add_executable(
  export_compare
  ${TESTS_SRC_DIR}/export_compare.cpp
)
target_include_directories(export_compare PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(
  export_compare PRIVATE
  $<TARGET_FILE:litejson>
)

# export_compare
add_executable(
  create
  ${TESTS_SRC_DIR}/create.cpp
)
target_include_directories(create PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(
  create PRIVATE
  $<TARGET_FILE:litejson>
)

# t_array test
add_test(
  NAME t_array
  COMMAND $<TARGET_FILE:validate> ${TESTS_SRC_DIR}/array.json
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)

# t_null test
add_test(
  NAME t_null
  COMMAND $<TARGET_FILE:validate> ${TESTS_SRC_DIR}/null.json
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)

# t_number test
add_test(
  NAME t_number
  COMMAND $<TARGET_FILE:validate> ${TESTS_SRC_DIR}/number.json
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)

# t_object test
add_test(
  NAME t_object
  COMMAND $<TARGET_FILE:validate> ${TESTS_SRC_DIR}/object.json
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)

# t_string test
add_test(
  NAME t_string
  COMMAND $<TARGET_FILE:validate> ${TESTS_SRC_DIR}/string.json
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)

# t_true test
add_test(
  NAME t_true
  COMMAND $<TARGET_FILE:validate> ${TESTS_SRC_DIR}/true.json
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)

# t_string_invalid test
add_test(
  NAME t_string_invalid
  COMMAND $<TARGET_FILE:validate> ${TESTS_SRC_DIR}/string_invalid.json
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)
set_property(
  TEST t_string_invalid
  PROPERTY WILL_FAIL True
)

# t_number_invalid1 test
add_test(
  NAME t_number_invalid1
  COMMAND $<TARGET_FILE:validate> ${TESTS_SRC_DIR}/number_invalid1.json
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)
set_property(
  TEST t_number_invalid1
  PROPERTY WILL_FAIL True
)

# t_number_invalid2 test
add_test(
  NAME t_number_invalid2
  COMMAND $<TARGET_FILE:validate> ${TESTS_SRC_DIR}/number_invalid2.json
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)
set_property(
  TEST t_number_invalid2
  PROPERTY WILL_FAIL True
)

# t_number_invalid3 test
add_test(
  NAME t_number_invalid3
  COMMAND $<TARGET_FILE:validate> ${TESTS_SRC_DIR}/number_invalid3.json
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)
set_property(
  TEST t_number_invalid3
  PROPERTY WILL_FAIL True
)

# t_number_invalid4 test
add_test(
  NAME t_number_invalid4
  COMMAND $<TARGET_FILE:validate> ${TESTS_SRC_DIR}/number_invalid4.json
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)
set_property(
  TEST t_number_invalid4
  PROPERTY WILL_FAIL True
)

# t_number_invalid5 test
add_test(
  NAME t_number_invalid5
  COMMAND $<TARGET_FILE:validate> ${TESTS_SRC_DIR}/number_invalid5.json
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)
set_property(
  TEST t_number_invalid5
  PROPERTY WILL_FAIL True
)

# t_number_invalid6 test
add_test(
  NAME t_number_invalid6
  COMMAND $<TARGET_FILE:validate> ${TESTS_SRC_DIR}/number_invalid6.json
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)
set_property(
  TEST t_number_invalid6
  PROPERTY WILL_FAIL True
)

# t_literal_invalid test
add_test(
  NAME t_literal_invalid
  COMMAND $<TARGET_FILE:validate> ${TESTS_SRC_DIR}/literal_invalid.json
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)
set_property(
  TEST t_literal_invalid
  PROPERTY WILL_FAIL True
)

# t_array_invalid test
add_test(
  NAME t_array_invalid
  COMMAND $<TARGET_FILE:validate> ${TESTS_SRC_DIR}/array_invalid.json
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)
set_property(
  TEST t_array_invalid
  PROPERTY WILL_FAIL True
)

# t_object_invalid1 test
add_test(
  NAME t_object_invalid1
  COMMAND $<TARGET_FILE:validate> ${TESTS_SRC_DIR}/object_invalid1.json
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)
set_property(
  TEST t_object_invalid1
  PROPERTY WILL_FAIL True
)

# t_object_invalid2 test
add_test(
  NAME t_object_invalid2
  COMMAND $<TARGET_FILE:validate> ${TESTS_SRC_DIR}/object_invalid2.json
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)
set_property(
  TEST t_object_invalid2
  PROPERTY WILL_FAIL True
)

# t_object_invalid3 test
add_test(
  NAME t_object_invalid3
  COMMAND $<TARGET_FILE:validate> ${TESTS_SRC_DIR}/object_invalid3.json
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)
set_property(
  TEST t_object_invalid3
  PROPERTY WILL_FAIL True
)

# t_object_invalid4 test
add_test(
  NAME t_object_invalid4
  COMMAND $<TARGET_FILE:validate> ${TESTS_SRC_DIR}/object_invalid4.json
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)
set_property(
  TEST t_object_invalid4
  PROPERTY WILL_FAIL True
)

# t_compare test
add_test(
  NAME t_compare
  COMMAND $<TARGET_FILE:export_compare> --compare --output=result.json ${TESTS_SRC_DIR}/object.json
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)

# t_create test
add_test(
  NAME t_create
  COMMAND $<TARGET_FILE:create> -o ${TESTS_BIN_DIR}/result.json
  WORKING_DIRECTORY ${TESTS_BIN_DIR}
)

add_custom_target(
  check
  COMMAND ${CMAKE_CTEST_COMMAND}
  DEPENDS validate export_compare create
)
