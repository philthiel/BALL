// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//


#include <BALL_core/FORMAT/commandlineParser.h>
#include <BALL_core/FORMAT/HINFile.h>
#include <BALL_core/FORMAT/INIFile.h>
#include <BALL_core/FORMAT/molFileFactory.h>
#include <BALL_core/FORMAT/PDBFile.h>
#include <BALL_core/KERNEL/PTE.h>
#include <BALL_core/MOLMEC/COMMON/radiusRuleProcessor.h>
#include <BALL_core/MOLMEC/COMMON/chargeRuleProcessor.h>
#include <BALL_core/STRUCTURE/fragmentDB.h>
#include <BALL_core/SOLVATION/poissonBoltzmann.h>
#include <BALL_core/STRUCTURE/defaultProcessors.h>

#include <BALL_core/COMMON/version.h>

#include <iostream>

using namespace BALL;
using namespace std;


// Dump the atom charges and radii to a file
void dumpFile(const System& s, const String& dump_file)
{
	File outfile(dump_file, File::MODE_OUT);

	outfile << "#   PB dump file" << endl;
	outfile << "# atom  element   charge[e0]  radius[A]" << endl;
	outfile << "#---------------------------------------" << endl;

	double total_charge = 0.0;
	for (AtomConstIterator it=s.beginAtom(); +it; ++it)
	{
		total_charge += it->getCharge();

		outfile << setprecision(5)
				<< it->getFullName()
				<< " " << it->getElement().getSymbol()
				<< " " << it->getCharge()
				<< " " << it->getRadius()
				<< endl;
	}

	outfile << "# total charge: " << total_charge << " e0" << endl;

	outfile.close();
}



