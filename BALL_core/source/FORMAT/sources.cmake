# Set the source group name
SET(GROUP FORMAT)

# List all filenames of this group here
SET(SOURCES_LIST
	amiraMeshFile.C
	antechamberFile.C
	bruker1DFile.C
	bruker2DFile.C
	CCP4File.C
	CIFFile.C
	commandlineParser.C
	DCDFile.C
	dockResultFile.C
	DSN6File.C
	GAMESSDatFile.C
#       GAMESSLogFile.C
	genericMolFile.C
	HINFile.C
	HMOFile.C
	INIFile.C
	JCAMPFile.C
	KCFFile.C
	lineBasedFile.C
	MOL2File.C
	MOLFile.C
	molFileFactory.C
	MOPACInputFile.C
	MOPACOutputFile.C
	NMRStarFile.C
	parameters.C
	parameterSection.C
	paramFile.C
	PDBdefs.C
	PDBFileDetails.C
	PDBFileGeneral.C
	PDBInfo.C
	PDBRecords.C
	pubchemDownloader.C
	resourceFile.C
	SCWRLRotamerFile.C
	SDFile.C
	trajectoryFile.C
	trajectoryFileFactory.C
	TRRFile.C
	XYZFile.C
)

SET(PARSER_LEXER_LIST
	CIFParser
	GAMESSDatParser
)
