// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
// $Id: reissCavFreeEnergyProcessor.C,v 1.11 2002/02/27 12:24:07 sturm Exp $

#include <BALL/SOLVATION/reissCavFreeEnergyProcessor.h>
#include <BALL/STRUCTURE/numericalSAS.h>

using namespace std;

namespace BALL
{

	const char* ReissCavFreeEnergyProcessor::Option::VERBOSITY = "verbosity";
	const char* ReissCavFreeEnergyProcessor::Option::SOLVENT_NUMBER_DENSITY 
		= "solvent_number_density";
	const char* ReissCavFreeEnergyProcessor::Option::PRESSURE = "pressure";
	const char* ReissCavFreeEnergyProcessor::Option::ABSOLUTE_TEMPERATURE 
		= "absolute_temperature";
	const char* ReissCavFreeEnergyProcessor::Option::PROBE_RADIUS 
		= "probe_radius";
	
	const int ReissCavFreeEnergyProcessor::Default::VERBOSITY = 0;
	const float ReissCavFreeEnergyProcessor::Default::SOLVENT_NUMBER_DENSITY 
		= 3.33253e-2;
	const float ReissCavFreeEnergyProcessor::Default::PRESSURE = 1.01325e5;
	const float ReissCavFreeEnergyProcessor::Default::ABSOLUTE_TEMPERATURE 
		= 298.0;
	const float ReissCavFreeEnergyProcessor::Default::PROBE_RADIUS = 1.385;


	ReissCavFreeEnergyProcessor::ReissCavFreeEnergyProcessor()
		: EnergyProcessor()
	{
		setDefaultOptions();

		valid_ = true;
	}


	ReissCavFreeEnergyProcessor::ReissCavFreeEnergyProcessor
		(const ReissCavFreeEnergyProcessor& proc)
		: EnergyProcessor(proc)
	{
	}


	ReissCavFreeEnergyProcessor::~ReissCavFreeEnergyProcessor()
	{
		clear();

		valid_ = false;
	}


	void ReissCavFreeEnergyProcessor::clear()
	{
		EnergyProcessor::clear();
		setDefaultOptions();

		valid_ = true;
	}


	const ReissCavFreeEnergyProcessor& ReissCavFreeEnergyProcessor::operator = (const ReissCavFreeEnergyProcessor& proc) 
	{
		valid_ = proc.valid_;
		energy_ = proc.energy_;
		fragment_ = proc.fragment_;  
		return *this;
	}


	bool ReissCavFreeEnergyProcessor::operator == (const ReissCavFreeEnergyProcessor& proc) const
	{
		bool result;
		if ((fragment_ == 0) && (proc.fragment_ == 0))
		{
			result = ((energy_ == proc.energy_) && (valid_ == proc.valid_));
		}
		else
		{
			if ((fragment_ == 0) || (proc.fragment_ == 0))
			{
				result = false;
			}
			else
			{
				result = ((*fragment_ == *proc.fragment_) 
						&& (energy_ 	 == proc.energy_)
						&& (valid_ 	 == proc.valid_));
			}
		}
		return result;
	}


	bool ReissCavFreeEnergyProcessor::finish()
	{

		// first check for user settings

		int verbosity = (int) options.getInteger(Option::VERBOSITY);
		// rho is the number density of the solvent (i. e. water) [1/m^3]
		double rho = options.getReal(Option::SOLVENT_NUMBER_DENSITY) * 1e30;
		// the pressure [ Pa ]
		double P = options.getReal(Option::PRESSURE);
		// the temperature [ K ]
		double T = options.getReal(Option::ABSOLUTE_TEMPERATURE);
		// the solvent radius [ A ]
		double solvent_radius = options.getReal(Option::PROBE_RADIUS);
		if (verbosity > 0) 
		{
			Log.info() << "Using a probe radius of " << solvent_radius << " A" <<
				endl;
		}
		
		// now compute some constant terms (names as in Pierotti, Chem. Rev.
		// 76(6):717--726, 1976)

		double sigma1 = 2 * solvent_radius * 1e-10; // [ m ]
		double sigma1_2 = sigma1 * sigma1; // [ m^2 ]
		double sigma1_3 = sigma1 * sigma1 * sigma1; // [ m^3 ]
		double y = Constants::PI * sigma1_3 * (rho/6);	// [ 1 ]
		double y_frac = y/(1-y); // [ 1 ]
		double y_frac_2 = y_frac * y_frac; // [ 1 ]
		double NkT = Constants::AVOGADRO * Constants::BOLTZMANN * T; // [ J/mol ]
		double NpiP = Constants::AVOGADRO * Constants::PI * P; // [ ? ]

		if (verbosity > 0)
		{
			Log.info() << "y = " << y << endl;
			Log.info() << "y_frac = " << y_frac << endl;
		}

		NumericalSAS sas_computer;
		sas_computer.options[NumericalSAS::Option::PROBE_RADIUS  ] = solvent_radius;
		sas_computer.options[NumericalSAS::Option::COMPUTE_VOLUME] = false;

		sas_computer(*fragment_);
		HashMap<const Atom*,float> atom_areas = sas_computer.getAtomAreas();
		
		// R is the sum of atom radius and probe radius [ m ]
		double R; 
		// deltaGspher is the cavitatonal energy of a spherical solute [ J/mol ]
		double deltaGspher; 
		// deltaGcav is the cavitatonal energy of the molecule [ J/mol ]
		double deltaGcav = 0; 

		// now iterate over the atoms.

		HashMap<const Atom*,float>::Iterator it = atom_areas.begin();
		for (; it != atom_areas.end(); ++it)
		{
			R = it->first->getRadius() * 1e-10 + sigma1 / 2.0;
			deltaGspher =	
				  NkT * (-log(1.0 - y) + 4.5 * y_frac_2) - (NpiP * sigma1_3 / 6.0)
				- (NkT * ((6.0 * y_frac + 18 * y_frac_2) / sigma1) 
						+ (NpiP * sigma1_2)) * R
				+ (NkT * ((12.0 * y_frac + 18 * y_frac_2) / sigma1_2) 
						- (2.0 * NpiP * sigma1)) * (R * R)
				+ 4.0 / 3.0 * NpiP * (R * R * R);
			deltaGcav += it->second * 1e-20 /
				( 4 * Constants::PI * R * R ) * deltaGspher;
		}
		// return energy in units of kJ/mol
		energy_ = deltaGcav/1000;
		return 1;
	}
		
	
	void ReissCavFreeEnergyProcessor::setDefaultOptions()
	{
		options.setDefaultInteger(Option::VERBOSITY, Default::VERBOSITY);
		options.setDefaultReal(Option::SOLVENT_NUMBER_DENSITY, Default::SOLVENT_NUMBER_DENSITY);
		options.setDefaultReal(Option::PRESSURE, Default::PRESSURE);
		options.setDefaultReal(Option::ABSOLUTE_TEMPERATURE, Default::ABSOLUTE_TEMPERATURE);
		options.setDefaultReal(Option::PROBE_RADIUS, Default::PROBE_RADIUS);
	}


} // namespace BALL
