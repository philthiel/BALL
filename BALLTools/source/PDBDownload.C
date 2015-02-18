// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//


#include <BALL_core/FORMAT/commandlineParser.h>
#include <BALL_core/FORMAT/lineBasedFile.h>
#include <BALL_core/SYSTEM/directory.h>

#include <BALLTools/version.h>


using namespace BALL;
using namespace std;


int main(int argc, char* argv[])
{
	CommandlineParser par("PDBDownload", "Download an entry from the Protein Data Bank", VERSION, String(__DATE__), "Get Data");
	par.registerParameter("id", "PDB ID of entry to download", STRING, true);
	par.registerParameter("o", "Output file", OUTFILE, true);
	par.registerParameter("format", "Download format. Possible formats are PDB, CIF and XML (default: PDB)", STRING, false, "PDB");
	par.registerParameter("p", "Proxy server name", STRING, false);
	
	String man = "Download an entry from the Protein Data Bank (http://www.pdb.org/) using the specified ID of the desired structure.\n"
				 "Possible download formats are PDB, mmCIF and XML.";

	par.setToolManual(man);
	
	par.setSupportedFormats("o","pdb,cif,xml");
	
	par.parse(argc, argv);

	if (par.has("quiet"))
	{
		Log.disableOutput();
	}

	String format = par.get("format");
	format.toLower();

	if (format != "pdb" && format != "cif" && format != "xml")
	{
		Log.error() << "-- Error: The specified format '" << format << "' is invalid. Valid formats are PDB, CIF or XML." << endl << endl;
		exit(1);
	}

	String url = "http://www.rcsb.org/pdb/files/" + par.get("id") + "." + format;

	String command = "";
	#ifndef BALL_OS_DARWIN
		if (par.has("p"))
		{
			command += String("export http_proxy=") + par.get("p") + String(" > /dev/null 2> /dev/null; ");
			command += String("setenv http_proxy ") + par.get("p") + String(" > /dev/null 2> /dev/null; ");
		}

		command += String("wget ");
		command += url + String(" -O ") + par.get("o") + String(" > /dev/null 2> /dev/null; ");
	#else
		command = String("curl ");
		command += String("-o ") + par.get("o");

		if (par.has("p"))
		{
			command += String(" --proxy1.0 ") + par.get("p");
		}

		command += String(" ") + url + String(" > /dev/null 2> /dev/null; ");
	#endif

	int status = system(command.c_str());

	if (status > 0)
	{
		Log.error() << "-- Error: Could no network connection. Perhaps you need a proxy or the specified proxy is incorrect." << endl << endl;
		exit(2);
	}

	// Check if we really dowloaded a file from the PDB
	LineBasedFile file;
	try
	{
		file.open(par.get("o"));
	}
	catch (BALL::Exception::FileNotFound)
	{
		Log.error() << "-- Error: No output file written. An unkown error occurred. Please check your input options." << endl << endl;
		exit(3);
	}


	// File existing ... check it
	status = 0;
	file.readLine();
	if (file.getLine().hasSubstring("The requested resource is not available"))
	{
		Log.error() << "-- Error: A PDB entry with the ID '" << par.get("id") << "' does not exist." << endl << endl;
		status = 4;
	}
	else if (format == "pdb" && !file.getLine().hasSubstring("HEADER"))
	{
		Log.error() << "-- Error Downloaded file is not a valid PDB file." << endl << endl;
		status = 5;
	}
	else if(format == "cif" && !file.getLine().hasSubstring("data_"))
	{
		Log.error() << "-- Error: Downloaded file is not a valid CIF file." << endl << endl;
		status = 6;
	}
	else if (format == "xml" && !file.getLine().hasSubstring("<?xml version"))
	{
		Log.error() << "-- Error: Downloaded file is not a valid XML file." << endl << endl;
		status = 7;
	}
	else
	{
		Log.level(10) << "++ PDB entry " << par.get("id") << " sucessfully downloaded to " << par.get("o") << "." << endl << endl;
	}

	file.close();
	if (status != 0)
	{
		File::remove(par.get("o"));
		exit(status);
	}

	Log.level(10) << "++ DONE." << endl;

	return 0;
}
