//_new_file_header


#ifndef BALL_CORE_MOLMEC_CHARMM_CHARMMBEND_H
#define BALL_CORE_MOLMEC_CHARMM_CHARMMBEND_H

#include <BALL/core/molmec/common/bendComponent.h>


namespace BALL 
{
	/**	Charmm bond stretch component
			
    	\ingroup  CHARMM
	*/
	class BALL_EXPORT CharmmBend : public BendComponent
	{
		public:

		BALL_CREATE(CharmmBend)

		/// flag to enable BENDS 
		#define CHARMM_BENDS_ENABLED "enable Bends"

		/**@name	Constructors and Destructors	
		*/
		//@{ 

		/**	Default constructor.
		*/
		CharmmBend();

		/**	Constructor.
		*/
		CharmmBend(ForceField& force_field);

		/**	Destructor.
		*/
		virtual ~CharmmBend();

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

#endif // BALL_CORE_MOLMEC_CHARMM_CHARMMBEND_H
