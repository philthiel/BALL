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
# $Authors: Philipp Thiel, others $
# -----------------------------------------------------------------------------


PROJECT("BALL_view")

SET(SUBPROJECT_NAME "BALL_view")


###############################################################################
# Set BALL_view CMake module path and load macros and other paths
#
LIST(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# BALL standard include directory
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include")

# BALL include directory for configured files
INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}/include")

# BALL_core include directories
INCLUDE_DIRECTORIES(${BALL_core_INCLUDE_DIRS})


###############################################################################
###    Build BALL_view library                                              ###
###############################################################################

# Collect all source and header files of the project BALL_view.
# The CMake file 'BALLCollectSourceFiles.cmake' creates the following variables:
#   - BALL_sources: a list that contains all source files
#   - BALL_headers: a list that contains all files files. All header files have the property 'HEADER_FILE_ONLY'
INCLUDE(BALLCollectSourceFiles)

# Add BALL_view library
# Note: header files are only included to make them visible in Visual Studio
ADD_LIBRARY(BALL_view SHARED ${BALL_sources} ${BALL_headers})

# Add libraries to be linked against
TARGET_LINK_LIBRARIES(BALL_view BALL_core ${BALL_DEPENDENCY_LIBS})

# BALL compile flags
SET(BALL_COMPILE_FLAGS)

# BALL link flags
SET(BALL_LINK_FLAGS)

# Set compile flag properties of target BALL_view
SET_TARGET_PROPERTIES(BALL_view PROPERTIES COMPILE_FLAGS "${BALL_COMPILE_FLAGS}" LINK_FLAGS "${BALL_LINK_FLAGS}")

# Set version property of target BALL_view
SET_TARGET_PROPERTIES(BALL_view PROPERTIES VERSION "${BALL_VERSION_MAJOR}.${BALL_VERSION_MINOR}")


###############################################################################
###    Set upstream variables                                               ###
###############################################################################

# Fetch BALL_view include directories
GET_DIRECTORY_PROPERTY(TMP_BALL_view_INCLUDE_DIRS INCLUDE_DIRECTORIES)
SET(BALL_view_INCLUDE_DIRS "${TMP_BALL_view_INCLUDE_DIRS}" PARENT_SCOPE)


###############################################################################
###    Build BALLView                                                       ###
###############################################################################

ADD_SUBDIRECTORY(BALLView)


###############################################################################
###    BALL_view tests                                                      ###
###############################################################################

ADD_SUBDIRECTORY(TEST EXCLUDE_FROM_ALL)







