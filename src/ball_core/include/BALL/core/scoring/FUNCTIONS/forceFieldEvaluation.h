//_new_file_header


#ifndef BALL_CORE_SCORING_FUNCTIONS_FORCEFIELDEVALUATION_H
#define BALL_CORE_SCORING_FUNCTIONS_FORCEFIELDEVALUATION_H

#include <BALL/core/molmec/common/forceField.h>
#include <BALL/core/scoring/functions/energeticEvaluation.h>


namespace BALL
{
		/** Base class for energetic evaluators of docking results using
		    a force field as scoring function.
				\ingroup Docking
		 */
		class BALL_EXPORT ForceFieldEvaluation
			: public EnergeticEvaluation
		{
			public:

				/// Default constructor.
				ForceFieldEvaluation()
					throw();

				///
				ForceFieldEvaluation(ForceField& ff)
					throw();

				///
				virtual ~ForceFieldEvaluation()
					throw();

				/** Operations
				*/
				void setForceField(ForceField& ff)
					throw();

				///
				void setOptions(const Options& options)
					throw();

				///
				ForceField& getForceField()
					throw();

				///
				const ForceField& getForceField() const
					throw();

				///
				Options& getOptions()
					throw();

				///
				const Options& getOptions() const
					throw();

				///
				virtual std::vector < ConformationSet::Conformation > operator () (ConformationSet& conformations)
					throw(Exception::TooManyErrors);

			protected:

				ForceField* ff_;
				Options     options_;
				bool 				delete_force_field_;
		};
}

#endif // BALL_CORE_SCORING_FUNCTIONS_FORCEFIELDEVALUATION_H
