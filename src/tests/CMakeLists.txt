#new_header#


project("BALL_tests")


# --------------------------------------------------------------------------
# Test data path
#
set(TEST_DATA_PATH ${PROJECT_SOURCE_DIR}/data/)


# --------------------------------------------------------------------------
# BALL class tests
#
add_subdirectory(class_tests)
