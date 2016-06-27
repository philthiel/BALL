//_new_file_header


#ifndef BALL_CORE_QSAR_LDAMODEL_H
#define BALL_CORE_QSAR_LDAMODEL_H

#include <BALL/core/qsar/classificationModel.h>
#include <BALL/core/qsar/statistics.h>

#include <vector>


namespace BALL{
	namespace QSAR {

		/** class for support vector classification */
		class BALL_EXPORT LDAModel : public ClassificationModel
		{ 
			public:
				/** @name Constructors and Destructors
				 */
				//@{
				LDAModel(const QSARData& q);

				~LDAModel();
				//@}
				
				
				/** @name Accessors
				 */
				//@{
				void train();
				
				Eigen::VectorXd predict(const std::vector<double>& substance, bool transform=1);

				void setParameters(std::vector<double>& v);
				
				std::vector<double> getParameters() const;
				
				void saveToFile(String filename);
				
				void readFromFile(String filename);
				//@}
				
				
			private:
				/** @name Attributes
				 */
				//@{
				/** covariance matrix of descriptors */
				Eigen::MatrixXd sigma_;
				

				double lambda_;				

				/** vector containing one matrix for each modelled activity. Each matrix contains a mean vector of a class in each line */
				std::vector<Eigen::MatrixXd > mean_vectors_;
				//@}
		};
	}
}

#endif // BALL_CORE_QSAR_LDAMODEL_H
