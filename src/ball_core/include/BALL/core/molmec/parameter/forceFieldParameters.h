//_new_file_header


#ifndef BALL_CORE_MOLMEC_FORCEFIELDPARAMETERS_H
#define BALL_CORE_MOLMEC_FORCEFIELDPARAMETERS_H

#include <BALL/core/format/parameters.h>
#include <BALL/core/molmec/parameter/atomTypes.h>


namespace BALL 
{
	class AtomTypes;
	
	/**	Force field parameter class.
			
			\ingroup  MolmecParameters
	*/
	class BALL_EXPORT ForceFieldParameters
		:	public Parameters
	{
		public:

		BALL_CREATE(ForceFieldParameters)

		friend class ForceField;

		/**@name	Constructors and destructor	
		*/
		//@{

		/**	Default constructor.
		*/
		ForceFieldParameters();

		/**	Constructor.
		*/
		ForceFieldParameters(const String& filename);

		/**	Copy constructor
		*/
		ForceFieldParameters(const ForceFieldParameters& force_field_parameter);

		/**	Destructor.
		*/
		virtual ~ForceFieldParameters()
			;

		//@}
		/** @name Assignment 
		*/
		//@{

		/** Clear method 
		*/
		virtual void clear()
			;

		/** Assignment operator 
		*/
		const ForceFieldParameters& operator = (const ForceFieldParameters& param);
		
		//@}
		/**@name	Accessors 	
		*/
		//@{

		/**	Return a reference to the atom type parameter section
		*/
		AtomTypes&	getAtomTypes();

		/**	Read the contents of the INI file and interpret them.
		*/
		virtual bool init();

		//@}
		/**	@name	Predicates
		*/
		//@{
			
		/**	Valididty predicate.
				Return <b>true</b> if the force field parameters were correctly
				initialized, the internal INI file is valid and the internal atom types		
				object is valid.
				@return bool - <tt>valid_ && parameter_file_.isValid() && atom_types_.isValid()</tt>
		*/
		virtual bool isValid() const;

		/** Equality operator 
		*/
		bool operator == (const ForceFieldParameters& param) const;

		//@}

		protected:

		/*_@name	Protected Members 
		*/
		//_@{ 

		/*_	the atom types section
		*/
		AtomTypes	atom_types_;

		//_@} 
	};
} // namespace BALL

#endif // BALL_CORE_MOLMEC_FORCEFIELDPARAMETERS_H