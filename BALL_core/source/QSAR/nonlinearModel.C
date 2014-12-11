// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
//

#include <BALL_core/QSAR/nonlinearModel.h>

namespace BALL
{
	namespace QSAR
			{

		NonLinearModel::NonLinearModel(const QSARData& q) : RegressionModel(q) { }

		NonLinearModel::~NonLinearModel()
		{
		}

	}
}
