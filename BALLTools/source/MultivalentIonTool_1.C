// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#include <BALL/FORMAT/molFileFactory.h>
#include <BALL/FORMAT/genericMolFile.h>
#include <BALL/FORMAT/PDBFile.h>
#include <BALL/KERNEL/forEach.h>
#include <BALL/KERNEL/molecule.h>
#include <BALL/KERNEL/system.h>
#include <BALL/FORMAT/commandlineParser.h>
#include <BALL/STRUCTURE/structureMapper.h>
#include <BALL/XRAY/crystalGenerator.h>

#include <BALL/COMMON/version.h>


using namespace BALL;
using namespace std;


bool mapping(Protein& p1, Protein& p2, float rmsd_cutoff)
{
	double upper = 8.0;
	double lower = 4.0;
	double tolerance = 0.6;

	map<String, Position> type_map;
	type_map["ALA"] = 0;
	type_map["GLY"] = 0;
	type_map["VAL"] = 0;
	type_map["LEU"] = 0;
	type_map["ILE"] = 0;
	type_map["SER"] = 0;
	type_map["CYS"] = 0;
	type_map["THR"] = 0;
	type_map["MET"] = 0;
	type_map["PHE"] = 0;
	type_map["TYR"] = 0;
	type_map["TRP"] = 0;
	type_map["PRO"] = 0;
	type_map["HIS"] = 0;
	type_map["LYS"] = 0;
	type_map["ARG"] = 0;
	type_map["ASP"] = 0;
	type_map["GLU"] = 0;
	type_map["ASN"] = 0;
	type_map["GLN"] = 0;

	Size no_ca;
	double rmsd = -1.0;
	StructureMapper	mapper;

	Matrix4x4 T = mapper.mapProteins(p1, p2, type_map, no_ca, rmsd, upper, lower, tolerance);

	if (rmsd < rmsd_cutoff)
	{
		mapper.setTransformation(T);
		p1.apply(mapper);

		return true;
	}

	return false;
}


void getIonResidues(const String& ion_id, System& s, vector<Residue*>& ions)
{
	ResidueIterator r_it;
	BALL_FOREACH_RESIDUE(s, r_it)
	{
		if (r_it->getName() == ion_id)
		{
			ions.push_back(&(*r_it));
		}
	}
}


void getIonContactChains(const String& ion_id, System& s, vector<Protein>& contacts, float c_cutoff, unsigned int min_c, float i_cutoff, vector<vector<String> >& contact_residues)
{
	vector<Residue*> ions;
	getIonResidues(ion_id, s, ions);

	AtomIterator a_it;
	ResidueIterator r_it;
	ChainIterator c_it;
	for (unsigned int i=0; i!=ions.size(); ++i)
	{
		Protein p;
		vector<String> tmp;

		Atom* ion = ions[i]->getAtom(0);

		BALL_FOREACH_CHAIN(s, c_it)
		{
			bool chain_contact = false;

			BALL_FOREACH_RESIDUE(*c_it, r_it)
			{
				bool has_contact = false;

				BALL_FOREACH_ATOM(*r_it, a_it)
				{
					float distance = ion->getDistance(*a_it);

					if (distance <= c_cutoff)
					{
						chain_contact = true;

						if (distance <= i_cutoff)
						{
							has_contact = true;
							break;
						}
					}
				}

				if (has_contact && r_it->isAminoAcid())
				{
					tmp.push_back(c_it->getName() + ":" + r_it->getName());
				}
			}

			if (chain_contact)
			{
				p.insert(*(new Chain(*c_it)));
			}
		}

		if (p.countChains() > 2)
		{
			contacts.push_back(p);
			contact_residues.push_back(tmp);
		}
	}
}


