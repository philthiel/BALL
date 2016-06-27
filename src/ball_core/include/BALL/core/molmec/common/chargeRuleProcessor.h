//_new_file_header


#ifndef BALL_CORE_MOLMEC_COMMON_CHARGERULEPROCESSOR_H
#define BALL_CORE_MOLMEC_COMMON_CHARGERULEPROCESSOR_H

#include <BALL/core/molmec/common/ruleProcessor.h>


namespace BALL 
{
	/**	Charge Rule Processor.
			
    	\ingroup  MolmecAssignment
	*/
	class BALL_EXPORT ChargeRuleProcessor
		:	public RuleProcessor
	{
		public:

		BALL_CREATE(ChargeRuleProcessor)

		/**	Constructors and Destructors
		*/
		//@{

		/**	Default constructor
		*/
		ChargeRuleProcessor();
			
		/**	Detailed constructor
		*/
		ChargeRuleProcessor(INIFile& file, const String& prefix = "ChargeRules");
			
		/**	Copy constructor
		*/
		ChargeRuleProcessor(const ChargeRuleProcessor& rule_processor);

		/**	Destructor
		*/
		~ChargeRuleProcessor();

		//@}
		/**	@name Processor related methods
		*/
		//@{

		/**
		*/
		virtual Processor::Result operator () (Atom& atom);
		
		//@}

	};
} // namespace BALL


#endif // BALL_CORE_MOLMEC_COMMON_CHARGERULEPROCESSOR_H
