//_new_file_header


#ifndef BALL_CORE_QSAR_KNNMODEL_H
#define BALL_CORE_QSAR_KNNMODEL_H

#include <BALL/core/qsar/allModel.h>

#include <vector>


namespace BALL
{
	namespace QSAR
	{

		/** class for automated lazy learning (ALL-QSAR) */
		class BALL_EXPORT KNNModel : public ALLModel
		{ 
			public:
				/** @name Constructors and Destructors
				 */
				//@{
				KNNModel(const QSARData& q, int k=3);
				//@}
				
				void calculateWeights(Eigen::MatrixXd& dist, Eigen::VectorXd& w);
				
				void setParameters(std::vector<double>& v);
				
				std::vector<double> getParameters() const;
				
				bool optimizeParameters(int k, int no_steps);
				
			private:
				int k_ ;
		};
	}
}

#endif // BALL_CORE_QSAR_KNNMODEL_H
