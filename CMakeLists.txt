#new_header#


project("BALL_master")

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)


# --------------------------------------------------------------------------
# BALL Version
#
set(BALL_PACKAGE_VERSION_MAJOR "2")
set(BALL_PACKAGE_VERSION_MINOR "0")
set(BALL_PACKAGE_VERSION_PATCH "0")

set(BALL_PACKAGE_VERSION ${BALL_PACKAGE_VERSION_MAJOR}.${BALL_PACKAGE_VERSION_MINOR}.${BALL_PACKAGE_VERSION_PATCH} CACHE INTERNAL "BALL VERSION" FORCE)


# --------------------------------------------------------------------------
# Add CMake module and script search paths
#
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/modules)

# Load BALL CMake functions
include(ball_functions)


# --------------------------------------------------------------------------
# Set default build type
#
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
	message(STATUS "Set default build type to 'Release'")
endif()


# --------------------------------------------------------------------------
# Build shared libraries
#
set(BUILD_SHARED_LIBS TRUE)


# --------------------------------------------------------------------------
# Build options
#
OPTION(BALL_BUILD_PYTHON "Build BALL python bindings" OFF)
OPTION(BALL_BUILD_VIEW "Build BALL's VIEW library required for visualization and graphical user interfaces" OFF)
OPTION(BALL_USE_CUDA "Use CUDA tools to build the project" OFF)


# --------------------------------------------------------------------------
# Add the BALL subprojects
#
add_subdirectory(src)























