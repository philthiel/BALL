//_new_file_header


#ifndef BALL_CORE_SCORING_FUNCTIONS_RESCORING4D_H
#define BALL_CORE_SCORING_FUNCTIONS_RESCORING4D_H

#include <BALL/core/scoring/functions/rescoring3D.h>

#include <vector>


namespace BALL
{
	class BALL_EXPORT Rescoring4D : public Rescoring3D
	{
		public:
			Rescoring4D(AtomContainer& receptor, AtomContainer& reference_ligand, Options& options, String free_energy_label, ScoringFunction* sf);

		protected:
			/** Obtain score-contributions for a single atom. Overloaded by class Rescoring4D */
			void generateAtomScoreContributions_(const Atom* atom, std::vector<double>& contributions);
	};
}

#endif // BALL_CORE_SCORING_FUNCTIONS_RESCORING4D_H