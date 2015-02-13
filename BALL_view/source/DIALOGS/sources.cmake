# Set the source group name
SET(GROUP DIALOGS)

# List all filenames of this group here
SET(SOURCES_LIST
	amberConfigurationDialog.C
	assignBondOrderConfigurationDialog.C
	assignBondOrderResultsDialog.C
	atomOverview.C
	bondProperties.C
	charmmConfigurationDialog.C
	clippingDialog.C
	coloringSettingsDialog.C
	compositeProperties.C
	contourSurfaceDialog.C
	displayProperties.C
	dockDialog.C
	dockProgressDialog.C
	dockResultDialog.C
	downloadElectronDensity.C
	downloadPDBFile.C
	editSettings.C
	editSingleShortcut.C
	exportGeometryDialog.C
	FDPBDialog.C
	fieldLinesDialog.C
	generateCrystalDialog.C
	gridVisualizationDialog.C
	labelDialog.C
	lightSettings.C
	mainControlPreferences.C
	materialSettings.C
	minimizationDialog.C
	MMFF94ConfigurationDialog.C
	modelSettingsDialog.C
	modifyRepresentationDialog.C
	molecularDynamicsDialog.C
	molecularFileDialog.C
	networkPreferences.C
	openSavePreferences.C
	parsedFunctionDialog.C
	peptideDialog.C
	pluginDialog.C
	preferences.C
	PTEDialog.C
	pubchemDialog.C
	raytraceableContourSurfaceDialog.C
	serverPreferences.C
	setCamera.C
	setClippingPlane.C
	shortcutDialog.C
	snapShotVisualisation.C
	stageSettings.C
	stereoSettingsDialog.C
	undoManagerDialog.C
)

# List all UI files here
SET(UI_SOURCES_LIST
	amberConfigurationDialog.ui
	assignBondOrderConfigurationDialog.ui
	assignBondOrderResultsDialog.ui
	atomOverview.ui
	bondProperties.ui
	charmmConfigurationDialog.ui
	clippingDialog.ui
	coloringSettingsDialog.ui
	compositeProperties.ui
	contourSurfaceDialog.ui
	displayProperties.ui
	dockDialog.ui
	dockProgressDialog.ui
	dockResultDialog.ui
	downloadElectronDensity.ui
	downloadPDBFile.ui
	editorPDBInfoDialog.ui
	editSettings.ui
	editSingleShortcut.ui
	exportGeometryDialog.ui
	FDPBDialog.ui
	fieldLinesDialog.ui
	generateCrystalDialog.ui
	gridColorWidget.ui
	gridVisualizationDialog.ui
	labelDialog.ui
	lightSettings.ui
	mainControlPreferences.ui
	materialSettings.ui
	minimizationDialog.ui
	MMFF94ConfigurationDialog.ui
	modelSettingsDialog.ui
	modifyRepresentationDialog.ui
	molecularDynamicsDialog.ui
	networkPreferences.ui
	openSavePreferences.ui
	parsedFunctionDialog.ui
	peptideDialog.ui
	pluginDialog.ui
	preferences.ui
	propEditorWidget.ui
	propertyEditor.ui
	PTEDialog.ui
	pubchemDialog.ui
	raytraceableContourSurfaceDialog.ui
	setCamera.ui
	setClippingPlane.ui
	shortcutDialog.ui
	snapShotVisualisation.ui
	stageSettings.ui
	stereoSettingsDialog.ui
	undoManagerDialog.ui
)

IF(BALL_PYTHON_SUPPORT)
	SET(UI_SOURCES_LIST ${UI_SOURCES_LIST} pythonSettings.ui)
	SET(SOURCES_LIST ${SOURCES_LIST} pythonSettings.C)
ENDIF()

IF(BALL_HAS_FFTW)
	SET(UI_SOURCES_LIST ${UI_SOURCES_LIST} geometricFitDialog.ui)
	SET(SOURCES_LIST ${SOURCES_LIST} geometricFitDialog.C)
ENDIF()

# List all files requiring a moc run here
SET(MOC_SOURCES_LIST "${SOURCES_LIST}")
