//_new_file_header


#ifndef BALL_CORE_SCORING_COMPONENTS_PB_H
#define BALL_CORE_SCORING_COMPONENTS_PB_H

#include <BALL/core/scoring/common/scoringComponent.h>
#include <BALL/core/solvation/poissonBoltzmann.h>

#include <vector>


namespace BALL
{
	/** Poisson-Boltzmann scoring term */
	class BALL_EXPORT PB : public ScoringComponent
	{
		public :
			PB(ScoringFunction& sf);

			~PB();

			void update(const std::vector<std::pair<Atom*, Atom*> >& pair_vector);

			double updateScore();

			void setupLigand();

		protected:
			FDPB* pb_solver_;

			System receptor_atoms_;
			System ligand_atoms_;
			System complex_atoms_;
	};
}

#endif // BALL_CORE_SCORING_COMPONENTS_PB_H
