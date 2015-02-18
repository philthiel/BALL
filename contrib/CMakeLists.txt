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


PROJECT("BALL_contrib")


###############################################################################
###    General settings                                                     ###
###############################################################################

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12 FATAL_ERROR)

# ExternalProjects package
INCLUDE(ExternalProject)

# Path to install modules
LIST(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Contrib URL that contains source bundles
SET(CONTRIB_PACKAGE_URL "http://abi.inf.uni-tuebingen.de/Software/ball_contrib_devel")

# Set appropriate operating system
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	SET(OS_LINUX "True")
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	SET(OS_DARWIN "True")
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	SET(OS_WINDOWS "True")
ENDIF()


###############################################################################
###    Setup CMake variables and create necessary directories               ###
###############################################################################

# Install base directory
SET(CONTRIB_INSTALL_BASE "${PROJECT_BINARY_DIR}/install")
FILE(MAKE_DIRECTORY "${CONTRIB_INSTALL_BASE}")

# Binary install directory
SET(CONTRIB_INSTALL_BIN "${CONTRIB_INSTALL_BASE}/bin")
FILE(MAKE_DIRECTORY "${CONTRIB_INSTALL_BIN}")

# Library install directory
SET(CONTRIB_INSTALL_LIB "${CONTRIB_INSTALL_BASE}/lib")
FILE(MAKE_DIRECTORY "${CONTRIB_INSTALL_LIB}")

# Header install directory
SET(CONTRIB_INSTALL_INC "${CONTRIB_INSTALL_BASE}/include")
FILE(MAKE_DIRECTORY "${CONTRIB_INSTALL_INC}")


###############################################################################
###    Download contrib patches                                             ###
###############################################################################

# Patch directory
SET(CONTRIB_PATCHES "${PROJECT_BINARY_DIR}/patches")

# Download patches archive
FILE(DOWNLOAD "${CONTRIB_PACKAGE_URL}/patches.tar.gz" "${PROJECT_BINARY_DIR}/patches.tar.gz")

# Extract patches
EXECUTE_PROCESS(COMMAND tar xz INPUT_FILE "${PROJECT_BINARY_DIR}/patches.tar.gz")


###############################################################################
###    Include BALL contrib packages                                        ###
###############################################################################


# Qt4
INCLUDE(ADD_QT4)

# Boost
# Dependencies: Bzip2, Zlib
INCLUDE(ADD_BZIP2)
INCLUDE(ADD_ZLIB)
INCLUDE(ADD_BOOST)

# TBB
INCLUDE(ADD_TBB)

# Eigen3
INCLUDE(ADD_EIGEN3)

# FFTW
INCLUDE(ADD_FFTW)

# GSL
INCLUDE(ADD_GSL)

# GLEW
INCLUDE(ADD_GLEW)

# OpenBabel2
INCLUDE(ADD_OPENBABEL2)

# SIP Python
INCLUDE(ADD_SIP)

# LP_solve
INCLUDE(ADD_LP_SOLVE)


###############################################################################
###    Generate contrib config file that stores its install directory       ###
###############################################################################

CONFIGURE_FILE("${PROJECT_SOURCE_DIR}/cmake/templates/BALLContribConfig.cmake.in" "${PROJECT_SOURCE_DIR}/BALLContribConfig.cmake")









