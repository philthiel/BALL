//_new_file_header


#ifndef BALL_CORE_QSAR_LOGITMODEL_H
#define BALL_CORE_QSAR_LOGITMODEL_H

#include <BALL/core/qsar/classificationModel.h>

#include <vector>


namespace BALL{
	namespace QSAR {

		/** class for logistic regression */
		class BALL_EXPORT LogitModel : public ClassificationModel
		{ 
			public:
				/** @name Constructors and Destructors
				 */
				//@{
				LogitModel(const QSARData& q);

				~LogitModel();

				EIGEN_MAKE_ALIGNED_OPERATOR_NEW
				//@}
				
				
				/** @name Accessors
				 */
				//@{
				void train();
				
				Eigen::VectorXd predict(const std::vector<double>& substance, bool transform);
				
				void saveToFile(String filename);
				
				void readFromFile(String filename);
				//@}
				
				
			protected:	
				/** @name Attributes
				 */
				//@{
				Eigen::MatrixXd training_result_;
				//@}
				
		};
	}
}

#endif // BALL_CORE_QSAR_LOGITMODEL_H
