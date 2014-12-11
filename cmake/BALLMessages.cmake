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


# Config success message
MACRO(BALL_MESSAGE_CONFIG_SUCCESS)
	MESSAGE(STATUS "")
	MESSAGE(STATUS "-----------------------------------------------------------------")
	MESSAGE(STATUS "")
	MESSAGE(STATUS "You have successfully configured BALL.")
	MESSAGE(STATUS "")

	IF(MSVC)
		MESSAGE(STATUS "Execute the 'targets' project to see prominent targets!")
	ELSE()
		MESSAGE(STATUS "For a full list of make targets execute:")
		MESSAGE(STATUS "'make targets'")
	ENDIF()

	MESSAGE(STATUS "")
	MESSAGE(STATUS "-----------------------------------------------------------------")
	MESSAGE(STATUS "")
ENDMACRO()



# Build success message
# TODO: Rewrite this message!!!
MACRO(BALL_MESSAGE_BUILD_SUCCESS)
	IF(MSVC)
		# Copy BALL.dll to test executables dir
		GET_TARGET_PROPERTY(WIN32_DLLLOCATION BALL_core LOCATION)
		GET_FILENAME_COMPONENT(WIN32_DLLPATH ${WIN32_DLLLOCATION} PATH)
		FILE(TO_NATIVE_PATH "${WIN32_DLLPATH}/$(TargetFileName)" DLL_SOURCE)
		FILE(TO_NATIVE_PATH "${PROJECT_BINARY_DIR}/source/TEST/bin/$(OutDir)/$(TargetFileName)" DLL_TARGET)

		ADD_CUSTOM_COMMAND(TARGET BALL_core
		    POST_BUILD
		    COMMAND ${CMAKE_COMMAND} -E echo ""
		    COMMAND ${CMAKE_COMMAND} -E echo "=========================================================================="
		    COMMAND ${CMAKE_COMMAND} -E echo ""
		    COMMAND ${CMAKE_COMMAND} -E echo "The BALL library has been built."
		    COMMAND ${CMAKE_COMMAND} -E echo ""
		    COMMAND ${CMAKE_COMMAND} -E echo "You can now build BALLView and the unit tests."
		    COMMAND ${CMAKE_COMMAND} -E echo "Then you should test your installation by executing the tests."
		    COMMAND ${CMAKE_COMMAND} -E echo ""
		    COMMAND ${CMAKE_COMMAND} -E echo "Execute the 'targets' project to see prominent targets!"
		    COMMAND ${CMAKE_COMMAND} -E echo ""
		    COMMAND ${CMAKE_COMMAND} -E echo "=========================================================================="
		    COMMAND ${CMAKE_COMMAND} -E echo ""
		    COMMENT "message after library is built and copy BALL(d).dll to test binary dir"
		    VERBATIM
		)
	ELSE()
		ADD_CUSTOM_COMMAND(TARGET BALL_core
		    POST_BUILD
		    COMMAND ${CMAKE_COMMAND} -E echo ""
		    COMMAND ${CMAKE_COMMAND} -E echo "=========================================================================="
		    COMMAND ${CMAKE_COMMAND} -E echo ""
		    COMMAND ${CMAKE_COMMAND} -E echo "The BALL library has been built."
		    COMMAND ${CMAKE_COMMAND} -E echo ""
		    COMMAND ${CMAKE_COMMAND} -E echo "You should now build BALLView and the unit tests."
		    COMMAND ${CMAKE_COMMAND} -E echo "Then you should test your installation by executing the tests."
		    COMMAND ${CMAKE_COMMAND} -E echo ""
		    COMMAND ${CMAKE_COMMAND} -E echo "Make sure to add the BALL and contrib lib/ path"
		    COMMAND ${CMAKE_COMMAND} -E echo "to your LD_LIBRARY_PATH environment variable."
		    COMMAND ${CMAKE_COMMAND} -E echo "Otherwise the tests and BALLView will not work."
		    COMMAND ${CMAKE_COMMAND} -E echo ""
		    COMMAND ${CMAKE_COMMAND} -E echo "For a full list of targets execute:"
		    COMMAND ${CMAKE_COMMAND} -E echo "make targets"
		    COMMAND ${CMAKE_COMMAND} -E echo ""
		    COMMAND ${CMAKE_COMMAND} -E echo "=========================================================================="
		    COMMAND ${CMAKE_COMMAND} -E echo ""
		    COMMENT "message after library is built"
		    VERBATIM
		)
	ENDIF()
ENDMACRO()

