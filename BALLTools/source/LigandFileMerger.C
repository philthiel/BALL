// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//


#include <BALL_core/FORMAT/commandlineParser.h>
#include <BALL_core/FORMAT/dockResultFile.h>
#include <BALL_core/FORMAT/genericMolFile.h>
#include <BALL_core/FORMAT/molFileFactory.h>
#include <BALL_core/FORMAT/MOL2File.h>
#include <BALL_core/FORMAT/SDFile.h>
#include <BALL_core/KERNEL/molecule.h>

#include <BALL_core/COMMON/version.h>


using namespace BALL;
using namespace std;


int main(int argc, char* argv[])
{
	CommandlineParser par("DockResultMerger", "merge docking output files", VersionInfo::getVersion(), String(__DATE__), "File Manipulation");
	par.registerParameter("i", "List of input files to be merged", INFILELIST, true);
	par.registerParameter("o", "Output file name", OUTFILE, true);
	par.registerFlag("rm", "Remove input files after merging");

	par.setSupportedFormats("i","mol,mol2,sdf,drf");
	par.setSupportedFormats("o","mol2,sdf,drf");

	String manual = "This tool merges multiple molecule files into a single one.";
	par.setToolManual(manual);

	par.parse(argc, argv);

	// Open output file
	String outfile_name = par.get("o");
	GenericMolFile* outfile = MolFileFactory::open(outfile_name, File::MODE_OUT);

	if (outfile == NULL)
	{
		Log.error() << "-- Error: The format of the specified output file is unknown or not supported." << endl << endl;
		exit(1);
	}

	// Check if we have DRF output format
	DockResultFile* drf_outfile = dynamic_cast<DockResultFile*>(outfile);
	if (drf_outfile != NULL)
	{
		drf_outfile->disableAutomaticResultCreation();
	}

	Size n_mols = 0;
	Molecule* mol;
	GenericMolFile* infile;

	const list<String>& input_files = par.getList("i");
	for (list<String>::const_iterator it=input_files.begin(); it!=input_files.end(); ++it)
	{
		// Open input file
		infile = MolFileFactory::open(*it, File::MODE_IN);

		if (infile == NULL)
		{
			Log.level(10) << "++ NOTE: Input file '" << *it << "'' could not be read. File is skipped" << endl;
		}
		else
		{
			// Read molecules
			mol = infile->read();
			while (mol != NULL)
			{
				cout << mol->getProperty("PUBCHEM_EXT_DATASOURCE_REGID").toString() << endl;
				// Write molecule to output file
				outfile->write(*mol);
				++n_mols;

				delete mol;
				mol = infile->read();
				cout << mol << endl;
			}

			// Close and delete infile
			infile->close();
			delete infile;
		}

		// Check if input files should be deleted
		if (par.has("rm"))
		{
			File::remove(*it);
		}
	}

	// Clean up
	outfile->close();
	delete outfile;

	Log.level(10) << "++ Output file '" << outfile_name << "' contains " << n_mols << " molecules." << endl;
	Log.level(10) << "++ DONE." << endl;


	return 0;
}
