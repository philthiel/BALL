#new_header#


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
