// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#include <BALL_core/CONCEPT/classTest.h>
#include <BALLTestConfig.h>

///////////////////////////
#include <BALL_core/SOLVATION/reissCavFreeEnergyProcessor.h>
#include <BALL_core/FORMAT/HINFile.h>
#include <BALL_core/KERNEL/system.h>
#include <BALL_core/ENERGY/energyProcessor.h>
#include <BALL_core/STRUCTURE/fragmentDB.h>
///////////////////////////

START_TEST(ReissCavFreeEnergyProcessor)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

using namespace BALL;

CHECK(ReissCavFreeEnergyProcessor::ReissCavFreeEnergyProcessor())
	ReissCavFreeEnergyProcessor* proc = new ReissCavFreeEnergyProcessor;
	TEST_NOT_EQUAL(proc, 0)
	TEST_EQUAL(proc->isValid(), true)
	TEST_REAL_EQUAL(proc->getEnergy(), 0)
	delete proc;
RESULT 

CHECK(ReissCavFreeEnergyProcessor::ReissCavFreeEnergyProcessor(const ReissCavFreeEnergyProcessor& proc))
  HINFile f(BALL_TEST_DATA_PATH(methane.hin));
  System S;
  f >> S;
  f.close();
  ReissCavFreeEnergyProcessor proc;
  S.apply(proc);
  ReissCavFreeEnergyProcessor proc2(proc); 
  TEST_EQUAL((proc == proc2), true) 
  bool test = proc.isValid() == proc2.isValid();
  TEST_EQUAL(test, true)
  test = proc.getEnergy() == proc2.getEnergy();
  TEST_EQUAL(test, true)
RESULT
  

CHECK(ReissCavFreeEnergyProcessor::~ReissCavFreeEnergyProcessor())
	ReissCavFreeEnergyProcessor* proc = new ReissCavFreeEnergyProcessor;
	delete proc;
RESULT


CHECK(ReissCavFreeEnergyProcessor::clear())
  ReissCavFreeEnergyProcessor proc;
  proc.clear();
RESULT


CHECK(ReissCavFreeEnergyProcessor::ReissCavFreeEnergyProcessor& operator = (const ReissCavFreeEnergyProcessor& proc) + operator ==)
  HINFile f(BALL_TEST_DATA_PATH(methane.hin));
  System S;
  f >> S;
  f.close();
  ReissCavFreeEnergyProcessor proc;
  S.apply(proc);
  ReissCavFreeEnergyProcessor proc2;
  proc2 = proc;
  TEST_EQUAL((proc  ==  proc2), true)
  bool test = proc.isValid() == proc2.isValid();
  TEST_EQUAL(test, true)
  test = proc.getEnergy() == proc2.getEnergy();
  TEST_EQUAL(test, true) 
RESULT


CHECK(ReissCavFreeEnergyProcessor::start())
  ReissCavFreeEnergyProcessor proc; 
  TEST_EQUAL(proc.start(), true)
RESULT


CHECK(ReissCavFreeEnergyProcessor / Methane)
	PRECISION(0.05)
	HINFile f(BALL_TEST_DATA_PATH(methane.hin));
	System S;
	f >> S;
	f.close();
	ReissCavFreeEnergyProcessor proc;
	S.apply(proc);
	TEST_REAL_EQUAL(proc.getEnergy(),20.68)
	TEST_EQUAL(S.countAtoms(),5)
RESULT

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
