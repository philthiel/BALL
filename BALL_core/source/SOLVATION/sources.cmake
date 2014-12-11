# Set the source group name
SET(GROUP SOLVATION)

# List all filenames of this group here
SET(SOURCES_LIST
	claverieParameter.C
	electrostaticPotentialCalculator.C
	generalizedBornCase.C
	molecularSurfaceGrid.C
	ooiEnergy.C
	pair6_12InteractionEnergyProcessor.C
	pair6_12RDFIntegrator.C
	pairExpInteractionEnergyProcessor.C
	pairExpRDFIntegrator.C
	PCMCavFreeEnergyProcessor.C
	pierottiCavFreeEnergyProcessor.C
	poissonBoltzmann.C
	reissCavFreeEnergyProcessor.C
	solventDescriptor.C
	solventParameter.C
	uhligCavFreeEnergyProcessor.C
)
