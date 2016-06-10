# --------------------------------------------------------------------------
# BALL: Biochemical ALgorithms Library
#       A C++ framework for molecular modeling and structural bioinformatics
# --------------------------------------------------------------------------
#
# Copyright (C) 2016 the BALL team:
# - Andreas Hildebrandt (andreas.hildebrandt@uni-mainz.de)
# - Oliver Kohlbacher (oliver.kohlbacher@uni-tuebingen.de)
# - Hans-Peter Lenhof (lenhof@bioinf.uni-sb.de)
# - others
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301 USA
#
# http://www.ball-project.org
#
# --------------------------------------------------------------------------


project("BALL_master")

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)


# --------------------------------------------------------------------------
# BALL Version
#
set(BALL_PACKAGE_VERSION_MAJOR "2")
set(BALL_PACKAGE_VERSION_MINOR "0")
set(BALL_PACKAGE_VERSION_PATCH "0")

set(CF_BALL_PACKAGE_VERSION ${BALL_PACKAGE_VERSION_MAJOR}.${BALL_PACKAGE_VERSION_MINOR}.${BALL_PACKAGE_VERSION_PATCH} CACHE INTERNAL "BALL VERSION" FORCE)


# --------------------------------------------------------------------------
# Unsupported systems
#
if (MINGW OR MSYS)
	message(FATAL_ERROR "MSYS and MinGW are not supported! Please use a Visual Studio environment.")
endif()

# --------------------------------------------------------------------------
# Add BALL module path
#
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)


# --------------------------------------------------------------------------
# BALL contrib path
#
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_PREFIX_PATH})


# --------------------------------------------------------------------------
# Set default build type
#
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()


# --------------------------------------------------------------------------
# BALL options
#
OPTION(BBUILD_PYTHON "Build BALL python bindings" OFF)
OPTION(BBUILD_VIEW "Build BALL's VIEW library required for visualization and graphical user interfaces" OFF)


# --------------------------------------------------------------------------
# Add the BALL subprojects
#
add_subdirectory(src)























