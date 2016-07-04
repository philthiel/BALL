//_new_file_header


#include <BALL/test/testConfig.h>
#include <BALL/core/concept/classTest.h>

///////////////////////////

#include <BALL/core/qsar/QSARData.h>
#include <BALL/core/qsar/mlrModel.h>

using namespace BALL::QSAR;

///////////////////////////

START_TEST(MLR-model)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

PRECISION(1E-7)

QSARData data;
data.readCSVFile(TEST_DATA_PATH(ball_core/Regression_test.csv),1,1,1,"	",0,0);

CHECK(MLR-model)
	MLRModel mlr(data);
	mlr.readTrainingData();
	mlr.train();
	const Eigen::MatrixXd* res = mlr.getTrainingResult();
	TEST_EQUAL(res->rows(),3)
	TEST_REAL_EQUAL((*res)(0,0),0.1407737)
	TEST_REAL_EQUAL((*res)(1,0),0.5902179)
	TEST_REAL_EQUAL((*res)(2,0),0.4159182)
RESULT

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

END_TEST
