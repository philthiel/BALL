//_new_file_header


#ifndef BALL_CORE_QSAR_LMODEL_H
#define BALL_CORE_QSAR_LMODEL_H

#include <BALL/core/qsar/regressionModel.h>

#include <vector>


namespace BALL
{
	namespace QSAR
	{
		class BALL_EXPORT LinearModel : public RegressionModel
		{
		
			public: 
				/** @name Constructors and Destructors
				 */
				//@{
				/** constructur,
				@param q QSAR-wrapper object, from which the data for this model should be taken */
				LinearModel(const QSARData& q);
		
				~LinearModel();
				
				virtual void operator=(const LinearModel& m);
				
				//@}
				
				
				/** @name Accessors
				 */
				//@{
				virtual Eigen::VectorXd predict(const std::vector<double>& substance, bool transform=1);
	
			protected:
				void calculateOffsets();
				//@}
		};
	}
}

#endif // BALL_CORE_QSAR_LMODEL_H
