### Directory name
SET(DIRECTORY source)

SET(TOOLS_SOURCES
	#LigandFileSplitter
	LigandFileMerger
	PDBChainSplitter
	PDBReceptorSplitter
	PDBDownload
	RemoveWater
	#PlayTool
)

SET(UTILITIES_SOURCES
	#AMBER
	AddHydrogens
	AddMissingAtoms
	AntitargetRescorer
	AssignBondOrders
	AssignChargesFromRules
	AssignPositionsFromTemplate
	AssignRadiiFromRules
	AssignTypenamesFromRules
	AtomTyper
	AutoModel
	BindingDBCleaner
	BondOrderAssigner
	CalculateBindingFreeEnergy
	CalculateEnergy
	CalculateRMSD
	CalculateSolvationFreeEnergy
	ClipProteinAroundLigand
	CombiLibGenerator
	ComputeConnectedComponents
	ComputeDockingRMSD
	ConstraintsFinder
	CrystalGenerator
	DCD2DCD
	DockPoseClustering
	DockResultMerger
	EvenSplit
	ExportFragment
	ExtractClustersFromWardTree
	ExtractProteinChains
	ExtractProteinSequence
	FeatureSelector

	#FingerprintSimilarityClustering
	#FingerprintSimilarityNetwork
	#FingerprintSimilaritySearch
	#GeometricFit_slave

	GridBuilder
	HIN2MOL2
	IMGDock
	InputPartitioner
	InputReader
	InteractionConstraintDefiner
	Ligand3DGenerator
	LigCheck
	ModelCreator
	MolecularFileConverter
	MolCombine
	MolDepict
	MolFilter
	MolPredictor
	PartialChargesCopy
	PDB2AmberNaming
	PDB2DCD
	PDB2HIN
	PDBRMSDCalculator
	PeptideBuilder
	PocketDetector
	PoissonBoltzmannSolver
	PoseIndices2PDB
	Predictor
	PropertyModifier
	PropertyPlotter
	ProteinCheck
	ProteinMapper
	ProteinProtonator
	ReconstructFragment

	#RescoringCommon

	ResidueChecker

	#RigidDocking

	RMSDCalculator
	ScoreAnalyzer
	SideChainGridBuilder
	SimilarityAnalyzer
	SimpleRescorer
	SLICK
	SolventAccessibility
	SpatialConstraintDefiner
	Split2ConnectedComponents
	SurfaceAndVolume
	TaGRes
	TaGResTrain
	Trajectory2RigidTransformation
	TrajectoryFile2PDBSplitter
	Validator
	WaterFinder
)

