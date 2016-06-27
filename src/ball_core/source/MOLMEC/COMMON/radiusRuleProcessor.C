//_new_file_header


#include <BALL/core/molmec/common/radiusRuleProcessor.h>


namespace BALL
{
	RadiusRuleProcessor::RadiusRuleProcessor()
	{
	}

	RadiusRuleProcessor::RadiusRuleProcessor
		(INIFile& file, const String& prefix)
	{
		initialize(file, prefix);
	}

	RadiusRuleProcessor::RadiusRuleProcessor
		(const RadiusRuleProcessor& rule_processor)
		: RuleProcessor(rule_processor)
	{
	}

	RadiusRuleProcessor::~RadiusRuleProcessor()
	{
	}

	Processor::Result RadiusRuleProcessor::operator () (Atom& atom)
	{
		atom.setRadius(evaluate(atom).toFloat());
		return Processor::CONTINUE;
	}
}
