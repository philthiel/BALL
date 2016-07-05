//_new_file_header


#include <BALL/core/molmec/common/typeRuleProcessor.h>


namespace BALL
{
	TypeRuleProcessor::TypeRuleProcessor()
	{
	}

	TypeRuleProcessor::TypeRuleProcessor
		(INIFile& file, const String& prefix)
	{
		initialize(file, prefix);
	}

	TypeRuleProcessor::TypeRuleProcessor
		(const TypeRuleProcessor& rule_processor)
		: RuleProcessor(rule_processor)
	{
	}

	TypeRuleProcessor::~TypeRuleProcessor()
	{
	}

	Processor::Result TypeRuleProcessor::operator () (Atom& atom)
	{
		atom.setType((Atom::Type)evaluate(atom).toInt());
		return Processor::CONTINUE;
	}
}
