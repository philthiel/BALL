//_new_file_header


#ifndef BALL_CORE_SCORING_COMPONENTS_ADVELECTROSTATIC_H
#define BALL_CORE_SCORING_COMPONENTS_ADVELECTROSTATIC_H

#include <BALL/core/scoring/components/electrostatic.h>


namespace BALL
{
	class BALL_EXPORT AdvancedElectrostatic : public Electrostatic
	{
		public :
			AdvancedElectrostatic(ScoringFunction* sf, Options& options, ForceFieldParameters& forcefield_parameters);

			AdvancedElectrostatic(ScoringFunction* sf, VanDerWaals* vdw);

			double calculateDielectricConstant(Vector3& atom1, Vector3& atom2);

		private:
			float protein_dielectric_constant_;

			float solvate_dielectric_constant_;
	};
}

#endif // BALL_CORE_SCORING_COMPONENTS_ADVELECTROSTATIC_H
