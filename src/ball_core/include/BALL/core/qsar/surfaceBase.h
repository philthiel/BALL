//_new_file_header


#ifndef BALL_CORE_QSAR_SURFACEBASE_H
#define BALL_CORE_QSAR_SURFACEBASE_H

#include <BALL/core/qsar/descriptor.h>


namespace BALL
{
	/** Generic QSAR molecular surface descriptors class
		\\
	*/
	class BALL_EXPORT SurfaceBase
		:	public Descriptor
	{
		public:

		BALL_CREATE(SurfaceBase)

		/** @name Constructors and Destructors
		*/
		//@{
		/** Default constructor
		*/
		SurfaceBase();

		/** Copy constructor
		*/
		SurfaceBase(const SurfaceBase& sb);

		/** Named constructor
		*/
		SurfaceBase(const String& name);

		/** Named unity constructor
		*/
		SurfaceBase(const String& name, const String& unit);

		/** Destructor
		*/
		virtual ~SurfaceBase();
		//@}	
		
		/** @name Accessors
		*/
		//@{
		void computeAllDescriptors(AtomContainer& ac);
		//@}

		/** @name Assignment
		*/
		//@{
		/** Assignment operator
		*/
		SurfaceBase& operator = (const SurfaceBase& sb);
		//@}

		protected:

		/** @name Predicates
		*/
		//@{
		bool isValid_(AtomContainer& ac);
		//@}
		
		/** @name Accessors
		*/
		//@{
		void calculate_(AtomContainer& ac);
		//@}
	};
} // namespace BALL

#endif // BALL_CORE_QSAR_SURFACEBASE_H

