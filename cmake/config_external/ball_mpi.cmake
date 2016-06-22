#new_header#


find_package(MPI QUIET)

if(MPI_FOUND)
	set(BALL_HAS_MPI TRUE)
	include_directories(${MPI_CXX_INCLUDE_PATH})
	list(APPEND TMP_DEP_LIBS ${MPI_LIBRARIES})
	add_definitions(${MPI_CXX_COMPILE_FLAGS})
else()
	set(BALL_HAS_MPI FALSE)
	list(APPEND TMP_DEP_MISSING "MPI")
endif()
