// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#include <BALL_core/CONCEPT/classTest.h>
#include <BALLTestConfig.h>

#include <BALL_core/FORMAT/PDBFile.h>
#include <BALL_core/KERNEL/forEach.h>
#include <BALL_core/KERNEL/bond.h>
#include <BALL_core/KERNEL/extractors.h>

#include <BALL_view/PRIMITIVES/disc.h>
#include <BALL_view/PRIMITIVES/tube.h>

///////////////////////////
#include <BALL_view/MODELS/HBondModel.h>
///////////////////////////

using namespace BALL;
using namespace BALL::VIEW;

START_TEST(HBondModelProcessor)

CHECK(CSTR)
	HBondModelProcessor();
RESULT

CHECK(HBondModelProcessor::BALL_CREATE(HBondModelProcessor))
  //BAUSTELLE
RESULT


PDBFile pdb(BALL_TEST_DATA_PATH(1BNA.pdb));
System system;
pdb >> system;

CHECK(HBondModelProcessor::Processor::Result operator() (Composite& composite))
	HBondModelProcessor bs;
	bool result = bs.operator() (system);
	TEST_EQUAL(result, true)
RESULT

CHECK(HBondModelProcessor::createGeometricObjects() throw())
	HBondModelProcessor bs;
	system.apply(bs);
	bs.createGeometricObjects();
	TEST_EQUAL(bs.getGeometricObjects().size(), 96 * 3 )
RESULT

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
