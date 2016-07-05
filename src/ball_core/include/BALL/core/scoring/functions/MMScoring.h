//_new_file_header


#ifndef BALL_CORE_SCORING_FUNCTIONS_MMSCORING_H
#define BALL_CORE_SCORING_FUNCTIONS_MMSCORING_H

#include <BALL/core/molmec/amber/amber.h>
#include <BALL/core/scoring/common/diffScoringFunction.h>


namespace BALL
{
	class BALL_EXPORT MMScoring : public DifferentiableScoringFunction
	{
		public:
			/** constructor */
			MMScoring(AtomContainer& receptor, AtomContainer& reference_ligand, Options& options);

			MMScoring(AtomContainer& receptor, Vector3& hashgrid_origin, Options& options);

		protected:
			void setup();

			double getES();

			/** saving the ForceFieldParameters here allow access to the atom-types and prevents multiple reading of the same parameter file in case of mulitple force-fields components */
			ForceFieldParameters forcefield_parameters_;
	};
}

#endif // BALL_CORE_SCORING_FUNCTIONS_MMSCORING_H
