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
PROJECT("BALL_core_tests")


# Path to place the binaries
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BALL_CMAKE_BINARY_BASE}/TEST")

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

FOREACH(group ${BALL_TESTS})

	# Add group-wise test targets
	ADD_CUSTOM_TARGET("${group}")
	ADD_DEPENDENCIES("${group}" ${group})

	FOREACH(test ${${group}})

		ADD_EXECUTABLE(${test} "source/${test}.C")
		TARGET_LINK_LIBRARIES(${test} BALL_core)
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

# Set the timeout of some tests to 2h
# This is needed for the memcheck running on the CI server
# which takes _very_ long
SET_TESTS_PROPERTIES(
	ScoringFunction_test
	AssignBondOrderProcessor_test
	PROPERTIES TIMEOUT 7200
)

# Create a suitable target
ADD_CUSTOM_TARGET(ball_tests)
ADD_DEPENDENCIES(ball_tests ${ALL_TESTS})


