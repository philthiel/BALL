//_new_file_header


#ifndef BALL_CORE_SCORING_COMMON_BASEFUNCTION_H
#define BALL_CORE_SCORING_COMMON_BASEFUNCTION_H


namespace BALL
{

	/** Define the interface for the base function
	 */
	class ScoringBaseFunction
	{

		public:

			/**
			 */
			enum BaseFunctionType
			{
				/**
				 */
				BASE_FUNCTION_TYPE__LINEAR,

				/**
				 */
				BASE_FUNCTION_TYPE__FERMI
			};


			///
			ScoringBaseFunction()
				;

			///
			ScoringBaseFunction(float lower, float upper)
				;

			///
			virtual ~ScoringBaseFunction()
				;

			///
			virtual void setLower(float lower)
				;

			///
			virtual void setUpper(float upper)
				;

			///
			virtual float calculate(float x) const
				;

			///
			virtual float calculate(float x, float lower, float upper) 
				;


		protected:

			//_
			float lower_;

			//_
			float upper_;

	};

}

#endif // BALL_CORE_SCORING_COMMON_BASEFUNCTION_H
