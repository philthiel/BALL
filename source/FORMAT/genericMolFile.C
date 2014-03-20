// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#include <BALL/FORMAT/genericMolFile.h>
#include <BALL/KERNEL/system.h>
#include <BALL/KERNEL/molecule.h>

#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/bzip2.hpp>


using namespace std;
using namespace boost;


namespace BALL 
{
	GenericMolFile::GenericMolFile()
		:	LineBasedFile(),
			input_is_temporary_(false),
			compression_(""),
			gmf_is_closed_(false)
	{
	}

	GenericMolFile::GenericMolFile(const String& filename, File::OpenMode open_mode)
		:	LineBasedFile(filename, open_mode),
			input_is_temporary_(false),
			compression_(""),
			gmf_is_closed_(false)
	{
	}

	GenericMolFile::~GenericMolFile()
	{
		GenericMolFile::close();
	}

	void GenericMolFile::close()
	{
		LineBasedFile::close();

		if (gmf_is_closed_)
		{
			return;
		}

		if (getOpenMode()==File::MODE_IN && input_is_temporary_)
		{
			File::remove(name_);
		}

		if(getOpenMode()==File::MODE_OUT && !compression_.isEmpty())
		{
			fstream::close();
			ifstream unzipped_file(name_.c_str(), ios_base::in);
			iostreams::filtering_streambuf<iostreams::input> in;

			if (compression_ == ".gz")
			{
				// Apply gzip compression
				in.push(iostreams::gzip_compressor());
			}
			else
			{
				if (compression_ == ".bz2")
				{
					// Apply bzip2 compression
					in.push(iostreams::bzip2_compressor());
				}
			}

			in.push(unzipped_file);

			ofstream zipped_file(zipped_filename_.c_str(), std::ios::out | std::ios_base::binary);
			iostreams::copy(in, zipped_file);
			File::remove(name_);
		}

		gmf_is_closed_ = true;
	}

	void GenericMolFile::defineInputAsTemporary(bool b)
	{
		input_is_temporary_ = b;
	}

	void GenericMolFile::enableOutputCompression(const String& zipped_filename, const String& compression)
	{
		compression_ = compression;
		zipped_filename_ = zipped_filename;
	}

	bool GenericMolFile::isCompressedFile(String& compression)
	{
		if (input_is_temporary_ || !compression_.isEmpty())
		{
			compression = compression_;
			return true;
		}

		compression = "";
		return false;
	}

	const GenericMolFile& GenericMolFile::operator = (const GenericMolFile& rhs)
	{
		LineBasedFile::operator = (rhs);
		return *this;
	}

	bool GenericMolFile::read(System& system)
	{
		if (!isOpen())
		{
			return false;
		}

		initRead_();

		bool read_anything = false;
		Molecule* molecule = 0;
		while ((molecule = read()) != 0)
		{
			system.append(*molecule);
			read_anything = true;
		}

		return read_anything;
	}

	Molecule* GenericMolFile::read()
	{
		return 0;
	}

	bool GenericMolFile::write(const Molecule& /* molecule */)
	{
		if (!isOpen() || getOpenMode() != std::ios::out)
		{
			throw (File::CannotWrite(__FILE__, __LINE__, name_));
		}
		return true;
	}

	bool GenericMolFile::write(const System& system)
	{
		if (!isOpen() || getOpenMode() != std::ios::out)
		{
			throw (File::CannotWrite(__FILE__, __LINE__, name_));
		}

		initWrite_();
		MoleculeConstIterator molecule = system.beginMolecule();
		for (; +molecule; ++molecule)
		{
			if (!write(*molecule)) return false;
		}
		return true;
	}

	GenericMolFile& GenericMolFile::operator >> (System& system)
	{
		read(system);
		return *this;
	}
 
	GenericMolFile& GenericMolFile::operator << (const System& system)
	{
		write(system);
		return *this;
	}

	GenericMolFile& GenericMolFile::operator >> (Molecule& molecule)
	{
		molecule.clear();
		Molecule* new_mol = read();
		if (new_mol != 0)
		{
			molecule = *new_mol; // copy the Molecule
		}
		
		delete new_mol;
		return *this;
	}
 
	GenericMolFile& GenericMolFile::operator << (const Molecule& molecule)
	{
		write(molecule);
		return *this;
	}

	void GenericMolFile::initRead_()
	{
	}

	void GenericMolFile::initWrite_()
	{
	}

} // namespace BALL
