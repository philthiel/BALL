//_new_file_header


#ifndef BALL_CORE_QSAR_MLRMODEL_H
#define BALL_CORE_QSAR_MLRMODEL_H

#include <BALL/core/qsar/exception.h>
#include <BALL/core/qsar/linearModel.h>


namespace BALL
{
	namespace QSAR
	{
		class BALL_EXPORT MLRModel : public LinearModel
		{
			public:
				/** @name Constructors and Destructors
				 */
				//@{
				/** constructur
				@param q QSAR-wrapper object, from which the data for this model should be taken */
				MLRModel(const QSARData& q);

				~MLRModel();
				//@}
				
				/** @name Accessors
				 */
				//@{
				/** Starts multiple linear regression with the current data and saves the resulting linear combination of descriptors to training_result. \n 
				In order for this to work, descriptor_matrix MUST have more rows than columns, so that the matrix is invertible !! \n
				If this is not the case, start a feature selection method before running train() !  */
				virtual void train();
				//@}
		};
	}
}

#endif // BALL_CORE_QSAR_MLRMODEL_H
