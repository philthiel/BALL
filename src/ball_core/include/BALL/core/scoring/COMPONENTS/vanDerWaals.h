//_new_file_header


#ifndef BALL_CORE_SCORING_COMPONENTS_VANDERWAALS_H
#define BALL_CORE_SCORING_COMPONENTS_VANDERWAALS_H

#include <BALL/core/molmec/amber/amberNonBonded.h>

#include <vector>


namespace BALL
{
	class Electrostatic;

	class BALL_EXPORT VanDerWaals : public ScoringComponent
	{
		public :
			VanDerWaals(Options& options, ForceFieldParameters& forcefield_parameters);

			VanDerWaals(Electrostatic* es);

			~VanDerWaals();

			void update(const std::vector<std::pair<Atom*, Atom*> >& pair_vector);

			double updateScore();

			AmberNonBonded* getAmberNonBonded();

		private:
			bool do_calculations_;

			AmberNonBonded* amber_nb_;
	};
}


#endif // BALL_CORE_SCORING_COMPONENTS_VANDERWAALS_H
