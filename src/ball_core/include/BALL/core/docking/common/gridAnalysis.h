//_new_file_header

#ifndef BALL_CORE_DOCKING_COMMON_GRIDANALYSIS_H
#define BALL_CORE_DOCKING_COMMON_GRIDANALYSIS_H

#include <BALL/core/datatype/regularData3D.h>
#include <BALL/core/scoring/common/scoringFunction.h>

#include <map>


namespace BALL
{
	class BALL_EXPORT GridAnalysis
	{
		public:
			GridAnalysis(ScoringFunction* sf, AtomContainer* probe_group);

			void setResolution(const double& resolution);

			void enableSavingBestPoses(Size number_best_poses);

			RegularData3D* calculate();

			std::list<AtomContainer*> getBestPoses();

		protected:
			typedef std::multimap<double, std::pair<Vector3, Vector3> > PoseList;

			/** Translate probe_group_ to the given destination. */
			void moveProbeGroup_(const Vector3& destination);

			/** Rotates probe_group_ around a specified axis.
			@param axis 0 == rotation around X axis, 1 == rotation around Y axis, 2 == rotation around Z axis */
			void rotateProbeGroup_(int axis, int degree);

			ScoringFunction* scoring_function_;

			AtomContainer probe_group_;

			double resolution_;

			Vector3 origin_;

			/** the current geometrical center of the probe group */
			Vector3 center_;

			Size no_best_poses_;

			/** contains pairs of  < score, < position, rotation > > . */
			PoseList best_poses_;

			Size border_;

	};
}

#endif // BALL_CORE_DOCKING_COMMON_GRIDANALYSIS_H