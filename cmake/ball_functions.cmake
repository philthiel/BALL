#new_header#


# --------------------------------------------------------------------------
# Function to remove duplicates from a list of libraries
# and to print messages on missing optional external dependencies
#
macro(BALL_MACRO_print_missing_dependencies BALL_DEP_MISSING)

	# Print missing optional dependencies
	foreach(dep ${BALL_DEP_MISSING})
		message(STATUS "[BALL optional dependecy missing] ${dep}\t - skipping dependent features.")
	endforeach()

endmacro()


# --------------------------------------------------------------------------
# Function to collect  header files (*.h and *.iC) from include directory
#
macro(BALL_MACRO_collect_headers)

	# Step 1: collect groups
	set(GROUPS)
	file(GLOB_RECURSE ENTRIES RELATIVE ${PROJECT_SOURCE_DIR}/include/BALL "include/BALL/*")
	foreach(e ${ENTRIES})
		get_filename_component(group ${e} DIRECTORY)
		list(APPEND GROUPS ${group})
	endforeach()
	list(REMOVE_DUPLICATES GROUPS)

	# Step 2: collect files per group and add to list
	foreach(g ${GROUPS})
		file(GLOB_RECURSE FILES RELATIVE ${PROJECT_SOURCE_DIR} "include/BALL/${g}/*.h" "include/BALL/${g}/*.iC")

		set(HEADER_FILES_GROUP)
		foreach(f ${FILES})
			list(APPEND HEADER_FILES_GROUP ${f})
		endforeach()

		# Add header files to global list of header files
		list(APPEND ball_headers ${HEADER_FILES_GROUP})

		string(REGEX REPLACE "/" "\\\\" S_GROUP ${g})
		source_group("Header Files\\\\${S_GROUP}" FILES ${HEADER_FILES_GROUP})
	endforeach()

endmacro()


# --------------------------------------------------------------------------
# Function to collect source files (*.C) from source directory
#
macro(BALL_MACRO_collect_sources)

	# Step 1: collect sources.cmake files listing all source files
	file(GLOB_RECURSE SOURCES_CMAKE RELATIVE ${PROJECT_SOURCE_DIR} "*sources.cmake")

	set(SOURCE_FILES)
	foreach(s ${SOURCES_CMAKE})
		set(PARSER_LIST)

		get_filename_component(group ${s} DIRECTORY)
		include(${PROJECT_SOURCE_DIR}/${s})

		string(REGEX REPLACE "/" "\\\\" S_GROUP ${group})
		source_group("Source Files\\\\${S_GROUP}" FILES ${SOURCES_LIST})

		foreach(f ${SOURCES_LIST})
			list(APPEND ball_sources ${group}/${f})
		endforeach()

		# Collect and process parser/lexer files
		foreach(f ${PARSER_LIST})
			string(SUBSTRING ${f} 0 1 first)
			string(SUBSTRING ${f} 1 -1 suffix)
			string(TOUPPER ${first} first_uppercase)
			set(PREFIX ${first_uppercase}${suffix})

			SET(PARSERINPUT ${group}/${f}Parser.y)
			SET(LEXERINPUT ${group}/${f}Lexer.l)
			FILE(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/${group})
			SET(PARSEROUTPUT ${PROJECT_BINARY_DIR}/${group}/${f}Parser.C)
			SET(PARSERHEADER ${PROJECT_BINARY_DIR}/${group}/${f}Parser.h)
			SET(LEXEROUTPUT  ${PROJECT_BINARY_DIR}/${group}/${f}Lexer.C )
			BISON_TARGET(${f}Parser ${PARSERINPUT} ${PARSEROUTPUT} COMPILE_FLAGS "--defines=${PARSERHEADER} -p${PREFIX}")
			FLEX_TARGET(${f}Lexer ${LEXERINPUT} ${LEXEROUTPUT} COMPILE_FLAGS "-P${PREFIX}")
			ADD_FLEX_BISON_DEPENDENCY(${f}Lexer ${f}Parser)
			list(APPEND ball_sources ${PARSERINPUT} ${PARSEROUTPUT} ${LEXERINPUT} ${LEXEROUTPUT})
		endforeach()


	endforeach()

endmacro()


# --------------------------------------------------------------------------
# Function to add class tests
#
macro(BALL_MACRO_add_class_test_targets GROUP_PREFIX LINK_LIBRARIES)

	# Disable optimization for gcc like compilers
	if(CMAKE_COMPILER_IS_INTELCXX OR CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG)
		set(BACKUP_CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
		set(CMAKE_CXX_FLAGS_RELEASE "-O0")
	endif()

	SET(ALL_TESTS "")

	get_cmake_property(cmake_variables VARIABLES)
	foreach(v ${cmake_variables})
		if(v MATCHES ${GROUP_PREFIX}*)
			string(TOUPPER ${v} GROUP)
			add_custom_target(${GROUP})
			add_dependencies(${GROUP} ${${v}})

			foreach(test ${${v}})
				add_executable(${test} source/${test}.C)
				target_link_libraries(${test} ${LINK_LIBRARIES})
				set_property(TARGET ${test} PROPERTY FOLDER ${GROUP})
				set_target_properties(${test} PROPERTIES COMPILE_FLAGS "${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")

				add_test(${test} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test})
				list(APPEND ALL_TESTS ${test})
			endforeach()
		endif()
	endforeach()

	# Reset original compiler flags if they were changed
	if(CMAKE_COMPILER_IS_INTELCXX OR CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG)
		set(CMAKE_CXX_FLAGS_RELEASE ${BACKUP_CMAKE_CXX_FLAGS_RELEASE})
	endif()

endmacro()

