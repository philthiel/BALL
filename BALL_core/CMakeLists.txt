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


PROJECT("BALL_core")

SET(SUBPROJECT_NAME "BALL_core")


###############################################################################
# Set BALL_core CMake module path and load macros and other paths
#
LIST(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Include BALL components
INCLUDE(BALLComponents)

# BALL standard include directory
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include")

# BALL include directory for configured files
INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}/include")

# Used for linking BALL dependent applications and libraries (BALLView, Python bindings, ...)
SET(BALL_LIBRARIES optimized BALL debug BALLd)


###############################################################################
###    Configure required BALL header files                                 ###
###############################################################################

# BALL_core/CONFIG/config.h
CONFIGURE_FILE("${PROJECT_SOURCE_DIR}/cmake/templates/config.h.in" "${PROJECT_BINARY_DIR}/include/BALL_core/CONFIG/config.h")

# BALL_core/COMMON/version.h
CONFIGURE_FILE("${PROJECT_SOURCE_DIR}/cmake/templates/version.h.in" "${PROJECT_BINARY_DIR}/include/BALL_core/COMMON/version.h")


###############################################################################
###    Build BALL_core library                                              ###
###############################################################################

# Collect all source and header files of the project BALL_core.
# The CMake file 'BALLCollectSourceFiles.cmake' creates the following variables:
#   - BALL_sources: a list that contains all source files
#   - BALL_headers: a list that contains all files files. All header files have the property 'HEADER_FILE_ONLY'
INCLUDE(BALLCollectSourceFiles)

# Add BALL_core library
# Note: header files are only included to make them visible in Visual Studio
ADD_LIBRARY(BALL_core SHARED ${BALL_sources} ${BALL_headers})

# Add libraries to be linked against
TARGET_LINK_LIBRARIES(BALL_core ${BALL_DEPENDENCY_LIBS})

# BALL compile flags
SET(BALL_COMPILE_FLAGS)

# BALL link flags
SET(BALL_LINK_FLAGS)

# Set compile flag properties of target BALL
SET_TARGET_PROPERTIES(BALL_core PROPERTIES COMPILE_FLAGS "${BALL_COMPILE_FLAGS}" LINK_FLAGS "${BALL_LINK_FLAGS}")

# Set version property of target BALL
SET_TARGET_PROPERTIES(BALL_core PROPERTIES VERSION "${BALL_VERSION_MAJOR}.${BALL_VERSION_MINOR}")


###############################################################################
###    Set upstream variables                                               ###
###############################################################################

# Fetch BALL_view include directories
GET_DIRECTORY_PROPERTY(TMP_BALL_core_INCLUDE_DIRS INCLUDE_DIRECTORIES)
SET(BALL_core_INCLUDE_DIRS "${TMP_BALL_core_INCLUDE_DIRS}" PARENT_SCOPE)


###############################################################################
###    BALL_core tests                                                      ###
###############################################################################

ADD_SUBDIRECTORY(TEST EXCLUDE_FROM_ALL)

