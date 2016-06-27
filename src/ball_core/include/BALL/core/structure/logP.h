//_new_file_header


#ifndef BALL_CORE_STRUCTURE_LOGP_H
#define BALL_CORE_STRUCTURE_LOGP_H

#include <BALL/core/structure/molecularSimilarity.h>


namespace BALL
{
	/** Class for calculation of the Octonal/Water partition coefficient.\n
	Based on Wildman and Crippen, J. Chem. Inf. Comput. Sci. 1999, 39, 868-873 */
	class BALL_EXPORT LogP
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

#endif // BALL_CORE_STRUCTURE_LOGP_H
