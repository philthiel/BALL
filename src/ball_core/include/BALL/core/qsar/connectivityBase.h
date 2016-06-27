//_new_file_header


#ifndef BALL_CORE_QSAR_CONNECTIVITYBASE_H
#define BALL_CORE_QSAR_CONNECTIVITYBASE_H

#include <BALL/core/common/global.h>
#include <BALL/core/qsar/descriptor.h>


namespace BALL
{
	// forward declarations
	template <typename Key, typename Value> class HashMap;

	/** Generic QSAR molecular connectivity descriptors class
			\\
	*/
	class BALL_EXPORT ConnectivityBase
		:	public Descriptor
	{
		public:
				
		/** @name Constructors and Destructors
		*/
		//@{
		/** Default constructor
		*/
		ConnectivityBase();

		/** Copy constructor
		*/
		ConnectivityBase(const ConnectivityBase& cb);

		/** Named constructor
		*/
		ConnectivityBase(const String& name);

		/** Named unity constructor
		*/
		ConnectivityBase(const String& name, const String& unit);

		/** Destructor
		*/
		virtual ~ConnectivityBase();
		//@}

		/** @name Assignment
		*/
		//@{
		/** Assignment operator
		*/
		virtual ConnectivityBase& operator = (const ConnectivityBase& cb);
		//@}
		
		/** @name Accessors
		*/
		//@{
		void computeAllDescriptors(AtomContainer& ac);
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


		private:

		/*_ @name Accessors
		*/
		//@{
		/*_ Dijkstra recursion. Performs a single source shortest path approach
				@param distances to the other nodes are stored in referenced vector<double>
				@param Atom which acts as source atom
				@param indices map, which maps for each atom a index for the dist vector
		*/
		void recursion_(std::vector<double>& dists, const Atom* source, HashMap<const Atom*, Size>& index_map);
		//@}

	};

} // namespace BALL

#endif // BALL_CORE_QSAR_CONNECTIVITYBASE_H