void removeDistantResidues(const String& ion_id, System& s, float c_cutoff)
{
	vector<Residue*> ions;
	getIonResidues(ion_id, s, ions);

	// Delete residues too far from ions
	s.select();

	AtomIterator a_it;
	ResidueIterator r_it;
	for (unsigned int i=0; i!=ions.size(); ++i)
	{
		Atom* ion = ions[i]->getAtom(0);
		ions[i]->deselect();

		BALL_FOREACH_RESIDUE(s, r_it)
		{
			BALL_FOREACH_ATOM(*r_it, a_it)
			{
				if (&(*a_it) != ion)
				{
					float distance = ion->getDistance(*a_it);

					if (distance <= c_cutoff)
					{
						r_it->deselect();
						break;
					}
				}
			}
		}
	}

	s.removeSelected();

	return;
}


void generateSymmetryMates(const String& ion_id, System& s, float c_cutoff)
{
	vector<Residue*> ions;
	getIonResidues(ion_id, s, ions);

	CrystalGenerator cg;
	cg.setSystem(&s);
	list<System*> packing = cg.generatePacking(-1 , 1, -1 , 1, -1 , 1);

	Protein *prot;
	Chain *tmp_chain;
	vector<Protein*> to_insert;
	for (unsigned int i=0; i!=ions.size(); ++i)
	{
		Atom* ion = ions[i]->getAtom(0);

		prot = new Protein;

		for (list<System*>::iterator it=packing.begin(); it!=packing.end(); ++it)
		{
			ProteinIterator pit;
			ChainIterator cit;
			AtomIterator ait, ait2;
			BALL_FOREACH_PROTEIN(**it, pit)
			{
				BALL_FOREACH_CHAIN(*pit, cit)
				{
					BALL_FOREACH_ATOM(*cit, ait)
					{
						float distance = ait->getDistance(*ion);

						if (distance < c_cutoff)
						{
							tmp_chain = new Chain(*cit);
							tmp_chain->setName("S");

							BALL_FOREACH_ATOM(*tmp_chain, ait2)
							{
								if (ait2->getResidue()->getName() == ion_id)
								{
									ait2->getResidue()->select();
								}
							}

							if (tmp_chain->isSelected())
							{
								delete tmp_chain;
							}
							else
							{
								tmp_chain->removeSelected();
								prot->insert(*tmp_chain);
							}

							break;
						}
					}
				}
			}
		}

		ChainIterator cit1, cit2;
		BALL_FOREACH_CHAIN(s, cit1)
		{
			Atom* a1 = cit1->getPDBAtom(0);
			BALL_FOREACH_CHAIN(*prot, cit2)
			{
				Atom* a2 = cit2->getPDBAtom(0);
				if (a1->getDistance(*a2) < 0.01)
				{
					cit2->select();
				}
			}

		}

		if (prot->isSelected())
		{
			delete prot;
		}
		else
		{
			prot->removeSelected();

			if (prot->countChains() > 0)
			{
				to_insert.push_back(prot);
			}
			else
			{
				delete prot;
			}
		}
	}

	for (unsigned int i=0; i!=to_insert.size(); ++i)
	{
		s.insert(*to_insert[i]);
	}
}


void cleanupSystem(const String& ion_id, System& s)
{
	ResidueIterator rit;
	BALL_FOREACH_RESIDUE(s, rit)
	{
		if (!(rit->isAminoAcid() || rit->getName() == "HOH" || rit->getName() == ion_id))
		{
			rit->select();
		}
	}

	s.removeSelected();
}


