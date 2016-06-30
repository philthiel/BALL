#new_header#


project("BALL_tests")


# --------------------------------------------------------------------------
# Configure root path for all test data
#
configure_file(${PROJECT_SOURCE_DIR}/cmake/templates/testConfig.h.in ${PROJECT_BINARY_DIR}/include/testConfig.h)

# Include header directories
include_directories(${PROJECT_BINARY_DIR}/include)


# --------------------------------------------------------------------------
# BALL class tests
#
add_subdirectory(class_tests)
