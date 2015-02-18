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


PROJECT("BALLTools")


###############################################################################
###    Upstream include directories                                         ###
###############################################################################

# BALLTools include directory
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include")

# BALL_core include directories
INCLUDE_DIRECTORIES(${BALL_core_INCLUDE_DIRS})

# BALL_view include directories
INCLUDE_DIRECTORIES(${BALL_view_INCLUDE_DIRS})


###############################################################################
###    Some settings                                                        ###
###############################################################################

# Set runtime output path for TOOLS and UTILITIES
SET(TOOLS_RUNTIME_OUTPUT_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/TOOLS")
SET(UTILS_RUNTIME_OUTPUT_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/UTILITIES")

# Path to write CTD output files
SET(TOOLS_CTD_PATH "${PROJECT_BINARY_DIR}/ctd")

# Log file for ctd generation of BALLTools
SET(TOOLS_CTD_LOGFILE "${PROJECT_BINARY_DIR}/generate_ctd.log")



###############################################################################
###    Add TOOLS and UTILITIES                                              ###
###############################################################################

INCLUDE(source/sources.cmake)

FOREACH(source_file ${TOOLS_SOURCES})
	BALL_ADD_EXECUTABLE(TARGET_NAME ${source_file}
			    SOURCE_FILES "source/${source_file}.C" "include/BALLTools/version.h"
			    LINK_LIBRARIES BALL_core OUTPUT_DIR "${TOOLS_RUNTIME_OUTPUT_PATH}")
ENDFOREACH()

FOREACH(source_file ${UTILITIES_SOURCES})
	BALL_ADD_EXECUTABLE(TARGET_NAME ${source_file}
			    SOURCE_FILES "source/${source_file}.C" "include/BALLTools/version.h"
			    LINK_LIBRARIES BALL_core OUTPUT_DIR "${UTILS_RUNTIME_OUTPUT_PATH}")
ENDFOREACH()


###############################################################################
###    Generate CTD files for TOOLS                                         ###
###############################################################################

# Create CTD output directory
FILE(MAKE_DIRECTORY ${TOOLS_CTD_PATH})

# Create empty CTD generation log file
FILE(WRITE ${TOOLS_CTD_LOGFILE} "")

# Generate CTD files after BALLTools are build
FOREACH(tool ${TOOLS_SOURCES})
	ADD_CUSTOM_COMMAND(TARGET ${tool} POST_BUILD
		COMMAND "echo" "== ${tool}" >> ${TOOLS_CTD_LOGFILE}
		WORKING_DIRECTORY "${TOOLS_CTD_PATH}"
		VERBATIM
	)

	ADD_CUSTOM_COMMAND(TARGET ${tool} POST_BUILD
		COMMAND "${TOOLS_RUNTIME_OUTPUT_PATH}/${tool}" -write_par ${tool}.ctd >> ${TOOLS_CTD_LOGFILE} 2>&1
		WORKING_DIRECTORY "${TOOLS_CTD_PATH}"
		VERBATIM
	)
ENDFOREACH()


########################################################
###    Build TOOLS tests                             ###
########################################################

ADD_SUBDIRECTORY(TEST EXCLUDE_FROM_ALL)
