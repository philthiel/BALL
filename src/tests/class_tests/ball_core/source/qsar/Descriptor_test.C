//_new_file_header


#include <BALL/core/concept/classTest.h>
#include <BALL/test/testConfig.h>

///////////////////////////

#include <BALL/core/format/SDFile.h>
#include <BALL/core/kernel/system.h>
#include <BALL/core/kernel/molecule.h>
#include <BALL/core/qsar/descriptor.h>

using namespace BALL;

///////////////////////////

START_TEST(Descriptor)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

SDFile infile(TEST_DATA_PATH(ball_core/descriptors_test.sdf));
System S;
infile >> S;
infile.close();

Molecule * molecule;
Size limit = S.countMolecules();

CHECK(Descriptor)	

	Descriptor desc;
	const String name = "the fancy name";
	const String unit = "a heavy unit";

	// test default values
	TEST_EQUAL(desc.getName(), "generic descriptor")
	TEST_EQUAL(desc.getUnit(), "")
	
	desc.setName(name);
	desc.setUnit(unit);
	S.apply(desc);

	for (Size i=0;i!=limit;++i)
  {
		molecule = S.getMolecule(i);
		TEST_EQUAL(molecule->hasProperty(name), true)
		TEST_EQUAL(molecule->getProperty(name).getDouble(), 0)
		TEST_EQUAL(desc.getName(), name)
		TEST_EQUAL(desc.getUnit(), unit)
	}

		
RESULT

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
