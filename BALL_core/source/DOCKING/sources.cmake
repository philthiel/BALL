# Set the source group name
SET(GROUP DOCKING)

# List all filenames of this group here
SET(SOURCES_LIST )

IF(BALL_HAS_FFTW)
	SET(SOURCES_LIST geometricFit.C)
ENDIF()
