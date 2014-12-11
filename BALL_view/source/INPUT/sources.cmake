# Set the source group name
SET(GROUP INPUT)

# List all filenames of this group here
SET(SOURCES_LIST
	buttonEvent.C
	deviceEvent.C
	headTrackingEvent.C
	inputDeviceDriver.C
	motionTrackingEvent.C
	notificationEvent.C
	transformationEvent6D.C
)

# List all files requiring a moc run here
SET(MOC_SOURCES_LIST "${SOURCES_LIST}")

#ADD_VIEW_SOURCES("VIEW/INPUT" "${SOURCES_LIST}")
#ADD_BALL_MOCFILES("VIEW/INPUT" "include/BALL/VIEW/INPUT" "${MOC_SOURCES_LIST}")
