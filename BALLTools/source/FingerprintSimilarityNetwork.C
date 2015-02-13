// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//


#include <BALL/COMMON/limits.h>
#include <BALL/DATATYPE/string.h>
#include <BALL/FORMAT/lineBasedFile.h>
#include <BALL/FORMAT/commandlineParser.h>
#include <BALL/FORMAT/molFileFactory.h>
#include <BALL/FORMAT/SDFile.h>
#include <BALL/KERNEL/molecule.h>
#include <BALL/STRUCTURE/binaryFingerprintMethods.h>
#include <BALL/SYSTEM/sysinfo.h>

#include <BALL/COMMON/version.h>

#include <boost/foreach.hpp>
#include <boost/unordered_map.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/stream.hpp>

#include <locale>
#include <map>
#include <sstream>
#include <vector>


using namespace BALL;
using namespace boost;
using namespace std;


// Format of fingerprint: 1 = Comma separated list of integer features, 2 = Fixed sized binay string
unsigned int fprint_format;

// Format of fingerprint: 1 = Comma separated list of integer features, 2 = Fixed sized binay string
unsigned int fixed_size_len;

// Limit of molecules to be read
unsigned int limit;

// Column number which contains the fingerprint
int fp_col;

// Column number which contains a identifier of the compounds
int id_col;

// True if input library file is in SD format
bool is_lib_sdf;

// SDF tag which contains the fingerprint
String fp_tag;

// SDF tag which contains a identifier of the compounds
String id_tag;


void readFingerprintsCSV(LineBasedFile& fprints_in, vector<vector<unsigned short> >& mol_features, vector<String>& mol_identifiers)
{
	String fprint;
	String identifier;
	vector<unsigned short> features;
	unsigned int mol_count = 0;
	
	mol_features.clear();
	mol_identifiers.clear();
	
	fprints_in.readLine();
	while (fprints_in.startsWith("#"))
	{
		fprints_in.readLine();
	}
	
	fprint = fprints_in.getField(fp_col).trim();
	while (!fprint.isEmpty())
	{
		if (id_col!=-1)
		{
			identifier = fprints_in.getField(id_col).trim();
		}
		else
		{
			identifier = String(mol_count);
		}
		
		if (mol_count == 0 && fprint_format == 2)
		{
			fixed_size_len = fprint.size();
		}
		
		if (BinaryFingerprintMethods::parseBinaryFingerprint(fprint, features, fprint_format))
		{
			mol_features.push_back(features);
			mol_identifiers.push_back(identifier);
		}
		else
		{
			Log.error() << "-- WARNING: Fingerprint could not be read" << endl;
		}
		
		++mol_count;
		
		if (mol_count == limit)
		{
			break;
		}
		
		fprints_in.readLine();
		fprint = fprints_in.getField(fp_col).trim();
	}
	
	Log.level(10) << "++ Molecules read:     " << mol_count << endl;
}


void readFingerprintsSDF(SDFile* fprints_in, vector<vector<unsigned short> >& mol_features, vector<String>& mol_identifiers)
{
	String fprint;
	String identifier;
	vector<unsigned short> features;
	unsigned int mol_count = 0;
	
	mol_features.clear();
	mol_identifiers.clear();
	
	Molecule* mol = fprints_in->read();
	while (mol)
	{
		if (mol->hasProperty(id_tag))
		{
			if (mol->hasProperty(fp_tag))
			{
				identifier = mol->getProperty(id_tag).getString();
				fprint = mol->getProperty(fp_tag).getString().trim();
				
				if (mol_count == 0 && fprint_format == 2)
				{
					fixed_size_len = fprint.size();
				}
				
				if (BinaryFingerprintMethods::parseBinaryFingerprint(fprint, features, fprint_format))
				{
					mol_features.push_back(features);
					mol_identifiers.push_back(identifier);
					
					++mol_count;
					
					if (mol_count==limit)
					{
						break;
					}
				}
			}
		}
		
		delete mol;
		mol = fprints_in->read();
	}
	delete mol;
	
	Log.level(10) << "++ Molecules read:     " << mol_count << endl;
}


