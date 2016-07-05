//_new_file_header


#include <BALL/core/molmec/common/typenameRuleProcessor.h>


namespace BALL
{
	TypenameRuleProcessor::TypenameRuleProcessor()
	{
	}

	TypenameRuleProcessor::TypenameRuleProcessor
		(INIFile& file, const String& prefix)
	{
		initialize(file, prefix);
	}

	TypenameRuleProcessor::TypenameRuleProcessor
		(const TypenameRuleProcessor& rule_processor)
		: RuleProcessor(rule_processor)
	{
	}

	TypenameRuleProcessor::~TypenameRuleProcessor()
	{
	}

	Processor::Result TypenameRuleProcessor::operator () (Atom& atom)
	{
		atom.setTypeName(evaluate(atom));
		return Processor::CONTINUE;
	}
}
