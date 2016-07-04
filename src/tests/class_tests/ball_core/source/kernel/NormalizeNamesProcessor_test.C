//_new_file_header


#include <BALL/core/concept/classTest.h>

///////////////////////////

#include <BALL/core/format/PDBFile.h>
#include <BALL/core/kernel/system.h>
#include <BALL/core/structure/fragmentDB.h>

using namespace BALL;

///////////////////////////

START_TEST(FragmentDB::NormalizeNamesProcessor)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

FragmentDB frag_db("");

FragmentDB::NormalizeNamesProcessor* nnp = 0;
CHECK(NormalizeNamesProcessor())
	nnp = new FragmentDB::NormalizeNamesProcessor;
	TEST_NOT_EQUAL(nnp, 0)
RESULT

CHECK(~NormalizeNamesProcessor())
	delete nnp;
RESULT

CHECK(NormalizeNamesProcessor(FragmentDB& db))
	FragmentDB::NormalizeNamesProcessor nnp(frag_db);
	// ???
RESULT

CHECK(Processor::Result operator () (Fragment& fragment))
  // ???
RESULT

CHECK(bool finish())
  // ???
RESULT

CHECK((bool matchName(String& res_name, String& atom_name, const StringHashMap<String>* map) const))
  // ???
RESULT

CHECK(bool start())
  // ???
RESULT

CHECK(const String& getNamingStandard())
  // ???
RESULT

CHECK(void setFragmentDB(FragmentDB& db))
  // ???
RESULT

CHECK(void setNamingStandard(const String& naming_standard))
  // ???
RESULT

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
