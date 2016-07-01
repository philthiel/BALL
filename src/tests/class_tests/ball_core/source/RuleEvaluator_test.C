// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#include <BALL/core/concept/classTest.h>
#include <testConfig.h>

///////////////////////////

#include <BALL/core/molmec/common/ruleEvaluator.h>
#include <BALL/core/format/INIFile.h>
#include <BALL/core/format/HINFile.h>
#include <BALL/core/kernel/system.h>
#include <BALL/core/kernel/molecule.h>

///////////////////////////

START_TEST(RuleEvaluator)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

using namespace BALL;

RuleEvaluator* eval;
CHECK(RuleEvaluator::RuleEvaluator())
  eval = new RuleEvaluator;
	TEST_NOT_EQUAL(eval, 0)
RESULT


CHECK(RuleEvaluator::~RuleEvaluator())
  delete eval;
RESULT


CHECK(RuleEvaluator::setPrefix() const )
	eval = new RuleEvaluator;
	eval->setPrefix("PREFIX");
RESULT


CHECK(RuleEvaluator::getPrefix() const )
  TEST_EQUAL(eval->getPrefix(), "PREFIX")
	eval->setPrefix("");
  TEST_EQUAL(eval->getPrefix(), "")
RESULT

INIFile ini(TEST_DATA_PATH(ball_core/RuleEvaluator_test.ini));
ini.read();
CHECK(RuleEvaluator::RuleEvaluator(INIFile& file, const String& prefix))
	TEST_EQUAL(ini.isValid(), true)
	RuleEvaluator eval(ini, "TEST1");
	TEST_EQUAL(eval.getPrefix(), "TEST1")
	TEST_EQUAL(eval.isValid(), true)
RESULT


CHECK(RuleEvaluator::RuleEvaluator(const RuleEvaluator& evaluator))
	RuleEvaluator ev1(ini, "TEST1");
	RuleEvaluator ev2(ev1);
	TEST_EQUAL(ev2.getPrefix(), "TEST1");
	TEST_EQUAL(ev2.isValid(), true)	
RESULT


CHECK(RuleEvaluator::initialize(INIFile& file, const String& prefix))
  //?????
RESULT


CHECK(RuleEvaluator::clear() const)
	RuleEvaluator eval(ini, "TEST1");
	eval.clear();
	TEST_EQUAL(eval.getPrefix(), "")
	TEST_EQUAL(eval.isValid(), false)
RESULT


CHECK(RuleEvaluator::RuleEvaluator& operator = (const RuleEvaluator& evaluator))
  //?????
RESULT


CHECK(RuleEvaluator::set(const RuleEvaluator& evaluator))
  //?????
RESULT


CHECK(RuleEvaluator::String operator () (const Atom& atom) const )
	RuleEvaluator eval(ini, "TEST1");
	HINFile f(TEST_DATA_PATH(ball_core/RuleEvaluator_test.hin));
	System S;
	f >> S;
	f.close();
	TEST_EQUAL(S.countAtoms(), 5)
	
	AtomIterator it = S.beginAtom();
	TEST_EQUAL(eval.operator()(*it), "F-def")
	++it;
	TEST_EQUAL(eval.operator()(*it), "CT")
	++it;
	TEST_EQUAL(eval.operator()(*it), "HCF")
	++it;
	TEST_EQUAL(eval.operator()(*it), "HCF")
	++it;
	TEST_EQUAL(eval.operator()(*it), "")
RESULT
delete eval;


CHECK(RuleEvaluator::isValid() const )
  //?????
RESULT


CHECK(RuleEvaluator::dump(std::ostream& s = std::cout, Size indent_depth = 0) const )
  //?????
RESULT



/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
