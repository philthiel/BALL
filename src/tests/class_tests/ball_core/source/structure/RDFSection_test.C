//_new_file_header


#include <BALL/core/concept/classTest.h>

///////////////////////////

#include <BALL/core/structure/RDFSection.h>

using namespace BALL;

///////////////////////////

START_TEST(RDFSection)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

RDFSection* pointer;

CHECK(RDFSection::RDFSection())
  pointer = new RDFSection();
	TEST_NOT_EQUAL(pointer, 0)
RESULT


CHECK(RDFSection::~RDFSection())
  delete pointer;
RESULT


CHECK(RDFSection::RDFSection(const RDFSection& rdf_section))
  //?????
RESULT


CHECK(RDFSection::destroy())
  //?????
RESULT


CHECK(RDFSection::clear())
  //?????
RESULT


CHECK(RDFSection::set(const RDFSection& rdf_section))
  //?????
RESULT


CHECK(RDFSection::RDFSection& operator = (const RDFSection& rdf_section))
  //?????
RESULT


CHECK(RDFSection::extractSection(Parameters& parameters, const String& section_name))
  //?????
RESULT


CHECK(RDFSection::getRDF() const )
  //?????
RESULT




/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
