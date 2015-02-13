// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//


#include <BALL_core/common.h>
#include <BALL_core/FORMAT/commandlineParser.h>
#include <BALL_core/FORMAT/PDBFile.h>
#include <BALL_core/KERNEL/system.h>
#include <BALL_core/KERNEL/selector.h>
#include <BALL_core/STRUCTURE/numericalSAS.h>
#include <BALL_core/STRUCTURE/defaultProcessors.h>

#include <BALL_core/COMMON/version.h>


using namespace std;
using namespace BALL;


int main(int argc, char* argv[])
{
	NumericalSAS nsas;

	CommandlineParser par("SolventAccessibility", "Calculate solvent exposed residues from a PDB protein", VersionInfo::getVersion(), String(__DATE__), "Analysis");
	par.registerParameter("i", "PDB input file", INFILE,  true);
	par.registerParameter("o", "Tab-separared output file", OUTFILE, true);
	par.registerParameter("b", "Buriedness cutoff in A^2 to mark residues buried.", DOUBLE, false, "10.0");
	par.registerParameter("r", "Probe sphere radius used for surface calculation in Angstrom", DOUBLE, false, nsas.options.getReal(NumericalSAS::Option::PROBE_RADIUS));

	par.registerFlag("p", "Print results on the command line");

	String man = String("This utility reads a PDB structure, removes water and"
						" computes which residues are solvent exposed by summing up"
						" atom-based solvent-accessible surface areas."
						" Output is a list of all residues annotated with their solvent-accessible surface area"
						" and if the residue is buried according to the buriedness cutoff parameter 'b'."
						" The output is written to the specified file (parameter 'o') and can optionally be printed on the command line (flag 'p')");

	par.setToolManual(man);

	par.setSupportedFormats("i", "pdb");
	par.setSupportedFormats("o", "txt");

	par.parse(argc, argv);


	// Read PDB input file
	PDBFile infile(par.get("i"));
	if (!infile)
	{
		// if the file could not be opened, print error message and exit
		Log.info() << "-- PBD input file cannot be opened: " << argv[1] << endl;
		return 1;
	}

	System S;
	infile >> S;
	infile.close();

	// Remove water molecules
	Size atoms = S.countAtoms();
	Selector wat("residue(HOH) OR residue(WAT)");
	S.apply(wat);
	S.removeSelected();
	Log.info() << "++ Removed " << atoms - S.countAtoms() << " water molecules." << endl;


	// Assign atom radii
	Log.info() << "++ Apply AssignRadiusProcessor." << endl;

	AssignRadiusProcessor rp("radii/PARSE.siz");
	S.apply(rp);


	// Get buriedness cutoff
	float min_area = par.get("b").toFloat();
	Log.info() << "++ Buriedness cutoff set to " << min_area << " A^2" << endl;
	Log.info() << "++ Residues with SAS area below this cutoff are marked as 'buried'." << endl;


	// Perform SAS calculation
	nsas.options.setReal(NumericalSAS::Option::PROBE_RADIUS, par.get("r").toFloat());
	nsas.options.setBool(NumericalSAS::Option::COMPUTE_VOLUME, false);
	nsas(S);
	HashMap<const Atom*, float> atom_areas = nsas.getAtomAreas();


	// Write and optionally print results
	File outfile(par.get("o"), File::MODE_OUT);

	if (par.has("p"))
	{
		Log.info() << "++ Residue solvent-accessible areas [A^2]:" << endl;
		Log.info() << "   RES_NAME\tRES_ID\tSASA\tBURIED" << endl;
	}
	outfile << "RES_NAME\tRES_ID\tSASA\tBURIED" << endl;

	for (ResidueIterator ri = S.beginResidue(); +ri; ++ri)
	{
		float area = 0.0;
		for (AtomIterator ai = ri->beginAtom(); +ai; ++ai)
		{
			if (atom_areas.has(&*ai))
			{
				area += atom_areas[&*ai];
			}
		}

		if (par.has("p"))
		{
			Log.info() << "  " << ri->getName() << "\t" << ri->getID() << "\t" << area << "\t";
			if (area < min_area)
			{
				Log.info() << "buried";
			}
			Log.info() << endl;
		}

		outfile << ri->getName() << "\t" << ri->getID() << "\t" << area << "\t";
		if (area < min_area)
		{
			outfile << "buried";
		}
		outfile <<  endl;
	}

	outfile.close();

	return 0;
}
