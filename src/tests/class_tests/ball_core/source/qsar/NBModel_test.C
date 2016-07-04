//_new_file_header


#include <BALL/test/testConfig.h>
#include <BALL/core/concept/classTest.h>

///////////////////////////

#include <BALL/core/qsar/QSARData.h>
#include <BALL/core/qsar/nBModel.h>

using namespace BALL::QSAR;

///////////////////////////

START_TEST(NB-model)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

PRECISION(1E-7)

QSARData data;
data.readCSVFile(TEST_DATA_PATH(ball_core/Regression_test.csv),1,1,1,"	",0,0);

CHECK(NB-model)
	NBModel model(data);
	model.readTrainingData();
	model.train();
	model.validation->testInputData();
	double quality=model.validation->getFitRes();
	TEST_REAL_EQUAL(quality,1.0)
RESULT

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

END_TEST
