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

	ExternalProject_Add(LP_solve
		URL "${CONTRIB_PACKAGE_URL}/lp_solve_5.5.2.0_source.tar.gz"
		PREFIX ${PROJECT_BINARY_DIR}

		LOG_DOWNLOAD 1

		CONFIGURE_COMMAND ""
		BUILD_COMMAND ""
		INSTALL_COMMAND ""
	)

	# Build step
	ExternalProject_Add_Step(LP_solve custom_build
		WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/src/LP_solve/lpsolve55/"
		COMMAND sh "ccc"
		LOG 1
		DEPENDEES install
	)

	# Install library
	ExternalProject_Add_Step(LP_solve custom_install_lib
		COMMAND find "${PROJECT_BINARY_DIR}/src/LP_solve/lpsolve55/bin" -iname "liblpsolve55*" | xargs -I {} install {} "${CONTRIB_INSTALL_LIB}"
		DEPENDEES custom_build
	)

	# Install headers
	ExternalProject_Add_Step(LP_solve custom_install_headers
		COMMAND cd "${PROJECT_BINARY_DIR}/src/LP_solve/" && install -d "${CONTRIB_INSTALL_INC}/lpsolve"
		COMMAND find "${PROJECT_BINARY_DIR}/src/LP_solve/" -iname "*.h" | xargs -I {} install {} "${CONTRIB_INSTALL_INC}/lpsolve"
		DEPENDEES custom_install_lib
	)


ELSEIF(OS_DARWIN)

	ExternalProject_Add(LP_solve
		URL "${CONTRIB_PACKAGE_URL}/lp_solve_5.5.2.0_source.tar.gz"
		PREFIX ${PROJECT_BINARY_DIR}

		LOG_DOWNLOAD 1

		CONFIGURE_COMMAND ""
		BUILD_COMMAND ""
		INSTALL_COMMAND ""
	)

	# Build step
	ExternalProject_Add_Step(LP_solve custom_build
		WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/src/LP_solve/lpsolve55/"
		COMMAND sh "ccc.osx"
		LOG 1
		DEPENDEES install
	)

	# Install library
	ExternalProject_Add_Step(LP_solve custom_install_lib
		COMMAND find "${PROJECT_BINARY_DIR}/src/LP_solve/lpsolve55/bin" -iname "liblpsolve55*" | xargs -I {} install {} "${CONTRIB_INSTALL_LIB}"
		DEPENDEES custom_build
	)

	# Install headers
	ExternalProject_Add_Step(LP_solve custom_install_headers
		COMMAND cd "${PROJECT_BINARY_DIR}/src/LP_solve/" && install -d "${CONTRIB_INSTALL_INC}/lpsolve"
		COMMAND find "${PROJECT_BINARY_DIR}/src/LP_solve/" -iname "*.h" | xargs -I {} install {} "${CONTRIB_INSTALL_INC}/lpsolve"
		DEPENDEES custom_install_lib
	)

ELSEIF(OS_WINDOWS)
	# TODO
ENDIF()
