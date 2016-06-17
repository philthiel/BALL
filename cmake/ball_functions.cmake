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
# Function to remove duplicates from a list of libraries
# and to print messages on missing optional external dependencies
#
macro(BALL_FUNCTIONS_evaluate_dependencies BALL_DEP_LIBRARIES BALL_DEP_MISSING)

	# Remove duplicate libraries
	list(REMOVE_DUPLICATES BALL_DEP_LIBRARIES)

	# Print missing optional dependencies
	foreach(dep ${BALL_DEP_MISSING})
		message(STATUS "[BALL optional dependecy missing] ${dep}\t - skipping dependent features.")
	endforeach()

endmacro()


# --------------------------------------------------------------------------
# Function to collect  header files (*.h and *.iC) from include directory
#
function(BALL_FUNCTIONS_collect_headers)

	# Step 1: collect groups
	set(GROUPS)
	file(GLOB_RECURSE ENTRIES RELATIVE ${PROJECT_SOURCE_DIR}/include/BALL "include/BALL/*")
	foreach(e ${ENTRIES})
		get_filename_component(group ${e} DIRECTORY)
		list(APPEND GROUPS ${group})
	endforeach()
	list(REMOVE_DUPLICATES GROUPS)

	# Step 2: collect files per group and add to list
	set(HEADER_FILES)
	foreach(g ${GROUPS})
		file(GLOB_RECURSE FILES RELATIVE ${PROJECT_SOURCE_DIR} "include/BALL/${g}/*.h" "include/BALL/${g}/*.iC")

		set(HEADER_FILES_GROUP)
		foreach(f ${FILES})
			list(APPEND HEADER_FILES_GROUP ${f})
		endforeach()

		list(APPEND HEADER_FILES "${HEADER_FILES_GROUP}")

		string(REGEX REPLACE "/" "\\\\" S_GROUP ${g})
		source_group("Header Files\\\\${S_GROUP}" FILES ${HEADER_FILES_GROUP})
	endforeach()

	# Step 3: set retrieved file in parent scope
	set(BALL_core_headers ${HEADER_FILES} PARENT_SCOPE)

endfunction()


# --------------------------------------------------------------------------
# Function to collect source files (*.C) from source directory
#
function(BALL_FUNCTIONS_collect_sources)

	# Step 1: collect sources.cmake files listing all source files
	file(GLOB_RECURSE SOURCES_CMAKE RELATIVE ${PROJECT_SOURCE_DIR} "*sources.cmake")

	set(SOURCE_FILES)
	foreach(s ${SOURCES_CMAKE})
		get_filename_component(group ${s} DIRECTORY)
		include(${PROJECT_SOURCE_DIR}/${s})

		string(REGEX REPLACE "/" "\\\\" S_GROUP ${group})
		source_group("Source Files\\\\${S_GROUP}" FILES ${SOURCES_LIST})

		foreach(f ${SOURCES_LIST})
			list(APPEND SOURCE_FILES ${group}/${f})
		endforeach()

	endforeach()

	# Step 2: set retrieved file in parent scope
	set(BALL_core_sources ${SOURCE_FILES} PARENT_SCOPE)

endfunction()

















