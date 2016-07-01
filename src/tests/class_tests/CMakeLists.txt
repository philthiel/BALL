#new_header#


project("BALL_class_tests")


# --------------------------------------------------------------------------
# Configure testConfig.h header file
#
configure_file(${PROJECT_SOURCE_DIR}/cmake/templates/testConfig.h.in ${PROJECT_BINARY_DIR}/include/testConfig.h)

# Include header directories
include_directories(${PROJECT_BINARY_DIR}/include)


# --------------------------------------------------------------------------
# Class tests for ball_core library classes
#
add_subdirectory(ball_core EXCLUDE_FROM_ALL)


# --------------------------------------------------------------------------
# Class tests for ball_view library classes
#
if(BALL_BUILD_VIEW)
	add_subdirectory(ball_view EXCLUDE_FROM_ALL)
endif()










