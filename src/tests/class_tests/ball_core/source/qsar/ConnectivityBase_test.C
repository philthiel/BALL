//_new_file_header


#include <BALL/core/concept/classTest.h>
#include <BALL/test/testConfig.h>

///////////////////////////

#include <BALL/core/format/SDFile.h>
#include <BALL/core/kernel/system.h>
#include <BALL/core/kernel/molecule.h>
#include <BALL/core/qsar/connectivityBase.h>

using namespace BALL;

///////////////////////////

START_TEST(ConnectivityBase)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

SDFile infile(TEST_DATA_PATH(ball_core/descriptors_test.sdf));
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
