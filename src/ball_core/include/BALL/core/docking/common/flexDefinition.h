//_new_file_header


#ifndef BALL_CORE_DOCKING_COMMON_FLEXDEFINITION_H
#define BALL_CORE_DOCKING_COMMON_FLEXDEFINITION_H

#include <BALL/core/kernel/protein.h>

#include <vector>


namespace BALL
{
		/**     FlexDefinition class.
					  This class is used to store flexibility information
					  about a receptor object.
		 */
		class BALL_EXPORT FlexDefinition
		{
			public:

				enum RotamerLibrary
				{
					DUNBRACK = 0,
					LOVELL
				};

				/** Make a rigid FlexDefinition.
				 */
				static FlexDefinition Rigid();

				BALL_CREATE(FlexDefinition)

				/** Constructor.
				 */
				FlexDefinition();

				/** Destructor.
				 */
				virtual	~FlexDefinition();

				/** Add a fully (all-atom) flexible residue.
							@param residue index
				 */
				void addFullyFlexibleResidue(Position idx);

				/** Get all fully-flexible residues.
							@param vector of residue indices
				 */
				std::vector<Position> getFullyFlexibleResidues() const;

				/** Add a rotamer-flexible residue.
							@param residue index
				 */
				void addRotamerFlexibleResidue(Position idx);

				/** Get all rotamer-flexible residues.
							@param vector of residue indices
				 */
				std::vector<Position> getRotamerFlexibleResidues() const;

			private:
				std::vector<Position> fully_flexible_;
				std::vector<Position> rotamer_flexible_;
		};
}

#endif // BALL_CORE_DOCKING_COMMON_FLEXDEFINITION_H
