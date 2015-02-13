// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#include <BALL_core/DATATYPE/options.h>
#include <BALL_core/FORMAT/commandlineParser.h>
#include <BALL_core/FORMAT/HINFile.h>
#include <BALL_core/FORMAT/INIFile.h>
#include <BALL_core/FORMAT/molFileFactory.h>
#include <BALL_core/FORMAT/PDBFile.h>
#include <BALL_core/KERNEL/selector.h>
#include <BALL_core/MOLMEC/AMBER/amber.h>
#include <BALL_core/MOLMEC/COMMON/gradient.h>
#include <BALL_core/MOLMEC/COMMON/radiusRuleProcessor.h>
#include <BALL_core/MOLMEC/COMMON/chargeRuleProcessor.h>
#include <BALL_core/MOLMEC/MINIMIZATION/conjugateGradient.h>
#include <BALL_core/MOLMEC/MINIMIZATION/steepestDescent.h>
#include <BALL_core/SOLVATION/poissonBoltzmann.h>
#include <BALL_core/STRUCTURE/fragmentDB.h>
#include <BALL_core/STRUCTURE/defaultProcessors.h>
#include <BALL_core/STRUCTURE/residueChecker.h>

#include <BALL_core/COMMON/version.h>

#include <iostream>

using namespace BALL;
using namespace std;


class	SingleFile
{
	public:

		void moveTo(System& new_system);

		void moveBack();

		void readPDB(const String& file);
		void readHIN(const String& file, System& S);

		void write() const;

		System& getSystem()
		{
			return system;
		}


	protected:

		enum Type
		{ PDB,
		  HIN
		};

		list<Composite*>	composites;
		System				system;
		String				filename;
		Type				type;
};


void SingleFile::moveTo(System& new_system)
{
	Log.info() << "moving all " << system.countAtoms() << " of " << filename << " into new system" << endl;
	while (system.countDescendants() != 0)
	{
		Log.info() << "moving composite..." << endl;
		// save the address of the composite and insert it into the new system
		composites.push_back(system.getChild(0));
		new_system.Composite::prependChild(*system.getChild(0));
	}
}


void SingleFile::moveBack()
{
	while (!composites.empty())
	{
		// insert all composites back into the system
		system.prependChild(*composites.back());
		composites.pop_back();
	}
}


void SingleFile::readPDB(const String& file)
{
	type = PDB;
	filename = file;
	PDBFile pdb_file(filename);
	if (!pdb_file.good())
	{
		Log.error() << "cannot open " << filename << " for reading." << endl;
	}
	else
	{
		pdb_file >> system;
	}
	pdb_file.close();
}


void SingleFile::readHIN(const String& file, System& S)
{
	type = HIN;
	filename = file;
	HINFile hin_file(filename);
	if (!hin_file.good())
	{
		Log.error() << "cannot open " << filename << " for reading." << endl;
	}
	else
	{
		hin_file >> S;
	}

	hin_file.close();
}


void SingleFile::write() const
{
	if (type == HIN)
	{
		HINFile hin_file(filename + "_opt", ios::out);
		if (hin_file.bad())
		{
			Log.error() << "cannot open " << filename << " for writing." << endl;
		}
		else
		{
			hin_file.write(system);
		}
	}
	else
	{
		PDBFile pdb_file(filename + "_opt", ios::out);
		if (pdb_file.bad())
		{
			Log.error() << "cannot open " << filename << " for writing." << endl;
		}
		else
		{
			pdb_file << system;
		}
		pdb_file.close();
	}
}


void singlePoint(AmberFF& amber)
{
	double energy = amber.updateEnergy();

	amber.updateForces();
	Gradient grad;
	grad.set(amber.getAtoms());
	grad.normalize();

	Log.info() << "++ Single point energy: " << energy << " kJ/mol" << endl;
	Log.info() << "   stretch      :" << amber.getStretchEnergy() << " kJ/mol" << endl;
	Log.info() << "   bend         :" << amber.getBendEnergy() << " kJ/mol" << endl;
	Log.info() << "   torsion      :" << amber.getTorsionEnergy() << " kJ/mol" << endl;
	Log.info() << "   VdW          :" << amber.getVdWEnergy() << " kJ/mol" << endl;
	Log.info() << "   electrostatic:" << amber.getESEnergy() << " kJ/mol" << endl;
	Log.info() << "   grad: " << grad.rms << endl;
}


void writeSystem(vector<SingleFile>& PDB_files)
{
	// Dissolve the system again
	Log.info() << "++ Writing PDB files" << endl;

	for (Size i = 0; i < PDB_files.size(); i++)
	{
		PDB_files[i].moveBack();
		PDB_files[i].write();
	}
}


