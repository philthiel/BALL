//_new_file_header


#ifndef BALL_CORE_SCORING_FUNCTIONS_ENERGETICEVALUATION_H
#define BALL_CORE_SCORING_FUNCTIONS_ENERGETICEVALUATION_H

#include <BALL/core/docking/common/conformationSet.h>

#include <vector>


namespace BALL
{
	/** Base class for energetic evaluators of docking results.
		This trivial class will return the identity scoring, leaving
		permutation and score unchanged.
			\ingroup Docking
	 */
	class BALL_EXPORT EnergeticEvaluation
	{
		public:
			EnergeticEvaluation()
				throw();

			virtual ~EnergeticEvaluation()
				throw();

			/** Operations
			*/
			virtual std::vector<ConformationSet::Conformation> operator () (ConformationSet& conformations);
	};
}

#endif // BALL_CORE_SCORING_FUNCTIONS_ENERGETICEVALUATION_H
