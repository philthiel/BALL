#new_header#


find_package(TBB)

if(TBB_FOUND)
	set(BALL_HAS_TBB TRUE)
	include_directories(${TBB_INCLUDE_DIRS})
	list(APPEND TMP_DEP_LIBS ${TBB_LIBRARIES})
else()
	set(BALL_HAS_TBB FALSE)
	list(APPEND TMP_DEP_MISSING "TBB")
endif()

