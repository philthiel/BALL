set(SOURCES_LIST
	AStarBondOrderStrategy.C
	bondOrderAssignment.C
	bondOrderAssignmentStrategy.C
	branchAndBoundBondOrderStrategy.C
	FPTBondOrderStrategy.C
	KGreedyBondOrderStrategy.C
	partialBondOrderAssignment.C
)

if(BALL_HAS_LPSOLVE)
	list(APPEND SOURCES_LIST ILPBondOrderStrategy.C)
endif()
