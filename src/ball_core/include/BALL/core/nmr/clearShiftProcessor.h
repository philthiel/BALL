//_new_file_header


#ifndef BALL_CORE_NMR_CLEARSHIFTPROCESSOR_H
#define BALL_CORE_NMR_CLEARSHIFTPROCESSOR_H

#include <BALL/core/nmr/shiftModule.h>


namespace BALL 
{
	/**	Clear assigned shift data of all atoms.
			This processors clears the named property defined by  \link ShiftModule::PROPERTY__SHIFT ShiftModule::PROPERTY__SHIFT \endlink 
			in the atoms of all data structures it is applied to.  \par
	\ingroup ShiftModulesNMR		
	*/
	class BALL_EXPORT ClearShiftProcessor
		:	public ShiftModule
	{
		public:
		
		/** @name	Constructors and Destructors
		*/
		//@{

		/**	Default constructor.
		*/
		ClearShiftProcessor();
		
		/**	Copy constructor.
		*/
		ClearShiftProcessor(const ClearShiftProcessor& processor);
		
		/**	Destructor
		*/
		virtual ~ClearShiftProcessor();
		
		//@}

		/** @name	Processor specific functions.
		*/
		//@{

		/**	Application method
		*/
		virtual Processor::Result operator () (Composite& composite);

		//@}
		
	};
  
} // namespace BALL

#endif // BALL_CORE_NMR_CLEARSHIFTPROCESSOR_H
