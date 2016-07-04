//_new_file_header


#include <BALL/test/testConfig.h>
#include <BALL/core/concept/classTest.h>

///////////////////////////

#include <BALL/core/qsar/QSARData.h>
#include <BALL/core/qsar/snBModel.h>

using namespace BALL::QSAR;

///////////////////////////

START_TEST(SNB-model)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

PRECISION(1E-7)

QSARData data;
data.readCSVFile(TEST_DATA_PATH(ball_core/Regression_test.csv),1,1,1,"	",0,0);

CHECK(SNB-model)
	SNBModel model(data);
	model.readTrainingData();
	model.train();
	model.validation->testInputData();
	double quality=model.validation->getFitRes();
	TEST_REAL_EQUAL(quality,0.25)
RESULT

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

END_TEST
