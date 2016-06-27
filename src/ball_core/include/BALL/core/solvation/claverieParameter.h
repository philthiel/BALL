//_new_file_header


#ifndef BALL_CORE_SOLVATION_CLAVERIEPARAMETER_H
#define BALL_CORE_SOLVATION_CLAVERIEPARAMETER_H

#include <BALL/core/format/parameters.h>
#include <BALL/core/format/parameterSection.h>
#include <BALL/core/molmec/parameter/forceFieldParameters.h>


namespace BALL
{
	/** ClaverieParameter class. 
			This class provides the parameters needed for the computation of
			van-der-Waals interaction energies according to the scheme by Huron and
			Claverie. [missing: units, reference].
			<b>Note:</b> Dispersion and repulsion terms are <b>not</b> distinguished.  \par
		\ingroup Solvation	
	 */
	class BALL_EXPORT ClaverieParameter
		:	public ParameterSection
	{

		public:

		BALL_CREATE(ClaverieParameter)

		/** @name Constructors and destructors. 
		*/
		//@{

		/** Default constructor 
		*/
		ClaverieParameter();

		/** Detailed constructor 
		*/
		ClaverieParameter(const Parameters& parameters) 
			;

		/** Copy constructor 
		*/
		ClaverieParameter(const ClaverieParameter& param);

		/** Destructor 
		*/
		virtual ~ClaverieParameter();

		//@}
		/** @name Assignment 
		*/
		//@{

		/** Assignment operator 
		*/
		const ClaverieParameter& operator = (const ClaverieParameter& param);

		/** Clear method 
		*/
		virtual void clear();

		//@}
		/** @name Accessors 
		*/
		//@{

		/** Indicate, whether this parameter set has parameters for the
				specified atom types.
		*/
		bool hasParameters(Atom::Type solvent_type, Atom::Type solute_type) const;

		/** Get the parameters for the specified atom types.
		*/
		std::pair<float, float> getParameters(Atom::Type solvent_type,
				Atom::Type solute_type) const;

		/** ?????
		*/
		std::pair<float, float> getParameters(Atom::Type type) const;

		/** Return the whole parameter set.
		*/
		const ::std::vector< ::std::pair<float, float> >& getParameters() const;

		/** Return the indices used for mapping types to numbers
		*/
		const HashMap<Atom::Type, Index>& getIndices() const;

		//@}
		/** @name Predicates 
		*/
		//@{

		/** Equality operator.
		*/
		bool operator == (const ClaverieParameter& param) const;

		//@}

		/** Extract the parameter file section (@see ParameterSection).
		*/
		virtual bool extractSection(ForceFieldParameters& parameters,
				const String& section_name);

		protected:

		/*_ This vector contains the paramaters that were read from the
			  parameter file 
		*/
		std::vector< std::pair<float, float> > parameters_;

		/*_ Here the atom types are mapped to the indices of the vector 
		*/
		HashMap<Atom::Type, Index> indices_;

	};
   
} // namespace BALL

#endif // BALL_CORE_SOLVATION_CLAVERIEPARAMETER_H
