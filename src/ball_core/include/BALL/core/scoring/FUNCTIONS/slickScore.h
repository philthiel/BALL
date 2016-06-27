//_new_file_header


#ifndef BALL_CORE_SCORING_FUNCTIONS_SLICKSCORE_H
#define BALL_CORE_SCORING_FUNCTIONS_SLICKSCORE_H

#include <BALL/core/datatype/hashMap.h>
#include <BALL/core/kernel/system.h>
#include <BALL/core/scoring/common/scoringFunction.h>


namespace BALL 
{
	/** SLICKEnergy scoring function
			{\bf Definition:} \URL{BALL/SCORING/FUNCTIONS/slickScore.h}
	*/
	class BALL_EXPORT SLICKScore : public ScoringFunction
	{
		public:

		/**	@name Constant Definitions
		*/
		//@{

		/**	Option names
		*/
		struct Option
		{
			/**	The additive constant (@see Default::CONST)
			*/
			static const char* CONST;

			/**
			*/
			static const char* CHPI;

			/**
			*/
			static const char* HB;

			/**
			*/
			static const char* VDW;

			/**
			*/
			static const char* POLAR;

		};


		/** Default values for SLICKEnergy options.
		*/
		struct Default
		{

			/**	The additive constant (@see Default::CONST)
			*/
			static const float CONST;

			/**
			*/
			static const float CHPI;

			/**
			*/
			static const float HB;

			/**
			*/
			static const float VDW;

			/**
			*/
			static const float POLAR;

		};



		//@}
		/** @name	Constructors and Destructors
		*/
		//@{

		BALL_CREATE(SLICKScore)

		/**	Default constructor.
		*/
		SLICKScore()
			;

		/** Construct a SLICKScore with options.
		*/
		SLICKScore(Molecule& protein, Molecule& ligand,
				Options& options)
			;

		/**	Copy constructor
		*/
		SLICKScore(const SLICKScore& slick)
			;

		/** Destructor
		*/
		virtual ~SLICKScore()
			;

		//@}
		/**	@name Assignment
		*/
		//@{

		/**	Assignment operator.
		*/
		const SLICKScore& operator = (const SLICKScore& slick)
			;

		/** Clear method.
		*/
		virtual void clear()
			;

		//@}
		/**	@name	Setup Methods
		*/
		//@{

		/**
		 * 	Setup scorinf function
		 */
		bool setup();

		//@}
		/**	@name Accessors specific to the SLICKScore scoring function
		*/
		//@{

		/**
		*/
		double getVDWScore() const
			;

		/**
		*/
		double getCHPIScore() const
			;

		/**
		*/
		double getPolarSolvationScore() const
			;

		/**
		*/
		double getNonpolarSolvationScore() const
			;

		/**
		*/
		double getHydrogenBondScore() const
			;
		//@}


		private:

		/*_
		*/
		void registerComponents_()
			;

	};

} // namespace BALL

#endif // BALL_CORE_SCORING_FUNCTIONS_SLICKSCORE_H
