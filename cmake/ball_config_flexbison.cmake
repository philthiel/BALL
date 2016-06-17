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


find_package(BISON)
find_package(FLEX)

if(FLEX_FOUND AND BISON_FOUND)
	# Figure out if the used flex version supports lex_destroy()
	string(REGEX REPLACE "^([0-9]+)\\.([0-9]+)\\.([0-9]+).*$" "\\1;\\2;\\3"
		FLEX_VERSION_NUMERIC ${FLEX_VERSION})

	list(GET FLEX_VERSION_NUMERIC 2 FLEX_PATCH_LEVEL)

	if(FLEX_PATCH_LEVEL GREATER 8)
		message(STATUS "Flex yylex_destroy support - found")
		set(BALL_HAS_YYLEX_DESTROY TRUE)
	else()
		message(STATUS "Flex yylex_destroy support - Not found")
		set(BALL_HAS_YYLEX_DESTROY FALSE)
	endif()
else()
	message(SEND_ERROR "Could not find bison parser or flex scanner generator.")
endif()
