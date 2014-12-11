# Set the source group name
SET(GROUP KERNEL)

# List all filenames of this group here
SET(SOURCES_LIST
	clippingPlane.C
	common.C
	compositeManager.C
	connectionObject.C
	editOperation.C
	geometricObject.C
	iconLoader.C
	mainControl.C
	message.C
	modelInformation.C
	modularWidget.C
	preferencesEntry.C
	representation.C
	representationManager.C
	shortcutRegistry.C
	snapshotManagerInterface.C
	stage.C
	threads.C
	UIOperationMode.C
)

# List all files requiring a moc run here
SET(MOC_SOURCES_LIST
	mainControl.C
	shortcutRegistry.C
)

IF(BALL_HAS_ASIO)
	SET(SOURCES_LIST ${SOURCES_LIST} serverWidget.C)
	SET(MOC_SOURCES_LIST ${MOC_SOURCES_LIST} serverWidget.C)
ENDIF()

#ADD_VIEW_SOURCES("VIEW/KERNEL" "${SOURCES_LIST}")
#ADD_BALL_MOCFILES("VIEW/KERNEL" "include/BALL/VIEW/KERNEL" "${MOC_SOURCES_LIST}")
