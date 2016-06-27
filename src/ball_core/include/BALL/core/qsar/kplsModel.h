//_new_file_header


#ifndef BALL_CORE_QSAR_KPLSMODEL_H
#define BALL_CORE_QSAR_KPLSMODEL_H

#include <BALL/core/qsar/kernelModel.h>
#include <BALL/core/qsar/latentVariableModel.h>
#include <BALL/core/qsar/nonlinearModel.h>

#include <vector>


namespace BALL
{
	namespace QSAR
	{
		/** kernel partial-least-squares class */
		class BALL_EXPORT KPLSModel : public KernelModel, public LatentVariableModel
		{
			public:
				/** @name Constructors and Destructors
				 */
				//@{
				KPLSModel(const QSARData& q, int k_type, double p1, double p2=-1);
				
				KPLSModel(const QSARData& q, Eigen::VectorXd& w);
				
				KPLSModel(const QSARData& q, String s1, String s2);
				
				KPLSModel(const QSARData& q, const LinearModel& lm, int column);

				~KPLSModel();

				EIGEN_MAKE_ALIGNED_OPERATOR_NEW
				//@}
				
				
				/** @name Accessors
				 */
				//@{
				
				void train();
				
				/** tries to find the optimal number of latente variables (=PLS components) */
				bool optimizeParameters(int k, int no_steps);
				
				/** returns the number of latente variables (=PLS components) */
				int getNoComponents();
				
				void setNoComponents(int d);
				
				/** returns a pointer to the  PLS Y-scores matrix U */
				const Eigen::MatrixXd* getU();
				
				void setParameters(std::vector<double>& v);
				
				std::vector<double> getParameters() const;
				//@}
				
				
			protected:
				/** @name Attributes
				 */
				Eigen::MatrixXd U_;
				
				int no_components_;
				//@}
				
		};
	}
}

#endif // BALL_CORE_QSAR_KPLSMODEL_H
