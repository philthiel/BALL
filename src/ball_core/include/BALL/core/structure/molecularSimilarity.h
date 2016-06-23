// ----------------------------------------------------
// $Maintainer: Marcel Schumann $
// $Authors: Marcel Schumann $
// ----------------------------------------------------

// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#ifndef BALL_STRUCTURE_MOLECULARSIMILARITY_H
#define BALL_STRUCTURE_MOLECULARSIMILARITY_H

#include <vector>

#ifndef BALL_CONFIG_CONFIG_H
		#include <BALL/config.h>
#endif

#include <BALL/core/structure/smartsMatcher.h>
#include <BALL/core/kernel/system.h>

#ifdef BALL_HAS_OPENBABEL
	#include <openbabel/mol.h>
#endif


namespace BALL
{
	class BALL_EXPORT MolecularSimilarity
	{
		public:

			MolecularSimilarity(String smarts_file);

			void generateFingerprints(System& molecules, std::vector<std::vector<Size> >& fingerprints);

			void generateFingerprints(const list<Molecule*>& molecules, std::vector<std::vector<Size> >& fingerprints);

			void generateFingerprint(Molecule& molecule, std::vector<Size>& fingerprint);


			#ifdef BALL_HAS_OPENBABEL
				/** Create an Openbabel-molecule from a given BALL::Molecule
				 * @param suppress_warning if set to true, warning about aromatic bonds
				 * of carboxyl- and guanidinium-groups being de-aromatized (which OpenBabel requires) will not be shown.
				*/
				static OpenBabel::OBMol* createOBMol(const Molecule& mol, bool ignore_hydrogen=0, bool suppress_warning=0);

				/** Create a BALL::Molecule from a given OpenBabel-molecule
				*/
				static Molecule* createMolecule(OpenBabel::OBMol& obmol, bool ignore_hydrogen=0);

				void generateCanSmile(const Molecule& mol, String& cansmile, OpenBabel::OBMol** output_obmol=0, bool ignore_hydrogen=0);

				/** Match the given SMARTS pattern to the supplied smile and return the number of matches.
				 * @param max_matches the maximal number of SMART matches to be made; can be used as a speed-up.
				 * If this number of matches has been found, the SMARTS-matching algorithm will abort.
				 * Specifying zero will not set any such constraint.*/
				void matchSmarts(const String& usmile, const String& smarts, Size& no_matches, Size max_matches=0);
			#endif

			void generatePathFingerprint(Molecule& mol, std::vector<bool>& fingerprint);

			/** Calculate Tanimoto coefficient for two given binary fingerprints. */
			float calculateSimilarity(std::vector<bool>& fingerprint1, std::vector<bool>& fingerprint2);

			void filterRedundantMolecules(const list<Molecule*>& molecules, float similarity_threshold);

			void filterRedundantMolecules(System& molecules, float similarity_threshold);

			/** Calculate similarity between two fingerprints.\n
			If stddev for function-group counts are specified, then the similarity of position i in the fingerprint-vectors is defined as zero if their absolute difference is larger than the the standard deviation, else as 1-abs(difference_i/stddev_i).
			If no stddev for function-group counts are given, the calculated similarity-value is equal to Tanimoto. */
			float calculateSimilarity(std::vector<Size>& fingerprint1, std::vector<Size>& fingerprint2, std::vector<float>* stddev);

			/** Returns the names of the functional groups that have been read from the SMARTS-file */
			const std::vector<String>& getFunctionalGroupNames();


		protected:

			std::vector<std::vector<Size> > fingerprints_;
			std::vector<String> smarts_;
			std::vector<String> smart_names_;

			SmartsMatcher matcher_;

			/** Generate a hash-ID for a given molecule-path. \n
			This function was adapted from OpenBabel (finger2.cpp). */
			void generatePathHash_(std::vector<Size>& path, Size& hash);

			bool generatePathFingerprint_(const Atom* atom, std::vector<Size>& path, std::set<const Bond*>& path_bonds, 
			                              std::vector<bool>& fingerprint);

	};
}

#endif
