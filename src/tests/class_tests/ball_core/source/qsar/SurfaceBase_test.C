//_new_file_header


#include <BALL/core/concept/classTest.h>
#include <BALL/test/testConfig.h>

///////////////////////////

#include <BALL/core/format/SDFile.h>
#include <BALL/core/kernel/system.h>
#include <BALL/core/kernel/molecule.h>
#include <BALL/core/kernel/PTE.h>
#include <BALL/core/qsar/surfaceBase.h>

using namespace BALL;

///////////////////////////

START_TEST(SurfaceBase)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

SDFile infile(TEST_DATA_PATH(ball_core/descriptors_test.sdf));
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
