// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//


#include <BALL_core/FORMAT/commandlineParser.h>
#include <BALL_core/FORMAT/PDBFile.h>
#include <BALL_core/FORMAT/MOLFile.h>

#include <BALL_core/COMMON/version.h>


using namespace BALL;
using namespace std;


int main (int argc, char* argv[])
{
	CommandlineParser par("PDBReceptorSplitter", "Separate ligand and receptor", VersionInfo::getVersion(), String(__DATE__), "Protein Preparation");
	par.registerParameter("i", "PDB input file", INFILE, true);
	par.registerParameter("rec", "Receptor output file name", OUTFILE, true);
	par.registerParameter("lig", "Ligand output file name", OUTFILE, true);
	par.registerParameter("lig_chain", "Ligand chain name", STRING, true);
	par.registerParameter("lig_name", "Ligand identifier (PDB chemical component identifier)", STRING, true);
	par.registerParameter("rmc", "Protein chains to be deleted", STRINGLIST);
	par.registerParameter("rmr", "Residues to be deleted (e.g. water or ions)", STRINGLIST);

	String man = "This tool splits a PDB file into two files containing receptor and reference ligand, respectively.\n"
				 "The name of the reference ligand (chemical component identifier) and the name of its chain need to be specified.\n"
				 "Optionally, chains (e.g. in case of multimers) or residues (e.g. water or ions) that you don't need can be deleted from the receptor.\n"
				 "Output of this tool is one PDB file containing the receptor and one MOL file containing the reference ligand.";

	par.setToolManual(man);

	par.setSupportedFormats("i", "pdb");
	par.setSupportedFormats("rec", "pdb");
	par.setSupportedFormats("lig", "mol");

	par.parse(argc, argv);

	if (par.has("quiet"))
	{
		Log.disableOutput();
	}

	String lig_chain = par.get("lig_chain");
	String lig_name = par.get("lig_name");

	list<String> plist = par.getList("rmc");
	set<String> delete_chains;
	for (list < String > ::iterator it = plist.begin(); it != plist.end(); it++)
	{
		delete_chains.insert(*it);
	}

	plist = par.getList("rmr");
	set<String> delete_residues;
	for (list < String > ::iterator it = plist.begin(); it != plist.end(); it++)
	{
		delete_residues.insert(*it);
	}

	Molecule ligand;
	Protein protein;

	PDBFile pdb_in;
	pdb_in.open(par.get("i"));
	pdb_in >> protein;
	pdb_in.close();

	for (ChainIterator it_ch = protein.beginChain(); it_ch != protein.endChain(); ++it_ch)
	{
		if (it_ch->getName() == lig_chain)
		{
			for (ResidueIterator it_res = it_ch->beginResidue(); it_res != it_ch->endResidue(); ++ it_res)
			{
				if (it_res->getName() == lig_name)
				{
					Residue* res = new Residue(*it_res);
					ligand.append(*res);
					ligand.setName(it_res->getName());
					it_res->select();
				}
				else if (delete_residues.find(it_res->getName()) != delete_residues.end())
				{
					it_res->select();
				}
			}
		}
		else if (delete_residues.size() > 0)
		{
			for (ResidueIterator it_res = it_ch->beginResidue(); it_res != it_ch->endResidue(); ++ it_res)
			{
				if (delete_residues.find(it_res->getName()) != delete_residues.end())
				{
					it_res->select();
				}
			}
		}

		if (delete_chains.find(it_ch->getName()) != delete_chains.end())
		{
			it_ch->select();
		}
	}

	protein.removeSelected();

	PDBFile rec_out(par.get("rec"), File::MODE_OUT);
	rec_out << protein;
	rec_out.close();

	if (ligand.countAtoms() == 0)
	{
		Log.error() << "-- Error: A ligand with identifier '" << lig_name << "' has not been found in chain '" << lig_chain << "'." << endl << endl;
		exit(1);
	}
	else
	{
		MOLFile lig_out(par.get("lig"), File::MODE_OUT);
		lig_out << ligand;
		lig_out.close();
	}

	Log.level(10) << "++ Generated receptor PDB file: " << par.get("rec") << endl;
	Log.level(10) << "++ Generated ligand MOL file: " << par.get("lig") << endl;
	Log.level(10) << "++ DONE." << endl;

	return 0;
}
