//_new_file_header


#ifndef BALL_CORE_SCORING_FUNCTIONS_RESCORING1D_H
#define BALL_CORE_SCORING_FUNCTIONS_RESCORING1D_H

#include <BALL/core/scoring/functions/rescoring.h>

#include <vector>


namespace BALL
{
	class BALL_EXPORT Rescoring1D : public Rescoring
	{
		public:
			Rescoring1D(AtomContainer& receptor, AtomContainer& reference_ligand, Options& options, String free_energy_label, ScoringFunction* sf);

		protected:
			void setup_();
			const Protein* protein_;
			void generateScoreContributions_(std::vector<std::vector<double> >* matrix, std::vector<double>* v);
	};
}

#endif // BALL_CORE_SCORING_FUNCTIONS_RESCORING1D_H
