//_new_file_header


#ifndef BALL_CORE_QSAR_SVMMODEL_H
#define BALL_CORE_QSAR_SVMMODEL_H

#include <BALL/core/qsar/classificationModel.h>
#include <BALL/core/qsar/kernelModel.h>
#include <BALL/core/qsar/nonlinearModel.h>


namespace BALL{
	namespace QSAR {

		/** class for support vector classification */
		class BALL_EXPORT SVMModel : public ClassificationModel
		{ 
			public:
				/** @name Constructors and Destructors
				 */
				//@{
				SVMModel(const QSARData& q);

				virtual ~SVMModel();
				//@}			
				
				
		};
	}
}

#endif // BALL_CORE_QSAR_SVMMODEL_H
