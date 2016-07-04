//_new_file_header


#include <BALL/core/concept/classTest.h>
#include <BALL/test/testConfig.h>

///////////////////////////

#include <BALL/core/qsar/knnModel.h>
#include <BALL/core/qsar/QSARData.h>

using namespace BALL::QSAR;

///////////////////////////

START_TEST(KNN-model)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

PRECISION(1E-7)

QSARData data;
data.readCSVFile(TEST_DATA_PATH(ball_core/Regression_test.csv),1,1,1,"	",0,0);

CHECK(KNN-model)
	KNNModel model(data,3);
	model.readTrainingData();
	model.train();
	model.validation->testInputData();
	double r2=model.validation->getFitRes();
	TEST_REAL_EQUAL(r2,0.9995563)
RESULT

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

END_TEST
