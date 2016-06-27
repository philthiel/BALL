//_new_file_header


#ifndef BALL_CORE_DOCKING_COMMON_SIDECHAINOPTIMIZER_H
#define BALL_CORE_DOCKING_COMMON_SIDECHAINOPTIMIZER_H

#include <BALL/core/scoring/common/scoringFunction.h>
#include <BALL/core/structure/rotamerLibrary.h>

#include <list>
#include <set>


namespace BALL
{
	class BALL_EXPORT SideChainOptimizer
	{
		public:
			SideChainOptimizer(ScoringFunction* sf);

			~SideChainOptimizer();

			void setFlexibleResidues(const std::set<String>& residues_IDs);

			void optimize();

			void findFlexibleSideChains(std::set<Residue*>& residues, const double& dist_cutoff, const double& min_B_factor);

		private:
			FragmentDB* frag_db_;

			RotamerLibrary* rotamer_lib_;

			ScoringFunction* scoring_function_;

			std::list<Residue*> residues_;
	};
}

#endif // BALL_CORE_DOCKING_COMMON_SIDECHAINOPTIMIZER_H
