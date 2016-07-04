//_new_file_header


#include <BALL/core/concept/classTest.h>
#include <BALL/test/testConfig.h>

///////////////////////////

#include <BALL/core/format/SDFile.h>
#include <BALL/core/kernel/system.h>
#include <BALL/core/kernel/molecule.h>
#include <BALL/core/qsar/partialChargeProcessor.h>

using namespace BALL;

///////////////////////////

START_TEST(PartialChargeProcessor)

/////////////////////////////////////////////////////////////
// tests only if the partial charge processor
// creates the PEOEPartialCharge proeprty
// no numerical correctness is tested
/////////////////////////////////////////////////////////////

SDFile infile(TEST_DATA_PATH(ball_core/descriptors_test.sdf));
System S;
infile >> S;
infile.close();

Molecule * molecule;
Size limit = S.countMolecules();

CHECK(PartialChargeProcessor)	

	PartialChargeProcessor pcp;
	S.apply(pcp);

	for (Size i=0;i!=limit;++i)
	{
		molecule = S.getMolecule(i);
		AtomConstIterator a_it = molecule->beginAtom();
		for (;a_it!=molecule->endAtom();++a_it)
		{
			TEST_EQUAL(a_it->hasProperty("PEOEPartialCharge"), true)
		}
	}
RESULT

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

END_TEST