int main(int argc, char* argv[])
{
	/*
	 * This TOOLS is created from the source code in BALL/source/APPLICATIONS/AMBER
	 * It should have the same functionality with somewaht different command line parameters.
	 */

	CommandlineParser par("AMBER", "Optimization and energy calculation", VersionInfo::getVersion(), String(__DATE__), "ForceField");
	par.registerParameter("i", "Input file containing target structure", INFILELIST, true);
	par.registerParameter("f", "Force field file", STRING, false, "Amber/amber96.ini");
	par.registerParameter("o", "Read options file from <OPTIONS> (advanced users only!)", STRING, false);

	par.registerParameter("t", "Processing options: energy minimization [min], energy calculation [calc], or input structure check [check]", STRING, false, "min");
	par.registerParameter("c", "Maximum number of iterations", INT, false, 400);
	par.registerParameter("g", "Gradient criterion for optimization in units of kJ/(mol A)", DOUBLE, false, 0.1);
	par.registerParameter("e", "Energy limit per residue in kJ/mol", DOUBLE, false, 500.0);
	par.registerParameter("s", "Select only the atoms that match <STRING> for optimization.", STRING, false);

	par.registerFlag("a", "If HyperChem input file do not assign charges", false);
	par.registerFlag("n", "Normalize all atom names in input structures", false);
	par.registerFlag("b", "Try to build bonds input structures", false);
	par.registerFlag("d", "Steepest descent minimizer", false);
	
	String man = "STRING can contain any of the BALL expression predicates, e.g. 'resname(ARG)' would select all arginines,\n"
				 "to select their CA and CB only, 'resname(ARG) AND (name(CA) OR name(CB))' should do."
				 "Supported predicates are:\n"
				 "  - name(<atomname>)\n"
				 "  - type(<atomtype>)\n"
				 "  - element(<element>)\n"
				 "  - residue(<residuename>)\n"
				 "  - residueID(<PDB ID>)\n"
				 "  - secondaryStruct()\n"
				 "  - solvent()\n"
				 "  - backbone()\n"
				 "  - chain(<chain ID>)\n"
				 "  - nucleotide()\n"
				 "  - connectedTo(<neighbors>) -- special syntax!\n"
				 "All predicates can be combined using 'AND', 'OR', brackets, and '!' (in front of a predicate) for negation.\n"
				 "In order to avoid shell argument trouble, please enclose any expression string with single quotes (e.g. -s 'residueID(17)').";

	par.setToolManual(man);
	par.setSupportedFormats("i", "pdb,hin");

	par.parse(argc, argv);

	/*
	 * Globally used objects
	 */

	FragmentDB*           frag_db = new FragmentDB;
	FDPB                  fdpb;
	AssignChargeProcessor charges("charges/PARSE.crg");
	AssignRadiusProcessor radii("radii/PARSE.siz");
	ClearChargeProcessor  clear_charge_proc;

	ChargeRuleProcessor   charge_rules;
	RadiusRuleProcessor   radius_rules;

	Options               options;
	System                S;

	String dump_file;

	vector<SingleFile>	PDB_files;

	AmberFF amber;

	String proc_opt = par.get("t");

	// Check if valid processing option is given
	if (proc_opt != "check" && proc_opt != "calc" && proc_opt != "min")
	{
		Log.error() << "-- Please specify a valid processing option (-t)." << endl;
		Log.error() << "-- Candidates are: energy minimization [min], energy calculation [calc], or input structure check [check]" << endl;

		return 1;
	}

	// Maximum number of iterations
	Size max_iterations = par.get("c").toUnsignedInt();

	// Gradient criterion
	double max_gradient = par.get("g").toDouble();

	// Energy limit per residue
	double energy_limit = par.get("e").toDouble();

	// Assign charges in case of HyperChem input file
	bool assign_charges = par.get("a").toBool();

	// Normalize names flag
	bool normalize_names = par.get("n").toBool();

	// Build bonds flag
	bool build_bonds = par.get("b").toBool();

	// Steepest descent minimizer flag
	bool sd_minimizer = par.get("d").toBool();

	// Use and parse selection
	bool use_selection = false;
	String selection;
	if (par.has("s"))
	{
		selection = par.get("s");
		use_selection = true;
	}

	// Force field file name
	String FF_filename = par.get("f");

	// Option file
	if (par.has("o"))
	{
		Options o;
		o.readOptionFile(par.get("o"));
		amber.options = o;
		Log.info() << "++ Options:" << endl;
		amber.options.dump(cout);
	}


	// Read input file
	String infile_format;
	const list<String>& infile_list = par.getList("i");
	for (list<String>::const_iterator it=infile_list.begin(); it!=infile_list.end(); ++it)
	{
		infile_format = MolFileFactory::getFileFormat(*it, false);
		infile_format.toLower();

		if (infile_format == String(".pdb"))
		{
			Log.info() << "++ Reading PDB file: " << *it << endl;

			PDB_files.push_back(SingleFile());
			PDB_files.back().readPDB(*it);

			Log.info() << "   read " << PDB_files.back().getSystem().countAtoms() << " atoms from " << *it << endl;

			if (normalize_names)
			{
				System& tmp_system = PDB_files.back().getSystem();
				tmp_system.apply(frag_db->normalize_names);
			}

			if (build_bonds)
			{
				System& tmp_system = PDB_files.back().getSystem();
				tmp_system.apply(frag_db->build_bonds);
			}

			// insert into the system
			PDB_files.back().moveTo(S);
		}

		if (infile_format == String(".hin"))
		{
			System system;

			Log.info() << "++ Reading HIN file: " << *it << endl;
			PDB_files.push_back(SingleFile());
			PDB_files.back().readHIN(*it, S);

			Log.info() << "   read " << PDB_files.back().getSystem().countAtoms() << " atoms from " << *it << endl;

			if (normalize_names)
			{
				System& tmp_system = PDB_files.back().getSystem();
				tmp_system.apply(frag_db->normalize_names);
			}

			if (build_bonds)
			{
				System& tmp_system = PDB_files.back().getSystem();
				tmp_system.apply(frag_db->build_bonds);
			}

			// insert into the system
			PDB_files.back().moveTo(system);

			if (par.get("h").toBool())
			{
				S.splice(system);
			}
		}
	}


	// Check whether anything was constructed at all
	if (S.countAtoms() == 0)
	{
		Log.error() << "-- Error: no atoms given." << endl;
		return 1;
	}

	// Setup logging to print the current time in front of each line
	Log.setPrefix(cout, "[%T] ");
	Log.setPrefix(cerr, "[%T ERROR] ");

	if (proc_opt == String("check"))
	{
		// Do structure check only
		Log.info() << "++ System contains " << S.countAtoms() << " atoms." << endl;

		// building bonds
		S.apply(frag_db->build_bonds);

		// checking residues
		Log.info() << "++ Checking system" << endl;
		ResidueChecker check(*frag_db);
		S.apply(check);

		// Check residue energies
		double energy_limit = 500.0;

		S.deselect();

		amber.setup(S);

		ResidueIterator it = S.beginResidue();
		for (; +it; ++it)
		{
			it->select();
			amber.updateEnergy();
			double residue_energy = amber.getStretchEnergy() + amber.getBendEnergy() + amber.getVdWEnergy();

			if (residue_energy > energy_limit)
			{
				Log.info() << "++ Suspicious energies in residue "
						   << it->getFullName() << ":" << it->getID() << " " << residue_energy
						   << " kJ/mol (bend: " << amber.getBendEnergy() << " kJ/mol, stretch: " << amber.getStretchEnergy()
						   << " kJ/mol, vdW: " << amber.getVdWEnergy() << " kJ/mol)" << endl;
			}

			it->deselect();

			double quality = std::max(0.0, std::min(1.0, (energy_limit - residue_energy) / energy_limit));

			for (PDBAtomIterator ai = it->beginPDBAtom(); +ai; ++ai)
			{
				ai->setOccupancy(quality);
			}
		}

		writeSystem(PDB_files);
	}
	else
	{
		// Create force field
		Log.info() << "++ Setting up force field" << endl;
		Log.info() << "++ Force field parameters are read from " << FF_filename << endl;

		S.deselect();

		amber.options[AmberFF::Option::FILENAME] = FF_filename;

		if (!amber.setup(S))
		{
			Log.error() << "-- Force field setup failed! Abort." << endl;

			delete frag_db;

			exit(10);
		}

		if (proc_opt == String("calc"))
		{
			// Do single point calculation
			singlePoint(amber);
		}
		else
		{
			singlePoint(amber);

			// Apply selection
			if (use_selection)
			{
				Log.info() << "++ SELECT: " << selection << endl;
				Selector selector(selection);
				S.apply(selector);

				// Count selected vs. unselected atoms
				Size selected = 0;
				AtomConstIterator ai = S.beginAtom();
				for (; +ai; ++ai)
				{
					selected += (ai->isSelected() ? 1 : 0);
				}

				Log.info() << "++ Selected " << selected << " out of " << S.countAtoms() << " atoms." << endl;
			}

			// Do minimization
			Log.info() << "++ Starting minimization";

			EnergyMinimizer* minimizer;
			if (sd_minimizer)
			{
				minimizer = new SteepestDescentMinimizer(amber);
			}
			else
			{
				minimizer = new ConjugateGradientMinimizer(amber);
			}

			minimizer->setEnergyOutputFrequency(10);
			minimizer->setEnergyDifferenceBound(1e-9);
			minimizer->setMaxSameEnergy(20);
			minimizer->setMaxGradient(max_gradient);
			minimizer->minimize(max_iterations);

			Log.info() << "++ Minimization complete" << endl;
			Log.info() << "++ Final gradient: " << amber.getRMSGradient() << " kJ/mol A" << endl;

			S.deselect();

			amber.updateEnergy();
			Log.info() << "++ Final energy: " << amber.getEnergy() << " kJ/mol" << endl;

			// Dump the minimizer and force field options for documentation purposes
			amber.options.dump(Log);
			minimizer->options.dump(Log);

			Log.info() << "++ Done." << endl;

			singlePoint(amber);

			writeSystem(PDB_files);
		}
	}


	// Clean up ...
	delete frag_db;

	return 0;
}
