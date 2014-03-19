// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#include <BALL/CONCEPT/classTest.h>
#include <BALLTestConfig.h>

///////////////////////////

#include <BALL/FORMAT/molFileFactory.h>

#include <BALL/FORMAT/antechamberFile.h>
#include <BALL/FORMAT/dockResultFile.h>
#include <BALL/FORMAT/genericMolFile.h>
#include <BALL/FORMAT/HINFile.h>
#include <BALL/FORMAT/MOLFile.h>
#include <BALL/FORMAT/MOL2File.h>
#include <BALL/FORMAT/PDBFile.h>
#include <BALL/FORMAT/SDFile.h>
#include <BALL/FORMAT/XYZFile.h>

///////////////////////////

START_TEST(MolFileFactory)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

using namespace std;
using namespace BALL;

CHECK(getSupportedCompressionFormats())
	TEST_EQUAL(MolFileFactory::getSupportedCompressionFormats(), ".gz,.bz2")
RESULT

CHECK(getSupportedCompressionFormats(set<String>& compression_formats))
	set<String> tmp;
	MolFileFactory::getSupportedCompressionFormats(tmp);

	TEST_EQUAL(tmp.count(".gz"), 1)
	TEST_EQUAL(tmp.count(".bz2"), 1)
	TEST_EQUAL(tmp.size(), 2)
RESULT

CHECK(isFileCompressed(const String& name, String& compression_format, String& base_name))
	String f1 = "/home/mol.sdf.gz";
	String f2 = "/home/mol.sdf.bz2";
	String f3 = "/home/mol.sdf";
	String f4 = "../mol.sdf.gz";
	String f5 = "../mol.sdf";

	String format;
	String base_name;

	TEST_EQUAL(MolFileFactory::isFileCompressed(f1, format, base_name), true)
	TEST_EQUAL(format, ".gz")
	TEST_EQUAL(base_name, "/home/mol.sdf")
	TEST_EQUAL(MolFileFactory::isFileCompressed(f2, format, base_name), true)
	TEST_EQUAL(format, ".bz2")
	TEST_EQUAL(base_name, "/home/mol.sdf")
	TEST_EQUAL(MolFileFactory::isFileCompressed(f3, format, base_name), false)
	TEST_EQUAL(format, "")
	TEST_EQUAL(base_name, "")
	TEST_EQUAL(MolFileFactory::isFileCompressed(f4, format, base_name), true)
	TEST_EQUAL(format, ".gz")
	TEST_EQUAL(base_name, "../mol.sdf")
	TEST_EQUAL(MolFileFactory::isFileCompressed(f5, format, base_name), false)
	TEST_EQUAL(format, "")
	TEST_EQUAL(base_name, "")
RESULT

CHECK(getSupportedFormats())
	TEST_EQUAL(MolFileFactory::getSupportedFormats(), ".ac,.brk,.drf,.ent,.hin,.mol,.mol2,.pdb,.sdf,.xyz")
RESULT

CHECK(getSupportedFormats(set<String>& formats))
	set<String> tmp;
	MolFileFactory::getSupportedFormats(tmp);

	TEST_EQUAL(tmp.size(), 10)
	TEST_EQUAL(tmp.count(".ac"), 1)
	TEST_EQUAL(tmp.count(".brk"), 1)
	TEST_EQUAL(tmp.count(".drf"), 1)
	TEST_EQUAL(tmp.count(".ent"), 1)
	TEST_EQUAL(tmp.count(".hin"), 1)
	TEST_EQUAL(tmp.count(".mol"), 1)
	TEST_EQUAL(tmp.count(".mol2"), 1)
	TEST_EQUAL(tmp.count(".pdb"), 1)
	TEST_EQUAL(tmp.count(".sdf"), 1)
	TEST_EQUAL(tmp.count(".xyz"), 1)
RESULT

