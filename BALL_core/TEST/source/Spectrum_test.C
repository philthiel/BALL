// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#include <BALL_core/CONCEPT/classTest.h>

///////////////////////////
#include <BALL_core/FORMAT/HINFile.h>
#include <BALL_core/FORMAT/PDBFile.h>
#include <BALL_core/STRUCTURE/fragmentDB.h>
#include <BALL_core/STRUCTURE/residueChecker.h>
#include <BALL_core/NMR/spectrum.h>
#include <BALL_core/NMR/peak.h>
#include <BALL_core/KERNEL/system.h>
///////////////////////////

START_TEST(Spectrum1D)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

using namespace BALL;
using namespace std;

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
