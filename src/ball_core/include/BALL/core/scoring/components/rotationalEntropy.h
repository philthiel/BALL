//_new_file_header


#ifndef BALL_CORE_SCORING_COMPONENTS_ROTATIONALENTROPY_H
#define BALL_CORE_SCORING_COMPONENTS_ROTATIONALENTROPY_H

#include <BALL/core/scoring/common/scoringComponent.h>

#include <vector>


namespace BALL
{
	class BALL_EXPORT RotationalEntropy : public ScoringComponent
	{
		public:

			RotationalEntropy(ScoringFunction& sf);

			double updateScore();

			/** Overloads ScoringComponent::setLigandIntraMolecular() in order to make sure that no one can set ligand_intra_molecular_ to false. **/
			void setLigandIntraMolecular(bool b);

			void update(const std::vector<std::pair<Atom*, Atom*> >& pair_vector);

	};
}

#endif // BALL_CORE_SCORING_COMPONENTS_ROTATIONALENTROPY_H
