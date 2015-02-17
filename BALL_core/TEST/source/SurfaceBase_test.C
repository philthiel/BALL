// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#include <BALL_core/CONCEPT/classTest.h>
#include <BALLTestConfig.h>

///////////////////////////

#include <BALL_core/QSAR/surfaceBase.h>
#include <BALL_core/FORMAT/SDFile.h>
#include <BALL_core/KERNEL/system.h>
#include <BALL_core/KERNEL/molecule.h>
#include <BALL_core/KERNEL/PTE.h>


///////////////////////////
START_TEST(SurfaceBase)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

using namespace BALL;

SDFile infile(BALL_TEST_DATA_PATH(descriptors_test.sdf));
System S;
infile >> S;
infile.close();

Molecule * molecule;
Size limit = S.countMolecules();

CHECK(SurfaceBase)	

	SurfaceBase sb;
	S.apply(sb);

	for (Size i=0;i!=limit;++i)
	{
		molecule = S.getMolecule(i);
		TEST_EQUAL(molecule->hasProperty("PositiveVdWSurface"), true)
		TEST_EQUAL(molecule->hasProperty("NegativeVdWSurface"), true)
		TEST_EQUAL(molecule->hasProperty("PositivePolarVdWSurface"), true)
		TEST_EQUAL(molecule->hasProperty("NegativePolarVdWSurface"), true)
		TEST_EQUAL(molecule->hasProperty("HydrophobicVdWSurface"), true)
		TEST_EQUAL(molecule->hasProperty("PolarVdWSurface"), true)
		TEST_EQUAL(molecule->hasProperty("VdWSurface"), true)
		TEST_EQUAL(molecule->hasProperty("VdWVolume"), true)
		TEST_EQUAL(molecule->hasProperty("Density"), true)
	}
		
RESULT

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
