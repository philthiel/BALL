//_new_file_header


#ifndef BALL_CORE_QSAR_NLMODEL_H
#define BALL_CORE_QSAR_NLMODEL_H

#include <BALL/core/qsar/regressionModel.h>


namespace BALL
{
	namespace QSAR
	{
		class BALL_EXPORT NonLinearModel : public RegressionModel
		{
			public:
				/** @name Constructors and Destructors
				 */
				//@{
				NonLinearModel(const QSARData& q);

				~NonLinearModel();
				
			protected:
				/** do nothing for non-kernel models. KernelModel on the other hand overloads this function... */
				virtual void calculateOffsets() {};
				//@}	
	
	
	
	
		};
	}
}


#endif // BALL_CORE_QSAR_NLMODEL_H
