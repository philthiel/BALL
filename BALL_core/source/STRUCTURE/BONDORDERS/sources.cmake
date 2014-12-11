# Set the source group name
SET(GROUP STRUCTURE/BONDORDERS)

# List all filenames of this group here
SET(SOURCES_LIST
	AStarBondOrderStrategy.C
	bondOrderAssignment.C
	bondOrderAssignmentStrategy.C
	branchAndBoundBondOrderStrategy.C
	FPTBondOrderStrategy.C
	KGreedyBondOrderStrategy.C
	partialBondOrderAssignment.C
)

IF(BALL_HAS_LPSOLVE)
	LIST(APPEND SOURCES_LIST ILPBondOrderStrategy.C)
ENDIF()
