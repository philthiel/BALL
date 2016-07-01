#new_header#


project("ball_core_class_tests")


enable_testing()


# --------------------------------------------------------------------------
# Set test output directory
#
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/TEST)


# --------------------------------------------------------------------------
# Necessary include directories from upstream targets
#
include_directories(${ball_core_INCLUDE_DIRECTORIES})


# --------------------------------------------------------------------------
# Include lists of test sources and add test groups as targets
#
include(source/sources.cmake)
BALL_MACRO_add_class_test_targets(tests_core_ ball_core)


# --------------------------------------------------------------------------
# Some tests need special treatment (e.g. increased timeout)
#
#set_tests_properties(
#	ScoringFunction_test
#	AssignBondOrderProcessor_test
#	PROPERTIES TIMEOUT 7200
#)


# --------------------------------------------------------------------------
# Add global ball_core test target
#
add_custom_target(ball_core_tests)
add_dependencies(ball_core_tests ${ALL_TESTS})




