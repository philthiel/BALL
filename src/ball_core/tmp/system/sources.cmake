set(SOURCES_LIST
	binaryFileAdaptor.C
	directory.C
	file.C
	fileSystem.C
	mutex.C
	networking.C
	path.C
#	simpleDownloader.C
	sysinfo.C
	systemCalls.C
	timer.C
)

if(BALL_HAS_MPI)
	list(APPEND SOURCES_LIST MPISupport.C)
endif()
