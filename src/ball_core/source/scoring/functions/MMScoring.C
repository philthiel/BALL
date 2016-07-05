//_new_file_header


#include <BALL/core/scoring/functions/MMScoring.h>

#include <BALL/core/molmec/amber/amberNonBonded.h>
#include <BALL/core/molmec/common/forceFieldComponent.h>
#include <BALL/core/scoring/components/advElectrostatic.h>
#include <BALL/core/scoring/components/aromaticRingStacking.h>
#include <BALL/core/scoring/components/burialDepth.h>
#include <BALL/core/scoring/components/electrostatic.h>
#include <BALL/core/scoring/components/fragmentationalSolvation.h>
#include <BALL/core/scoring/components/hydrogenBond.h>
#include <BALL/core/scoring/components/lipophilic.h>
#include <BALL/core/scoring/components/rotationalEntropy.h>
#include <BALL/core/scoring/components/solvation.h>
#include <BALL/core/scoring/components/vanDerWaals.h>

#include <vector>

using namespace std;
using namespace BALL;



MMScoring::MMScoring(AtomContainer& receptor, AtomContainer& reference_ligand, Options& options)
	: DifferentiableScoringFunction(receptor, reference_ligand, options)
{
	setup();
}


MMScoring::MMScoring(AtomContainer& receptor, Vector3& hashgrid_origin, Options& options)
	: DifferentiableScoringFunction(receptor, hashgrid_origin, options)
{
	setup();
}


void MMScoring::setup()
{
	ScoringFunction::setName("MMScoring");

	AdvancedElectrostatic* es = new AdvancedElectrostatic(this, options_, forcefield_parameters_);
	es->setCoefficient(0.01);
	scoring_components_.push_back(es);

	VanDerWaals* vdw = new VanDerWaals(es);
	vdw->setCoefficient(0.1);
	vdw->setScoringFunction(*this);
	scoring_components_.push_back(vdw);

	FragmentationalSolvation* solv = new FragmentationalSolvation(*this);
	solv->setCoefficient(19.823265);
	scoring_components_.push_back(solv);

	HydrogenBond* hb = new HydrogenBond(*this, HydrogenBond::ALL_HYDROGENS);
	hb->selectBaseFunction("fermi");
	hb->setCoefficient(3);
	hb->setup();
	scoring_components_.push_back(hb);

	//add ( = penalize) 1kJ/mol for each rotatable bond exceeding 14
	RotationalEntropy* re = new RotationalEntropy(*this);
	re->setNormalizationParameters(1, 14);
	re->setCoefficient(1);
	scoring_components_.push_back(re);
}


double MMScoring::getES()
{
	double es_score = 0;

	for (vector<ScoringComponent*> ::iterator it = scoring_components_.begin(); it != scoring_components_.end(); ++it)
	{
		Electrostatic* es = dynamic_cast<Electrostatic*>(*it);
		if (!(*it)->isLigandIntraMolecular() && (*it)->isEnabled() && es != NULL)
		{
			es_score += es->getScaledScore();
		}
	}

	return es_score;
}
