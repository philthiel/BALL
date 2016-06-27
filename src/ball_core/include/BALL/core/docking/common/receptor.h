//_new_file_header


#ifndef BALL_CORE_DOCKING_COMMON_RECEPTOR_H
#define BALL_CORE_DOCKING_COMMON_RECEPTOR_H

#include <BALL/core/datatype/hashSet.h>
#include <BALL/core/docking/common/conformation.h>
#include <BALL/core/docking/common/flexibleMolecule.h>
#include <BALL/core/docking/common/flexDefinition.h>
#include <BALL/core/kernel/PDBAtom.h>
#include <BALL/core/kernel/protein.h>

#include <vector>


namespace BALL
{
	/**     Receptor class.
				  This class represents protein receptors.
	 */
	class BALL_EXPORT Receptor : public FlexibleMolecule
	{
		public:
			Receptor();
			Receptor(Protein* p);
			virtual ~Receptor();
			FlexDefinition getFlexDefinition(Position i);
			void setFlexDefinition(Position i, FlexDefinition& fd);
			std::vector<FlexDefinition> getFlexDefinitions();

			/** Add a conformation with flexible side chains
					@param conformation pointer
					@param FlexDefinition
			 */
			void addFlexConformation(Conformation* conf, FlexDefinition &fd);

			/** Add a conformation
					@param conformation pointer
			 */
			void addConformation(Conformation* conf);

		protected:
			std::vector<FlexDefinition> flexinfo_;
	};
}

#endif // BALL_CORE_DOCKING_COMMON_RECEPTOR_H
