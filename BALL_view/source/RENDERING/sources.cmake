# Set the source group name
SET(GROUP RENDERING)

# List all filenames of this group here
SET(SOURCES_LIST
	camera.C
	glDisplayList.C
	glOffscreenTarget.C
	glRenderWindow.C
	pixelFormat.C
	renderSetup.C
	renderWindow.C
	vertexBuffer.C
)

#ADD_VIEW_SOURCES("VIEW/RENDERING" "${SOURCES_LIST}")
#ADD_BALL_MOCFILES("VIEW/RENDERING" "include/BALL/VIEW/RENDERING" "${MOC_SOURCES_LIST}")
