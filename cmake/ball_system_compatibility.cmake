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


# --------------------------------------------------------------------------
# We do not support 32-bit architectures
#
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	message(FATAL_ERROR "Unsupported architecture. Only 64-bits are currently supported by BALL.")
endif()

if (MINGW OR MSYS)
	message(FATAL_ERROR "MSYS and MinGW are not supported! Please use a Visual Studio environment.")
endif()

IF (CMAKE_SIZEOF_VOID_P MATCHES "8")
	SET(BALL_64BIT_ARCHITECTURE TRUE CACHE INTERNAL "Architecture-bits")
ELSE()
	SET(BALL_64BIT_ARCHITECTURE FALSE CACHE INTERNAL "Architecture-bits")
ENDIF()
