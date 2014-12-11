# Set the source group name
SET(GROUP PRIMITIVES)

# List all filenames of this group here
SET(SOURCES_LIST
	box.C
	disc.C
	gridVisualisation.C
	label.C
	line.C
	mesh.C
	multiLine.C
	point.C
	quadMesh.C
	simpleBox.C
	sphere.C
	tube.C
	twoColoredLine.C
	twoColoredTube.C
)

#ADD_VIEW_SOURCES("VIEW/PRIMITIVES" "${SOURCES_LIST}")
#ADD_BALL_MOCFILES("VIEW/PRIMITIVES" "include/BALL/VIEW/PRIMITIVES" "${MOC_SOURCES_LIST}")
