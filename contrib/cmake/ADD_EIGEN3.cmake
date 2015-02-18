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

	ExternalProject_Add(Eigen3
		URL "${CONTRIB_PACKAGE_URL}/eigen-eigen-6b38706d90a9.tar.gz"
		PREFIX ${PROJECT_BINARY_DIR}

		LOG_DOWNLOAD 1
		LOG_UPDATE 1
		LOG_CONFIGURE 1
		LOG_BUILD 1
		LOG_INSTALL 1

		CMAKE_COMMAND cmake
		CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CONTRIB_INSTALL_BASE}
		BUILD_COMMAND make
		INSTALL_COMMAND make install -Wno-dev
	)

ELSEIF(OS_DARWIN)

	ExternalProject_Add(Eigen3
		URL "${CONTRIB_PACKAGE_URL}/eigen-eigen-6b38706d90a9.tar.gz"
		PREFIX ${PROJECT_BINARY_DIR}

		LOG_DOWNLOAD 1
		LOG_UPDATE 1
		LOG_CONFIGURE 1
		LOG_BUILD 1
		LOG_INSTALL 1

		CMAKE_COMMAND cmake
		CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CONTRIB_INSTALL_BASE}
		BUILD_COMMAND make
		INSTALL_COMMAND make install -Wno-dev
	)

ELSEIF(OS_WINDOWS)
	# TODO
ENDIF()
