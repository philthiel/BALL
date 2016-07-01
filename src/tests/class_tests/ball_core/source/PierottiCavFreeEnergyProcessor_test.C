// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#include <BALL/core/concept/classTest.h>
#include <testConfig.h>

///////////////////////////
#include <BALL/core/solvation/pierottiCavFreeEnergyProcessor.h>
#include <BALL/core/format/HINFile.h>
#include <BALL/core/kernel/system.h>
#include <BALL/core/energy/energyProcessor.h>
#include <BALL/core/structure/fragmentDB.h>
///////////////////////////

START_TEST(PierottiCavFreeEnergyProcessor)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

using namespace BALL;

CHECK(PierottiCavFreeEnergyProcessor::PierottiCavFreeEnergyProcessor())
	PierottiCavFreeEnergyProcessor* proc = new PierottiCavFreeEnergyProcessor;
	TEST_NOT_EQUAL(proc, 0)
	TEST_EQUAL(proc->isValid(), true)
	TEST_REAL_EQUAL(proc->getEnergy(), 0)
	delete proc;
RESULT 

CHECK(PierottiCavFreeEnergyProcessor::PierottiCavFreeEnergyProcessor(const PierottiCavFreeEnergyProcessor& proc))
  HINFile f(TEST_DATA_PATH(ball_core/methane.hin));
  System S;
  f >> S;
  f.close();
  PierottiCavFreeEnergyProcessor proc;
  S.apply(proc);
  PierottiCavFreeEnergyProcessor proc2(proc); 
  TEST_EQUAL((proc == proc2), true) 
  bool test = proc.isValid() == proc2.isValid();
  TEST_EQUAL(test, true)
  test = proc.getEnergy() == proc2.getEnergy();
  TEST_EQUAL(test, true)
RESULT
  

CHECK(PierottiCavFreeEnergyProcessor::~PierottiCavFreeEnergyProcessor())
	PierottiCavFreeEnergyProcessor* proc = new PierottiCavFreeEnergyProcessor;
	delete proc;
RESULT


CHECK(PierottiCavFreeEnergyProcessor::clear())
  PierottiCavFreeEnergyProcessor proc;
  proc.clear();
RESULT


CHECK(PierottiCavFreeEnergyProcessor::PierottiCavFreeEnergyProcessor& operator = (const PierottiCavFreeEnergyProcessor& proc) + operator ==)
  HINFile f(TEST_DATA_PATH(ball_core/methane.hin));
  System S;
  f >> S;
  f.close();
  PierottiCavFreeEnergyProcessor proc;
  S.apply(proc);
  PierottiCavFreeEnergyProcessor proc2;
  proc2 = proc;
  TEST_EQUAL((proc  ==  proc2), true)
  bool test = proc.isValid() == proc2.isValid();
  TEST_EQUAL(test, true)
  test = proc.getEnergy() == proc2.getEnergy();
  TEST_EQUAL(test, true) 
RESULT


CHECK(PierottiCavFreeEnergyProcessor::start())
  PierottiCavFreeEnergyProcessor proc; 
  TEST_EQUAL(proc.start(), true)
RESULT


CHECK(PierottiCavFreeEnergyProcessor / Methane)
	PRECISION(0.05)
	HINFile f(TEST_DATA_PATH(ball_core/methane.hin));
	System S;
	f >> S;
	f.close();
	PierottiCavFreeEnergyProcessor proc;
	S.apply(proc);
	TEST_REAL_EQUAL(proc.getEnergy(),20.6908)
	TEST_EQUAL(S.countAtoms(),5)
RESULT

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
