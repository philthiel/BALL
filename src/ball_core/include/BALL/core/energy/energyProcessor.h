//_new_file_header


#ifndef BALL_CORE_ENERGY_ENERGYPROCESSOR_H
#define BALL_CORE_ENERGY_ENERGYPROCESSOR_H

#include <BALL/core/concept/processor.h>
#include <BALL/core/kernel/atomContainer.h>


namespace BALL
{
	/** Processor for energy calculations.
			With this class we provide an interface to different (free) energy
			calculations.
			
	 		\ingroup EnergyMiscellaneous
	*/
	class BALL_EXPORT EnergyProcessor
		:	public UnaryProcessor<AtomContainer>
	{

		public:

		BALL_CREATE(EnergyProcessor)

		/** @name Constructors and Destructors 
		*/
		//@{

		/** Default constructor 
		*/
		EnergyProcessor();

		/** Copy constructor 
		*/
		EnergyProcessor(const EnergyProcessor& proc);

		/** Destructor 
		*/
		virtual ~EnergyProcessor();

		//@}
		/** @name Assignment 
		*/
		//@{

		/** Assignment operator.
		 */ 
		const EnergyProcessor& operator = (const EnergyProcessor& proc);

		/** Clear method.
		 */
		virtual void clear();

		//@}
		/** @name	Processor related methods
		*/
		//@{

		/** Start-function. 
		*/
		virtual bool start();

		/** Operator-function. This function only stores the AtomContainer. 
		*/
		virtual Processor::Result operator () (AtomContainer& fragment);
		
		//@}
		/** @name Accessors 
		*/
		//@{

		/** Return the computed energy 
		*/
		double getEnergy() const;

		//@}	
		/** @name Predicates 
		*/
		//@{

		/** Validity.
		*/
		bool isValid() const;

		/** Equality operator.
		*/
		bool operator == (const EnergyProcessor& proc) const;

		//@}

		protected:

		/*_ this is the Fragment for which the computation is to be done */
		const AtomContainer* fragment_;

		/*_ the calculated energy */
		double energy_;

		/*_ the valid flag */
		bool valid_;

	};
}

#endif // BALL_CORE_ENERGY_ENERGYPROCESSOR_H
