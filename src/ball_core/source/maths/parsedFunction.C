//_new_file_header


#include <BALL/core/maths/parsedFunction.h>


namespace BALL
{
	StringHashMap<double*> *ParsedFunctionConstants;
	StringHashMap<double(*)(double)> *ParsedFunctionFunctions;

	template <>
	double ParsedFunction<float>::operator () (float argument)
	{
		double arg = argument;
		constants_["X"] = &arg;
		ParsedFunctionConstants = &constants_;
		ParsedFunctionFunctions = &functions_;
		ParsedFunction_initBuffer(expression_.c_str());
		ParsedFunctionparse();
		ParsedFunction_delBuffer();
		return ParsedFunctionResult;
	}

	template <>
	double ParsedFunction<double>::operator () (double argument)
	{
		double arg = argument;
		constants_["X"] = &arg;
		ParsedFunctionConstants = &constants_;
		ParsedFunctionFunctions = &functions_;
		ParsedFunction_initBuffer(expression_.c_str());
		ParsedFunctionparse();
		ParsedFunction_delBuffer();
		return ParsedFunctionResult;
	}

}
