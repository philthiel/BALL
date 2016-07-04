//_new_file_header


#include <BALL/core/concept/classTest.h>

///////////////////////////

#include <BALL/core/format/HINFile.h>
#include <BALL/core/format/PDBFile.h>
#include <BALL/core/kernel/system.h>
#include <BALL/core/nmr/spectrum.h>
#include <BALL/core/nmr/peak.h>
#include <BALL/core/structure/fragmentDB.h>
#include <BALL/core/structure/residueChecker.h>

using namespace std;
using namespace BALL;

///////////////////////////

START_TEST(Spectrum1D)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

Spectrum1D* p;

CHECK(Spectrum1D::Spectrum1D())
	p = new Spectrum1D;
	TEST_NOT_EQUAL(p, 0);
RESULT

CHECK(Spectrum1D::~Spectrum1D())
	delete p;
RESULT


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
