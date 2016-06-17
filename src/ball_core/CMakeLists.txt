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


project("BALL_core")


# --------------------------------------------------------------------------
# Collect source and header files
#
SET(BALL_core_sources CACHE INTERNAL "This variable should hold all BALL source files at the end of the config step")
SET(BALL_core_headers CACHE INTERNAL "This variable should hold all BALL header files at the end of the config step")

BALL_FUNCTIONS_collect_headers()
BALL_FUNCTIONS_collect_sources()

# Mark header files
SET_PROPERTY(SOURCE ${BALL_core_headers} APPEND PROPERTY HEADER_FILE_ONLY TRUE)

# Also include header files configured by CMake
INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR}/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)


# --------------------------------------------------------------------------
# Add ball_core library target
#
if(BALL_HAS_CUDA AND BALL_USE_CUDA)
	cuda_add_library(ball_core SHARED ${BALL_core_sources} ${BALL_core_headers} ${Cuda_sources})
else()
	add_library(ball_core SHARED ${BALL_core_sources} ${BALL_core_headers})
endif()

target_link_libraries(ball_core ${BALL_DEP_LIBRARIES})

#set_target_properties(ball_core PROPERTIES
#	COMPILE_FLAGS "${BALL_COMPILE_FLAGS}"
#	LINK_FLAGS "${BALL_LINK_FLAGS}"
#)

set_target_properties(ball_core PROPERTIES
	SOVERSION "${BALL_PACKAGE_VERSION_MAJOR}.${BALL_PACKAGE_VERSION_MINOR}"
)

set_target_properties(ball_core PROPERTIES INSTALL_NAME_DIR "@executable_path/../Frameworks")





