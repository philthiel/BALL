//_new_file_header


#ifndef BALL_CORE_MOLMEC_MMFF94_PROCESSORS_H
#define BALL_CORE_MOLMEC_MMFF94_PROCESSORS_H

#include <BALL/core/datatype/hashSet.h>
#include <BALL/core/datatype/stringHashMap.h>
#include <BALL/core/kernel/bond.h>
#include <BALL/core/molmec/mmff94/MMFF94Parameters.h>
#include <BALL/core/structure/atomTyper.h>

#include <vector>


namespace BALL 
{
	using std::vector;

	class MMFF94ESParameters;
	class Molecule;
	class System;

	///
	class BALL_EXPORT MMFF94AtomTyper
		: public AtomTyper
	{
		public:

		struct AromaticType
		{
			String new_type;
			Position atomic_number;
			bool     cation;
			bool     anion;
		};

		BALL_CREATE(MMFF94AtomTyper)

		///
		MMFF94AtomTyper();

		///
		MMFF94AtomTyper(const MMFF94AtomTyper& t);

		///
		virtual ~MMFF94AtomTyper() {};

		///
		virtual void assignTo(System& s);

		/// Read the hydrogen matching from MMFFHDEF.PAR
		virtual bool setupHydrogenTypes(Parameters& p, const String& section);

		/// Read the matching from ID to numerical type from MFFSYMB.PAR
		virtual bool setupSymbolsToTypes(Parameters& p, const String& section);

		/// Read the matching from general ID to ID in aromatic rings
		virtual bool setupAromaticTypes(Parameters& p, const String& section);

		///
		void collectHeteroAtomTypes(const MMFF94AtomTypes& atom_types);

		protected:

		bool assignAromaticType_5_(Atom& atom, Position L5, bool anion, bool cation);

		StringHashMap<String> partner_type_to_htype_;
		StringHashMap<Position> id_to_type_;
		HashMap<String, AromaticType> aromatic_types_5_map_;
		HashSet<String> cation_atoms_;
		MMFF94AtomTypes* atom_types_;
		HashSet<Position> hetero_atom_types_;
	};


	/**	Assign MMFF94 Charges
      \ingroup  MMFF94
	*/
	class BALL_EXPORT MMFF94ChargeProcessor
		:	public UnaryProcessor<Atom>
	{
		public:

		BALL_CREATE(MMFF94ChargeProcessor)

		///
		MMFF94ChargeProcessor();

		///
    MMFF94ChargeProcessor(const MMFF94ChargeProcessor& cp);
 
		///
		virtual ~MMFF94ChargeProcessor() {};

		///
		const MMFF94ChargeProcessor& operator = (const MMFF94ChargeProcessor& cp)
			;

		///
		virtual void clear()
			;
		
		///
		virtual bool start();

		///
		virtual bool finish();

		///
		virtual Processor::Result operator () (Atom& atom);

		///
		void assignFormalCharge(Atom& atom);
		
		///
		const HashSet<Atom*>& getUnassignedAtoms() { return unassigned_atoms_;}

		///
		void setESParameters(const MMFF94ESParameters& es) { es_parameters_ = &es; }

		///
		void setup(const String& filename);

		///
		void setAromaticRings(const vector<HashSet<Atom*> >& rings) { aromatic_rings_ = rings;}

		protected:

		void assignPartialCharges_();

		vector<Atom*> 							atoms_;
		HashSet<Atom*> 							unassigned_atoms_;
		const MMFF94ESParameters* 	es_parameters_;
		HashMap<String, float> 			types_to_charges_;
		HashSet<String> 						rule_types_;
		vector<HashSet<Atom*> > 		aromatic_rings_;
	};
	
} // namespace BALL

#endif // BALL_CORE_MOLMEC_MMFF94_PROCESSORS_H
