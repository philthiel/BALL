//_new_file_header


#ifndef BALL_CORE_QSAR_FEATURESELECTION_H
#define BALL_CORE_QSAR_FEATURESELECTION_H

#include <set>

#include <BALL/core/qsar/kernelModel.h>
#include <BALL/core/qsar/linearModel.h>
#include <BALL/core/qsar/Model.h>


namespace BALL 
{
	namespace QSAR
	{

		class BALL_EXPORT FeatureSelection
		{
			public:
				/** @name Constructors and Destructors
				 */
				//@{
				FeatureSelection(Model& m);
				
				FeatureSelection(KernelModel& m);

				~FeatureSelection();

				EIGEN_MAKE_ALIGNED_OPERATOR_NEW
				//@}
				
				
				/** @name Accessors
				 */
				//@{
				/** set the model, or which feature selection is to be done */
				void setModel(Model& m);
				
				void setModel(KernelModel& km);
	
				/** starts forward selection. \n
				In order to evaluate how much a descriptor increases the accuracy of the model, cross-validation is started in each step using descriptor_matrix from class QSARData as data source.\n
				@param optPar 1 : Model.optimizeParameters() is used to try to find the optimal parameters during *each* step of feature selection. \n
				0: Model.optimizeParameters() is not used during feature selection*/
				void forwardSelection(int k=4, bool optPar=0);
				
				/** starts backward selection. \n
				In order to evaluate how much a descriptor increases the accuracy of the model, cross-validation is started in each step using descriptor_matrix from class QSARData as data source.\n
				@param optPar 1 : Model.optimizeParameters() is used to try to find the optimal parameters during *each* step of feature selection. \n
				0: Model.optimizeParameters() is not used during feature selection*/
				void backwardSelection(int k=4, bool optPar=0);
				
				void stepwiseSelection(int k=4, bool optPar=0);
				
				/** Does a simple check consisting of two successive scans of all features.\n
				In the first scan, the best feature to start with is searched.\n
				In the second scan, it is checked for each remaining (non-empty) descriptor whether it can increase the prediction quality. The features are tested in the descending order of their predictive qualities as determined in the first scan.  \n
				Thus, this method is particularly suited for models that consider all features to be independent for each other (e.g. Bayesian classifiaction models). */
				void twinScan(int k, bool optPar=0);
				
				/** uses the coefficients generated by a linear regression model (LinearModel.training_result) in order to select features.\n
				All descriptors whose coefficients are within 0 +/-  d*stddev are considered to be unimportant and are not selected.\n
				Futhermore, if feature selection has already been done on FeatureSelection->model, only those descriptors that are already part of lm AND of FeatureSelection->model are tested.
				@param act determines which coefficients are to be used, i.e. which column of LinearModel.training_result */
				void implicitSelection(LinearModel& lm, int act=1, double d=1);
				
				/** reomves features that are highly correlated to another feature.
				@param cor_threshold all feature which a correlation (to another feature) > cor_threshold or \< cor_threshold are removed */
				void removeHighlyCorrelatedFeatures(double& cor_threshold);
				
				
				/** removes those features that do not have a correlation greater than the specified value to any of the response variables */
				void removeLowResponseCorrelation(double& min_correlation);
				
				
				/** removes descriptors whose values are 0 in all substances from the list of selected features */
				void removeEmptyDescriptors();
				
				void selectStat(int s);
				
				/** Sets a cutoff value for feature selections. \n
				If the preditive quality is increased by less than d after adding/removing a descriptor, feature selection is stopped. */
				void setQualityIncreaseCutoff(double& d);
				//@}
	
	
			private:
				
				/** @name Accessors
				 */
				//@{
				void updateWeights(std::multiset<unsigned int>& oldDescIDs, std::multiset<unsigned int>& newDescIDs, Eigen::VectorXd& oldWeights);
				//@}
				
				
				/** @name Attributes
				 */
				//@{
				/** searches for empty or irrelevant descriptors and returns a sorted list containing their IDs.
				\n If more than one feature selection method is applied, all descriptors that have not been selected by the previous method are considered to be irrelevant.*/
				std::multiset<unsigned int>* findIrrelevantDescriptors();
				
				/** pointer to the model, for which feature selection is to be done */
				Model* model_;
				
				/** pointer to KernelModel.weights (if the model to be optimized is a KernelModel) */
				Eigen::VectorXd* weights_;
				
				/** implements forward selection; if stepwise==1, backwardSelection() is called after each forward step, i.e. after adding a feature. */
				void forward(bool stepwise, int k, bool optPar);
				
				/** if the preditive quality is increased by less than this value after adding/removing a descriptor, feature selection is stopped. */
				double quality_increase_cutoff_;
				//@}
		};
	}
}


#endif // BALL_CORE_QSAR_FEATURESELECTION_H