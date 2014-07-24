// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#include <BALL/FORMAT/molFileFactory.h>

#include <BALL/DATATYPE/string.h>
#include <BALL/FORMAT/antechamberFile.h>
#include <BALL/FORMAT/dockResultFile.h>
#include <BALL/FORMAT/genericMolFile.h>
#include <BALL/FORMAT/HINFile.h>
#include <BALL/FORMAT/MOLFile.h>
#include <BALL/FORMAT/MOL2File.h>
#include <BALL/FORMAT/PDBFile.h>
#include <BALL/FORMAT/SDFile.h>
#include <BALL/FORMAT/XYZFile.h>

#include <set>
#include <vector>

#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filtering_stream.hpp>


using namespace std;
using namespace boost;


namespace BALL
{
	String MolFileFactory::getSupportedCompressionFormats()
	{
		String supported_compression_formats = "gz,bz2";

		return supported_compression_formats;
	}


	void MolFileFactory::getSupportedCompressionFormats(set<String>& compression_formats)
	{
		vector<String> tmp;
		String supported_compression_formats = getSupportedCompressionFormats();
		supported_compression_formats.split(tmp, ",");

		compression_formats.clear();
		compression_formats.insert(tmp.begin(), tmp.end());

		return;
	}


	bool MolFileFactory::isFileCompressed(const String& file_name, String& compression_format, String& decompressed_name)
	{
		compression_format = "";
		decompressed_name = "";

		// Get supported file formats
		set<String> supported_compression_formats;
		getSupportedCompressionFormats(supported_compression_formats);

		for (set<String>::iterator it=supported_compression_formats.begin(); it!=supported_compression_formats.end(); ++it)
		{
			if (file_name.hasSuffix(*it))
			{
				compression_format = *it;
				decompressed_name = file_name.before("." + *it).toLower();

				return true;
			}
		}

		return false;
	}


	void MolFileFactory::decompressFile(const String& file_name, const String& decompressed_name, const String& compression_format)
	{
		// Open input file stream
		ifstream zfile(file_name.c_str(), File::MODE_IN | File::MODE_BINARY);

		iostreams::filtering_istream in;

		if (compression_format == "gz")
		{
			// Apply BOOST gzip decompressor
			in.push(iostreams::gzip_decompressor());
		}
		else
		{
			if (compression_format == "bz2")
			{
				// Apply BOOST bzip2 decompressor
				in.push(iostreams::bzip2_decompressor());
			}
		}

		in.push(zfile);

		ofstream out(decompressed_name.c_str());
		iostreams::copy(in, out);

		zfile.close();

		return;
	}


	String MolFileFactory::getSupportedFormats()
	{
		String supported_formats = "ac,brk,drf,ent,hin,mol,mol2,pdb,sdf,xyz";

		return supported_formats;
	}


	void MolFileFactory::getSupportedFormats(set<String>& formats)
	{
		vector<String> tmp;
		String supported_formats = getSupportedFormats();
		supported_formats.split(tmp, ",");

		formats.clear();
		formats.insert(tmp.begin(), tmp.end());

		return;
	}


	bool MolFileFactory::isFileExtensionSupported(const String& extension)
	{
		set<String> formats;
		getSupportedFormats(formats);

		if (formats.count(extension) != 1)
		{
			return false;
		}

		return true;
	}


	bool MolFileFactory::isFileFormatSupported(const String& file_name, bool input_mode)
	{
		String format = getFileFormat(file_name, input_mode);

		if (format.isEmpty())
		{
			return false;
		}

		return true;
	}


