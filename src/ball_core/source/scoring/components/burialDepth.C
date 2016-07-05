//_new_file_header


#include <BALL/core/scoring/components/burialDepth.h>

#include <BALL/core/kernel/atom.h>

#include <vector>

using namespace BALL;
using namespace std;


BurialDepth::BurialDepth(ScoringFunction& sf)
	: ScoringComponent(sf)
{
	gridable_ = false;
	setName("BurialDepth");
}

BurialDepth::~BurialDepth()
{

}

void BurialDepth::update(const vector<std::pair<Atom*, Atom*> >& /*pair_vector*/)
{
	// no need to do anything here
}


double BurialDepth::updateScore()
{
	score_ = scoring_function_->getNoNeighboringReceptorAtoms();

	/*
	scaleScore();
	return score_;
	*/

	return getScaledScore();
}

