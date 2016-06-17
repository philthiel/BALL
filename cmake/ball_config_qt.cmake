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


set(QTDIR "" CACHE PATH "Path to the qt installation (optional)")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${QTDIR})

if(QTDIR)
	include_directories(BEFORE "${QTDIR}/include")
endif()

find_package(Qt5Core REQUIRED)
list(APPEND BALL_DEP_LIBRARIES Qt5::Core)

find_package(Qt5Network REQUIRED)
if(Qt5Network_FOUND)
	list(APPEND BALL_DEP_LIBRARIES Qt5::Network)
else()
	list(APPEND BALL_MISSING_DEPENDENCIES "Qt5Network")
endif()

find_package(Qt5Xml REQUIRED)
if(Qt5Xml_FOUND)
	list(APPEND BALL_DEP_LIBRARIES Qt5::Xml)
else()
	list(APPEND BALL_MISSING_DEPENDENCIES "Qt5Xml")
endif()
