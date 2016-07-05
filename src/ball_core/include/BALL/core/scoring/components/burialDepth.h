//_new_file_header


#ifndef BALL_CORE_SCORING_COMPONENTS_BURIALDEPTH_H
#define BALL_CORE_SCORING_COMPONENTS_BURIALDEPTH_H

#include <BALL/core/scoring/common/scoringComponent.h>
#include <BALL/core/scoring/common/scoringFunction.h>

#include <vector>


namespace BALL
{
	class BALL_EXPORT BurialDepth : public ScoringComponent
	{
		public :
			BurialDepth(ScoringFunction& sf);

			~BurialDepth();

			void update(const std::vector<std::pair<Atom*, Atom*> >& pair_vector);

			double updateScore();
	};
}

#endif // BALL_CORE_SCORING_COMPONENTS_BURIALDEPTH_H
