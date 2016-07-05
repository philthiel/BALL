//_new_file_header


#ifndef BALL_CORE_SCORING_FUNCTIONS_SLICKENERGY_H
#define BALL_CORE_SCORING_FUNCTIONS_SLICKENERGY_H

#include <BALL/core/datatype/hashMap.h>
#include <BALL/core/kernel/system.h>
#include <BALL/core/scoring/common/scoringFunction.h>


namespace BALL 
{
	/** SLICKEnergy scoring function
			{\bf Definition:} \URL{BALL/SCORING/FUNCTIONS/slickEnergy.h}
	*/
	class BALL_EXPORT SLICKEnergy : public ScoringFunction
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
				static const char* NONPOLAR;

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
				static const float NONPOLAR;

				/**
				*/
				static const float POLAR;

			};



			//@}
			/** @name	Constructors and Destructors
			*/
			//@{

			BALL_CREATE(SLICKEnergy)

			/**	Default constructor.
			*/
			SLICKEnergy();

			/** Construct a SLICKEnergy with a system and pointers to protein and
					ligand
			*/
			SLICKEnergy(Molecule& protein, Molecule& ligand);

			/** Construct a SLICKEnergy with a system and options.
			*/
			SLICKEnergy(Molecule& protein, Molecule& ligand,
					Options& options);

			/**	Copy constructor
			*/
			SLICKEnergy(const SLICKEnergy& slick);

			/** Destructor
			*/
			virtual ~SLICKEnergy();

			//@}
			/**	@name Assignment
			*/
			//@{

			/**	Assignment operator.
			*/
			const SLICKEnergy& operator = (const SLICKEnergy& slick);

			/** Clear method.
			*/
			virtual void clear();

			//@}
			/**	@name	Setup Methods
			*/
			//@{

			/**
			* 	Setup of scoring function
			*/
			bool setup();

			//@}
			/**	@name Accessors specific to the SLICKEnergy scoring function
			*/
			//@{

			/**
			*/
			double getCHPIScore() const;

			/**
			*/
			double getHydrogenBondScore() const;

			/**
			*/
			double getVDWScore() const;

			/**
			*/
			double getPolarSolvationScore() const;

			/**
			*/
			double getNonpolarSolvationScore() const;
			//@}

		private:
			/**
			* Register the scoring components used by SLICKEnergy.
			*/
			void registerComponents_();
	};

} // namespace BALL

#endif // BALL_CORE_SCORING_FUNCTIONS_SLICKENERGY_H
