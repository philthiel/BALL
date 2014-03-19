// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#ifndef BALL_FORMAT_MOLFILEFACTORY_H
#define BALL_FORMAT_MOLFILEFACTORY_H

#include <BALL/SYSTEM/file.h>

#include <set>


namespace BALL
{
	class String;
	class GenericMolFile;

	/**
	 * This class offers a factory method, which takes a path to a molecule file,
	 * tries to determine its molecular file format. If the molecular file format
	 * can be detected and is supported by this class, a pointer to an object of
	 * the appropriate GenericMolFile subclass with the open file is returned.
	*/
	class BALL_EXPORT MolFileFactory
	{
		public:

			/**
			 * This method tries to determine the file format based on the file extension of name and
			 * returns a pointer to an object of the appropriate subclass of GenericMolFile if available.
			 * If the file should be opened in read-mode and the extension is unknown or the file does not
			 * have an extension, we try to automatically detect the format.
			 * If the detection fails, NULL is returned.
			 * Be aware that the file handle has not been checked for validity and that you have to delete it yourself.
			 *
			 * @param name name of the requested molecule file
			 * @param open_mode the file open mode to use
			 * @return a pointer to a subclass of GenericMolFile, NULL if none is appropriate
			*/
			static GenericMolFile* open(const String& name, File::OpenMode open_mode = File::MODE_IN);

			/**
			 * When trying to open a file in write-mode, this function can be used to pass along a desired default format.
			 * If the given filename does not have a supported extension and/or forced is set, the specified default format will be used.
			 *
			 * @param name name of the requested molecule file
			 * @param open_mode the file open mode to use
			 * @param default_format the format to be used
			 * @param forced
			 * @return a pointer to a subclass of GenericMolFile, NULL if none is appropriate
			*/
			static GenericMolFile* open(const String& name, File::OpenMode open_mode, String default_format, bool forced = false);

			/**
			 * When trying to open a file in write-mode, this function can be used to pass along a desired default-format.
			 * If the given filename does not have a supported extension, the format of 'default_format_file' will be used.
			 *
			 * @param name name of the requested molecule file
			 * @param open_mode the file open mode to use
			 * @param default_format the molecular file format to be used
			 * @return a pointer to a subclass of GenericMolFile, NULL if none is appropriate
			*/
			static GenericMolFile* open(const String& name, File::OpenMode open_mode, GenericMolFile* default_format_file);

			static String getSupportedCompressionFormats();
			static void getSupportedCompressionFormats(std::set<String>& compression_formats);
			static bool isFileCompressed(const String& name, String& compression_format, String& base_name);

			/**
			 * Return a comma-separated string with all supported file-extensions of the MolFileFactory.
			 *
			 * @return comma-separated string of accepted file formats
			*/
			static String getSupportedFormats();

			/**
			 * Store supported file-extensions in a given set<String>, which will be cleared by this method.
			 *
			 * @param formats set of Strings to store accepted file formats
			*/
			static void getSupportedFormats(std::set<String>& formats);

			/**
			 * Check if the format of the specified filen is supported of MolFileFactory.
			 *
			 * @param name name of the molecular file to inspect
			 * @param input_mode true if an extisting file should be read, false if the name specifies a non-existing output file
			 * @return true if the format is supported, else otherwise
			*/
			static bool isFileFormatSupported(const String& name, bool input_mode);

			/**
			 * Try to determine the format of the given molecular file.
			 * If the format is supported by MolFileFactory the extension is returned.
			 *
			 * @param name name of the molecular file to inspect
			 * @param input_mode true if an extisting file should be read, false if the name specifies a non-existing output file
			 * @return file format extension if it is supported by the MolFileFactory, otherwise an empty String
			*/
			static String getFileFormat(const String& name, bool input_mode);


		private:

			/**
			 * Function tries to automatically detect the molecular file format of an input file.
			 * It works by searching for format specific keywords. The method does not necessarily detect
			 * the format of the requested file, especially if it is too far away from the format specifications.
			 *
			 * @param name name of the molecular file to inspect
			 * @return file extension of the matching molecular file format, an empty String if no matching format was found
			*/
			static String detectFileFormat(const String& name);

			/**
			 * Open uncompressed molecular file using the given format.
			 * This function should be used after the format has been detected using \link MolFileFactory::getFileFormat MolFileFactory::getFileFormat() \endlink.
			 *
			 * @param name name of the requested molecule file
			 * @param format the molecular file format to be used
			 * @param open_mode the file open mode to use
			 * @return a pointer to a subclass of GenericMolFile, NULL if none is appropriate
			*/
			static GenericMolFile* openBase(const String& name, const String& format, File::OpenMode open_mode);
	};
}

#endif //BALL_FORMAT_MOLFILEFACTORY_H
