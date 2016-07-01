// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#include <BALL/core/concept/classTest.h>
#include <testConfig.h>

///////////////////////////

#include <BALL/core/qsar/partialChargeDescriptors.h>
#include <BALL/core/format/SDFile.h>
#include <BALL/core/format/HINFile.h>
#include <BALL/core/kernel/system.h>
#include <BALL/core/kernel/molecule.h>
#include <BALL/core/kernel/PTE.h>

///////////////////////////

START_TEST(SimpleDescriptors)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

using namespace BALL;

	SDFile infile(TEST_DATA_PATH(ball_core/descriptors_test.sdf));
	System S;
	infile >> S;

	Molecule * molecule;
	Size limit = S.countMolecules();


///////////////////////
CHECK(TotalPositivePartialCharge)
	TotalPositivePartialCharge tppc;
	S.apply(tppc);

	PRECISION(0.0001)
	double results[] = {0.318341, 0.370549, 0.426301, 0.435711, 1.42026, 1.64172, 0.190191, 0.32429, 0};
	for (Size i=0;i!=limit;++i) 
	{
		molecule = S.getMolecule(i);
		TEST_EQUAL(molecule->hasProperty("TotalPositivePartialCharge"), true);
		if (molecule->hasProperty("TotalPositivePartialCharge"))
		{
			double value = molecule->getProperty("TotalPositivePartialCharge").getDouble();
			TEST_REAL_EQUAL(value, results[i]);
		}
	}

RESULT


///////////////////////////////////
CHECK(TotalNegativePartialCharge)
	TotalNegativePartialCharge tnpc;
	S.apply(tnpc);

	PRECISION(0.0001)
	double results[] = {-0.318341, -0.370549, -0.426301, -0.435711, -1.42026, -1.64172, -0.190191, -0.32429, 0};
	for (Size i=0;i!=limit;++i)
	{
		molecule = S.getMolecule(i);
		TEST_EQUAL(molecule->hasProperty("TotalNegativePartialCharge"), true);
		if (molecule->hasProperty("TotalNegativePartialCharge"))
		{
			double value = molecule->getProperty("TotalNegativePartialCharge").getDouble();
			TEST_REAL_EQUAL(value, results[i])
		}
	}

RESULT


//////////////////////////////////
CHECK(RelPositivePartialCharge)
	RelPositivePartialCharge rppc;
	S.apply(rppc);

	double results[] = {0.0833333, 0.166667, 0.0727568, 0.142361, 0.140169, 0.26484, 0.654438, 0.193613, 0};
	for (Size i=0;i!=limit;++i)
	{
		molecule = S.getMolecule(i);
		TEST_EQUAL(molecule->hasProperty("RelPositivePartialCharge"), true)
		if (molecule->hasProperty("RelPositivePartialCharge"))
		{
			double value = molecule->getProperty("RelPositivePartialCharge").getDouble();
			TEST_REAL_EQUAL(value, results[i])
		}
	}

RESULT


///////////////////////////////////
CHECK(RelNegativePartialCharge)
	RelNegativePartialCharge rnpc;
	S.apply(rnpc);

	double results[] = {0.166667, 0.166667, 0.163618, 0.140565, 0.173074, 0.163544, 0.333333, 0.190254, 0};
	for (Size i=0;i!=limit;++i)
	{
		molecule = S.getMolecule(i);
		TEST_EQUAL(molecule->hasProperty("RelNegativePartialCharge"), true)
		if (molecule->hasProperty("RelNegativePartialCharge"))
		{
			double value = molecule->getProperty("RelNegativePartialCharge").getDouble();
			TEST_REAL_EQUAL(value, results[i])
		}
	}

RESULT

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