	String MolFileFactory::getFileFormat(const String& file_name, bool input_mode)
	{
		String format = "";

		// Strip path from file name
		String base_name = FileSystem::baseName(file_name);
		base_name.toLower();

		// Get supported file formats
		set<String> supported_formats;
		getSupportedFormats(supported_formats);

		for (set<String>::iterator it=supported_formats.begin(); it!=supported_formats.end(); ++it)
		{
			if (base_name.hasSuffix(*it))
			{
				format = *it;
				break;
			}
		}

		if (format.isEmpty() && input_mode)
		{
			// Try to identify by file content
			format = detectFileFormat(file_name);

			if (!format.isEmpty())
			{
				Log.warn() << "Input file '" << file_name << "' has no valid extension. Automatically detected format '" << format << "' could be wrong!" << endl;
			}
		}

		return format;
	}


	GenericMolFile* MolFileFactory::openBase(const String& file_name, const String& format, File::OpenMode open_mode)
	{
		GenericMolFile* gmf = NULL;

		if (format == "ac")
		{
			gmf = new AntechamberFile(file_name, open_mode);
		}
		else if (format == "pdb" || format == "brk" || format == "ent")
		{
			gmf = new PDBFile(file_name, open_mode);
		}
		else if (format == "hin")
		{
			gmf = new HINFile(file_name, open_mode);
		}
		else if (format == "mol")
		{
			gmf = new MOLFile(file_name, open_mode);
		}
		else if (format == "sdf")
		{
			gmf = new SDFile(file_name, open_mode);
		}
		else if (format == "mol2")
		{
			gmf = new MOL2File(file_name, open_mode);
		}
		else if (format == "xyz")
		{
			gmf = new XYZFile(file_name, open_mode);
		}
		else if (format == "drf")
		{
			gmf = new DockResultFile(file_name, open_mode);
		}

		return gmf;
	}


	GenericMolFile* MolFileFactory::open(const String& file_name, File::OpenMode open_mode)
	{
		GenericMolFile* gmf = NULL;

		String compression_format;
		String decompressed_name;

		if (isFileCompressed(file_name, compression_format, decompressed_name))
		{
			// Compressed file

			if (open_mode == File::MODE_IN)
			{
				// File read mode

				// Create decompressed file
				decompressFile(file_name, decompressed_name, compression_format);

				// Get molecular file format
				String format = getFileFormat(decompressed_name, true);

				// Check if format is not empty (supported)
				if (!format.isEmpty())
				{
					// Use appropriate molecular file class to open file
					gmf = openBase(decompressed_name, format, open_mode);

					// Make sure that temporary input file is deleted when GenericMolFile is closed.
					gmf->defineInputAsTemporary();
				}
				else
				{
					// Molecular file format unsupported - so cleanup
					File::remove(decompressed_name);
				}
			}
			else
			{
				// File write mode

				// Get molecular file format
				String format = getFileFormat(decompressed_name, true);

				// Check if format is not empty (supported)
				if (!format.isEmpty())
				{
					// Use appropriate molecular file class to open file
					gmf = openBase(decompressed_name, format, open_mode);

					// Make sure that temporary output file is compressed and then deleted when GenericMolFile is closed.
					gmf->enableOutputCompression(file_name, compression_format);
				}
			}
		}
		else
		{
			// Uncompressed molecular file

			// Get molecular file format
			String format = getFileFormat(file_name, true);

			// Check if format is not empty (supported)
			if (!format.isEmpty())
			{
				// Use appropriate molecular file class to open file
				gmf = openBase(file_name, format, open_mode);
			}
		}

		return gmf;
	}


	GenericMolFile* MolFileFactory::open(const String& file_name, File::OpenMode open_mode, String default_format)
	{
		GenericMolFile* gmf = NULL;

		if (open_mode == File::MODE_IN)
		{
			gmf = open(file_name, open_mode);
			if (gmf)
			{
				return gmf;
			}
		}
		else if (open_mode == File::MODE_OUT)
		{
			String compression_format;
			String file_format;

			// Open temporary decompressed molecular file
			gmf = openBase(file_name, default_format, open_mode);

			if (isFileCompressed(file_name, compression_format, file_format))
			{
				// Make sure that temporary output file is compressed and then deleted when GenericMolFile is closed.
				gmf->enableOutputCompression(file_name, compression_format);
			}
		}

		return gmf;
	}


