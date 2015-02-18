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
# $Maintainer: $
# $Authors: $
# -----------------------------------------------------------------------------


PROJECT("BALLTools_test")


###############################################################################
###    Configure BALL header files                                          ###
###############################################################################

# Path to place the binaries
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BALL_CMAKE_BINARY_BASE}/TEST/TOOLS")

# Data path path for BALLTools tests
SET(TOOLS_TEST_DATA_PATH "${PROJECT_SOURCE_DIR}/data")

# BALLTools test configuration
CONFIGURE_FILE("${PROJECT_SOURCE_DIR}/cmake/BALLToolsTestConfig.h.in" "${PROJECT_BINARY_DIR}/include/BALLToolsTestConfig.h")

INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}/include")

# Include TOOL_Test sources
INCLUDE(source/sources.cmake)

SET(ALL_TESTS)
FOREACH(test ${BALL_TOOL_TESTS})

		IF(WIN32)
			# Workaround for the stupid MSVC
			ADD_EXECUTABLE(${test} "source/${test}.C" stringStub.C)
		ELSE()
			#ADD_EXECUTABLE(${test} "source/${test}.C")
			BALL_ADD_EXECUTABLE(TARGET_NAME ${test}
					    SOURCE_FILES "source/${test}.C"
					    LINK_LIBRARIES BALL_core OUTPUT_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
		ENDIF()

		#TARGET_LINK_LIBRARIES(${i} BALL_core)

		ADD_TEST(NAME ${test} COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test})
		LIST(APPEND ALL_TESTS ${test})

ENDFOREACH()

# Create a suitable target
ADD_CUSTOM_TARGET(tool_tests)
ADD_DEPENDENCIES(tool_tests ${ALL_TESTS})
