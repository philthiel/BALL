# Set the source group name
SET(GROUP SYSTEM)

# List all filenames of this group here
SET(SOURCES_LIST
	binaryFileAdaptor.C
	directory.C
	file.C
	fileSystem.C
	mutex.C
	path.C
	simpleDownloader.C
	sysinfo.C
	systemCalls.C
	timer.C
)

SET(MOC_SOURCES_LIST
	simpleDownloader.C
)

IF(BALL_HAS_ASIO)
	SET(SOURCES_LIST ${SOURCES_LIST} networking.C)
ENDIF()

IF(BALL_HAS_MPI)
	SET(SOURCES_LIST ${SOURCES_LIST} MPISupport.C)
ENDIF()