CHECK(isFileFormatSupported(const String& name, bool input_mode))
	// Write mode file name check
	TEST_EQUAL(MolFileFactory::isFileFormatSupported("mol.sdf", false), true)
	TEST_EQUAL(MolFileFactory::isFileFormatSupported("mol.pdb", false), true)
	TEST_EQUAL(MolFileFactory::isFileFormatSupported("mol", false), false)
	TEST_EQUAL(MolFileFactory::isFileFormatSupported("mol.txt", false), false)

	// Read mode file name check
	TEST_EQUAL(MolFileFactory::isFileFormatSupported(BALL_TEST_DATA_PATH(AntechamberFile_test2.ac), true), true)
	TEST_EQUAL(MolFileFactory::isFileFormatSupported(BALL_TEST_DATA_PATH(AmberFF_test_4.hin), true), true)
	TEST_EQUAL(MolFileFactory::isFileFormatSupported(BALL_TEST_DATA_PATH(MOLFile_test1.mol), true), true)
	TEST_EQUAL(MolFileFactory::isFileFormatSupported(BALL_TEST_DATA_PATH(MOL2File_test.mol2), true), true)
	TEST_EQUAL(MolFileFactory::isFileFormatSupported(BALL_TEST_DATA_PATH(PDBFile_test2.pdb), true), true)
	TEST_EQUAL(MolFileFactory::isFileFormatSupported(BALL_TEST_DATA_PATH(SDFile_test1.sdf), true), true)
	TEST_EQUAL(MolFileFactory::isFileFormatSupported(BALL_TEST_DATA_PATH(XYZFile_test1.xyz), true), true)
	TEST_EQUAL(MolFileFactory::isFileFormatSupported(BALL_TEST_DATA_PATH(NucleicAcid_test.txt), true), false)

	// File format estimation check
	TEST_EQUAL(MolFileFactory::isFileFormatSupported(BALL_TEST_DATA_PATH(AntechamberFile), true), true)
	TEST_EQUAL(MolFileFactory::isFileFormatSupported(BALL_TEST_DATA_PATH(HinFile), true), true)
	TEST_EQUAL(MolFileFactory::isFileFormatSupported(BALL_TEST_DATA_PATH(MOLFile), true), true)
	TEST_EQUAL(MolFileFactory::isFileFormatSupported(BALL_TEST_DATA_PATH(MOL2File), true), true)
	TEST_EQUAL(MolFileFactory::isFileFormatSupported(BALL_TEST_DATA_PATH(PDBFile), true), true)
	TEST_EQUAL(MolFileFactory::isFileFormatSupported(BALL_TEST_DATA_PATH(SDFile), true), true)
	TEST_EQUAL(MolFileFactory::isFileFormatSupported(BALL_TEST_DATA_PATH(XYZFile), true), true)
	TEST_EQUAL(MolFileFactory::isFileFormatSupported(BALL_TEST_DATA_PATH(NucleicAcid), true), false)
RESULT

CHECK(open(const String& name, File::OpenMode open_mode))
	GenericMolFile* gmf;

	// Read mode tests
	gmf = MolFileFactory::open(BALL_TEST_DATA_PATH(AntechamberFile_test2.ac), File::MODE_IN);
	TEST_NOT_EQUAL(gmf, NULL)
	TEST_NOT_EQUAL(dynamic_cast<AntechamberFile*>(gmf), NULL)
	gmf->close();
	delete gmf;

	gmf = MolFileFactory::open(BALL_TEST_DATA_PATH(AmberFF_test_4.hin), File::MODE_IN);
	TEST_NOT_EQUAL(gmf, NULL)
	TEST_NOT_EQUAL(dynamic_cast<HINFile*>(gmf), NULL)
	gmf->close();
	delete gmf;

	gmf = MolFileFactory::open(BALL_TEST_DATA_PATH(MOLFile_test1.mol), File::MODE_IN);
	TEST_NOT_EQUAL(gmf, NULL)
	TEST_NOT_EQUAL(dynamic_cast<MOLFile*>(gmf), NULL)
	gmf->close();
	delete gmf;

	gmf = MolFileFactory::open(BALL_TEST_DATA_PATH(MOL2File_test.mol2), File::MODE_IN);
	TEST_NOT_EQUAL(gmf, NULL)
	TEST_NOT_EQUAL(dynamic_cast<MOL2File*>(gmf), NULL)
	gmf->close();
	delete gmf;

	gmf = MolFileFactory::open(BALL_TEST_DATA_PATH(PDBFile_test2.pdb), File::MODE_IN);
	TEST_NOT_EQUAL(gmf, NULL)
	TEST_NOT_EQUAL(dynamic_cast<PDBFile*>(gmf), NULL)
	gmf->close();
	delete gmf;

	gmf = MolFileFactory::open(BALL_TEST_DATA_PATH(SDFile_test1.sdf), File::MODE_IN);
	TEST_NOT_EQUAL(gmf, NULL)
	TEST_NOT_EQUAL(dynamic_cast<SDFile*>(gmf), NULL)
	gmf->close();
	delete gmf;

	gmf = MolFileFactory::open(BALL_TEST_DATA_PATH(XYZFile_test1.xyz), File::MODE_IN);
	TEST_NOT_EQUAL(gmf, NULL)
	TEST_NOT_EQUAL(dynamic_cast<XYZFile*>(gmf), NULL)
	gmf->close();
	delete gmf;

	// Write mode tests
RESULT

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
