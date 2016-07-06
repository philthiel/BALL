#new_header#


# --------------------------------------------------------------------------
# Macro to remove duplicates from a list of libraries
# and to print messages on missing optional external dependencies
#
macro(BALL_MACRO_print_missing_dependencies BALL_DEP_MISSING)

	# Print missing optional dependencies
	foreach(dep ${BALL_DEP_MISSING})
		message(STATUS "[BALL optional dependecy missing] ${dep}\t - skipping dependent features.")
	endforeach()

endmacro()


# --------------------------------------------------------------------------
# Macros to set and reset CXX compiler flags
#
macro(BALL_MACRO_cxx_flags_set FLAGS)
	set(BACKUP_CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
	set(CMAKE_CXX_FLAGS_RELEASE ${FLAGS})
endmacro()

macro(BALL_MACRO_cxx_flags_reset)
	set(CMAKE_CXX_FLAGS_RELEASE ${BACKUP_CMAKE_CXX_FLAGS_RELEASE})
endmacro()


# --------------------------------------------------------------------------
# Macro to collect  header files (*.h and *.iC) from include directory
#
macro(BALL_MACRO_collect_headers HEADER_FILE_LIST)

	# Step 1: collect groups
	set(GROUPS)
	file(GLOB_RECURSE ENTRIES RELATIVE ${PROJECT_SOURCE_DIR}/include/BALL "include/BALL/*")
	foreach(entry ${ENTRIES})
		get_filename_component(group ${entry} DIRECTORY)
		list(APPEND GROUPS ${group})
	endforeach()
	list(REMOVE_DUPLICATES GROUPS)

	# Step 2: collect files per group and add to list
	foreach(group ${GROUPS})

		file(GLOB_RECURSE FILES RELATIVE ${PROJECT_SOURCE_DIR} "include/BALL/${group}/*.h" "include/BALL/${group}/*.iC")

		set(HEADER_FILES_GROUP)
		foreach(file ${FILES})
			list(APPEND HEADER_FILES_GROUP ${file})
		endforeach()

		# Add header files to global list of header files
		list(APPEND ${HEADER_FILE_LIST} ${HEADER_FILES_GROUP})

		string(REGEX REPLACE "/" "\\\\" S_GROUP ${group})
		source_group("Header Files\\\\${S_GROUP}" FILES ${HEADER_FILES_GROUP})

	endforeach()

endmacro()


# --------------------------------------------------------------------------
# Macro to collect source files (*.C) from source directory
#
macro(BALL_MACRO_collect_sources SOURCE_FILE_LIST)

	# Step 1: collect sources.cmake files listing all source files
	file(GLOB_RECURSE SOURCES_CMAKE RELATIVE ${PROJECT_SOURCE_DIR} "*sources.cmake")

	set(SOURCE_FILES)
	foreach(s ${SOURCES_CMAKE})

		get_filename_component(group ${s} DIRECTORY)
		include(${s})

		foreach(file ${SOURCES_LIST})
			list(APPEND ${SOURCE_FILE_LIST} ${group}/${file})
		endforeach()

		string(REGEX REPLACE "/" "\\\\" S_GROUP ${group})
		source_group("Source Files\\\\${S_GROUP}" FILES ${SOURCES_LIST})

	endforeach()

endmacro()


# --------------------------------------------------------------------------
# Macro to collect and configure flex/bison source files
#
macro(BALL_MACRO_collect_parser_sources SOURCE_FILE_LIST)

	# Step 1: collect sources.cmake files listing all source files
	file(GLOB_RECURSE SOURCES_CMAKE RELATIVE ${PROJECT_SOURCE_DIR} "*sources.cmake")

	foreach(s ${SOURCES_CMAKE})

		set(PARSER_LIST)
		get_filename_component(group ${s} DIRECTORY)
		include(${s})

		if(PARSER_LIST)
			SET(OUTPUT_DIR ${PROJECT_BINARY_DIR}/${group})
			FILE(MAKE_DIRECTORY ${OUTPUT_DIR})
		endif()

		# Collect and process parser/lexer files
		foreach(file ${PARSER_LIST})

			string(SUBSTRING ${file} 0 1 first)
			string(SUBSTRING ${file} 1 -1 suffix)
			string(TOUPPER ${first} first_uppercase)
			set(PREFIX ${first_uppercase}${suffix})

			SET(PARSER_INPUT ${group}/${file}Parser.y)
			SET(LEXER_INPUT ${group}/${file}Lexer.l)
			SET(PARSER_OUTPUT ${OUTPUT_DIR}/${file}Parser.C)
			SET(PARSER_HEADER ${OUTPUT_DIR}/${file}Parser.h)
			SET(LEXER_OUTPUT  ${OUTPUT_DIR}/${file}Lexer.C )

			BISON_TARGET(${file}Parser ${PARSER_INPUT} ${PARSER_OUTPUT} COMPILE_FLAGS "--defines=${PARSER_HEADER} -p${PREFIX}")
			FLEX_TARGET(${file}Lexer ${LEXER_INPUT} ${LEXER_OUTPUT} COMPILE_FLAGS "-P${PREFIX}")

			ADD_FLEX_BISON_DEPENDENCY(${file}Lexer ${file}Parser)

			list(APPEND ${SOURCE_FILE_LIST} ${PARSER_INPUT} ${PARSER_OUTPUT} ${LEXER_INPUT} ${LEXER_OUTPUT})

			source_group("Source Files\\\\${group}" FILES ${PARSER_OUTPUT} ${LEXER_OUTPUT})
			source_group("Parser Files\\\\${group}" FILES ${PARSER_INPUT})
			source_group("Lexer Files\\\\${group}" FILES ${LEXER_INPUT})

		endforeach()

	endforeach()

endmacro()


# --------------------------------------------------------------------------
# Macro to add class tests
#
macro(BALL_MACRO_add_class_tests LINK_LIBRARIES)

	SET(ALL_TESTS "")

	# Step 1: collect sources.cmake files listing all source files
	file(GLOB_RECURSE SOURCES_CMAKE RELATIVE ${PROJECT_SOURCE_DIR} "*sources.cmake")

	set(SOURCE_FILES)
	foreach(s ${SOURCES_CMAKE})

		get_filename_component(tmp ${s} DIRECTORY)
		get_filename_component(group ${tmp} NAME)
		include(${s})

		list(APPEND ALL_TESTS ${SOURCES_LIST})

		add_custom_target("core_test_${group}")
		add_dependencies("core_test_${group}" ${SOURCES_LIST})

		foreach(test ${SOURCES_LIST})

			add_executable(${test} source/${group}/${test}.C ${HEADER_FILES_class_test_core})
			target_link_libraries(${test} ${LINK_LIBRARIES})
			set_property(TARGET ${test} PROPERTY FOLDER ${group})
			set_target_properties(${test} PROPERTIES COMPILE_FLAGS "${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")

			add_test(${test} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test})

		endforeach()

	endforeach()

endmacro()
