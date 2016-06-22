#new_header#


find_package(LPSolve)

if(LPSOLVE_FOUND)
	set(BALL_HAS_LPSOLVE TRUE)
	include_directories(${LPSOLVE_INCLUDE_DIR})
	list(APPEND TMP_DEP_LIBS ${LPSOLVE_LIBRARIES})
else()
	set(BALL_HAS_LPSOLVE FALSE)
	list(APPEND TMP_DEP_MISSING "lpsolve")
endif()
