#new_header#


set(QTDIR "" CACHE PATH "Path to the qt installation (optional)")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${QTDIR})

if(QTDIR)
	include_directories(BEFORE "${QTDIR}/include")
endif()

find_package(Qt5Core REQUIRED)
list(APPEND TMP_DEP_LIBS Qt5::Core)

find_package(Qt5Network REQUIRED)
if(Qt5Network_FOUND)
	list(APPEND TMP_DEP_LIBS Qt5::Network)
else()
	list(APPEND TMP_DEP_MISSING "Qt5Network")
endif()

find_package(Qt5Xml REQUIRED)
if(Qt5Xml_FOUND)
	list(APPEND TMP_DEP_LIBS Qt5::Xml)
else()
	list(APPEND TMP_DEP_MISSING "Qt5Xml")
endif()
