// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//


#include <BALL_core/FORMAT/commandlineParser.h>
#include <BALL_core/FORMAT/PDBFile.h>

#include <BALL_core/COMMON/version.h>


using namespace BALL;
using namespace std;


int main (int argc, char* argv[])
{
	CommandlineParser par("PDBChainSplitter", "Split chains of a single PDB file into separate PDB files.", VersionInfo::getVersion(), String(__DATE__), "File Manipulation");
	par.registerParameter("i", "PDB input file", INFILE, true);
	par.registerParameter("rmc", "Protein chains to be deleted", STRINGLIST);

	String man = "This tool splits the chains of a single PDB file up and stores them in separate files.\n"
				 "By default, the output file names are the input file names with the contained chain ID as a suffix.\n"
				 "The parameter '-rmc' can be used to specify chain IDs that should not be written to an output file.";

	par.setToolManual(man);

	par.setSupportedFormats("i", "pdb");

	par.parse(argc, argv);

	if (par.has("quiet"))
	{
		Log.disableOutput();
	}

	list<String> plist = par.getList("rmc");
	set<String> delete_chains;
	for (list < String > ::iterator it = plist.begin(); it != plist.end(); it++)
	{
		delete_chains.insert(*it);
	}

	Protein protein;

	PDBFile pdb_in;
	pdb_in.open(par.get("i"));
	pdb_in >> protein;
	pdb_in.close();

	map<String, Protein*> protein_map;
	for (unsigned int i=0; i!=protein.countChains(); ++i)
	{
		String c_name = protein.getChain(i)->getName();

		if (delete_chains.find(c_name) == delete_chains.end())
		{
			if (protein_map.find(c_name) == protein_map.end())
			{
				protein_map.insert(make_pair(c_name, new Protein()));
			}

			Chain* c = new Chain(*protein.getChain(i));
			protein_map[c_name]->insert(*c);
		}
	}

	String out_base = FileSystem::baseName(par.get("i")).before(".");
	for (map<String, Protein*>::iterator it=protein_map.begin(); it!=protein_map.end(); ++it)
	{
		String out_name = out_base + "_" + it->first + ".pdb";

		PDBFile out(out_name, File::MODE_OUT);
		out << *it->second;
		out.close();

		Log.level(10) << "++ Generated PDB file: " << out_name << endl;

		delete it->second;
	}

	Log.level(10) << "++ DONE." << endl;

	return 0;
}