	GenericMolFile* MolFileFactory::open(const String& file_name, File::OpenMode open_mode, GenericMolFile* default_format_file)
	{
		GenericMolFile* gmf = NULL;
		gmf = open(file_name, open_mode);
		if (gmf)
		{
			return gmf;
		}

		if (open_mode == File::MODE_OUT)
		{
			String tmp_file_name;
			String compression_format = "";

			if (default_format_file->isCompressedFile(compression_format))
			{
				// Create temporary decompressed file name
				File::createTemporaryFilename(tmp_file_name);
			}
			else
			{
				tmp_file_name = file_name;
			}

			if (dynamic_cast<AntechamberFile*>(default_format_file))
			{
				gmf = new AntechamberFile(tmp_file_name, open_mode);
			}
			else if(dynamic_cast<PDBFile*>(default_format_file))
			{
				gmf = new PDBFile(tmp_file_name, open_mode);
			}
			else if(dynamic_cast<HINFile*>(default_format_file))
			{
				gmf = new HINFile(tmp_file_name, open_mode);
			}
			else if(dynamic_cast<SDFile*>(default_format_file))
			{
				gmf = new SDFile(tmp_file_name, open_mode);
			}
			else if(dynamic_cast<MOL2File*>(default_format_file))
			{
				gmf = new MOL2File(tmp_file_name, open_mode);
			}
			else if(dynamic_cast<MOLFile*>(default_format_file))
			{
				gmf = new MOLFile(tmp_file_name, open_mode);
			}
			else if(dynamic_cast<XYZFile*>(default_format_file))
			{
				gmf = new XYZFile(tmp_file_name, open_mode);
			}
			else if(dynamic_cast<DockResultFile*>(default_format_file))
			{
				gmf = new DockResultFile(tmp_file_name, open_mode);
			}

			// Make sure that temporary output-file is compressed and then deleted when GenericMolFile is closed.
			if (!compression_format.isEmpty())
			{
				gmf->enableOutputCompression(file_name, compression_format);
			}
		}

		return gmf;
	}


	String MolFileFactory::detectFileFormat(const String& file_name)
	{
		String format = "";
		String line;
		vector<String> tmp;

		LineBasedFile input(file_name, File::MODE_IN);

		unsigned int count = 0;
		unsigned int xyz_count = 0;
		while (getline(input, line))
		{
			// PDB check
			if (line.hasPrefix("HEADER") || line.hasPrefix("ATOM"))
			{
				format = "pdb";
				break;
			}

			// SDF/Mol check
			if (line.hasPrefix("$$$$") || line.hasPrefix("M  END"))
			{
				format = "sdf";
				break;
			}

			// Mol2 check
			if (line.hasPrefix("@<TRIPOS>MOLECULE"))
			{
				format = "mol2";
				break;
			}

			// DRF check
			if (line.hasPrefix("<dockingfile>"))
			{
				format = "drf";
				break;
			}

			// HIN check
			if (line.hasPrefix("forcefield"))
			{
				format = "hin";
				break;
			}

			// AC check
			if (line.hasPrefix("CHARGE") || line.hasPrefix("Formula:"))
			{
				format = "ac";
				break;
			}

			// XYZ coordinate line count
			line.split(tmp);
			if (tmp.size() == 4)
			{
				float num;

				// Check if columnds 2, 3 and 4 are numbers (coordinates should be numbers ...)
				if ((istringstream(tmp[1]) >> num) && (istringstream(tmp[2]) >> num) && (istringstream(tmp[3]) >> num))
				{
					++xyz_count;
				}
			}

			++count;
			if (count > 400)
			{
				break;
			}
		}

		// XYZ check
		if (count - xyz_count == 2)
		{
			format = "xyz";
		}

		input.close();

		return format;
	}
}

