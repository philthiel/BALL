// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#include <BALL_core/CONCEPT/classTest.h>
#include <BALLTestConfig.h>

///////////////////////////

#include <BALL_core/QSAR/simpleDescriptors.h>
#include <BALL_core/QSAR/connectivityDescriptors.h>
#include <BALL_core/FORMAT/SDFile.h>
#include <BALL_core/FORMAT/HINFile.h>
#include <BALL_core/KERNEL/system.h>
#include <BALL_core/KERNEL/molecule.h>
#include <BALL_core/KERNEL/PTE.h>
#include <iostream>
using std::cerr; using std::endl;


///////////////////////////
START_TEST(ConnectivityDescriptors)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

using namespace BALL;

SDFile infile(BALL_TEST_DATA_PATH(descriptors_test.sdf));
System S;
infile >> S;
infile.close();

Molecule * molecule;
Size limit = S.countMolecules();

CHECK(ZagrebIndex)	

	ZagrebIndex z_index;
	S.apply(z_index);

	double results[9] = { 24, 24, 42, 42, 76, 118, 12, 30, 36};
	for (Size i=0;i!=limit;++i)
	{
		molecule = S.getMolecule(i);
		TEST_EQUAL(molecule->hasProperty("ZagrebIndex"), true);
		if (molecule->hasProperty("ZagrebIndex"))
		{
			double value = molecule->getProperty("ZagrebIndex").getDouble();
			TEST_REAL_EQUAL(value, results[i])
		}
	}
		
RESULT

////////////////////////////////////////
//  BALABAN INDEX J 
/////////////////////

CHECK(BalabanIndexJ)

	BalabanIndexJ balaban_j;
	S.apply(balaban_j);

	PRECISION(0.00001)
	double results[9] = { 2.0, 3.0, 2.41332, 3.24783, 3.17677, 2.21811, 2.32379, 3.02147, 3};
	for (Size i=0;i!=limit;++i)
	{
		molecule = S.getMolecule(i);
		TEST_EQUAL(molecule->hasProperty("BalabanIndexJ"), true)
		if (molecule->hasProperty("BalabanIndexJ"))
		{
			double value = molecule->getProperty("BalabanIndexJ").getDouble();
			TEST_REAL_EQUAL(value, results[i])
		}
	}

RESULT

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
