class MolFileFactory
{
%TypeHeaderCode

	#include <BALL/FORMAT/molFileFactory.h>
	using namespace BALL;
%End
	public:
		/*
		static String getSupportedFormats();
		static bool isFileExtensionSupported(String filename);
		static GenericMolFile* open(const String&, OpenMode open_mode = std::ios::in);
	    static GenericMolFile* open(const String&, OpenMode, String, bool forced = false);
		static GenericMolFile* open(const String&, OpenMode, GenericMolFile*);
		static GenericMolFile* open(const String& name, File::OpenMode open_mode = File::MODE_IN);
		*/

		static GenericMolFile* open(const String& name, File::OpenMode open_mode, String default_format);

		static GenericMolFile* open(const String& name, File::OpenMode open_mode, GenericMolFile* default_format_file);

		static String getSupportedCompressionFormats();

		static void getSupportedCompressionFormats(std::set<String>& compression_formats);

		static bool isFileCompressed(const String& name, String& compression_format, String& decompressed_name);

		static String getSupportedFormats();

		static void getSupportedFormats(std::set<String>& formats);

		static bool isFileFormatSupported(const String& name, bool input_mode);

		static String getFileFormat(const String& name, bool input_mode);
};
