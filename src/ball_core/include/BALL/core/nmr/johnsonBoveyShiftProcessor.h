//_new_file_header


#ifndef BALL_CORE_NMR_JOHNSONBOVEYSHIFTPROCESSOR_H
#define BALL_CORE_NMR_JOHNSONBOVEYSHIFTPROCESSOR_H

#include <BALL/core/datatype/stringHashMap.h>
#include <BALL/core/format/parameters.h>
#include <BALL/core/format/parameterSection.h>
#include <BALL/core/kernel/expression.h>
#include <BALL/core/nmr/shiftModule.h>

#include <list>


namespace BALL 
{		
	/**	Shift assignment processor implementing Johnson Bovey theory. 
	\ingroup ShiftModulesNMR		
	*/
	class BALL_EXPORT JohnsonBoveyShiftProcessor
		:	public ShiftModule
	{
		public:

    BALL_CREATE(JohnsonBoveyShiftProcessor)

		/**	@name	Type definitions
		*/
		//@{

		///
		struct BALL_EXPORT Ring
    {
			double	radius;
			double	intensity;
			Size	electrons;
			std::vector<String>	atom_names;

			bool operator == (const Ring& ring) const;
			bool operator != (const Ring& ring) const { return !(*this == ring);}
		} ;
  
		//@}
		
    /** @name Enums and Constants
    */
    //@{

    /** A symbolic name for the ring current contribution to the chemical shift
        @see ShiftModule::PROPERTY__SHIFT
    */
    static const char* PROPERTY__RING_CURRENT_SHIFT;		
    //@}


 		/** @name	Constructors and Destructors
		*/
		//@{

		/**	Default constructor.
		*/
		JohnsonBoveyShiftProcessor();

		/**	Destructor
		*/
		virtual ~JohnsonBoveyShiftProcessor();

		//@}
		/** @name	Processor specific functions.
		*/
		//@{

		/**	Start method.
		*/
		virtual bool start();

		/**	Finish method.
		*/
		virtual bool finish();

		/**	Application method
		*/
		virtual Processor::Result operator () (Composite& composite);
		
		//@}
		/**	@name Accessors
		*/
		//@{
			
		/** Initialize all parameters required
		*/
		virtual void init();
			
		//@}

		protected:

		std::list<Atom*>	proton_list_;	
		std::list<Atom*>	atom_list_;	
		std::list<Residue*>	aromat_list_;
		StringHashMap<Ring>	rings_;
		StringHashMap<Position>	residues_with_rings_;
		std::vector<Expression>	expressions_;
		
		double carlsonEllipticalIntegral1_(double, double, double);	// Carlson elliptical Integral of 1st kind
		double carlsonEllipticalIntegral2_(double, double, double);	// Carlson elliptical Integral of 2nd kind
		double legendreEllipticalIntegral1_(double, double);	// Legendre elliptical Integral of 1st kind
		double legendreEllipticalIntegral2_(double, double);	// Legendre elliptical Integral of 2nd kind
	};
  
} // namespace BALL 

#endif // BALL_CORE_NMR_JOHNSONBOVEYSHIFTPROCESSOR_H
