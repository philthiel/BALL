//_new_file_header


#ifndef BALL_CORE_MOLMEC_COMMON_TYPENAMERULEPROCESSOR_H
#define BALL_CORE_MOLMEC_COMMON_TYPENAMERULEPROCESSOR_H

#include <BALL/core/molmec/common/ruleProcessor.h>


namespace BALL 
{
	/**	Typename Rule Processor.
	 * Molecular Mechanics: rule-based assignment of typenames
    	\ingroup  MolmecAssignment
	*/
	class BALL_EXPORT TypenameRuleProcessor
		:	public RuleProcessor
	{
		public:

		BALL_CREATE(TypenameRuleProcessor)

		/**	Constructors and Destructors
		*/
		//@{

		/**	Default constructor
		*/
		TypenameRuleProcessor();
			
		/**	Detailed constructor
		*/
		TypenameRuleProcessor(INIFile& file, const String& prefix);
			
		/**	Copy constructor
		*/
		TypenameRuleProcessor(const TypenameRuleProcessor& rule_processor);

		/**	Destructor
		*/
		~TypenameRuleProcessor();

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

#endif // BALL_CORE_MOLMEC_COMMON_TYPENAMERULEPROCESSOR_H
