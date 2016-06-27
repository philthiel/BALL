//_new_file_header


#ifndef BALL_CORE_DOCKING_COMMON_STATICLIGANDFRAGMENT_H
#define BALL_CORE_DOCKING_COMMON_STATICLIGANDFRAGMENT_H

#include <BALL/core/kernel/atom.h>
#include <BALL/core/maths/matrix44.h>

#include <list>
#include <vector>


namespace BALL
{
	class BALL_EXPORT StaticLigandFragment
	{
		public:
			class Connection;

			/** the position of this fragment within ligand_fragments_ */
			int ID;

			/** all atoms of this ligand fragment */
			std::list<Atom*> atoms;

			std::vector<Connection> connections;

			/** the overall force of the entire fragment */
			Vector3 force;

			/** direction of the fragment force; i.e. the sum of the absolute values of the atom forces */
			Vector3 force_axis;

			/** the geometrical center of the ligand fragment */
			Vector3 center;

			/** rotates the current and all connected ligand fragments (except static_fragment) around given axis (--> bond between two fragments) */
			//void rotate(const Connection* rotation_bond, int degree, int static_fragment);

			/** rotates the current and all connected ligand fragments (except static_fragment) according to a given transformation matrix */
			//void rotate(TMatrix4x4<float>& M, Vector3& origin, int static_fragment);

			/** A Connection represent a single rotatable bond which connects two StaticLigandFragments */
			struct Connection
			{
				// /** the position of this connection within neighbor_connections */
				//int ID;

				/** atom of *this* fragment that is part of this intra-fragment bond */
				Atom* atom;

				/** atom of the neighbor fragment that is part of this intra-fragment bond */
				Atom* neighbor_atom;

				StaticLigandFragment* fragment; // the neighboring fragment
			};
	};
}

#endif // BALL_CORE_DOCKING_COMMON_STATICLIGANDFRAGMENT_H
