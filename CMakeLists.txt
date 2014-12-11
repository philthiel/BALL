# -----------------------------------------------------------------------------
#   BALL - Biochemical ALgorithms Library
#   A C++ framework for molecular modeling and structural bioinformatics.
# -----------------------------------------------------------------------------
#
# Copyright (C) The BALL Team:
#  - Eberhard Karls University, Tuebingen
#  - Saarland University, Saarbrücken
#
# This file is part of BALL.
#
# BALL is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published
# by the Free Software Foundation, either version 3 of the License,
# or (at your option) any later version.
#
# BALL is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with BALL. If not, see <http://www.gnu.org/licenses/>.
#
# -----------------------------------------------------------------------------
# $Maintainer: Philipp Thiel $
# $Authors: Philipp Thiel $
# -----------------------------------------------------------------------------


PROJECT("BALL")


###############################################################################
###    BALL version (setup manually)                                        ###
###############################################################################


SET(BALL_VERSION_MAJOR "1")
SET(BALL_VERSION_MINOR "4")
SET(BALL_VERSION_PATCH "3")


###############################################################################
###    BALL global CMake setups                                             ###
###############################################################################


CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12 FATAL_ERROR)


###############################################################################
# BALL version String
#
SET(CF_BALL_VERSION "${BALL_VERSION_MAJOR}.${BALL_VERSION_MINOR}.${BALL_VERSION_PATCH}" CACHE INTERNAL "BALL VERSION" FORCE)


###############################################################################
# Set approproate build type (default: 'Release')
#
IF(NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE Release)
ENDIF()


###############################################################################
# Enable Dart test module
#
ENABLE_TESTING()
INCLUDE(Dart)


###############################################################################
# Set BALL global CMake module path and load macros
#
LIST(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
LIST(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")

# Include global modules
INCLUDE(BALLMacros)

# Include BALL messages (implemented as macros)
INCLUDE(BALLMessages)

# Include BALL compiler specififc settings
INCLUDE(BALLCompilerSpecific)

# Include BALL configuration
INCLUDE(BALLConfiguration)


###############################################################################
# The CMake options available for BALL
#

# Build BALL_view and BALLView
OPTION(BALL_BUILD_VIEW "Specify if the BALL view library and the application BALLView are build" ON)

# Build BALLTools
OPTION(BALL_BUILD_TOOLS "Specify if the BALLTools are build" ON)

# Enable verbose output for BALL tests
OPTION(BALL_TEST_VERBOSE "Use verbose output for all tests" ON)


###############################################################################
# Set CMake output paths and prefixes
#

# Variable storing the full path to the BALL project source directory root for use in downstream projects
SET(BALL_CMAKE_SOURCE_BASE "${PROJECT_SOURCE_DIR}")

# Variable storing the full path to the BALL top level build tree directory for use in downstream projects
SET(BALL_CMAKE_BINARY_BASE "${PROJECT_BINARY_DIR}")

# Base path to place CMake build output for projects added by 'ADD_SUBDIRECTORY'
SET(BALL_CMAKE_BINARY_SOURCE_BASE "${PROJECT_BINARY_DIR}/src")

# Path to place CMake generated libraries
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

# Path to place CMake generated binaries
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")


###############################################################################
###    Search external libraries needed by project BALL                     ###
###############################################################################

# Find libraries needed by BALL
SET(BALL_DEPENDENCY_LIBS)
INCLUDE(BALLFindDependecyLibs)

# BALL dependency libraries
LIST(APPEND BALL_DEPENDENCY_LIBS ${REGEX_LIBRARIES})

# Perform global postprocessing of external library list
POSTPROCESS_DEP_LIBS(BALL_DEPENDENCY_LIBS)


###############################################################################
###    Include BALL core library                                            ###
###############################################################################

# Variable to store the BALL_core includ files for downstream use
# Will be populated in the BALL_core subproject
SET(BALL_core_INCLUDE_DIRS)

# Variable pointing to BALL data path
# Will be set in the BALL_core subproject
SET(BALL_DATA_PATH)

ADD_SUBDIRECTORY(BALL_core "${BALL_CMAKE_BINARY_SOURCE_BASE}/BALL_core")


###############################################################################
###    Include BALL view library                                            ###
###############################################################################

# Variable to store the BALL_view includ files for downstream use
# Will be populated in the BALL_view subproject
SET(BALL_view_INCLUDE_DIRS)

ADD_SUBDIRECTORY(BALL_view "${BALL_CMAKE_BINARY_SOURCE_BASE}/BALL_view")

















