#include <BALL_core/SCORING/FUNCTIONS/energeticEvaluation.h>

//using namespace::std;
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
