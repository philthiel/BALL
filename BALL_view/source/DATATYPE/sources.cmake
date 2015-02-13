# Set the source group name
SET(GROUP DATATYPE)

# List all filenames of this group here
SET(SOURCES_LIST
	colorExtensions.C
	colorHSV.C
	colorMap.C
	colorRGBA.C
	colorUnit.C
	colorUnitHue.C
	dataset.C
	raytraceableGrid.C
	standardDatasets.C
	vertex1.C
	vertex2.C
)

# List all files requiring a moc run here
SET(MOC_SOURCES_LIST
	dataset.C
	standardDatasets.C
)
