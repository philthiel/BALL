//_new_file_header


#ifndef BALL_CORE_SCORING_FUNCTIONS_GRIDEDPLP_H
#define BALL_CORE_SCORING_FUNCTIONS_GRIDEDPLP_H

#include <BALL/core/molmec/mmff94/MMFF94.h>
#include <BALL/core/scoring/common/diffGridBasedScoring.h>


namespace BALL
{
	/** ScoringFunction using a grid-based version of Piecewise Linear Potential */
	class BALL_EXPORT GridedPLP : public DiffGridBasedScoring
	{
		public:
			GridedPLP(AtomContainer& receptor, AtomContainer& ligand, Options& options);

			GridedPLP(AtomContainer& receptor, Vector3& hashgrid_origin, Options& options);

			void setLigand(AtomContainer* sys);

		protected:
			AtomTypes& getAtomTypes();

			void setup();

			void setAtomType(Atom* atom, const String& type_name);

			double getES();

			AtomTypes atom_types_;
	};
}

#endif // BALL_CORE_SCORING_FUNCTIONS_GRIDEDPLP_H
