//_new_file_header


#ifndef BALL_CORE_SCORING_FUNCTIONS_RANDOMEVALUATION_H
#define BALL_CORE_SCORING_FUNCTIONS_RANDOMEVALUATION_H

#include <BALL/core/datatype/hashMap.h>
#include <BALL/core/docking/common/conformationSet.h>
#include <BALL/core/scoring/functions/energeticEvaluation.h>

#include <vector>


namespace BALL
{
	/** A basis class for energetic evaluators of docking results.
		This trivial class will return the identity scoring, leaving
		permutation and score unchanged.
			\ingroup Docking
	*/
	class BALL_EXPORT RandomEvaluation : public EnergeticEvaluation
	{
		public:
			RandomEvaluation()
				throw();

			virtual ~RandomEvaluation()
				throw();

			/** Operations
			*/
			std::vector < ConformationSet::Conformation > operator () (ConformationSet& conformations)
				throw();
	};
}

#endif // BALL_CORE_SCORING_FUNCTIONS_RANDOMEVALUATION_H