void uniqueFingerprintsFilter(vector<vector<unsigned short> >& mol_features, const vector<String>& mol_identifiers)
{
	locale loc;
	const collate<char>& coll = use_facet<collate<char> >(loc);
	
	String fp;
	long fp_hash;
	
	map<long, unsigned int> fp_hash_map;
	vector<vector<unsigned int> > duplicates;
	for (unsigned int i=0; i!=mol_features.size(); ++i)
	{
		fp = "";
		for (unsigned int j=0; j!=mol_features[i].size(); ++j)
		{
			fp += String(mol_features[i][j]);
		}
		
		fp_hash = coll.hash(fp.data(), fp.data() + fp.length());
		
		if (fp_hash_map.find(fp_hash)==fp_hash_map.end())
		{
			fp_hash_map.insert(make_pair(fp_hash, duplicates.size()));
			duplicates.push_back(vector<unsigned int>(1, i));
		}
		else
		{
			duplicates[fp_hash_map[fp_hash]].push_back(i);
		}
	}
	
	
	File out("FFC_1_fingerprint_duplicates.txt", File::MODE_OUT);
	
	out << "# FFC FINGERPRINT DUPLICATES MAPPING" << endl;
	out << "# Eeach line is a blank separated list of identical fingerprints and has at least two columns." << endl;
	out << "# The first column is a global internal ID [0, n-1] where n is the number of unique fingerprints." << endl;
	out << "# The second and possibly following columns list the external molecule identifiers of the fingerprint duplicates. " << endl;
	
	vector<vector<unsigned short> > tmp_features;
	for (unsigned int i=0; i!=duplicates.size(); ++i)
	{
		// Keep first occurrence of new feature list
		tmp_features.push_back(mol_features[duplicates[i][0]]);
		
		out << tmp_features.size() - 1;
		
		for (unsigned int j=0; j!=duplicates[i].size(); ++j)
		{
			out << " " << mol_identifiers[duplicates[i][j]];
		}
		
		out << endl;
	}
	
	out.close();
	mol_features = tmp_features;
	
	return;
}


void readMoleculeIdentifiers(unordered_map<unsigned int, set<String> >& mol_identifiers)
{
	File in("FFC_1_fingerprint_duplicates.txt", File::MODE_IN);
	
	String line;
	unsigned int parent;
	vector<String> line_split;
	
	while(getline(in, line))
	{
		if (!line.hasPrefix("#"))
		{
			line.split(line_split);
			
			parent = line_split[0].toInt();
			mol_identifiers.insert(make_pair(parent, set<String>()));
			mol_identifiers[parent].insert((++line_split.begin()), line_split.end());
		}
	}
	
	in.close();
}


bool readFingerprints(const String& input_file, vector<vector<unsigned short> >& mol_features, vector<String>& mol_identifiers)
{
	if (!MolFileFactory::isFileFormatSupported(input_file, true))
	{
		// Assuming space separated CSV file which contains fingerprints
		
		if (fp_col == -1)
		{
			Log.error() << "-- FAILED: For comma separated smiles input files please specify the column number (fp_col > 0) which contains the fingerprints." << endl;
			Log.error() << endl;
			
			return false;
		}
		
		if (input_file.hasSuffix(".gz"))
		{
			String tmp_unzipped;
			File::createTemporaryFilename(tmp_unzipped);
			LineBasedFile unzipped(tmp_unzipped, File::MODE_OUT);
			File zipped(input_file, File::MODE_IN | File::MODE_BINARY);
			
			iostreams::filtering_streambuf<iostreams::input> gzip_in;
			gzip_in.push(iostreams::gzip_decompressor());
			gzip_in.push(zipped);
			iostreams::copy(gzip_in, unzipped);
			
			zipped.close();
			
			unzipped.reopen(File::MODE_IN);
			readFingerprintsCSV(unzipped, mol_features, mol_identifiers);
			unzipped.close();
			
			File::remove(tmp_unzipped);
		}
		else
		{
			LineBasedFile lbf(input_file, File::MODE_IN);
			
			readFingerprintsCSV(lbf, mol_features, mol_identifiers);
			
			lbf.close();
		}
	}
	else
	{
		if (fp_tag == " ")
		{
			Log.error() << "-- FAILED: For SDF input files please specify the tag which contains the fingerprints." << endl;
			Log.error() << endl;
			
			return false;
		}
		if (id_tag == " ")
		{
			Log.error() << "-- FAILED: For SDF input files please specify the tag which contains the molecule identifier." << endl;
			Log.error() << endl;
			
			return false;
		}
		
		GenericMolFile* lib = MolFileFactory::open(input_file, File::MODE_IN);
		if (lib == NULL)
		{
			Log.error() << "-- FAILED: Specified library input could not be opened." << endl;
			Log.error() << "--" << endl;
			
			return false;
		}
		
		SDFile* lib_sdf = dynamic_cast<SDFile*>(lib);
		if (lib_sdf)
		{
			is_lib_sdf = true;
			lib_sdf->disableAtoms();
			
			readFingerprintsSDF(lib_sdf, mol_features, mol_identifiers);
			
			lib_sdf->close();
			delete lib_sdf;
		}
		else
		{
			Log.error() << "-- FAILED: Input file has an unsupported format." << endl;
			Log.error() << endl;
			
			lib->close();
			delete lib;
			
			return false;
		}
	}
	
	if (mol_features.empty())
	{
		Log.error() << "-- FAILED: Input file empty or wrong fingerprint tags or columns specified." << endl;
		Log.error() << endl;
		
		return false;
	}
	
	return true;
}


