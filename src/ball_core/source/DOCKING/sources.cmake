set(SOURCES_LIST)

if(BALL_HAS_FFTW)
	list(APPEND SOURCES_LIST geometricFit.C)
endif()