int main(int argc, char* argv[])
{
	CommandlineParser par("MultivalentIonTool_1", "", VersionInfo::getVersion(), String(__DATE__), "Analysis");
	par.registerParameter("i", "input file", INFILE, true);
	par.registerParameter("c", "clipping cutoff around ion", DOUBLE, false, "8.0");
	par.registerParameter("d", "contact distance for ion", DOUBLE, false, "2.5");
	par.registerParameter("r", "rmsd cutoff", DOUBLE, false, "2.0");
	par.registerParameter("n", "minimum number of required contact chains", INT, false, "2");

	String manual = "This tool extracts the desired ions and surrounding protein chains.";

	par.setToolManual(manual);

	par.setSupportedFormats("i","pdb");
	par.parse(argc, argv);

	// Get name of input PDB file
	String infile = par.get("i");

	// Distance cutoff
	float c_cutoff = par.get("c").toFloat();
	float i_cutoff = par.get("d").toFloat();
	float rmsd_cutoff = par.get("r").toFloat();
	unsigned int min_c = par.get("n").toInt();

	// Get name of ion to be parsed
	vector<String> split;
	FileSystem::baseName(infile).split(split, "_");
	String ion_id = split[0];
	String pdb_id = split[1].before(".");

	// Read PDB file into system
	System s;

	PDBFile inf(infile, File::MODE_IN);
	inf >> s;
	inf.close();

	Log.info() << "++ System read" << endl;


	// Clean up system
	// Remove everything but protein, ions of interest, and water
	cleanupSystem(ion_id, s);


	// Generate symmetry mates with ion contacts
	generateSymmetryMates(ion_id, s, c_cutoff);

	Log.info() << "++ Symmetry mates generated" << endl;


	// Remove distant residues from system
	removeDistantResidues(ion_id, s, c_cutoff);

	Log.info() << "++ Clipped around ions" << endl;


	// Retrieve ion contact chains
	vector<Protein> contacts;
	vector<vector<String> > contact_residues;
	getIonContactChains(ion_id, s, contacts, c_cutoff, min_c, i_cutoff, contact_residues);

	cout << contacts.size() << endl;

	// Analyse similarity
	set<unsigned int> reduced;
	for (unsigned int i=0; i!=contacts.size(); ++i)
	{
		reduced.insert(i);
	}

	set<unsigned int> mapped;
	for (unsigned int i=0; i!=contacts.size(); ++i)
	{
		if (mapped.count(i) == 0)
		{
			for (unsigned int j=0; j!=contacts.size(); ++j)
			{
				if (i != j)
				{
					if (mapped.count(j) == 0)
					{
						bool success = mapping(contacts[j], contacts[i], rmsd_cutoff);

						if (success)
						{
							mapped.insert(j);
							reduced.erase(j);
						}
					}
				}
			}

			mapped.insert(i);
		}
	}


	// Check if their are indeed interacting residues
	// If not skip entry

	unsigned int contact_count = 0;
	for (unsigned int i=0; i!=contact_residues.size(); ++i)
	{
		contact_count += contact_residues[i].size();
	}

	if(contact_count == 0)
	{
		// No interactions - skip
		return 0;
	}

	PDBFile out(ion_id + "_" + pdb_id + "_processed.pdb", File::MODE_OUT);
	out << s;
	out.close();

	String outfile_base = ion_id + "_" + pdb_id + "_mapped_";
	for (unsigned int i=0; i!=contacts.size(); ++i)
	{
		PDBFile out(outfile_base + String(i) + ".pdb", File::MODE_OUT);
		out << contacts[i];
		out.close();
	}

	unsigned int count = 0;
	outfile_base = ion_id + "_" + pdb_id + "_unique_";
	for (set<unsigned int >::iterator it=reduced.begin(); it!=reduced.end(); ++it)
	{
		PDBFile out1(outfile_base + String(count) + ".pdb", File::MODE_OUT);
		out1 << contacts[*it];
		out1.close();

		File out2(outfile_base + String(count) + ".txt", File::MODE_OUT);

		out2 << contact_residues[*it].size() << " ";
		for (unsigned int i=0; i!=contact_residues[*it].size(); ++i)
		{
			out2 << contact_residues[*it][i];

			if (i < contact_residues[*it].size() - 1)
			{
				out2 << ",";
			}
		}

		out2.close();

		++count;
	}

	return 0;
}
