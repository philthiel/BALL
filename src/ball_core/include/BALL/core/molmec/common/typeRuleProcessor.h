//_new_file_header


#ifndef BALL_CORE_MOLMEC_COMMON_TYPERULEPROCESSOR_H
#define BALL_CORE_MOLMEC_COMMON_TYPERULEPROCESSOR_H

#include <BALL/core/molmec/common/ruleProcessor.h>


namespace BALL 
{
	/**	Type Rule Processor.
	 * Molecular Mechanics: rule-based assignment of types
			
    	\ingroup  MolmecAssignment
	*/
	class BALL_EXPORT TypeRuleProcessor
		:	public RuleProcessor
	{
		public:

		BALL_CREATE(TypeRuleProcessor)

		/**	Constructors and Destructors
		*/
		//@{

		/**	Default constructor
		*/
		TypeRuleProcessor();
			
		/**	Detailed constructor
		*/
		TypeRuleProcessor(INIFile& file, const String& prefix);
			
		/**	Copy constructor
		*/
		TypeRuleProcessor(const TypeRuleProcessor& rule_processor);

		/**	Destructor
		*/
		~TypeRuleProcessor();

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

#endif // BALL_CORE_MOLMEC_COMMON_TYPERULEPROCESSOR_H
