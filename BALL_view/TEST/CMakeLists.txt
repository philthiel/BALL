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


# Build rules for BALL's class tests
PROJECT("BALL_view_tests")


# Path to place the binaries
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BALL_CMAKE_BINARY_BASE}/TEST/BALL_view")

# Path to test data
SET(BALL_TEST_DATA_PATH "${PROJECT_SOURCE_DIR}/data")

# BALL_tetst configuration header
CONFIGURE_FILE("${PROJECT_SOURCE_DIR}/cmake/templates/BALLTestConfig.h.in" "${PROJECT_BINARY_DIR}/include/BALLTestConfig.h")

# Here the BALLTestConfig.h will be located
INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}/include")

# Include test executables
INCLUDE(source/sources.cmake)

# Add all tests as a single target
SET(ALL_TESTS "")

FOREACH(group ${VIEW_TESTS})

	# Add group-wise test targets
	ADD_CUSTOM_TARGET("${group}")
	ADD_DEPENDENCIES("${group}" ${group})

	FOREACH(test ${${group}})

		ADD_EXECUTABLE(${test} "source/${test}.C")
		TARGET_LINK_LIBRARIES(${test} BALL_core BALL_view)
		SET_PROPERTY(TARGET ${test} PROPERTY FOLDER ${group})

		IF(NOT BALL_TEST_VERBOSE)
			ADD_TEST(NAME ${test}
				COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test}
			)
		ELSE()
			ADD_TEST(NAME ${test}
				COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test} "-v"
			)
		ENDIF()

		LIST(APPEND ALL_TESTS ${test})

	ENDFOREACH()

ENDFOREACH()


# Create a suitable target
ADD_CUSTOM_TARGET(view_tests)
ADD_DEPENDENCIES(view_tests ${ALL_TESTS})


