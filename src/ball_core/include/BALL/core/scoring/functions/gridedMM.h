//_new_file_header


#ifndef BALL_CORE_SCORING_FUNCTIONS_GRIDEDMM_H
#define BALL_CORE_SCORING_FUNCTIONS_GRIDEDMM_H

#include <BALL/core/molmec/amber/amber.h>
#include <BALL/core/scoring/common/diffGridBasedScoring.h>
#include <BALL/core/scoring/components/electrostatic.h>


namespace BALL
{
	class BALL_EXPORT GridedMM : public DiffGridBasedScoring
	{
		public:
			GridedMM(AtomContainer& receptor, AtomContainer& ligand, Options& options);

			GridedMM(AtomContainer& receptor, Vector3& hashgrid_origin, Options& options);

		protected:
			AtomTypes& getAtomTypes();

			void setup();

			double getES();

			ForceFieldParameters forcefield_parameters_;
	};
}

#endif // BALL_CORE_SCORING_FUNCTIONS_GRIDEDMM_H
