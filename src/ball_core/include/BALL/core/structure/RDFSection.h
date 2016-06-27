//_new_file_header


#ifndef BALL_CORE_STRUCTURE_RDFSECTION_H
#define BALL_CORE_STRUCTURE_RDFSECTION_H

#include <BALL/core/format/parameterSection.h>
#include <BALL/core/structure/radialDistributionFunction.h>


namespace BALL
{
	/** Helper class for RDFParameter.
	\ingroup RDF
	 */
	class BALL_EXPORT RDFSection
		:	public ParameterSection
	{
		public:

		BALL_CREATE(RDFSection)

		/** @name Enums 
		*/
		//@{

		enum Type
		{
			UNKNOWN_TYPE = 0,
			PIECEWISE_POLYNOMIAL = 1
		};

		//@}
		/** @name Constructors and destructors 
		*/
		//@{

		/** Default constructor 
		*/
		RDFSection() ;

		/** Copy constructor 
		*/
		RDFSection(const RDFSection& rdf_section) ;

		/** Destructor 
		*/
		virtual ~RDFSection() ;

		//@}
		/** @name Assignment 
		*/
		//@{

		/** */
		const RDFSection& operator = (const RDFSection& rdf_section) ;

		/** Clear method 
		*/
		virtual void clear() ;

		//@}
		/** @name Parameter extraction 
		*/
		//@{

		/** */
		virtual bool extractSection(Parameters& parameters,	const String& section_name) 
			;
		
		//@}
		/** @name Accessors 
		*/
		//@{

		/** return the RDF created by extractSection() 
		*/
		const RadialDistributionFunction& getRDF() const ;

		//@}
		/** @name Predicates 
		*/
		//@{

		/** Equality operator 
		*/
		bool operator == (const RDFSection& section) const ;

		//@}

		protected:

		/*_ The RDF that is to be read from a section */
		RadialDistributionFunction rdf_;
	
	};
   
} // namespace BALL

#endif //  BALL_CORE_STRUCTURE_RDFSECTION_H
