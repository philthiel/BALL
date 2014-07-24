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
			static GenericMolFile* open(const String& file_name, File::OpenMode open_mode = File::MODE_IN);

			/**
			 * When trying to open a file in write-mode, this function can be used to pass along a desired default format.
			 * If the given filename does not have a supported extension the specified default format will be used.
			 *
			 * @param name name of the requested molecule file
			 * @param open_mode the file open mode to use
			 * @param default_format the format to be used
			 * @param forced
			 * @return a pointer to a subclass of GenericMolFile, NULL if none is appropriate
			*/
			static GenericMolFile* open(const String& file_name, File::OpenMode open_mode, String default_format);

			/**
			 * When trying to open a file in write-mode, this function can be used to pass along a desired default-format.
			 * If the given filename does not have a supported extension, the format of 'default_format_file' will be used.
			 *
			 * @param name name of the requested molecule file
			 * @param open_mode the file open mode to use
			 * @param default_format the molecular file format to be used
			 * @return a pointer to a subclass of GenericMolFile, NULL if none is appropriate
			*/
			static GenericMolFile* open(const String& file_name, File::OpenMode open_mode, GenericMolFile* default_format_file);

			/**
			 * Return a comma-separated string with file extensions of all supported compression formats.
			 *
			 * @return comma-separated string with compression file extensions
			 */
			static String getSupportedCompressionFormats();

			/**
			 * Store supported compression file extensions in a given set<String>.
			 * The set will be cleared.
			 *
			 * @param compression_formats set to store the supported compression file extensions
			 */
			static void getSupportedCompressionFormats(std::set<String>& compression_formats);

			/**
			 * Check if the passed filename (name) has a supported compression file extension.
			 * Return the decompressed filename and the compression file extension.
			 *
			 * @param name name of the file to inspect
			 * @param compression_format stores compression file extension or empty String if file is not compressed
			 * @param decompressed_name string to store the file name without compression extension
			 * @return true if file is compressed, else otherwise
			 */
			static bool isFileCompressed(const String& file_name, String& compression_format, String& decompressed_name);

			/**
			 * Return a comma-separated string with all supported file extensions of the MolFileFactory.
			 *
			 * @return comma-separated string of supported file format extensions
			*/
			static String getSupportedFormats();

			/**
			 * Store supported file extensions in a given set<String>.
			 * The set will be cleared.
			 *
			 * @param formats set to store supported file format extensions
			*/
			static void getSupportedFormats(std::set<String>& formats);

			/**
			 * Check if the given file extension belongs to a supported file format.
			 *
			 * @param format extension to be checked
			 * @return true if supported file extension (format); false otherwise
			 */
			static bool isFileExtensionSupported(const String& extension);

			/**
			 * Check if the format of the specified filen is supported of MolFileFactory.
			 *
			 * @param name name of the molecular file to inspect
			 * @param input_mode true if an extisting file should be read, false if the name specifies a non-existing output file
			 * @return true if the format is supported, else otherwise
			*/
			static bool isFileFormatSupported(const String& file_name, bool input_mode);

			/**
			 * Try to determine the format of the given molecular file.
			 * If the format is supported by MolFileFactory the extension is returned.
			 *
			 * @param name name of the molecular file to inspect
			 * @param input_mode true if an extisting file should be read, false if the name specifies a non-existing output file
			 * @return file format extension if it is supported by the MolFileFactory, otherwise an empty String
			*/
			static String getFileFormat(const String& file_name, bool input_mode);


		private:

			/**
			 * Decompress an input file.
			 *
			 * @param name input file name
			 * @param decompressed_name name to use for decompressed output file
			 * @param compression_format the compression format
			 */
			static void decompressFile(const String& file_name, const String& decompressed_name, const String& compression_format);

			/**
			 * Function tries to automatically detect the molecular file format of an input file.
			 * It works by searching for format specific keywords. The method does not necessarily detect
			 * the format of the requested file, especially if it is too far away from the format specifications.
			 *
			 * @param name name of the molecular file to inspect
			 * @return file extension of the matching molecular file format, an empty String if no matching format was found
			*/
			static String detectFileFormat(const String& file_name);

			/**
			 * Open uncompressed molecular file using the given format.
			 * This function should be used after the format has been detected using \link MolFileFactory::getFileFormat MolFileFactory::getFileFormat() \endlink.
			 *
			 * @param name name of the requested molecule file
			 * @param format the molecular file format to be used
			 * @param open_mode the file open mode to use
			 * @return a pointer to a subclass of GenericMolFile, NULL if none is appropriate
			*/
			static GenericMolFile* openBase(const String& file_name, const String& format, File::OpenMode open_mode);
	};
}

#endif //BALL_FORMAT_MOLFILEFACTORY_H
