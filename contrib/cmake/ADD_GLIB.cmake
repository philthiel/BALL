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



ELSEIF(OS_DARWIN)

	ExternalProject_Add(Glib
		URL "${CONTRIB_PACKAGE_URL}/qt-everywhere-opensource-src-4.8.6.tar.gz"
		PREFIX ${PROJECT_BINARY_DIR}

		BUILD_IN_SOURCE 1

		LOG_DOWNLOAD 1
		LOG_UPDATE 1
		LOG_CONFIGURE 1
		LOG_BUILD 1
		LOG_INSTALL 1

		CONFIGURE_COMMAND "${PROJECT_BINARY_DIR}/src/QT4/configure" -framework -opensource -confirm-license -silent -prefix ${CONTRIB_INSTALL_BASE}
		-no-qt3support -nomake examples -nomake demos -no-nis -no-multimedia -no-audio-backend

		BUILD_COMMAND make
		INSTALL_COMMAND make install
	)

ELSEIF(OS_WINDOWS)
	# TODO
ENDIF()
