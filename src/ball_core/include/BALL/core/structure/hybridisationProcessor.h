//_new_file_header


#ifndef BALL_CORE_STRUCTURE_HYBRIDISATIONPROCESSOR_H
#define BALL_CORE_STRUCTURE_HYBRIDISATIONPROCESSOR_H

#include <BALL/core/concept/processor.h>
#include <BALL/core/datatype/hashMap.h>
#include <BALL/core/datatype/options.h>
#include <BALL/core/datatype/stringHashMap.h>
#include <BALL/core/kernel/atomContainer.h>
#include <BALL/core/kernel/bond.h>

#include <map>
#include <vector>


namespace BALL 
{

	/**	Hybridisation processor
			\ingroup StructureMiscellaneous
	*/
	class BALL_EXPORT HybridisationProcessor 
		: public UnaryProcessor<AtomContainer> 
	{

		public:

			/** @name Constant Definitions
			*/
			//@{
			/// Option names
			struct BALL_EXPORT Option
			{
				/** Name to the file where the atom types and corresponding
				 * hybridisation states are stored in.
				 */
				static const char* ATOM_TYPE_SMARTS_FILENAME;
				
				/** Name to the file where the atom types, corresponding
				 * hybridisation states, and bond angles are stored in (force field based method).
				 */
				static const char* ATOM_TYPE_FF_FILENAME;
				
				/** If true, the existing bonds are deleted before 
				 *  bonds detection begins. If the atoms are in 
				 *  non-bond distance no bonds will be build! Note
				 *  that the processor cannot rebuild inter-atomcontainer
				 *  bonds, that will cause problem using it with proteins.
				 */

				/**	Technique to compute the hybridisation states.
				 */
				static const String METHOD; 

			};

			/// Default values for options
			struct BALL_EXPORT Default
			{
				/// default file name for the atom type smarts
				static const char* ATOM_TYPE_SMARTS_FILENAME;
				
				/** default file name for the atom types, hybridisation states, and
				 *  bond angles (force field based)
				 */
				static const char* ATOM_TYPE_FF_FILENAME;
				
				/// this option is set to
				/// HybridisationProcessor::Method::SMART_MATCHING
				/// by default
				static const String METHOD;
			};

			struct BALL_EXPORT Method
			{
				static const String SMART_MATCHING;
				static const String STRUCTURE_BASED; 
				static const String FF_BASED; 
			};


			//@}
		

			/** @name	Constructors and Destructors
			 */
			//@{

			BALL_CREATE(HybridisationProcessor);
			
			///	default constructor
			HybridisationProcessor();
		
			/// copy construcor
			HybridisationProcessor(const HybridisationProcessor& hp);
		
			/// Constructor with parameter filename for the smarts based algorithm
			/// and parameter filename for the force field based method
			HybridisationProcessor(const String& smarts_file_name, const String& ff_file_name) throw(Exception::FileNotFound);
			
			/// destructor
			virtual ~HybridisationProcessor();
			//@}

			/**	@name	Processor-related methods 
			 */
			//@{

			/// processor method which is called before the operator () call
			virtual bool start();

			/// operator () for the processor
			virtual Processor::Result operator () (AtomContainer& ac);
			//@}

			/**	@name	Accessors
			 */
			//@{
			/// Return the number of hybridisation states set during the last application.
			Size getNumberOfHybridisationStatesSet(); 

			/// sets the parameters file
			void setAtomTypeSmarts(const String& file_name) throw(Exception::FileNotFound);

			/// Return the atom_types--hybridisation  Hashmap 
			std::vector<std::pair<String, Size> > getHybridisationMap() { return atom_type_smarts_;};
			//@}

			/** @name Assignment
			 */
			//@{
			/// assignment operator
			HybridisationProcessor& operator = (const HybridisationProcessor& hp);
			//@}

			/** @name Public Attributes
			 */
			//@{
			/// options
			Options options;

			/** reset the options to default values
			 */
			void setDefaultOptions();
			//@}
			
		protected:
			
			/** Struct for atom types and hybridization states
			 */
			struct Elements_
			{
				/// The type
				String type;
				/// Hybridization state
				unsigned char hyb;
			};
			
			/** The atom names for each bond angle
			 */
			struct AtomNames_
			{
				/// First atom
				String a1;
				/// Second atom
				String a2;
				/// Third atom
				String a3;
			};
			
			/// method to read the paramter file
			bool readAtomTypeSmartsFromFile_(const String& file_name = "") throw(Exception::FileNotFound);
			
			/// number of bonds, which are created during the processor call
			Size num_hybridisation_states_;

			/// structure where atom type smarts and the corresponding hybridisation states are stored in
			std::vector<std::pair<String, Size> > atom_type_smarts_;
			
			/** Contains the bond angles and their atom types. The bond angles 
			 *  are stored in 'rad'.
			 */
			StringHashMap<StringHashMap<StringHashMap<std::multimap<float, AtomNames_> > > > bond_angles_;
			
			bool readAndInitBondAnglesFromFile_(const String& file_name = "") throw(Exception::FileNotFound);
			
			/** Maps the atom types onto their elements
			 */
			StringHashMap<Elements_> elements_;
			

			/// the Processors state
			bool valid_;
			
	
			/// computes the averaged bond angle for the given Atom
			double AverageBondAngle_(Atom* a);

	};

} // namespace BALL 

#endif // BALL_CORE_STRUCTURE_HYBRIDISATIONPROCESSOR_H