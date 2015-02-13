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

#include<math.h>


using namespace BALL;
using namespace std;


enum SPLIT_METHODS {
	OUTFILE_LIST,
	NUM_OUTFILES,
	NUM_MOLS_PER_OUTFILE
};


void validateParameterCombination(CommandlineParser& par, SPLIT_METHODS& split_method)
{
	if (par.has("o"))
	{
		split_method = OUTFILE_LIST;

		if (par.has("opattern"))
		{
			Log.level(10) << "++ NOTE: Parameter 'opattern' is ignored because filenames are specified explicitly." << endl;
		}
		if (par.has("no"))
		{
			Log.level(10) << "++ NOTE: Parameter 'no' is ignored because filenames are specified explicitly." << endl;
		}
		if (par.has("nm"))
		{
			Log.level(10) << "++ NOTE: Parameter 'nm' is ignored because filenames are specified explicitly." << endl;
		}
		if (par.has("padding"))
		{
			Log.level(10) << "++ NOTE: Parameter 'padding' is ignored because filenames are specified explicitly." << endl;
		}
	}
	else
	{
		if (par.has("no"))
		{
			split_method = NUM_OUTFILES;

			if (par.has("o"))
			{
				Log.level(10) << "++ NOTE: Parameter 'o' is ignored because the number of output files is specified explicitly." << endl;
			}
			if (par.has("nm"))
			{
				Log.level(10) << "++ NOTE: Parameter 'nm' is ignored because the number of output files is specified explicitly." << endl;
			}
		}
		else
		{
			if (par.has("nm"))
			{
				split_method = NUM_MOLS_PER_OUTFILE;

				if (par.has("o"))
				{
					Log.level(10) << "++ NOTE: Parameter 'o' is ignored because the number of molecules per output file is specified explicitly." << endl;
				}
				if (par.has("no"))
				{
					Log.level(10) << "++ NOTE: Parameter 'no' is ignored because the number of molecules per output file is specified explicitly." << endl;
				}
			}
			else
			{
				// No parameter passed that can be used to determine how to split.
				Log.error() << "-- Error: No parameter passed to specify how to split. Please set either 'o', 'no' or 'nm'." << endl;
				exit(1);
			}
		}
	}

	if (par.has("opattern"))
	{
		String opattern = par.get("opattern");

		vector<String> tmp;
		opattern.split(tmp, "%");

		for (unsigned int i=0; i!=tmp.size(); ++i)
			cerr << tmp[i] << endl;

		if ((tmp.size() != 2 && !opattern.hasPrefix("%")) || (tmp[0][0] != 'd' && tmp[1][0] != 'd') )
		{
			Log.error() << "-- Error: The specified outname pattern '" << opattern << "' is invalid." << endl;
			exit(2);
		}
	}
}


void generateOutfileNames(const String& infile, const String& format_extension, const String& compression,
						  vector<String>& outfile_names, Size n_outfiles, const String& opattern, bool padding)
{
	String outname_prefix;
	String outname_suffix;

	String base_name = FileSystem::baseName(infile);

	// Get filename prefix for generating the output files
	if (opattern.isEmpty())
	{
		// No pattern - use input filename without format extension
		outname_prefix = base_name.before("." + format_extension);
		if (outname_prefix.isEmpty())
		{
			// No file extension
			outname_prefix = base_name;
			Log.level(10) << "++ NOTE: Outfile names will have standard format extension of input file format." << endl;
		}
	}
	else
	{
		outname_prefix = opattern.before("%d");
		outname_suffix = opattern.after("%d");
	}

	// Get number of outfile numbering digits
	Size digits = String(n_outfiles).size();

	// Generate outfile names
	String tmp_name;
	String zero_padding;
	outfile_names.clear();
	for (unsigned int i=1; i<=n_outfiles; ++i)
	{
		if (padding)
		{
			Size s = digits - String(i).size();
			zero_padding = String('0', s);
		}

		if (opattern.isEmpty())
		{
			tmp_name = outname_prefix + "_" + zero_padding + String(i) + "." + format_extension + compression;
		}
		else
		{
			tmp_name = outname_prefix + zero_padding + String(i) + outname_suffix;
		}

		outfile_names.push_back(tmp_name);
	}

	return;
}


