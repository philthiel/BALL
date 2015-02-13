# Set the source group name
SET(GROUP WIDGETS)

# List all filenames of this group here
SET(SOURCES_LIST
#       canvasWidget.C
	colorButton.C
	colorTable.C
	datasetControl.C
	dockingController.C
	dockWidget.C
	fileObserver.C
	genericControl.C
	geometricControl.C
	gridColorWidget.C
	helpViewer.C
	logView.C
	molecularControl.C
	molecularStructure.C
	propertyEditor.C
#       regularData1DWidget.C
#       regularData2DWidget.C
	scene.C
	SDWidget.C
	shortcutTableView.C
	testFramework.C
	textEditorWidget.C
)

IF(USE_QTWEBKIT)
	SET(SOURCES_LIST ${SOURCES_LIST} HTMLView.C)
ENDIF()

IF(BALL_PYTHON_SUPPORT)
	SET(SOURCES_LIST ${SOURCES_LIST} pyWidget.C hotkeyTable.C)
ENDIF()

# List all files requiring a moc run here
SET(MOC_SOURCES_LIST "${SOURCES_LIST}")
