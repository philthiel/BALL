//_new_file_header


#ifndef BALL_CORE_SCORING_COMMON_FERMIBASEFUNCTION_H
#define BALL_CORE_SCORING_COMMON_FERMIBASEFUNCTION_H

#include <BALL/core/common/macros.h>
#include <BALL/core/scoring/common/baseFunction.h>


namespace BALL
{

	/** Sigmoidal base function
	 */
	class BALL_EXPORT FermiBaseFunction
		: public ScoringBaseFunction
	{

		public:

			/// 
			FermiBaseFunction()
				;

			/// The function is defined in such a way that the score approaches 1
			/// for values < lower and 0 for values > upper. If you need contrary
			/// behaviour, you have to supply a "lower" which is greater than
			/// "upper". This will invert the function.
			FermiBaseFunction(float lower, float upper)
				;

			///
			void setLower(float lower)
				;

			///
			void setUpper(float upper)
				;

			///
			float calculate(float x) const
				;

			///
			float calculate(float x, float lower, float upper)
				;


		private:

			//_
			void computeFermiParameters_()
				;

			//_
			float a_;

			//_
			float b_;

	};

}

#endif // BALL_CORE_SCORING_COMMON_FERMIBASEFUNCTION_H