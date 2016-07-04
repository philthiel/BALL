//_new_file_header


#include <BALL/test/testConfig.h>
#include <BALL/core/concept/classTest.h>

///////////////////////////

#include <BALL/core/qsar/allModel.h>
#include <BALL/core/qsar/QSARData.h>

using namespace BALL::QSAR;

///////////////////////////

START_TEST(ALL-model)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

PRECISION(1E-7)

QSARData data;
data.readCSVFile(TEST_DATA_PATH(ball_core/Regression_test.csv),1,1,1,"	",0,0);

CHECK(ALL-model)
	ALLModel model(data,3);
	model.readTrainingData();
	model.train();
	model.validation->testInputData();
	double r2=model.validation->getFitRes();
	TEST_REAL_EQUAL(r2,0.4702708)
RESULT

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////


END_TEST