int main(int argc, char* argv[])
{
    CommandlineParser parpars("FingerprintSimilarityNetwork", "Calculate similarity network of input library", VersionInfo::getVersion(), String(__DATE__), "Chemoinformatics");
	
	parpars.registerParameter("t", "Target library input file", INFILE, true);
	parpars.registerParameter("o", "Output file to write similarity network", OUTFILE, true);
	parpars.registerParameter("f", "Fingerprint format [1 = binary bitstring, 2 = comma separated feature list]", INT, true, "1");
	parpars.registerParameter("fp_col", "Column number for comma separated smiles input which contains the fingerprint", INT, false, -1);
	parpars.registerParameter("id_col", "Column number for comma separated smiles input which contains the molecule identifier", INT, false, -1);
	parpars.registerParameter("fp_tag", "Tag name for SDF input which contains the fingerprint", STRING, false, " ");
	parpars.registerParameter("id_tag", "Tag name for SDF input which contains the molecule identifier", STRING, false, " ");
	parpars.registerParameter("tc", "Tanimoto cutoff [default: 0.7]", DOUBLE, false, 0.7);
	parpars.registerParameter("l", "Number of fingerprints to read", INT, false, "0");
	parpars.registerParameter("nt", "Number of parallel threads to use. To use all possible threads enter <max> [default: 1]", STRING, false, "1");
	parpars.registerFlag("keep_dup", "Keep the file storing the fingerprint duplicates information when finished.");
	
	parpars.setSupportedFormats("t","csv, csv.gz, txt, txt.gz, sdf, sdf.gz");
	parpars.setSupportedFormats("o","csv, csv.gz, txt, txt.gz");
	parpars.setParameterRestrictions("f", 1, 2);

    String man = "This tool takes a compound library encoded as 2D binary fingerprints and calculates all pairwise similarities.";
	parpars.setToolManual(man);
	parpars.parse(argc, argv);
	
	// Set read and parameters
	fprint_format = parpars.get("f").toInt();
	float sim_cutoff = parpars.get("tc").toFloat();
	
	limit = parpars.get("l").toInt();
	if (limit == 0)
	{
		limit = Limits<unsigned int>::max();
	}
	
	unsigned int n_threads = 1;
	if (parpars.get("nt") != "1")
	{
		if (parpars.get("nt") == "max")
		{
			n_threads = SysInfo::getNumberOfProcessors();
		}
		else
		{
			if (parpars.get("nt").toInt() > SysInfo::getNumberOfProcessors())
			{
				n_threads = SysInfo::getNumberOfProcessors();
				Log.info() << "++ INFO: Specified number of threads exceeds available threads. Setting number to available threads." << endl;
			}
			else
			{
				n_threads = parpars.get("nt").toInt();
			}
		}
	}
	
	if (parpars.get("fp_col") != "-1")
	{
		fp_col = parpars.get("fp_col").toInt() - 1;
	}
	else
	{
		fp_col = -1;
	}
	if (parpars.get("id_col") != "-1")
	{
		id_col = parpars.get("id_col").toInt() - 1;
	}
	else
	{
		id_col = -1;
	}
	
	if (parpars.get("fp_tag") != " ")
	{
		fp_tag = parpars.get("fp_tag");
	}
	if (parpars.get("id_tag") != " ")
	{
		id_tag = parpars.get("id_tag");
	}
	
	
	// Read library fingerprints
	Log.level(10) << "++ --------------------------------------------------------" << endl;
	Log.level(10) << "++ Read target library ... " << endl;
	
	is_lib_sdf = false;
	vector<String> mol_identifiers;
	vector<vector<unsigned short> > mol_features;
	
	bool read_success = readFingerprints(parpars.get("t"), mol_features, mol_identifiers);
	
	if (!read_success)
	{
		return 1;
	}
	
	Log.level(10) << "++" << endl;
	
	Options options;
	options.setDefaultInteger(BinaryFingerprintMethods::Option::BLOCKSIZE, 820);
	options.setDefaultReal(BinaryFingerprintMethods::Option::SIM_CUTOFF, sim_cutoff);
	options.setDefaultInteger(BinaryFingerprintMethods::Option::N_THREADS, n_threads);
	options.setDefaultInteger(BinaryFingerprintMethods::Option::MAX_CLUSTERS, 1000);
	options.setDefaultInteger(BinaryFingerprintMethods::Option::VERBOSITY, 15);
	
	
	// ------------------------------------------------------------------------------------------
	// Create unique fingerprint set
	
	Log.level(10) << "++ --------------------------------------------------------" << endl;
	Log.level(10) << "++ STEP 1: Unique Fingerprints Filter" << endl;
	Log.level(10) << "++ Fingerprints total : " << mol_features.size() << endl;
	
	uniqueFingerprintsFilter(mol_features, mol_identifiers);
	mol_identifiers.clear();
	
	Log.level(10) << "++ Fingerprints unique: " <<  mol_features.size() << endl;
	Log.level(10) << "++" << endl;
	
	
	// ------------------------------------------------------------------------------------------
	// Calculate similarity network
	
	Log.level(10) << "++ --------------------------------------------------------" << endl;
	Log.level(10) << "++ Similarity Network Calculation" << endl;
	
	vector<unsigned int> m_indices;
	
	// Add all input molecules for connected component calculation
	for (unsigned int i=0; i!=mol_features.size(); ++i)
	{
		m_indices.push_back(i);
	}
	
	String temp_file_name = "ballSimNetworkTemp.txt";
	
	BinaryFingerprintMethods bfm(options, mol_features);
	bfm.calculateSimilarityNetwork(m_indices, sim_cutoff, temp_file_name);
	
	
	// ------------------------------------------------------------------------------------------
	// Remap fingerprint duplicates and compound IDs
	
	String line;
	String source_id, dest_id;
	unsigned int source, dest;
	vector<String> parsed;
	stringstream buffer;
	
	unordered_map<unsigned int, set<String> > id_mapping;
	
	// Read molecule identifiers
	readMoleculeIdentifiers(id_mapping);
	
	// Open input file
	fstream in(temp_file_name, fstream::in);
	
	// Open output file
	File outfile(parpars.get("o"), File::MODE_OUT);
	iostreams::filtering_ostream out;
	
	if (parpars.get("o").hasSuffix(".gz"))
	{
		out.push(iostreams::gzip_compressor());
	}
	
	out.push(outfile);
	
	out << "CompoundID_1\tCompoundID_2\tTanimoto\n";
	
	float ident = 1.0;
	unsigned int count = 0;
	String external_id_1, external_id_2;
	unordered_map<unsigned int, set<String> >::iterator mapping = id_mapping.begin();

	for (; mapping!= id_mapping.end(); ++mapping)
	{
		if (mapping->second.size() > 1)
		{		
			BOOST_FOREACH(external_id_1, mapping->second)
			{
				BOOST_FOREACH(external_id_2, mapping->second)
				{
					if (external_id_1 != external_id_2)
					{
						buffer << external_id_1 << "\t" << external_id_2 << "\t" << ident << "\n";
						
						++count;
		
						if (count == 1000000)
						{
							out << buffer.str();
							buffer.str("");
							count = 0;
						}
					}
				}
			}
		}
	}
	
	out << buffer.str();
	buffer.str("");	
	count = 0;
	
	while (getline(in, line))
	{
		line.split(parsed);
		
		source = atoi(parsed[0].c_str());
		
		BOOST_FOREACH(source_id, id_mapping[source])
		{
			dest = atoi(parsed[1].c_str());
			
			BOOST_FOREACH(dest_id, id_mapping[dest])
			{
				buffer << source_id << "\t" << dest_id << "\t" << parsed[2] << "\n";
				buffer << dest_id << "\t" << source_id << "\t" << parsed[2] << "\n";
			}
		}
		
		++count;
		
		if (count == 1000000)
		{
			out << buffer.str();
			
			buffer.str("");
			count = 0;
		}
	}
	
	out << buffer.str();
	
	out.flush();
	out.pop();
	out.reset();
	
	outfile.close();
	in.close();
	
	File::remove(temp_file_name);
	
	if (!parpars.has("keep_dup"))
	{
		File::remove("FFC_1_fingerprint_duplicates.txt");
	}
	
	Log << "++" << endl;
	Log << "++ DONE" << endl;
	Log << "++" << endl;
	
	return 0;
}





