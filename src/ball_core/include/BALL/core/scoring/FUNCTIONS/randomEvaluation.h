// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:

#ifndef BALL_SCORING_FUNCTIONS_RANDOMEVALUATION_H
#define BALL_SCORING_FUNCTIONS_RANDOMEVALUATION_H

#ifndef BALL_DOCKING_COMMON_CONFORMATIONSET_H
# include <BALL/core/docking/common/conformationSet.h>
#endif

#ifndef BALL_DATATYPE_HASHMAP_H
# include <BALL/core/datatype/hashMap.h>
#endif

#ifndef BALL_SCORING_FUNCTIONS_ENERGETICEVALUATION_H
# include <BALL/core/scoring/functions/energeticEvaluation.h>
#endif

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

#endif // BALL_SCORING_FUNCTIONS_RANDOMEVALUATION_H
