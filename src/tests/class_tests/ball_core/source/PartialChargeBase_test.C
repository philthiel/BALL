// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#include <BALL/core/concept/classTest.h>
#include <testConfig.h>

///////////////////////////

#include <BALL/core/qsar/partialChargeBase.h>
#include <BALL/core/format/SDFile.h>
#include <BALL/core/kernel/system.h>
#include <BALL/core/kernel/molecule.h>

///////////////////////////
START_TEST(PartialChargeBase)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

using namespace BALL;

SDFile infile(TEST_DATA_PATH(ball_core/descriptors_test.sdf));
System S;
infile >> S;
infile.close();

Molecule * molecule;
Size limit = S.countMolecules();

CHECK(PartialChargeBase)	

	PartialChargeBase pcb;
	S.apply(pcb);

	for (Size i=0;i!=limit;++i)
	{
		molecule = S.getMolecule(i);
		TEST_EQUAL(molecule->hasProperty("TotalPositivePartialCharge"), true);
		TEST_EQUAL(molecule->hasProperty("TotalNegativePartialCharge"), true);
		TEST_EQUAL(molecule->hasProperty("RelPositivePartialCharge"), true);
		TEST_EQUAL(molecule->hasProperty("RelNegativePartialCharge"), true);
	}
		
RESULT

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