int main(int argc, char* argv[])
{
	/*
	 * This TOOLS is created from the source code in BALL/source/APPLICATIONS/PB
	 * It should have the same functionality with somewaht different command line parameters.
	 */

	CommandlineParser par("PoissonBoltzmannSolver", "Calculate solvation free energy using the BALL Poisson Boltzmann Solver", VersionInfo::getVersion(), String(__DATE__), "Solvation");
	par.registerParameter("i", "Input file containing target structure", INFILELIST, true);
	par.registerParameter("d", "Output file to dump the atom charges, radii, and surface fractions.", OUTFILE, false);
	par.registerParameter("o", "Input file with FDPB options", INFILE, false);
	par.registerParameter("c", "Input file with charges", INFILE, false);
	par.registerParameter("r", "Input file with radii", INFILE, false);
	par.registerParameter("t", "Input file with charge and radius rules", INFILE, false);
	par.registerParameter("u", "Input file with charge rules", INFILE, false);
	par.registerParameter("w", "Input file with radius rules", INFILE, false);

	par.registerParameter("E", "Dielectric constant of the surrounding medium", DOUBLE, false, "78.0");
	par.registerParameter("F", "Dielectric constant of the solute interior", DOUBLE, false, "2.0");
	par.registerParameter("I", "Ionic strength set for the Boltzmann part of the Poisson-Boltzmann equation", DOUBLE, false, "0.0");

	par.registerFlag("k", "Do not assign charges to input files in HIN format", false);
	par.registerFlag("z", "Clear all charges in input structures", false);
	par.registerFlag("s", "Calculate the solvation free energy by performing a second FDPB calculation in vacuum", false);
	par.registerFlag("n", "Normalize all atom names in input structures", false);
	par.registerFlag("b", "Try to build bonds input structures", false);
	
	String man = "";

	par.setToolManual(man);
	par.setSupportedFormats("i", "pdb,hin");
	par.setSupportedFormats("d", "txt");
	par.setSupportedFormats("o", "ini");
	par.setSupportedFormats("c", "ini");
	par.setSupportedFormats("r", "ini");
	par.setSupportedFormats("t", "ini");
	par.setSupportedFormats("u", "ini");
	par.setSupportedFormats("w", "ini");

	par.parse(argc, argv);

	System s;
	Options options;
	FragmentDB* fdb = new FragmentDB;
	FDPB fdpb;
	AssignChargeProcessor charges("charges/PARSE.crg");
	AssignRadiusProcessor radii("radii/PARSE.siz");
	ClearChargeProcessor clear_charge_proc;
	ChargeRuleProcessor charge_rules;
	RadiusRuleProcessor radius_rules;

	bool use_radius_rules = false;
	bool use_charge_rules = false;

	if (par.has("o"))
	{
		Log.info() << "++ Reading options from " << par.get("o") << endl;
		options.readOptionFile(par.get("o"));
	}

	if (par.has("c"))
	{
		Log.info() << "++ Reading charges from " << par.get("c") << endl;
		charges.setFilename(par.get("c"));
		use_charge_rules = false;
	}

	if (par.has("r"))
	{
		Log.info() << "++ Reading radii from " << par.get("r") << endl;
		radii.setFilename(par.get("r"));
		use_radius_rules = false;
	}

	if (par.has("t"))
	{
		Log.info() << "++ Reading charge and radius rules from " << par.get("t") << endl;

		// Open and read the rules file
		INIFile ini(par.get("t"));
		ini.read();

		charge_rules.initialize(ini, "ChargeRules");
		radius_rules.initialize(ini, "RadiusRules");

		use_charge_rules = true;
		use_radius_rules = true;
	}

	if (par.has("u"))
	{
		Log.info() << "++ Reading charge rules from " << par.get("u") << endl;

		// Open and read the rules file
		INIFile ini(par.get("u"));
		ini.read();

		charge_rules.initialize(ini, "ChargeRules");

		use_charge_rules = true;
	}

	if (par.has("w"))
	{
		Log.info() << "++ Reading radius rules from " << par.get("w") << endl;

		// Open and read the rules file
		INIFile ini(par.get("w"));
		ini.read();

		radius_rules.initialize(ini, "RadiusRules");

		use_radius_rules = true;
	}

	if (par.has("E"))
	{
		Log.info() << "++ Dielectric constant of the medium is set to " << par.get("E") << endl;
		options[FDPB::Option::SOLVENT_DC] = par.get("E").toDouble();
	}

	if (par.has("F"))
	{
		Log.info() << "++ Dielectric constant of the solute is set to " << par.get("F") << endl;
		options[FDPB::Option::SOLUTE_DC] = par.get("F").toDouble();
	}

	if (par.has("I"))
	{
		Log.info() << "++ Ionic strength for Boltzmann calculations is set to " << par.get("I") << " mol/l" << endl;
		options[FDPB::Option::IONIC_STRENGTH] = par.get("I").toDouble();
	}


	GenericMolFile* gmf;
	bool is_pdb;
	bool is_hin;

	const list<String>& infile_list = par.getList("i");
	for (list<String>::const_iterator it=infile_list.begin(); it!=infile_list.end(); ++it)
	{
		gmf = MolFileFactory::open(*it, File::MODE_IN);

		is_pdb = false;
		is_hin = false;
		if (dynamic_cast<PDBFile*>(gmf))
		{
			is_pdb = true;
		}
		if (dynamic_cast<HINFile*>(gmf))
		{
			is_hin = true;
		}

		if (is_pdb || is_hin)
		{
			System s_tmp;
			*gmf >> s_tmp;

			if (par.has("n"))
			{
				s_tmp.apply(fdb->normalize_names);
			}

			if (par.has("b") && is_pdb)
			{
				s_tmp.apply(fdb->build_bonds);
			}

			if (use_radius_rules)
			{
				s_tmp.apply(radius_rules);
			}
			else
			{
				s_tmp.apply(radii);
			}

			// Assign charges if not deactivated for HIN files
			if (!par.has("k"))
			{
				if (par.has("z"))
				{
					// Clear all charges
					s_tmp.apply(clear_charge_proc);
				}
				else
				{
					if (use_charge_rules)
					{
						s_tmp.apply(charge_rules);
					}
					else
					{
						s_tmp.apply(charges);
					}
				}
			}

			s.splice(s_tmp);
		}

		gmf->close();
		delete gmf;

		Log.info() << s.countAtoms() << endl;
	}

	if (s.countAtoms() == 0)
	{
		Log.error() << "-- Error: no atoms given." << endl;
		return 1;
	}

	if (par.has("d"))
	{
		dumpFile(s, par.get("d"));
	}

	// Setup the calculation
	fdpb.setup(s, options);

	if (par.has("s"))
	{
		Log.info() << "++ Calculating the solvation free energy." << endl;
		Log.info() << "++ First calculation step: solvent dielectric constant = " << fdpb.options[FDPB::Option::SOLVENT_DC] << endl;
	}

	// Solve the PB equation
	fdpb.solve();

	// Dump the options for documentation purposes
	//fdpb.options.dump(Log);

	// Print the energies
	Log.info() << "++ Total energy:          " << fdpb.getEnergy() << " kJ/mol" << endl;
	Log.info() << "++ Reaction field energy: " << fdpb.getReactionFieldEnergy() << " kJ/mol" << endl;

	if (par.has("s"))
	{
		Log.info() << "++ Calculating the solvation free energy." << endl;
		Log.info() << "++ First calculation step: solvent dielectric constant = " << fdpb.options[FDPB::Option::SOLVENT_DC] << endl;
	}

	Log.info() << "++ Second calculation step: solvent dielectric constant = 1.0 (vacuum)"  << endl;

	// Store old energies
	double dG = fdpb.getEnergy();
	double dG_RF = fdpb.getReactionFieldEnergy();

	options[FDPB::Option::SOLVENT_DC] = 1.0;
	fdpb.setup(s, options);

	// Solve the PB equation
	fdpb.solve();

	// Dump the options for documentation purposes
	//fdpb.options.dump(Log);

	// print the energies
	Log.info() << "++ Total energy:          " << fdpb.getEnergy() << " kJ/mol" << endl;
	Log.info() << "++ Reaction field energy: " << fdpb.getReactionFieldEnergy() << " kJ/mol" << endl;
	Log.info() << endl;

	Log.info() << "++ Solvation energy as change of the total energy:   " << dG - fdpb.getEnergy()<< " kJ/mol" << endl;
	Log.info() << "++ Solvation energy as change of the reaction field: " << dG_RF - fdpb.getReactionFieldEnergy() << " kJ/mol" << endl;

	return 0;
}
