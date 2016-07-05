//_new_file_header


#include <BALL/core/molmec/common/chargeRuleProcessor.h>


namespace BALL
{
	ChargeRuleProcessor::ChargeRuleProcessor()
	{
	}

	ChargeRuleProcessor::ChargeRuleProcessor
		(INIFile& file, const String& prefix)
	{
		initialize(file, prefix);
	}

	ChargeRuleProcessor::ChargeRuleProcessor
		(const ChargeRuleProcessor& rule_processor)
		: RuleProcessor(rule_processor)
	{
	}

	ChargeRuleProcessor::~ChargeRuleProcessor()
	{
	}

	Processor::Result ChargeRuleProcessor::operator () (Atom& atom)
	{
		atom.setCharge(evaluate(atom).toFloat());
		return Processor::CONTINUE;
	}
}
