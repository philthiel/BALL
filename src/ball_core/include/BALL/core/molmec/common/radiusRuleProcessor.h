//_new_file_header


#ifndef BALL_CORE_MOLMEC_COMMON_RADIUSRULEPROCESSOR_H
#define BALL_CORE_MOLMEC_COMMON_RADIUSRULEPROCESSOR_H

#include <BALL/core/molmec/common/ruleProcessor.h>


namespace BALL 
{
	/**	Radius Rule Processor.
			
    	\ingroup  MolmecAssignment
	*/
	class BALL_EXPORT RadiusRuleProcessor
		:	public RuleProcessor
	{
		public:

		BALL_CREATE(RadiusRuleProcessor)

		/**	Constructors and Destructors
		*/
		//@{

		/**	Default constructor
		*/
		RadiusRuleProcessor();
			
		/**	Detailed constructor
		*/
		RadiusRuleProcessor(INIFile& file, const String& prefix = "RadiusRules");
			
		/**	Copy constructor
		*/
		RadiusRuleProcessor(const RadiusRuleProcessor& rule_processor);

		/**	Destructor
		*/
		~RadiusRuleProcessor();

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


#endif // BALL_CORE_MOLMEC_COMMON_RADIUSRULEPROCESSOR_H
