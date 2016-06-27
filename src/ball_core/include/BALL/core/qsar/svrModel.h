//_new_file_header


#ifndef BALL_CORE_QSAR_SVRMODEL_H
#define BALL_CORE_QSAR_SVRMODEL_H

#include <BALL/core/qsar/kernelModel.h>
#include <BALL/core/qsar/nonlinearModel.h>


namespace BALL
{
	namespace QSAR
	{
		class BALL_EXPORT SVRModel : public KernelModel
		{
			public:
				/** @name Constructors and Destructors
				 */
				//@{
				SVRModel(const QSARData& q, int k_type, double p1, double p2);

				~SVRModel();
				//@}
				
	
	
		};
	}
}


#endif // BALL_CORE_QSAR_SVRMODEL_H
