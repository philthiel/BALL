// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#include <BALL/core/concept/classTest.h>
#include <BALL/test/testConfig.h>

///////////////////////////
#include <BALL/core/solvation/solventParameter.h>
///////////////////////////

START_TEST(SolventParameter)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

using namespace BALL;

SolventParameter* s_ptr;

CHECK(SolventParameter())
	s_ptr = new SolventParameter;	
	TEST_NOT_EQUAL(s_ptr,0)
	bool test = ( "" == s_ptr->getSolventName());
	TEST_EQUAL(test,true)
	test = ( 0.0 == s_ptr->getSolventDensity());
	TEST_EQUAL(test,true)
  ::std::vector<SolventAtomDescriptor> test_sae;
	//test = ( test_sae == s_ptr->getSolventDescription()); 
  //TEST_EQUAL(test, true)
  SolventDescriptor test_sd;
	test = ( test_sd == s_ptr->getSolventDescriptor());
	TEST_EQUAL(test, true)
RESULT


CHECK(~SolventParameter())
	delete s_ptr;
RESULT

CHECK(extractSection(Parameters& parameters, const String& section_name))
	//????? , da ????? in SolventParameter.C
 	bool result;
	SolventParameter s_ptr;

	Parameters param(TEST_DATA_PATH(ball_core/SolventParameter_test1.ini));
	param.init();
	CAPTURE_OUTPUT_LEVEL(2000)	
	result = s_ptr.extractSection(param,"SolventDescription");
	COMPARE_OUTPUT("SolventParameter::extractSection(): Variable missing.\n")
	TEST_EQUAL(result,false)
	
	param = Parameters(TEST_DATA_PATH(ball_core/SolventParameter_test2.ini));
	param.init();
	CAPTURE_OUTPUT_LEVEL(2000)	
	result = s_ptr.extractSection(param,"SolventDescription");
	COMPARE_OUTPUT("SolventParameter::extractSection(): no name given.\n")
	TEST_EQUAL(result,true)
	
	param = Parameters(TEST_DATA_PATH(ball_core/SolventParameter_test3.ini));
	param.init();
	CAPTURE_OUTPUT_LEVEL(2000)	
	result = s_ptr.extractSection(param,"SolventDescription");
	COMPARE_OUTPUT("SolventParameter::extractSection(): no number density given.\n")
	TEST_EQUAL(result,true)

	param = Parameters(TEST_DATA_PATH(ball_core/SolventParameter_test4.ini));
	param.init();
	CAPTURE_OUTPUT_LEVEL(2000)	
	result = s_ptr.extractSection(param,"SolventDescription");
	COMPARE_OUTPUT("SolventParameter::extractSection(): Cannot assign atom type.\n")
	TEST_EQUAL(result,true)
	
	param = Parameters(TEST_DATA_PATH(ball_core/SolventParameter_test.ini));
	param.init();
	result = s_ptr.extractSection(param,"SolventDescription");
	TEST_EQUAL(result,true)
RESULT


CHECK(clear())	
	SolventParameter s_ptr;
	Parameters param(TEST_DATA_PATH(ball_core/SolventParameter_test.ini));
	param.init();
	s_ptr.extractSection(param,"SolventDescription");
	s_ptr.clear();
	SolventParameter s_ptr2;
	//assumes that operator == is correct
	bool result = (s_ptr==s_ptr2);
	TEST_EQUAL(result,true)
RESULT


CHECK(SolventParameter& operator = (const SolventParameter& param))
	SolventParameter s_ptr;
	Parameters param(TEST_DATA_PATH(ball_core/SolventParameter_test.ini));
	param.init();
	s_ptr.extractSection(param,"SolventDescription");
	SolventParameter s_ptr2;
	s_ptr2=s_ptr;
	//assumes that operator == is correct
	bool result = (s_ptr==s_ptr2);
	TEST_EQUAL(result,true)
RESULT


CHECK(SolventParameter(const SolventParameter& param))
	SolventParameter s_ptr;
	Parameters param(TEST_DATA_PATH(ball_core/SolventParameter_test.ini));
	param.init();
	s_ptr.extractSection(param,"SolventDescription");
	SolventParameter s_ptr2;
	s_ptr2 = SolventParameter(s_ptr);
	//assumes that operator == is correct
	bool result = (s_ptr==s_ptr2);
	TEST_EQUAL(result,true)
RESULT


CHECK(getSolventDescriptor() const )
	SolventParameter s_ptr;
	Parameters param(TEST_DATA_PATH(ball_core/SolventParameter_test.ini));
	param.init();
	s_ptr.extractSection(param,"SolventDescription");
	const SolventDescriptor sd = s_ptr.getSolventDescriptor();
	TEST_EQUAL(sd.getName(),"PCM")
RESULT


CHECK(getSolventDescriptor() )
	SolventParameter s_ptr;
	Parameters param(TEST_DATA_PATH(ball_core/SolventParameter_test.ini));
	param.init();
	s_ptr.extractSection(param,"SolventDescription");
	SolventDescriptor sd = s_ptr.getSolventDescriptor();
	TEST_EQUAL(sd.getName(),"PCM")
RESULT


CHECK(operator == (const SolventParameter& param) const)
	//????? , da ????? in Quellcode
RESULT



/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
