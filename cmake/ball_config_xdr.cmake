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


find_package(XDR)

if(XDR_FOUND)
	set(XDR_TEST_HEADER "#include <rpc/types.h>
			#include <rpc/xdr.h>
			extern \"C\" int dummy")
	set(XDR_TEST_FOOTER " {return 0;}
			int main(){
			XDR xdrs;
			xdrrec_create(&xdrs, 0, 0, 0, dummy, dummy);
		}")

	message(STATUS "Checking for xdrrec_create signature")

	set(BALL_HAS_XDR TRUE)

	set(CMAKE_REQUIRED_LIBRARIES ${XDR_LIBRARIES})

	CHECK_CXX_SOURCE_COMPILES("${XDR_TEST_HEADER}(char*, char*, int)${XDR_TEST_FOOTER}" BALL_XDRREC_CREATE_CHAR_CHAR_INT)

	if(NOT BALL_XDRREC_CREATE_CHAR_CHAR_INT)
		CHECK_CXX_SOURCE_COMPILES("${XDR_TEST_HEADER}(void*, char*, int)${XDR_TEST_FOOTER}" BALL_XDRREC_CREATE_VOID_CHAR_INT)
		if(NOT BALL_XDRREC_CREATE_VOID_CHAR_INT)
			CHECK_CXX_SOURCE_COMPILES("${XDR_TEST_HEADER}(void*, void*, unsigned int)${XDR_TEST_FOOTER}" BALL_XDRREC_CREATE_VOID_VOID_UINT)
			if(NOT BALL_XDRREC_CREATE_VOID_VOID_UINT)
				CHECK_CXX_SOURCE_COMPILES("${XDR_TEST_HEADER}()${XDR_TEST_FOOTER}" BALL_XDRREC_CREATE_VOID)
				if(NOT BALL_XDRREC_CREATE_VOID)
					CHECK_CXX_SOURCE_COMPILES("${XDR_TEST_HEADER}(void*, void*, int)${XDR_TEST_FOOTER}" BALL_XDRREC_CREATE_VOID_VOID_INT)
					if(NOT BALL_XDRREC_CREATE_VOID_VOID_INT)
						set(BALL_HAS_XDR TRUE)
						message(SEND_ERROR "Could not determine xdrrec_create signature")
					endif()
				endif()
			endif()
		endif()
	endif()

	set(CMAKE_REQUIRED_LIBRARIES)

	list(APPEND BALL_DEP_LIBRARIES ${XDR_LIBRARIES})
endif()
