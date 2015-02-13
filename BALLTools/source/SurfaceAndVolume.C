// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//


#include <BALL_core/FORMAT/commandlineParser.h>
#include <BALL_core/FORMAT/molFileFactory.h>
#include <BALL_core/FORMAT/PDBFile.h>
#include <BALL_core/STRUCTURE/analyticalSES.h>
#include <BALL_core/STRUCTURE/defaultProcessors.h>
#include <BALL_core/STRUCTURE/fragmentDB.h>
#include <BALL_core/STRUCTURE/numericalSAS.h>

#include <BALL_core/COMMON/version.h>

#include <iostream>

using namespace BALL;
using namespace std;


int main(int argc, char* argv[])
{
	NumericalSAS nsas;

	CommandlineParser par("MolecularSurfaceAndVolume", "Calculate surface area and the volume of a molecule", VersionInfo::getVersion(), String(__DATE__), "Analysis");
	par.registerParameter("i", "Input file containing target structure", INFILE, true);
	par.registerParameter("s", "Surface type to be used. Options are 'SES' (solvent excluded surface: default) or 'SAS' (solvent accessible surface)", STRING, false, "SES");
	par.registerParameter("r", "Probe sphere radius used for surface calculation in Angstrom", DOUBLE, false, nsas.options.getReal(NumericalSAS::Option::PROBE_RADIUS));

	String man = "";

	par.setToolManual(man);
	par.setSupportedFormats("i", "pdb,hin,mol2,mol,sdf");

	par.parse(argc, argv);

	// Try to open the molecular file
	GenericMolFile* gmf = MolFileFactory::open(par.get("i"), File::MODE_IN);
	if (gmf == NULL)
	{
		Log.info() << "-- Input file '" << par.get("i") << "' can not be read" << endl;
	}

	// Read molecule from file into a system
	System s;
	*gmf >> s;

	// Apply radii to system
	AssignRadiusProcessor radii("radii/PARSE.siz");
	s.apply(radii);

	Log.info() << "++ Input structure contains " << s.countAtoms() << " atoms." << endl;


	// Get probe sphere radius
	float probe_radius = par.get("r").toFloat();
	Log.info() << "++ Probe sphere radius: " << probe_radius << " A" << endl;


	if (par.get("s") == "SES")
	{
		// Calculate the solvent excluded surface area of the solute

		float total_SES_area = calculateSESArea(s, probe_radius);
		float total_SES_volume = calculateSESVolume(s, probe_radius);
		Log.info() << "++ Solvent excluded surface area: " << total_SES_area << " A^2";
		Log.info() << endl;
		Log.info() << "++ Solvent excluded volume:       " << total_SES_volume << " A^3" << endl;
	}
	else if (par.get("s") == "SAS")
	{
		// Calculate the solvent accessible surface area of the solute

		nsas.options.setReal(NumericalSAS::Option::PROBE_RADIUS, probe_radius);
		nsas(s);

		double total_SAS_area = nsas.getTotalArea();
		double total_SAS_volume = nsas.getTotalVolume();
		Log.info() << "++ Solvent accessible surface area: " << total_SAS_area << " A^2";
		Log.info() << endl;
		Log.info() << "++ Solvent accessible volume:       " << total_SAS_volume << " A^3" << endl;
	}
	else
	{
		Log.info() << "-- Specified surface type '" << par.get("s") << "' is unknown. Use either 'SES' (default) or 'SAS'." << endl;
	}

	gmf->close();
	delete gmf;

	return 0;
}
