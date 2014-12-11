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


# BALLIncludes.cmake
#
# This file gathers all source and header files that are compiled into the project target(s)

# Set empty lists that will be filled with source and header files of BALL_core
SET(BALL_sources CACHE INTERNAL "This variable should hold all BALL sources at the end of the config step")
SET(BALL_headers CACHE INTERNAL "This variable should hold all BALL headers at the end of the config step")



###############################################################################
###    Step 1: Collect sources                                              ###
###############################################################################

# Recursively list all 'sources.cmake' files in the source subfolders
# sources.cmake files define the following variables:
#   - GROUP:             Source group name
#   - SOURCES_LIST:      list of source files to be added
#   - MOC_SOURCES_LIST:  list of source files that have to be compiled with moc (Qt)
#   - PARSER_LEXER_LIST: lsit of files that define parsers

FILE(GLOB_RECURSE sources_cmake_lists RELATIVE ${PROJECT_SOURCE_DIR} source/*sources.cmake)

FOREACH(source_file ${sources_cmake_lists})

	SET(SOURCES_LIST "")
	SET(MOC_SOURCES_LIST "")
	SET(PARSER_LEXER_LIST "")

	GET_FILENAME_COMPONENT(SOURCE_DIR "${source_file}" DIRECTORY)

	INCLUDE("${source_file}")

	IF(SOURCES_LIST)
		ADD_BALL_SOURCES("${GROUP}" "${SOURCE_DIR}" "${SOURCES_LIST}")
	ENDIF()

	IF(MOC_SOURCES_LIST)
		ADD_BALL_CORE_MOCFILES("${GROUP}" "${SOURCE_DIR}" "include/BALL_core/" "${MOC_SOURCES_LIST}")
	ENDIF()

	IF(PARSER_LEXER_LIST)
		ADD_BALL_PARSER_LEXER("${GROUP}" "${SOURCE_DIR}" "${PARSER_LEXER_LIST}")
	ENDIF()

ENDFOREACH()



###############################################################################
###    Step 2: Collect headers                                              ###
###############################################################################

# Recursively list all 'sources.cmake' files in the include subfolders
# sources.cmake files define the following variable:
#   - GROUP:             Source group name

FILE(GLOB_RECURSE header_directories RELATIVE ${PROJECT_SOURCE_DIR} include/*sources.cmake)

FOREACH(header_source_file ${header_directories})

	GET_FILENAME_COMPONENT(SOURCE_DIR "${header_source_file}" DIRECTORY)

	INCLUDE("${header_source_file}")

	FILE(GLOB HEADERS_LIST "${SOURCE_DIR}/*.h" "${SOURCE_DIR}/*.iC")

	ADD_BALL_HEADERS("${GROUP}" "${SOURCE_DIR}" "${HEADERS_LIST}")

ENDFOREACH()

# Fiinally, mark all header files as headers (property 'HEADER_FILE_ONLY')
SET_PROPERTY(SOURCE ${BALL_headers} APPEND PROPERTY HEADER_FILE_ONLY TRUE)


























