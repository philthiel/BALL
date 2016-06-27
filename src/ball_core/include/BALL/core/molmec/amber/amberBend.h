//_new_file_header


#ifndef BALL_CORE_MOLMEC_AMBER_AMBERBEND_H
#define BALL_CORE_MOLMEC_AMBER_AMBERBEND_H

#include <BALL/core/molmec/common/bendComponent.h>


namespace BALL 
{
	/**	Amber bond stretch component
			
    	\ingroup  AMBER
	*/
	class BALL_EXPORT AmberBend : public BendComponent
	{
		public:

		BALL_CREATE(AmberBend)

		/// flag to enable ES
		#define AMBER_BEND_ENABLED "enable Bends"

		/** @name	Constructors and Destructors	
		*/
		//@{ 

		/**	Default constructor.
		*/
		AmberBend();

		/**	Constructor.
		*/
		AmberBend(ForceField& force_field);

		/**	Destructor.
		*/
		virtual ~AmberBend();

		//@}

		/**	@name	Setup Methods	
		*/
		//@{

		/**	Setup method.
		*/
		virtual bool setup()
			throw(Exception::TooManyErrors);

		//@}
	};
} // namespace BALL

#endif // BALL_CORE_MOLMEC_AMBER_AMBERBEND_H
