//_new_file_header


#ifndef BALL_CORE_FORMAT_MOPACINPUTFILE_H
#define BALL_CORE_FORMAT_MOPACINPUTFILE_H

#include <BALL/core/common/global.h>
#include <BALL/core/datatype/string.h>
#include <BALL/core/format/genericMolFile.h>
#include <BALL/core/kernel/atomContainer.h>


namespace BALL
{
	/**
	 * MOPAC input file class.
	 * This class enables BALL to read and write MOPAC input files.	 
	 * \ingroup  StructureFormats
	 */
	class BALL_EXPORT MOPACInputFile
		: public GenericMolFile
	{
		public:
			/** @name Constructors and Destructors
			 */
			//@{

			/** Default constructor
			 */
			MOPACInputFile();

			/** Detailed constructor
			 *  @throw Exception::FileNotFound if the file could not be opened
			 */
			MOPACInputFile(const String& filename,
					           File::OpenMode open_mode = std::ios::in);

			/**	Destructor
			 */
			virtual ~MOPACInputFile();

			/**	@name Reading and Writing of Kernel Datastructures
			*/
			//@{

			/**	Write a molecule to a MOPAC input file.
			 *  
			 *  The mopac keywords will be taken from the property
			 *  MOPAC-Keywords, if it exists, and will default to
			 *	default_mopac_keywords otherwise. The spin multiplicity
			 *	will be taken from the property SpinMultiplicity, if it
			 *	exists, and will default to SINGLET.
			 *
			 *  @throw File::CannotWrite if writing to the file failed
			 */
			virtual bool write(const Molecule& molecule);

			/**	Write a system to a MOPAC input file.
			 *  
			 *  The mopac keywords will be taken from the property
			 *  MOPAC-Keywords, if it exists, and will default to
			 *	default_mopac_keywords otherwise. The spin multiplicity
			 *	will be taken from the property SpinMultiplicity, if it
			 *	exists, and will default to SINGLET.

			 *
			 *  @throw File::CannotWrite if writing to the file failed
			 */
			virtual bool write(const System& system);

			// TODO:
			/**	Read a molecule from the MOPACInputFile file
			 *  @throw Exception::ParseError if a syntax error was encountered
			 */
//			virtual Molecule* read();

			// TODO: 
			/** @copydoc GenericMolFile(System& system)
			 */
//			virtual bool read(System& system);

			//@}

		protected:
			void writeHeader_(const AtomContainer& ac);
			void writeAtoms_(const AtomContainer& ac);

			String default_mopac_keywords_;
	};
}
#endif // BALL_CORE_FORMAT_MOPACINPUTFILE_H

