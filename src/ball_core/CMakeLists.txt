#new_header#


project("ball_core")


# --------------------------------------------------------------------------
# Print missing optional BALL core dependencies
#
BALL_MACRO_print_missing_dependencies("${BALL_DEP_MISSING}")


# --------------------------------------------------------------------------
# Collect source and header files
#
set(ball_sources CACHE INTERNAL "This variable should hold all BALL source files at the end of the config step")
set(ball_headers CACHE INTERNAL "This variable should hold all BALL header files at the end of the config step")

# Automatically collect header and source files
BALL_MACRO_collect_headers()
BALL_MACRO_collect_sources()

# Mark header files
set_property(SOURCE ${ball_headers} APPEND PROPERTY HEADER_FILE_ONLY TRUE)

# Include header directories
include_directories(${PROJECT_BINARY_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include)


# --------------------------------------------------------------------------
# Add ball_core library target
#
ADD_DEFINITIONS(${BALL_DEFINITIONS})

if(FOUND_CUDART)
	CUDA_ADD_LIBRARY(ball_core ${ball_sources} ${ball_headers} ${Cuda_sources})
else()
	add_library(ball_core SHARED ${ball_sources} ${ball_headers})
endif()

target_link_libraries(ball_core ${BALL_DEP_LIBS})

#set_target_properties(ball_core PROPERTIES COMPILE_FLAGS "${BALL_COMPILE_FLAGS}" LINK_FLAGS "${BALL_LINK_FLAGS}")
set_target_properties(ball_core PROPERTIES SOVERSION "${BALL_PACKAGE_VERSION_MAJOR}.${BALL_PACKAGE_VERSION_MINOR}")
set_target_properties(ball_core PROPERTIES INSTALL_NAME_DIR "@executable_path/../Frameworks")

