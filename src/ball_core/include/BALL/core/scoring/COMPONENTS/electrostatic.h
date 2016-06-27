//_new_file_header


#ifndef BALL_CORE_SCORING_COMPONENTS_ELECTROSTATIC_H
#define BALL_CORE_SCORING_COMPONENTS_ELECTROSTATIC_H

#include <BALL/core/molmec/amber/amberNonBonded.h>
#include <BALL/core/scoring/common/scoringComponent.h>

#include <vector>


namespace BALL
{
	class VanDerWaals;

	class BALL_EXPORT Electrostatic : public ScoringComponent
	{
		public :
			Electrostatic(Options& options, ForceFieldParameters& forcefield_parameters);

			Electrostatic(VanDerWaals* vdw);

			~Electrostatic();

			void update(const std::vector<std::pair<Atom*, Atom*> >& pair_vector);

			double updateScore();

			AmberNonBonded* getAmberNonBonded();

		private:
			bool do_calculations_;

		protected:
			AmberNonBonded* amber_nb_;
	};
}

#endif // BALL_CORE_SCORING_COMPONENTS/ELECTROSTATIC_H
