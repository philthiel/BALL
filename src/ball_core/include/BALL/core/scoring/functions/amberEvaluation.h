//_new_file_header


#ifndef BALL_CORE_SCORING_FUNCTIONS_AMBEREVALUATION_H
#define BALL_CORE_SCORING_FUNCTIONS_AMBEREVALUATION_H

#include <BALL/core/molmec/amber/amber.h>
#include <BALL/core/scoring/functions/forceFieldEvaluation.h>


namespace BALL
{
		/** A class for energetic evaluators of docking results using
		    an AMBER force field as scoring function.
				\ingroup Docking
		 */
		class BALL_EXPORT AmberEvaluation : public ForceFieldEvaluation
		{
			public:

				// Default constructor.
				AmberEvaluation()
					throw();

				AmberEvaluation(AmberFF& ff)
					throw();

				AmberEvaluation(AmberFF& ff, Options& option)
					throw();

				virtual ~AmberEvaluation()
					throw();

				/** Operations
				*/
				void setForceField(ForceField& ff)
					throw();

				void setOptions(const Options& options)
					throw();

				ForceField& getForceField()
					throw();

				const ForceField& getForceField() const
					throw();

				Options& getOptions()
					throw();

				const Options& getOptions() const
					throw();

		};
}

#endif // BALL_CORE_SCORING_FUNCTIONS_AMBEREVALUATION_H
