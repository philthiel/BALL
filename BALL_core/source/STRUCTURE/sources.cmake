# Set the source group name
SET(GROUP STRUCTURE)

# List all filenames of this group here
SET(SOURCES_LIST
	addHydrogenProcessor.C
	analyticalSES.C
	assignBondOrderProcessor.C
	atomBijection.C
	atomTyper.C
	binaryFingerprintMethods.C
	bindingPocketProcessor.C
	buildBondsProcessor.C
	connectedComponentsProcessor.C
	connolly.C
	defaultProcessors.C
	disulfidBondProcessor.C
	DNAMutator.C
	fragmentDB.C
	geometricProperties.C
	geometricTransformations.C
	graphEdge.C
	graphFace.C
	graphVertex.C
	HBondProcessor.C
	hybridisationProcessor.C
	kekulizer.C
	molecularSimilarity.C
	mutator.C
	nucleotideMapping.C
	numericalSAS.C
	peptideBuilder.C
	peptideCapProcessor.C
	peptides.C
	radialDistributionFunction.C
	RDFIntegrator.C
	RDFParameter.C
	RDFSection.C
	reconstructFragmentProcessor.C
	reducedSurface.C
	residueChecker.C
	residueRotamerSet.C
	rGroupAssembler.C
	ringAnalyser.C
	RMSDMinimizer.C
	rotamerLibrary.C
	RSEdge.C
	RSFace.C
	RSVertex.C
	SASEdge.C
	SASFace.C
	SASVertex.C
	sdGenerator.C
	secondaryStructureProcessor.C
	SESEdge.C
	SESFace.C
	SESVertex.C
	sideChainPlacementProcessor.C
	smartsMatcher.C
	smartsParser.C
	smilesParser.C
	solventAccessibleSurface.C
	solventExcludedSurface.C
	structureMapper.C
	surfaceProcessor.C
	triangle.C
	triangleEdge.C
	trianglePoint.C
	triangulatedSAS.C
	triangulatedSES.C
	triangulatedSurface.C
	UCK.C
)

IF(BALL_HAS_OPENBABEL OR BALL_HAS_OPENEYE)
	LIST(APPEND SOURCES_LIST logP.C)
ENDIF()

SET(PARSER_LEXER_LIST
	smilesParser
	smartsParser
)
