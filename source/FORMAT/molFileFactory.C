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
		String supported_compression_formats = ".gz,.bz2";

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


	bool MolFileFactory::isFileCompressed(const String& name, String& compression_format, String& decompressed_name)
	{
		compression_format = "";
		decompressed_name = "";

		// Get supported file formats
		set<String> supported_compression_formats;
		getSupportedCompressionFormats(supported_compression_formats);

		for (set<String>::iterator it=supported_compression_formats.begin(); it!=supported_compression_formats.end(); ++it)
		{
			if (name.hasSuffix(*it))
			{
				compression_format = *it;
				decompressed_name = (name.left(name.size() - it->size())).toString();

				return true;
			}
		}

		return false;
	}


	void MolFileFactory::decompressFile(const String& name, const String& decompressed_name, const String& compression_format)
	{
		// Open input file stream
		ifstream zfile(name.c_str(), File::MODE_IN | File::MODE_BINARY);

		if (compression_format == ".gz")
		{
			// Apply BOOST gzip decompressor
			iostreams::filtering_istream in;
			in.push(iostreams::gzip_decompressor());
			in.push(zfile);

			ofstream out(decompressed_name.c_str());
			iostreams::copy(in, out);

			// Remove filters
			in.pop();
			in.pop();
		}
		else if (compression_format == ".bz2")
		{
			// Apply BOOST bzip2 decompressor
			iostreams::filtering_istream in;
			in.push(iostreams::bzip2_decompressor());
			in.push(zfile);

			ofstream out(decompressed_name.c_str());
			iostreams::copy(in, out);

			// Remove filters
			in.pop();
			in.pop();
		}

		zfile.close();

		return;
	}


	String MolFileFactory::getSupportedFormats()
	{
		String supported_formats = ".ac,.brk,.drf,.ent,.hin,.mol,.mol2,.pdb,.sdf,.xyz";

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


	bool MolFileFactory::isFileFormatSupported(const String& name, bool input_mode)
	{
		String format = getFileFormat(name, input_mode);

		if (format.isEmpty())
		{
			return false;
		}

		return true;
	}


	String MolFileFactory::getFileFormat(const String& name, bool input_mode)
	{
		String format = "";

		// Strip path from file name
		String base_name = FileSystem::baseName(name);
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
			format = detectFileFormat(name);
		}

		return format;
	}


	GenericMolFile* MolFileFactory::openBase(const String& name, const String& format, File::OpenMode open_mode)
	{
		GenericMolFile* gmf = NULL;

		if (format == ".ac")
		{
			gmf = new AntechamberFile(name, open_mode);
		}
		else if (format == ".pdb" || format == ".brk" || format == ".ent")
		{
			gmf = new PDBFile(name, open_mode);
		}
		else if (format == ".hin")
		{
			gmf = new HINFile(name, open_mode);
		}
		else if (format == ".mol")
		{
			gmf = new MOLFile(name, open_mode);
		}
		else if (format == ".sdf")
		{
			gmf = new SDFile(name, open_mode);
		}
		else if (format == ".mol2")
		{
			gmf = new MOL2File(name, open_mode);
		}
		else if (format == ".xyz")
		{
			gmf = new XYZFile(name, open_mode);
		}
		else if (format == ".drf")
		{
			gmf = new DockResultFile(name, open_mode);
		}

		return gmf;
	}


	GenericMolFile* MolFileFactory::open(const String& name, File::OpenMode open_mode)
	{
		GenericMolFile* gmf = NULL;

		String compression_format;
		String decompressed_name;

		if (isFileCompressed(name, compression_format, decompressed_name))
		{
			// Compressed file

			if (open_mode == File::MODE_IN)
			{
				// File read mode

				// Create decompressed file
				decompressFile(name, decompressed_name, compression_format);

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
					gmf->enableOutputCompression(name);
				}
			}
		}
		else
		{
			// Uncompressed molecular file

			// Get molecular file format
			String format = getFileFormat(name, true);

			// Check if format is not empty (supported)
			if (!format.isEmpty())
			{
				// Use appropriate molecular file class to open file
				gmf = openBase(name, format, open_mode);
			}
		}

		return gmf;

		/*
		bool compression = false;
		String filename = name;

		if (name.hasSuffix(".gz"))
		{
			compression = true;
		}
		else if (open_mode == std::ios::in && !isFileFormatSupported(filename)) // check whether file is zipped
		{
			std::ifstream zipped_file(filename.c_str(), std::ios_base::in | std::ios_base::binary);
			boost::iostreams::filtering_istream in;
			in.push(boost::iostreams::gzip_decompressor());
			in.push(zipped_file);
			bool ok = false;
			try
			{
				string s;
				ok = std::getline(in,s);
			}
			catch (const boost::iostreams::gzip_error& e)
			{
				compression = false;
			}
			if (ok) compression = true;
		}

		if (compression)
		{
			compression = true;
			String unzipped_filename;
			if (name.hasSuffix(".gz"))
			{
				String tmp = name.before(".gz");
				String ext = tmp.substr(tmp.find_last_of("."));
				File::createTemporaryFilename(unzipped_filename, ext);
			}
			else // unknown extension
			{
				File::createTemporaryFilename(unzipped_filename);
			}

			if (open_mode == std::ios::in)
			{
				std::ifstream zipped_file(name.c_str(), std::ios_base::in | std::ios_base::binary);
				boost::iostreams::filtering_istream in;
				in.push(boost::iostreams::gzip_decompressor());
				in.push(zipped_file);
				std::ofstream unzipped_file(unzipped_filename.c_str());
				boost::iostreams::copy(in, unzipped_file);
			}

			filename = unzipped_filename;
		}

		GenericMolFile* gmf = 0;
		if (filename.hasSuffix(".ac") || filename.hasSuffix(".AC"))
		{
			gmf = new AntechamberFile(filename, open_mode);
		}
		else if(filename.hasSuffix(".pdb") || filename.hasSuffix(".ent") || filename.hasSuffix(".brk") ||
				filename.hasSuffix(".PDB") || filename.hasSuffix(".ENT") || filename.hasSuffix(".BRK"))
		{
			gmf = new PDBFile(filename, open_mode);
		}
		else if(filename.hasSuffix(".hin") || filename.hasSuffix(".HIN"))
		{
			gmf = new HINFile(filename, open_mode);
		}
		else if(filename.hasSuffix(".mol") || filename.hasSuffix(".MOL"))
		{
			gmf = new MOLFile(filename, open_mode);
		}
		else if(filename.hasSuffix(".sdf") || filename.hasSuffix(".SDF"))
		{
			gmf = new SDFile(filename, open_mode);
		}
		else if(filename.hasSuffix(".mol2") || filename.hasSuffix(".MOL2"))
		{
			gmf = new MOL2File(filename, open_mode);
		}
		else if(filename.hasSuffix(".xyz") || filename.hasSuffix(".XYZ"))
		{
			gmf = new XYZFile(filename, open_mode);
		}
		else if(filename.hasSuffix(".drf") || filename.hasSuffix(".DRF"))
		{
			gmf = new DockResultFile(filename, open_mode);
		}
		else
		{
			if (open_mode == std::ios::in)
			{
				gmf = detectFileFormat(filename);
				// Make sure that temporary input-file is deleted when GenericMolFile is closed.
				if (gmf && compression)
				{
					gmf->defineInputAsTemporary();
				}
				return gmf;
			}

			return NULL;
		}

		if (compression)
		{
			if (open_mode == File::MODE_IN)
			{
				// Make sure that temporary input-file is deleted when GenericMolFile is closed.
				gmf->defineInputAsTemporary();
			}
			else
			{
				// Make sure that temporary output-file is compressed and then deleted when GenericMolFile is closed.
				gmf->enableOutputCompression(name);
			}
		}

		return gmf;
		*/
	}


	GenericMolFile* MolFileFactory::open(const String& name, File::OpenMode open_mode, String default_format, bool forced)
	{
		// If we do not force the default format, we start as in others
		// else skip to avoid unnecessary computation
		if(!forced)
		{
			// Try to read/write using filename with suffix (try recognise if necessary)
			GenericMolFile* file = open(name, open_mode);
			if (file)
			{
				return file;
			}
		}

		// if forced or if filetype could not be recognised by ending use default format
		GenericMolFile* file = 0;

		bool compression = false;
		String filename = name;
		String zipped_filename = "";

		if (default_format.hasSuffix(".gz"))
		{
			compression = true;
			zipped_filename = filename;
			default_format = default_format.before(".gz");
			String unzipped_filename;
			File::createTemporaryFilename(unzipped_filename, default_format);
			if (open_mode == std::ios::in)
			{
				std::ifstream zipped_file(zipped_filename.c_str(), std::ios_base::in | std::ios_base::binary);
				boost::iostreams::filtering_istream in;
				in.push(boost::iostreams::gzip_decompressor());
				in.push(zipped_file);
				std::ofstream unzipped_file(unzipped_filename.c_str());
				boost::iostreams::copy(in, unzipped_file);
			}

			filename = unzipped_filename;
		}

		if (default_format == "ac")
		{
			file = new AntechamberFile(filename, open_mode);
		}
		else if(default_format == "pdb" || default_format == "ent" || default_format == "brk")
		{
			file = new PDBFile(filename, open_mode);
		}
		else if(default_format == "hin")
		{
			file = new HINFile(filename, open_mode);
		}
		else if(default_format == "mol")
		{
			file = new MOLFile(filename, open_mode);
		}
		else if(default_format == "sdf")
		{
			file = new SDFile(filename, open_mode);
		}
		else if(default_format == "mol2")
		{
			file = new MOL2File(filename, open_mode);
		}
		else if(default_format == "xyz")
		{
			file = new XYZFile(filename, open_mode);
		}
		else if(default_format == "drf")
		{
			file = new DockResultFile(filename, open_mode);
		}


		if (compression)
		{
			if (open_mode == std::ios::in)
			{
				// Make sure that temporary input-file is deleted when GenericMolFile is closed.
				file->defineInputAsTemporary();
			}
			else
			{
				// Make sure that temporary output-file is compressed and then deleted when GenericMolFile is closed.
				file->enableOutputCompression(zipped_filename);
			}
		}

		return file;
	}


	GenericMolFile* MolFileFactory::open(const String& name, File::OpenMode open_mode, GenericMolFile* default_format_file)
	{
		GenericMolFile* file = open(name, open_mode);
		if (file)
		{
			return file;
		}

		if (open_mode == std::ios::out)
		{
			bool compression = false;
			String filename = name;
			String zipped_filename = "";
			if (default_format_file->isCompressedFile())
			{
				compression = true;
				zipped_filename = filename;
				String unzipped_filename;
				File::createTemporaryFilename(unzipped_filename);
				filename = unzipped_filename;
			}

			if (dynamic_cast<AntechamberFile*>(default_format_file))
			{
				file = new AntechamberFile(filename, open_mode);
			}
			else if(dynamic_cast<PDBFile*>(default_format_file))
			{
				file = new PDBFile(filename, open_mode);
			}
			else if(dynamic_cast<HINFile*>(default_format_file))
			{
				file = new HINFile(filename, open_mode);
			}
			else if(dynamic_cast<SDFile*>(default_format_file))
			{
				file = new SDFile(filename, open_mode);
			}
			else if(dynamic_cast<MOL2File*>(default_format_file))
			{
				file = new MOL2File(filename, open_mode);
			}
			else if(dynamic_cast<MOLFile*>(default_format_file))
			{
				file = new MOLFile(filename, open_mode);
			}
			else if(dynamic_cast<XYZFile*>(default_format_file))
			{
				file = new XYZFile(filename, open_mode);
			}
			else if(dynamic_cast<DockResultFile*>(default_format_file))
			{
				file = new DockResultFile(filename, open_mode);
			}

			// Make sure that temporary output-file is compressed and then deleted when GenericMolFile is closed.
			if (compression)
			{
				file->enableOutputCompression(zipped_filename);
			}
		}
		return file;
	}


	String MolFileFactory::detectFileFormat(const String& name)
	{
		String format = "";
		String line;
		vector<String> tmp;

		LineBasedFile input(name, File::MODE_IN);

		unsigned int count = 0;
		unsigned int xyz_count = 0;
		while (getline(input, line))
		{
			// PDB check
			if (line.hasPrefix("HEADER") || line.hasPrefix("ATOM"))
			{
				format = ".pdb";
				break;
			}

			// SDF/Mol check
			if (line.hasPrefix("$$$$") || line.hasPrefix("M  END"))
			{
				format = ".sdf";
				break;
			}

			// Mol2 check
			if (line.hasPrefix("@<TRIPOS>MOLECULE"))
			{
				format = ".mol2";
				break;
			}

			// DRF check
			if (line.hasPrefix("<dockingfile>"))
			{
				format = ".drf";
				break;
			}

			// HIN check
			if (line.hasPrefix("forcefield"))
			{
				format = ".hin";
				break;
			}

			// AC check
			if (line.hasPrefix("CHARGE") || line.hasPrefix("Formula:"))
			{
				format = ".ac";
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
			format = ".xyz";
		}

		input.close();

		return format;
	}
}

