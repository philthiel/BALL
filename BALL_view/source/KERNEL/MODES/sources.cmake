# Set the source group name
SET(GROUP KERNEL/MODES)

# List all filenames of this group here
SET(SOURCES_LIST
	editMode.C
	interactionMode.C
	interactionModeManager.C
	moveMode.C
	pickingMode.C
	rotateMode.C
)

# List all files requiring a moc run here
SET(MOC_SOURCES_LIST
	editMode.C
	moveMode.C
	interactionMode.C
	interactionModeManager.C
)
