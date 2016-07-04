#new_header#


project("ball_core_class_tests")


# --------------------------------------------------------------------------
# Set test output directory
#
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/TEST)


# --------------------------------------------------------------------------
# Collect header files
#
set(HEADER_FILES_class_test_core CACHE INTERNAL "This variable should hold all BALL core test header files at the end of the config step")
BALL_MACRO_collect_headers(${PROJECT_SOURCE_DIR} HEADER_FILES_class_test_core)
set_property(SOURCE ${HEADER_FILES_class_test_core} APPEND PROPERTY HEADER_FILE_ONLY TRUE)


# --------------------------------------------------------------------------
# Necessary include directories from upstream targets
#
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${ball_core_INCLUDE_DIRECTORIES})


# --------------------------------------------------------------------------
# Include lists of test sources and add test groups as targets
#
if(CMAKE_COMPILER_IS_INTELCXX OR CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG)
	BALL_MACRO_cxx_flags_set("-O0")
	BALL_MACRO_add_class_tests(ball_core)
	BALL_MACRO_cxx_flags_reset()
else()
	BALL_MACRO_add_class_tests(ball_core)
endif()


# --------------------------------------------------------------------------
# Some tests need special treatment (e.g. increased timeout)
#
set_tests_properties(AssignBondOrderProcessor_test PROPERTIES TIMEOUT 7200)
set_tests_properties(ScoringFunction_test PROPERTIES TIMEOUT 7200)


# --------------------------------------------------------------------------
# Add global ball_core test target
#
add_custom_target(ball_core_tests)
add_dependencies(ball_core_tests ${ALL_TESTS})