int main(int argc, char* argv[])
{
	CommandlineParser par("LigandFileSplitter", "Split single molecule file", VersionInfo::getVersion(), String(__DATE__), "File Manipulation");
	par.registerParameter("i", "Input molecule file", INFILE, true);
	par.registerParameter("no", "Number of output files to be created", BALL::INT, false);
	par.registerParameter("nm", "Maximal number of molecules per output file", BALL::INT, false);
	par.registerParameter("o", "Output filenames. If none are specified, input filename postfixed with IDs will be used", OUTFILELIST, false);
	par.registerParameter("opattern", "Pattern to generate output filenames (see examples)", BALL::STRING, false);
	par.registerFlag("padding", "Enable zero-padding of file numbering of >= 10 output files", false);

	String man = "LigandFileSplitter splits a single molecule file into a given number of subsets.\n\n"
				 "Examples:\n\n"
				 "$ LigandFileSplitter -i Trypsin_actives.sdf -o batch_1 batch_2\n"
				 "  => {batch_1.sdf, batch_2.sdf}.\n\n"
				 "$ LigandFileSplitter -i Trypsin_actives.sdf -no 3\n"
				 "  => {Trypsin_actives_0.sdf, Trypsin_actives_1.sdf, Trypsin_actives_2.sdf}\n\n"
				 "$ LigandFileSplitter -i ligands.sdf -ligands_per_file 4\n"
				 "  => {ligands_0.sdf, ligands_1.sdf, ..., ligands_N.sdf} where N = ceil(#Input molecules / 4).\n\n"
				 "$ LigandFileSplitter -i ligands.sdf -ligands_per_file 5 -opattern split_ligands-%d.sdf\n"
				 "  => {ligands-0.sdf, ligands-1.sdf, ..., ligands-N.sdf} where N = ceil(#Input molecules / 5).\n\n"
				 "$ LigandFileSplitter -i ligands.sdf -opattern split_ligands_%d.sdf -no 100\n"
				 "  => {split_ligands_0.sdf, split_ligands_1.sdf, ..., split_ligands_99.sdf}\n\n"
				 "$ LigandFileSplitter -i ligands.sdf -opattern split_ligands_%d.sdf -no 100 -padding\n"
				 "  => {split_ligands_00.sdf, split_ligands_01.sdf, ..., split_ligands_99.sdf}\n\n"
				 "NOTES:\n"
				 "- Molecules are not sorted.\n"
				 "- The tool is no converter and the output file format will be the same as the input file format.\n"
				 "- The parameter '-opattern' accepts a printf-like pattern, expecting exactly one decimal integer placeholder, %d.\n"
				 "- The following are valid patterns: output_ligand.sdf_%d, split_%d.mol, %d_lig.drf\n"
				 "- The following are invalid patterns: output_%f.sdf, ligands.drf_%u, %d_lig_%d.mol, molecules.sdf\n\n"
				 "WARNING:\n"
				 "- If the output filenames are specified explicitely by '-o' or defined by '-opattern',"
				 "  the user is responsible for a valid file extension. It has to be of the same file format as the input file.\n\n";

	par.setToolManual(man);

	par.setSupportedFormats("i","mol2,sdf,drf");
	par.setSupportedFormats("o","mol2,sdf,drf");
	par.setOutputFormatSource("o","i");

	par.parse(argc, argv);

	// Check if the parameter combination is valid
	SPLIT_METHODS split_method;
	validateParameterCombination(par, split_method);

	String infile = par.get("i");
	String opattern = "";
	if (par.has("opattern"))
	{
		opattern = par.get("opattern");
	}
	bool padding = par.has("padding");


	// Open input file

	GenericMolFile* input = MolFileFactory::open(infile, File::MODE_IN);
	if (!input)
	{
		Log.error() << "-- Error: The format of the input file is unknown." << endl;
		exit(3);
	}


	// Get number of input molecules, format and compression extensions

	DockResultFile* drf_input = dynamic_cast<DockResultFile*>(input);
	SDFile* sdf_input = dynamic_cast<SDFile*>(input);
	MOL2File* mol2_input = dynamic_cast<MOL2File*>(input);

	String compression;
	String format_extension;
	Size n_molecules = 0;
	if (drf_input)
	{
		drf_input->isCompressedFile(compression);
		format_extension = "drf";
		n_molecules = drf_input->countConformations();

		drf_input->selectAllResultsForInput();
	}
	else if (sdf_input)
	{
		sdf_input->isCompressedFile(compression);
		format_extension = "sdf";
		n_molecules = sdf_input->countMolecules();
	}
	else if (mol2_input)
	{
		mol2_input->isCompressedFile(compression);
		format_extension = "mol2";
		n_molecules = mol2_input->countMolecules();
	}

	// Check if infile is empty
	if (n_molecules == 0)
	{
		Log.error() << "-- Error: Input file is empty." << endl;
		exit(4);
	}
	else
	{
		Log.level(10) << "++ Number of input molecules: " << n_molecules << endl;
	}


	// Calculate necessary split parameters and generate output file names

	Size n_outfiles = 0;
	Size mols_per_file_base = 0;
	Size increment_files = 0;
	vector<String> outfile_names;

	switch (split_method)
	{
		case OUTFILE_LIST:
		{
			list<String> tmp = par.getList("o");
			for (list<String>::iterator it = tmp.begin(); it != tmp.end(); ++it)
			{
				if (!MolFileFactory::isFileFormatSupported(*it, false))
				{
					Log.level(10) << "++ NOTE: The format of the specified output filename " << *it << " is ignored because this tool performs no conversion." << endl;
				}

				outfile_names.push_back(*it);
			}

			n_outfiles = outfile_names.size();
			mols_per_file_base = floor(n_molecules / double(n_outfiles));
			increment_files = n_molecules - (mols_per_file_base * n_outfiles);

			break;
		}
		case NUM_OUTFILES:
		{
			n_outfiles = par.get("no").toInt();

			if (n_outfiles > n_molecules)
			{
				Log.level(10) << "++ NOTE: The number of molecules in the input file is smaller than the specified number of output files." << endl;
				Log.level(10) << "         The number of output files is set to the number of molecules in the input file." << endl;

				n_outfiles = n_molecules;
			}

			mols_per_file_base = floor(n_molecules / double(n_outfiles));
			increment_files = n_molecules - (mols_per_file_base * n_outfiles);

			generateOutfileNames(infile, format_extension, compression, outfile_names, n_outfiles, opattern, padding);

			break;
		}
		case NUM_MOLS_PER_OUTFILE:
		{
			if (par.get("nm").toInt() >= n_molecules)
			{
				Log.level(10) << "++ NOTE: The number of molecules in the input file is smaller than the specified number of molecules per output file." << endl;
				Log.level(10) << "         Exit without producing new output files." << endl;
				exit(0);
			}

			n_outfiles = ceil(n_molecules / par.get("nm").toDouble());
			mols_per_file_base = floor(n_molecules / double(n_outfiles));
			increment_files = n_molecules - (mols_per_file_base * n_outfiles);

			generateOutfileNames(infile, format_extension, compression, outfile_names, n_outfiles, opattern, padding);

			break;
		}
	}


	// Now do the splitting

	Molecule* mol;
	GenericMolFile* output;
	DockResultFile* drf_output;
	HashSet<String> conformation_ids;

	for (unsigned int i=0; i!=outfile_names.size(); ++i)
	{
		output = MolFileFactory::open(outfile_names[i], File::MODE_OUT, format_extension);

		if (!output)
		{
			Log.error() << "-- Error: Output file '" << outfile_names[i] << "' could not be opened." << endl;

			input->close();
			delete input;

			exit(3);
		}

		if (drf_input)
		{
			drf_output = dynamic_cast<DockResultFile*>(output);
			drf_output->disableAutomaticResultCreation();
		}

		conformation_ids.clear();

		Size batch_size = mols_per_file_base;
		if (i < increment_files)
		{
			++batch_size;
		}

		for (unsigned int j=0; j!=batch_size; ++j)
		{
			mol = input->read();
			if (mol == NULL)
			{
				// End of input file
				break;
			}

			if (drf_input && mol->hasProperty("Conformation_input_UID"))
			{
				conformation_ids.insert(mol->getProperty("Conformation_input_UID").toString());
			}

			output->write(*mol);
			delete mol;
		}

		if (drf_input)
		{
			const vector<Result*>* results = drf_input->getResults();
			for (unsigned int j=0; j<results->size(); j++)
			{
				Result* res = new Result(*(*results)[j], conformation_ids);
				drf_output->addResult(res);
			}
		}

		output->close();
		delete output;
	}

	input->close();
	delete input;

	Log.level(10) << "++ Generated " << n_outfiles << " output files." << endl;
	Log.level(10) << "++ DONE." << endl;

	return 0;
}
