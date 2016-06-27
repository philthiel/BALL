//_new_file_header


#ifndef BALL_CORE_STRUCTURE_SOLVENTACCESSIBLESURFACE_H
#define BALL_CORE_STRUCTURE_SOLVENTACCESSIBLESURFACE_H

#include <BALL/core/maths/sphere3.h>
#include <BALL/core/structure/reducedSurface.h>
#include <BALL/core/structure/SASEdge.h>
#include <BALL/core/structure/SASFace.h>
#include <BALL/core/structure/SASVertex.h>

#include <vector>


namespace BALL
{
	class TriangulatedSAS;
	class SASTriangulator;

	/** Generic SolventAccessibleSurface Class.
	\ingroup Surface			
	*/
	class BALL_EXPORT SolventAccessibleSurface
	{
		public:

		/** @name Class friends

					- class TriangulatedSAS
					- class SASTriangulator
				
		*/
		friend class TriangulatedSAS;
		friend class SASTriangulator;

		BALL_CREATE(SolventAccessibleSurface)

		/**	@name	Constructors and Destructors
		*/
		//@{
		
		/**	Default constructor.
				This method creates a new SolventAccessibleSurface object.
		*/
		SolventAccessibleSurface();

		/**	Copy constructor.
				Create a new SolventAccessibleSurface object from another.
				@param	sas		the SolventAccessibleSurface object to be copied
				@param	bool	ignored - just for interface consistency
		*/
		SolventAccessibleSurface(const SolventAccessibleSurface& sas, bool = false);

		/** Detailed constructor
		*/
		SolventAccessibleSurface(ReducedSurface* reduced_surface);

		/**	Destructor.
				As there are no dynamic	data structures, nothing happens.
		*/
		virtual ~SolventAccessibleSurface();

		//@}
		/**	@name	Accessors
		*/
		//@{
		
		/**
		*/
		void setVertex(SASVertex* vertex, Position i)
			throw(Exception::IndexOverflow);

		/**
		*/
		SASVertex* getVertex(Position i) const
			throw(Exception::IndexOverflow);

		/**
		*/
		Size numberOfVertices() const;
		
		/**
		*/
		void setEdge(SASEdge* edge, Position i)
			throw(Exception::IndexOverflow);

		/**
		*/
		SASEdge* getEdge(Position i) const
			throw(Exception::IndexOverflow);

		/**
		*/
		Size numberOfEdges() const;
		
		/**
		*/
		void setFace(SASFace* face, Position i)
			throw(Exception::IndexOverflow);

		/**
		*/
		SASFace* getFace(Position i) const
			throw(Exception::IndexOverflow);

		/**
		*/
		Size numberOfFaces() const;

		/**
		*/
		void setRS(ReducedSurface* rs);

		/**
		*/
		ReducedSurface* getRS() const;

		/**
		*/
		void clear();

		/**	Computes the solvent excluded surface from a ReducedSurface object
		*/
		void compute();

		//@}

		private:

		/*_	@name	SAS computation (private)
		*/
		//@{

		void preProcessing();

		void get();

		void createFace(Position j);
		void createVertex(Position j);
		void createEdge(Position j);

		//@}


		protected:

		Position number_of_vertices_;

		::std::vector<SASVertex*> vertices_;

		Position number_of_edges_;

		::std::vector<SASEdge*> edges_;

		Position number_of_faces_;

		::std::vector<SASFace*> faces_;

		ReducedSurface* reduced_surface_;
	};

	/**	@name	Storers
	*/
	//@{

	/**	Output- Operator
	*/
	BALL_EXPORT std::ostream& operator << (std::ostream& s, const SolventAccessibleSurface& sas);

	//@}

} // namespace BALL

#endif  // BALL_CORE_STRUCTURE_SOLVENTACCESSIBLESURFACE_H

