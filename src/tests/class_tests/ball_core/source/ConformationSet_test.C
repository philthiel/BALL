// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#include <BALL/core/concept/classTest.h>
#include <testConfig.h>

///////////////////////////

#include <BALL/core/docking/common/conformationSet.h>
#include <BALL/core/format/PDBFile.h>
#include <BALL/core/format/DCDFile.h>

///////////////////////////

using namespace BALL;

START_TEST(ConformationSet)

ConformationSet* cs;
CHECK(ConformationSet())
  cs = new ConformationSet();
	TEST_NOT_EQUAL(cs,0)
RESULT


CHECK(~ConformationSet())
	delete cs;
RESULT

CHECK(readDCDFile())
		ConformationSet cs;
		cs.readDCDFile(TEST_DATA_PATH(ball_core/ConformationSet_test.dcd));
		cs.resetScoring();
		TEST_EQUAL(cs.size(), 10)
RESULT

CHECK(writeDCDFile(const String& filename, const Size num = 0))
		ConformationSet cs;

		PDBFile pdb(TEST_DATA_PATH(ball_core/ConformationSet_test.pdb));
		System sys;
		pdb.read(sys);
		cs.setup(sys);

		cs.readDCDFile(TEST_DATA_PATH(ball_core/ConformationSet_test.dcd));
		cs.resetScoring();
		String tmp_filename;
		NEW_TMP_FILE(tmp_filename)

		cs.writeDCDFile(tmp_filename);
		TEST_FILE(tmp_filename.c_str(), TEST_DATA_PATH(ball_core/ConformationSet_test.dcd))
RESULT

CHECK(setup())
	PDBFile pdb(TEST_DATA_PATH(ball_core/ConformationSet_test.pdb));
	System sys;
	pdb.read(sys);

	ConformationSet cs;
	cs.setup(sys);
	TEST_EQUAL(sys.getProtein(0)->countAtoms(), 2145)

RESULT

/////////////////////////////////////////////////////////////
END_TEST
