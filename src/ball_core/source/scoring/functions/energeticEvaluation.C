//_new_file_header


#include <BALL/core/scoring/functions/energeticEvaluation.h>

using namespace std;
using namespace BALL;


EnergeticEvaluation::EnergeticEvaluation()
	throw()
{
}

EnergeticEvaluation::~EnergeticEvaluation()
	throw()
{
}

vector < ConformationSet::Conformation > EnergeticEvaluation::operator () (ConformationSet& conformations)
{
	return conformations.getScoring();
}
