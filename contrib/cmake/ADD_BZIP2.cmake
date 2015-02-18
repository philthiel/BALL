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

	SET(BZIP2_LONG_VERSION "1.0.6")
	SET(BZIP2_SHORT_VERSION "1.0")

	ExternalProject_Add(Bzip2
		URL "${CONTRIB_PACKAGE_URL}/bzip2-1.0.6.tar.gz"
		PREFIX ${PROJECT_BINARY_DIR}

		BUILD_IN_SOURCE 1

		LOG_DOWNLOAD 1
		LOG_UPDATE 1
		LOG_CONFIGURE 1
		LOG_BUILD 1
		LOG_INSTALL 1

		CONFIGURE_COMMAND ""
		BUILD_COMMAND make
		INSTALL_COMMAND make install PREFIX=${CONTRIB_INSTALL_BASE}
	)

	# Install shared libraries
	ExternalProject_Add_Step(Bzip2 install_shared_libs
		WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/src/Bzip2/"
		COMMAND make clean
		COMMAND make -f Makefile-libbz2_so
		COMMAND cp "libbz2.so.${BZIP2_LONG_VERSION}" "${CONTRIB_INSTALL_LIB}"
		DEPENDEES install
	)

	# Create symbolic links
	ExternalProject_Add_Step(Bzip2 create_symbolic_links
		WORKING_DIRECTORY "${CONTRIB_INSTALL_LIB}"
		COMMAND ln -s -f "libbz2.so.${BZIP2_LONG_VERSION}" "libbz2.so.${BZIP2_SHORT_VERSION}"
		COMMAND ln -s -f "libbz2.so.${BZIP2_SHORT_VERSION}" "libbz2.so"
		DEPENDEES install_shared_libs
	)

ELSEIF(OS_DARWIN)

	ExternalProject_Add(Bzip2
		URL "${CONTRIB_PACKAGE_URL}/bzip2-1.0.6.tar.gz"
		PREFIX ${PROJECT_BINARY_DIR}

		BUILD_IN_SOURCE 1

		LOG_DOWNLOAD 1
		LOG_UPDATE 1
		LOG_CONFIGURE 1
		LOG_BUILD 1
		LOG_INSTALL 1

		PATCH_COMMAND patch Makefile < "${CONTRIB_PATCHES}/darwin/bzip2-1.0.6-Makefile.diff"
		CONFIGURE_COMMAND ""
		BUILD_COMMAND make
		INSTALL_COMMAND make install PREFIX=${CONTRIB_INSTALL_BASE}
	)

ELSEIF(OS_WINDOWS)
	# TODO
ENDIF()
