// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#ifndef BALL_LOGP_H
#define BALL_LOGP_H

#ifndef BALL_COMMON_H
#       include <BALL_core/common.h>
#endif

#include <BALL_core/STRUCTURE/molecularSimilarity.h>

namespace BALL
{
	/** Class for calculation of the Octonal/Water partition coefficient.\n
	Based on Wildman and Crippen, J. Chem. Inf. Comput. Sci. 1999, 39, 868-873 */
	class LogP
	{
		public:
			LogP();

			~LogP();

			/** calculate the LogP value for the given compound */
			double calculate(const String& usmile);

		private:
			void addRule(String smarts, double value);
			std::vector<std::pair<String,double> > rules_;

			MolecularSimilarity* molecular_similarity_;

	};

}
#endif // BALL_LOGP_H
