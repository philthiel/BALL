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


IF(OS_LINUX)

	ExternalProject_Add(GLEW
		URL "${CONTRIB_PACKAGE_URL}/glew-1.9.0.tgz"
		PREFIX ${PROJECT_BINARY_DIR}

		BUILD_IN_SOURCE 1

		LOG_DOWNLOAD 1
		LOG_UPDATE 1
		LOG_CONFIGURE 1
		LOG_BUILD 1
		LOG_INSTALL 1

		CONFIGURE_COMMAND ""
		BUILD_COMMAND make
		INSTALL_COMMAND ""
		# Auto installation not possible: problem is the GLEW_DEST environment variable
		# Custom installation steps below
	)

	# Install libraries
	ExternalProject_Add_Step(GLEW install_libs
		COMMAND find "${PROJECT_BINARY_DIR}/src/GLEW/lib/" -iname "libGLEW.*" | xargs -I {} cp {} "${CONTRIB_INSTALL_LIB}"
		DEPENDEES build
	)

	# Install header files
	ExternalProject_Add_Step(GLEW install_headers
		COMMAND cp -R "${PROJECT_BINARY_DIR}/src/GLEW/include/GL"  "${CONTRIB_INSTALL_INC}"
		DEPENDEES build
	)

ELSEIF(OS_DARWIN)

	ExternalProject_Add(GLEW
		URL "${CONTRIB_PACKAGE_URL}/glew-1.9.0.tgz"
		PREFIX ${PROJECT_BINARY_DIR}

		BUILD_IN_SOURCE 1

		LOG_DOWNLOAD 1
		LOG_UPDATE 1
		LOG_CONFIGURE 1
		LOG_BUILD 1
		LOG_INSTALL 1

		CONFIGURE_COMMAND ""
		BUILD_COMMAND make
		INSTALL_COMMAND ""
		# Auto installation not possible: problem is the GLEW_DEST environment variable
		# Custom installation steps below
	)

	# Install libraries
	ExternalProject_Add_Step(GLEW install_libs
		COMMAND find "${PROJECT_BINARY_DIR}/src/GLEW/lib/" -iname "libGLEW.*" | xargs -I {} cp {} "${CONTRIB_INSTALL_LIB}"
		DEPENDEES build
	)

	# Install header files
	ExternalProject_Add_Step(GLEW install_headers
		COMMAND cp -R "${PROJECT_BINARY_DIR}/src/GLEW/include/GL"  "${CONTRIB_INSTALL_INC}"
		DEPENDEES build
	)

ELSEIF(OS_WINDOWS)
	# TODO
ENDIF()
