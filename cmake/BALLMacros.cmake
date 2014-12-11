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
# $Maintainer:  $
# $Authors:  $
# -----------------------------------------------------------------------------


FUNCTION(BALL_ADD_EXECUTABLE)

	SET(options)
	SET(oneValueArgs TARGET_NAME OUTPUT_DIR)
	SET(multiValueArgs SOURCE_FILES LINK_LIBRARIES)

	CMAKE_PARSE_ARGUMENTS(BALL_ADD_EXECUTABLE "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

	ADD_EXECUTABLE(${BALL_ADD_EXECUTABLE_TARGET_NAME} ${BALL_ADD_EXECUTABLE_SOURCE_FILES})

	TARGET_LINK_LIBRARIES(${BALL_ADD_EXECUTABLE_TARGET_NAME} ${BALL_ADD_EXECUTABLE_LINK_LIBRARIES})
	SET_TARGET_PROPERTIES(${BALL_ADD_EXECUTABLE_TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BALL_ADD_EXECUTABLE_OUTPUT_DIR})
	#SET_TARGET_PROPERTIES(${BALL_ADD_EXECUTABLE_TARGET_NAME} PROPERTIES VERSION "${BALL_VERSION_MAJOR}.${BALL_VERSION_MINOR}")

ENDFUNCTION()



# Simple helper: print items of a list
MACRO(PRINTLIST ITEMLIST)
MESSAGE("PRINTITEM PRINTITEM PRINTITEM")
	FOREACH(it ${ITEMLIST})
		MESSAGE("--> " ${it})
	ENDFOREACH()
MESSAGE("PRINTITEM PRINTITEM PRINTITEM")
ENDMACRO()


MACRO(POSTPROCESS_DEP_LIBS LIBRARY_LIST)

	# If unix: enable pthread linking
	IF(UNIX)
		LIST(APPEND ${LIBRARY_LIST} "pthread")
	ENDIF()

	# Remove duplicate link libraries
	LIST(REMOVE_DUPLICATES ${LIBRARY_LIST})
ENDMACRO()


## Add the source files in SOURCES_LIST to the specified list
## of files compiled into libBALL_core/libBALL_view,
## and mark them as part of source group GROUP
MACRO(ADD_BALL_SOURCES GROUP SOURCE_DIR SOURCES_LIST)

	SET(SOURCES)

	FOREACH(source_file ${SOURCES_LIST})

		# Make sure we do not have absolute paths flying around
		GET_FILENAME_COMPONENT(source_file ${source_file} NAME)

		# Add full path to the filenames
		LIST(APPEND SOURCES ${SOURCE_DIR}/${source_file})

	ENDFOREACH()

	# Pass source file list to the upper instance
	SET(BALL_sources ${BALL_sources} ${SOURCES})

	# Source group definition
	STRING(REGEX REPLACE "/" "\\\\" S_GROUP ${GROUP})
	SOURCE_GROUP("Source Files\\\\${S_GROUP}" FILES ${SOURCES})

ENDMACRO()


## Add the header files in HEADERS_LIST to the specified list
## of files compiled into libBALL_core/libBALL_view,
## and mark them as part of source group GROUP
MACRO(ADD_BALL_HEADERS GROUP SOURCE_DIR HEADERS_LIST)

	SET(HEADERS)

	FOREACH(header_file ${HEADERS_LIST})

		# Make sure we do not have absolute paths flying around
		GET_FILENAME_COMPONENT(header_file ${header_file} NAME)

		# Add full path to the filenames
		LIST(APPEND HEADERS ${SOURCE_DIR}/${header_file})

	ENDFOREACH()

	# Pass header file list to the upper instance
	SET(BALL_headers ${BALL_headers} ${HEADERS})

	# Source group definition
	STRING(REGEX REPLACE "/" "\\\\" S_GROUP ${GROUP})
	SOURCE_GROUP("Header Files\\\\${S_GROUP}" FILES ${HEADERS})

ENDMACRO()


## Add a parser and corresponding lexer to libBALL
MACRO(ADD_BALL_PARSER_LEXER GROUP SOURCE_DIR PARSER_LEXER_LIST)

	SET(DIRECTORY ${SOURCE_DIR})

	# Iterate over parser_lexer files
	FOREACH(parser_lexer ${PARSER_LEXER_LIST})

		# Capitalize the parser_lexer and store as PREFIX
		STRING(SUBSTRING ${parser_lexer} 0 1 PREFIX_TMP)
		STRING(TOUPPER ${PREFIX_TMP} PREFIX)
		STRING(SUBSTRING ${parser_lexer} 1 -1 PREFIX_TMP)
		SET(PREFIX ${PREFIX}${PREFIX_TMP})

		SET(PARSER_INPUT ${DIRECTORY}/${parser_lexer}Parser.y)
		SET(LEXER_INPUT ${DIRECTORY}/${parser_lexer}Lexer.l)

		FILE(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/${DIRECTORY})

		SET(PARSER_OUTPUT ${PROJECT_BINARY_DIR}/${DIRECTORY}/${parser_lexer}Parser.C)
		SET(PARSER_HEADER ${PROJECT_BINARY_DIR}/${DIRECTORY}/${parser_lexer}Parser.h)
		SET(LEXER_OUTPUT  ${PROJECT_BINARY_DIR}/${DIRECTORY}/${parser_lexer}Lexer.C)

		# Oh, what an ugly hack...
		IF(NOT WIN32)
			BISON_TARGET(${parser_lexer}Parser ${PARSER_INPUT} ${PARSER_OUTPUT} COMPILE_FLAGS "--defines=${PARSER_HEADER} -p${PREFIX}")
		ELSE()
			BISON_TARGET(${parser_lexer}Parser ${PARSER_INPUT} ${PARSER_OUTPUT} COMPILE_FLAGS "${BALL_BISON_BAT} --defines=${PARSER_HEADER} -p${PREFIX}")
		ENDIF()

		FLEX_TARGET(${parser_lexer}Lexer ${LEXER_INPUT} ${LEXER_OUTPUT} COMPILE_FLAGS "-P${PREFIX}")

		ADD_FLEX_BISON_DEPENDENCY(${parser_lexer}Lexer ${parser_lexer}Parser)

		# Pass source files to the upper instance
		SET(BALL_sources ${BALL_sources} ${PARSER_INPUT} ${PARSER_OUTPUT} ${LEXER_INPUT} ${LEXER_OUTPUT})

		# Source group definition
		SOURCE_GROUP("Source Files\\\\${GROUP}" FILES ${PARSER_OUTPUT} ${LEXER_OUTPUT})
		SOURCE_GROUP("Parser Files\\\\${GROUP}" FILES ${PARSER_INPUT})
		SOURCE_GROUP("Lexer Files\\\\${GROUP}" FILES ${LEXER_INPUT})

	ENDFOREACH()

ENDMACRO()


MACRO(ADD_BALL_CORE_MOCFILES GROUP SOURCE_DIR INPUT_DIRECTORY MOC_LIST)

	SET(DIRECTORY ${SOURCE_DIR})

	# For out of source builds, the output directory might not yet exist ###
	FILE(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/${DIRECTORY})

	# Iterate over the moc files
	FOREACH(moc_file ${MOC_LIST})

		GET_FILENAME_COMPONENT(moc_file ${moc_file} NAME_WE)

		SET(MOC_FILE ${INPUT_DIRECTORY}/${GROUP}/${moc_file}.h)
		SET(OUTFILE  ${PROJECT_BINARY_DIR}/${DIRECTORY}/moc_${moc_file}.C)

		# Generate the corresponding moc files ###
		QT4_GENERATE_MOC(${MOC_FILE} ${OUTFILE})

		# Add them to list of sources
		SET(BALL_sources ${BALL_sources} ${OUTFILE})

		# Source group definition
		STRING(REGEX REPLACE "/" "\\\\" S_GROUP ${GROUP})
		SOURCE_GROUP("Source Files\\\\${S_GROUP}" FILES ${OUTFILE})

	ENDFOREACH()

ENDMACRO()


MACRO(BALL_COMBINE_LIBS RESULT OPTIMIZED_LIBS DEBUG_LIBS)
	SET(OPTIMIZED_LIBS "${OPTIMIZED_LIBS}")
	SET(DEBUG_LIBS "${DEBUG_LIBS}")

	IF(OPTIMIZED_LIBS AND DEBUG_LIBS)
		SET(${RESULT} optimized "${OPTIMIZED_LIBS}" debug "${DEBUG_LIBS}" CACHE STRING "" FORCE)
	ELSEIF(OPTIMIZED_LIBS)
		SET(${RESULT} "${OPTIMIZED_LIBS}" CACHE STRING ${RESULT} FORCE)
	ELSEIF(DEBUG_LIBS)
		SET(${RESULT} "${DEBUG_LIBS}" CACHE STRING ${RESULT} FORCE)
	ENDIF()

	LIST(REMOVE_DUPLICATES ${RESULT})
ENDMACRO()


MACRO(BALL_LIB_TO_DLL RESULT_DEBUG RESULT_OPTIMZED LIBS)
	SET(NEXT_LIB_IS_OPT TRUE)
	FOREACH(LIB ${LIBS})
		STRING(TOLOWER "${LIB}" LOWER_LIB)
		IF(${LOWER_LIB} STREQUAL "debug")
			SET(NEXT_LIB_IS_OPT FALSE)
		ELSEIF(${LOWER_LIB} STREQUAL "optimized")
			SET(NEXT_LIB_IS_OPT TRUE) 
		ELSE()
			GET_FILENAME_COMPONENT(LIBPATH "${LIB}" PATH)
			GET_FILENAME_COMPONENT(LIBNAME "${LIB}" NAME_WE)
			SET(DLLPATH "DLLPATH-NOTFOUND" CACHE STRING "" FORCE)
			FIND_FILE(DLLPATH 
				NAMES  "${LIBNAME}.dll"
				HINTS "${LIBPATH}"
				PATH_SUFFIXES ../bin ../dlls
				NO_DEFAULT_PATH
			)
			IF(NOT DLLPATH)
				FIND_FILE(DLLPATH 
					NAMES  "${LIBNAME}.pyd"
					HINTS "${LIBPATH}"
					PATH_SUFFIXES ../bin ../dlls
				)
			ENDIF()
			IF(DLLPATH)
				IF (NEXT_LIB_IS_OPT)
					LIST(APPEND ${RESULT_OPTIMZED} "${DLLPATH}")
				ELSE()
					LIST(APPEND ${RESULT_DEBUG} "${DLLPATH}")
				ENDIF()
			ENDIF()
			SET(NEXT_LIB_IS_OPT TRUE)
		ENDIF()
	ENDFOREACH()
ENDMACRO()


MACRO(SET_COMPONENT_NAME COMPONENT NAME DESCRIPTION)
	STRING(TOUPPER ${COMPONENT} CURRENT_COMPONENT)
	SET(CPACK_COMPONENT_${CURRENT_COMPONENT}_DISPLAY_NAME ${NAME})
	SET(CPACK_COMPONENT_${CURRENT_COMPONENT}_DESCRIPTION  ${DESCRIPTION})
ENDMACRO()


MACRO(SET_COMPONENT_DEPENDENCIES COMPONENT DEPENDENCIES)
	## Dependencies of components seem to be currently broken for PackageMaker.
	## Or we do something completely wrong...
	IF(NOT APPLE)
		STRING(TOUPPER ${COMPONENT} CURRENT_COMPONENT)
		SET(CPACK_COMPONENT_${CURRENT_COMPONENT}_DEPENDS ${DEPENDENCIES})
	ENDIF()
ENDMACRO()
