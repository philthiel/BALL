#new_header#


find_package(OpenBabel2)

if(OPENBABEL2_FOUND)
	set(BALL_HAS_OPENBABEL TRUE)
	include_directories(${OPENBABEL2_INCLUDE_DIRS})
	list(APPEND TMP_DEP_LIBS ${OPENBABEL2_LIBRARIES})
else()
	set(BALL_HAS_OPENBABEL FALSE)
	list(APPEND TMP_DEP_MISSING "OpenBabel")
endif()
