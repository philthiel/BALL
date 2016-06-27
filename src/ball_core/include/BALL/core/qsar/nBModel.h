//_new_file_header


#ifndef BALL_CORE_QSAR_NBMODEL_H
#define BALL_CORE_QSAR_NBMODEL_H

#include <BALL/core/qsar/bayesModel.h>
#include <BALL/core/qsar/common.h>
#include <BALL/core/qsar/statistics.h>

#include <vector>


namespace BALL
{
	namespace QSAR 
	{

		/** class for Naive Bayes */
		class BALL_EXPORT NBModel : public BayesModel
		{ 
			public:
				/** @name Constructors and Destructors
				 */
				//@{
				NBModel(const QSARData& q);

				~NBModel();

				EIGEN_MAKE_ALIGNED_OPERATOR_NEW
				//@}
				
				
				/** @name Accessors
				 */
				//@{
				void train();
				
				Eigen::VectorXd predict(const std::vector<double>& substance, bool transform=1);
				
				void saveToFile(String filename);
				
				void readFromFile(String filename);
				
				std::vector<double> getParameters() const;
				
				void setParameters(std::vector<double>& v);
				
				bool isTrained();
				
				std::vector<double> calculateProbabilities(int activitiy_index, int feature_index, double feature_value);
				
				int getNoResponseVariables();	
				//@}
				
				
			private:
				/** @name Attributes
				 */
				//@{
				
				unsigned int discretization_steps_;
				
				
				/** the minmum (row1) and maximum (row2) of each feature. */
				Eigen::MatrixXd min_max_;
				
				/** One probability Matrix for each modelled activity and each class. \n
				Each Matrix stores in each cell the probability for a feature lying within a specific range to be in a specific class  */
				std::vector<MatrixVector, Eigen::aligned_allocator<MatrixVector> > probabilities_;
							

				
				//@}
		};
	}
}

#endif // BALL_CORE_QSAR_NBMODEL_H
