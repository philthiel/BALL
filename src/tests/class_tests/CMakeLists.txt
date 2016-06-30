#new_header#


project("BALL_class_tests")


# --------------------------------------------------------------------------
# Class tests for ball_core library classes
#
add_subdirectory(ball_core EXCLUDE_FROM_ALL)


# --------------------------------------------------------------------------
# Class tests for ball_view library classes
#
if(BALL_BUILD_VIEW)
	add_subdirectory(ball_view EXCLUDE_FROM_ALL)
endif()










