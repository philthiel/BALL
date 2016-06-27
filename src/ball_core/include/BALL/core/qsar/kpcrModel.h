//_new_file_header


#ifndef BALL_CORE_QSAR_KPCRMODEL_H
#define BALL_CORE_QSAR_KPCRMODEL_H

#include <BALL/core/qsar/kernelModel.h>
#include <BALL/core/qsar/nonlinearModel.h>
#include <BALL/core/qsar/pcrModel.h>

#include <vector>


namespace BALL
{
	namespace QSAR
	{
		/** class for kernel principal component regression */
		class BALL_EXPORT KPCRModel : public KernelModel, public LatentVariableModel
		{
			public:
				/** @name Constructors and Destructors
				 */
				//@{
				KPCRModel(const QSARData& q, int k_type, double p1, double p2=-1);
				
				KPCRModel(const QSARData& q, Eigen::VectorXd& w);
				
				KPCRModel(const QSARData& q, String s1, String s2);
				
				KPCRModel(const QSARData& q, const LinearModel& lm, int column);

				~KPCRModel();
				//@}
				
				
				/** @name Accessors
				 */
				//@{
				/** set the fraction of the variance that should be explained by the latente variables. */
				void setFracVar(double frac_var);
				
				void train();
				
				void setParameters(std::vector<double>& v);
				
				std::vector<double> getParameters() const;
				//@}
				
				
			private:
				
				double frac_var_;
		};
	}
}

#endif // BALL_CORE_QSAR_KPCRMODEL_H
