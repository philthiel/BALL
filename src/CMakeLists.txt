#new_header#


project("BALL")


# --------------------------------------------------------------------------
# - Global project configurations and system conpatibility checks
# - Find and configure external dependencies
#
include(ball_config)
include(ball_config_external)


# --------------------------------------------------------------------------
# Configure project files
#
configure_file(${PROJECT_SOURCE_DIR}/cmake/templates/config.h.in ${PROJECT_BINARY_DIR}/include/BALL/config.h)
configure_file(${PROJECT_SOURCE_DIR}/cmake/templates/version.h.in ${PROJECT_BINARY_DIR}/include/BALL/version.h)

# Include header directories
include_directories(${PROJECT_BINARY_DIR}/include)


# --------------------------------------------------------------------------
# BALL core library
#
add_subdirectory(ball_core)


# --------------------------------------------------------------------------
# BALL command line tools
#
#add_subdirectory(BALLTools)


# --------------------------------------------------------------------------
# BALL view library and BALLView application
#
if(BALL_BUILD_VIEW)
	add_subdirectory(ball_view)
	add_subdirectory(BALLView)
endif()


# --------------------------------------------------------------------------
# BALL python bindings
#
if(BALL_BUILD_PYTHON)
	add_subdirectory(ball_python)
endif()















