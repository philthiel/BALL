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


set(BALL_BOOST_COMPONENTS chrono date_time iostreams regex serialization system	thread)
set(Boost_ADDITIONAL_VERSIONS "1.60" "1.59" "1.58" "1.57")
set(Boost_DETAILED_FAILURE_MSG ON)

find_package(Boost 1.55 REQUIRED COMPONENTS ${BALL_BOOST_COMPONENTS})

if(WIN32)
	add_definitions(-DBOOST_ALL_NO_LIB)
	add_definitions(-DBOOST_ALL_DYN_LINK)
endif()

include_directories(${Boost_INCLUDE_DIR})
list(APPEND BALL_DEP_LIBRARIES ${Boost_LIBRARIES})
#LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
