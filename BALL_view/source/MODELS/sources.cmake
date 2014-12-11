# Set the source group name
SET(GROUP MODELS)

# List all filenames of this group here
SET(SOURCES_LIST
	atomBondModelBaseProcessor.C
	backboneModel.C
	ballAndStickModel.C
	cartoonModel.C
	colorByGridProcessor.C
	colorProcessor.C
	fieldLineCreator.C
	forceModel.C
	HBondModel.C
	labelModel.C
	lineModel.C
	modelProcessor.C
	standardColorProcessor.C
	surfaceModel.C
	vanDerWaalsModel.C
)

#ADD_VIEW_SOURCES("VIEW/MODELS" "${SOURCES_LIST}")
#ADD_BALL_MOCFILES("VIEW/MODELS" "include/BALL/VIEW/MODELS" "${MOC_SOURCES_LIST}")
