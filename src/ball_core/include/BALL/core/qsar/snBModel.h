//_new_file_header


#ifndef BALL_CORE_QSAR_SNBMODEL_H
#define BALL_CORE_QSAR_SNBMODEL_H

#include <BALL/core/qsar/bayesModel.h>
#include <BALL/core/qsar/common.h>
#include <BALL/core/qsar/statistics.h>

#include <vector>


namespace BALL{
	namespace QSAR {

		/** class for simple naive Bayes */
		class BALL_EXPORT SNBModel : public BayesModel
		{ 
			public:
				/** @name Constructors and Destructors
				 */
				//@{
				SNBModel(const QSARData& q);

				~SNBModel();
				//@}
				
				
				/** @name Accessors
				 */
				//@{
				void train();
				
				Eigen::VectorXd predict(const std::vector<double>& substance, bool transform=1);
				
				std::vector<double> getParameters() const;
				
				void setParameters(std::vector<double>& v);
				
				void saveToFile(String filename);
				
				bool isTrained();
				
				void readFromFile(String filename);
				
				/** calculate the probability for the specified feature to assume the given value for each class
				@return a probability for each class */
				std::vector<double> calculateProbabilities(int activitiy_index, int feature_index, double feature_value);
				
				int getNoResponseVariables();
				//@}
				
				
			private:
				/** @name Attributes
				 */
				//@{
				/** vector containing one matrix for each modelled activity which holds the mean of each feature for each class */
				MatrixVector mean_;
				
				/** vector containing one matrix for each modelled activity which holds the standard deviation of each feature for each class */
				MatrixVector stddev_;
				
				static const double sqrt2Pi_;
							

				
				//@}
		};
	}
}

#endif // BALL_CORE_QSAR_SNBMODEL_H
