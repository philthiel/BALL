//_new_file_header


#ifndef BALL_CORE_QSAR_RIDGEMODEL_H
#define BALL_CORE_QSAR_RIDGEMODEL_H

#include <BALL/core/qsar/exception.h>
#include <BALL/core/qsar/mlrModel.h>

#include <vector>


namespace BALL
{
	namespace QSAR
	{
		class BALL_EXPORT RRModel : public MLRModel
		{
			public:
				/** @name Constructors and Destructors
				 */
				//@{
				/** constructur
				@param q QSARData object, from which the data for this model should be taken */
				RRModel(const QSARData& q, double lambda=0.003);

				~RRModel();
				//@}
				
				/** @name Accessors
				 */
				//@{
				/** Starts multiple linear regression with the current data and saves the resulting linear combination of descriptors to training_result. \n */
				void train();
				
				void setParameters(std::vector<double>& v);
				
				std::vector<double> getParameters() const;
				//@}
		
			private:
				/** @name Attributes
				 */
				//@{
				double lambda_;
				
				//@}
		};
	}
}

#endif // BALL_CORE_QSAR_RIDGEMODEL_H

