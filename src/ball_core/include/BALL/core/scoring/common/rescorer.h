//_new_file_header


#ifndef BALL_CORE_SCORING_COMMON_RESCORER_H
#define BALL_CORE_SCORING_COMMON_RESCORER_H

#include <BALL/core/datatype/string.h>
#include <BALL/core/docking/common/structurePreparer.h>
#include <BALL/core/format/commandlineParser.h>
#include <BALL/core/format/genericMolFile.h>
#include <BALL/core/scoring/common/scoringFunction.h>
#include <BALL/core/scoring/functions/rescoring.h>


namespace BALL
{

	/** Class that performs rescoring. Taken originally from CADDSuite.
	 */
	class BALL_EXPORT Rescorer
	{

		public:
			// assignment operator
			Rescorer& operator = (const Rescorer& rescorer);

			// runs a rescoring
			static int runRescoring(CommandlineParser& par, bool simple_rescoring, bool train);

		private:

			static void processMultiMoleculeFile(ScoringFunction* scoring_function, StructurePreparer* sp, String par_file, Rescoring* rescoring, bool train, double min_dock_score, String dock_score_label, GenericMolFile* input, GenericMolFile* output, double output_score_threshold, bool ignore_top);

	};

}

#endif // BALL_CORE_SCORING_COMMON_RESCORER_H