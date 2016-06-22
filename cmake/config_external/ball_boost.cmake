#new_header#


set(BALL_BOOST_COMPONENTS chrono date_time iostreams regex serialization system	thread)
set(Boost_ADDITIONAL_VERSIONS "1.60" "1.59" "1.58" "1.57")
set(Boost_DETAILED_FAILURE_MSG ON)

find_package(Boost 1.55 REQUIRED COMPONENTS ${BALL_BOOST_COMPONENTS})

if(WIN32)
	add_definitions(-DBOOST_ALL_NO_LIB)
	add_definitions(-DBOOST_ALL_DYN_LINK)
endif()

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
list(APPEND TMP_DEP_LIBS ${Boost_LIBRARIES})
