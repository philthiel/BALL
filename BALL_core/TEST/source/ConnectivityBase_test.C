// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#include <BALL_core/CONCEPT/classTest.h>
#include <BALLTestConfig.h>

///////////////////////////

#include <BALL_core/QSAR/connectivityBase.h>
#include <BALL_core/FORMAT/SDFile.h>
#include <BALL_core/KERNEL/system.h>
#include <BALL_core/KERNEL/molecule.h>

///////////////////////////
START_TEST(ConnectivityBase)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

using namespace BALL;

SDFile infile(BALL_TEST_DATA_PATH(descriptors_test.sdf));
System S;
infile >> S;
infile.close();

Molecule * molecule;
Size limit = S.countMolecules();

CHECK(ConnectivityBase)	

	ConnectivityBase cb;
	S.apply(cb);

	for (Size i=0;i!=limit;++i)
	{
		molecule = S.getMolecule(i);
		TEST_EQUAL(molecule->hasProperty("BalabanIndexJ"), true);
	}
		
RESULT


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
