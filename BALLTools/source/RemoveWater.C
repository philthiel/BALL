// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//


#include <BALL_core/FORMAT/commandlineParser.h>
#include <BALL_core/FORMAT/PDBFile.h>

#include <BALL_core/COMMON/version.h>


using namespace BALL;
using namespace std;


int main(int argc, char* argv[])
{
	CommandlineParser par("RemoveWater", "Removes water molecules from a PDB file ", VersionInfo::getVersion(), String(__DATE__), "Protein Preparation");
	par.registerParameter("i",  "PDB input file", INFILE,  true);
	par.registerParameter("o",  "PDB output file", OUTFILE, true);

	String man = String("This tool removes all water molecules from a given PDB file.");

	par.setToolManual(man);

	par.setSupportedFormats("i", "pdb");
	par.setSupportedFormats("o", "pdb");

	par.parse(argc, argv);

	Protein protein;
	PDBFile pdb_in;
	pdb_in.open(par.get("i"));
	pdb_in >> protein;
	pdb_in.close();

	for (ChainIterator it_ch = protein.beginChain(); it_ch != protein.endChain(); ++it_ch)
	{
		for (ResidueIterator it_res = it_ch->beginResidue(); it_res != it_ch->endResidue(); ++ it_res)
		{
			if (it_res->getName() == "HOH")
			{
				it_res->select();
			}
		}
	}

	protein.removeSelected();

	PDBFile pdb_out(par.get("o"), File::MODE_OUT);
	pdb_out << protein;
	pdb_out.close();

	Log.level(10) << "++ Generated " << par.get("o") << " output file without water molecule." << endl;
	Log.level(10) << "++ DONE." << endl;

	return 0;
}
