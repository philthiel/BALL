//_new_file_header


#ifndef BALL_CORE_FORMAT_ANTECHAMBERFILE_H
#define BALL_CORE_FORMAT_ANTECHAMBERFILE_H

#include <BALL/core/format/genericMolFile.h>


namespace BALL
{
	class Atom;
	class AtomContainer;
	class System;

	/**	Antechamber file format (ac-file) class.
			
			This class is used to read and write antechamber input/output files.	 
			\par

    	\ingroup  StructureFormats
	*/
	class BALL_EXPORT AntechamberFile
		: public GenericMolFile
	{
		public:

			/**	@name	Constructors and Destructors
			*/
			//@{

			/**	Default constructor
			*/
			AntechamberFile();

			/** Detailed constructor
			 *  @throw Exception::FileNotFound if the file could not be opened
			*/
			AntechamberFile(const String& filename, File::OpenMode open_mode = std::ios::in);

			/// Destructor
			virtual ~AntechamberFile();
			//@}

			/**	@name Reading and Writing of Kernel Datastructures
			*/
			//@{

			/** Write an AtomContainer to the ac file
			 *  @throw File::CannotWrite if writing to the file failed
			 */
			virtual bool write(const AtomContainer& ac);

			/**	Write a system to the ac file
			 *  @throw File::CannotWrite if writing to the file failed
			 */
			virtual bool write(const System& system);

			/**	Read a system from the ac file
			 *  @throw Exception::ParseError if a syntax error was encountered
			*/
			virtual bool read(System&	system);

			/** Read a Molecule from the ac file
			 *  @throw Exception::ParseError if a syntax error was encountered
			 */
			virtual Molecule* read();

			/** Write a Molecule to the ac file
			 *  @throw File::CannotWrite if writing to the file failed
			 */
			virtual bool write(const Molecule& molecule);
	
			//@}
		
	  protected:
			void ac_split_(const String& line, std::vector<String>& split);
	};
}

#endif // BALL_CORE_FORMAT_ANTECHAMBERFILE_H
