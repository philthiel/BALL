//_new_file_header


#include <BALL/core/qsar/partialChargeBase.h>

#include <BALL/core/concept/timeStamp.h>
#include <BALL/core/kernel/atomIterator.h>
#include <BALL/core/kernel/bond.h>
#include <BALL/core/kernel/bondIterator.h>
#include <BALL/core/kernel/forEach.h>
#include <BALL/core/kernel/fragment.h>
#include <BALL/core/kernel/PTE.h>
#include <BALL/core/qsar/partialChargeProcessor.h>

#include <utility>

using namespace std;


namespace BALL
{
	PartialChargeBase::PartialChargeBase()
		:	Descriptor()
	{
		data_folder_ = "QSAR/";
	}

	PartialChargeBase::PartialChargeBase(const PartialChargeBase& pcb)
		:	Descriptor(pcb)
	{
		data_folder_ = "QSAR/";
	}

	PartialChargeBase::PartialChargeBase(const String& name)
		:	Descriptor(name)
	{
		data_folder_ = "QSAR/";
	}

	PartialChargeBase::PartialChargeBase(const String& name, const String& unit)
		:	Descriptor(name, unit)
	{
		data_folder_ = "QSAR/";
	}

	PartialChargeBase::~PartialChargeBase()
	{
	}

	PartialChargeBase& PartialChargeBase::operator = (const PartialChargeBase& pcb)
	{
		setName(pcb.getName());
		setUnit(pcb.getUnit());
		data_folder_ = pcb.data_folder_;
		return *this;
	}

  bool PartialChargeBase::isValid_(AtomContainer& ac)
  {
		static HashMap<Handle, PreciseTime> mod_times;
		PreciseTime last_mod = ac.getModificationTime(); 
		Handle mol_handle = ac.getHandle();
		if (mod_times.has(mol_handle))
		{
			if (mod_times[mol_handle] == last_mod)
			{
				return true;
			}
			else
			{
				mod_times[mol_handle] = last_mod;
				return false;
			}
		}
		else
		{
			mod_times.insert(std::make_pair(mol_handle, last_mod));
			return false;
		}
	}

	
	void PartialChargeBase::computeAllDescriptors(AtomContainer& ac)
	{	
		if (!isValid_(ac))
		{
			calculate_(ac);
		}
	}
	
	void PartialChargeBase::setDataFolder(const char* folder)
	{
		data_folder_ = folder;
	}

	void PartialChargeBase::calculate_(AtomContainer& ac)
	{
		// sets partial charges;
		PartialChargeProcessor pcp;
		pcp.setDataFolder(data_folder_.c_str());
		ac.apply(pcp);
	
		//HashMap<Atom*, double>::Iterator it = charges.begin();	
		AtomIterator it = ac.beginAtom();
		// assign the calculated values to the descriptors
		double tot_pos(0), tot_neg(0), rel_pos(0), rel_neg(0), max_charge(0), min_charge(0);	
		for (it = ac.beginAtom(); it != ac.endAtom(); ++it)
		{
			double charge = it->getProperty("PEOEPartialCharge").getDouble();
			if (charge > 0)
			{
				tot_pos += charge;
			} 
			else
			{
				tot_neg += charge;
			}
			if (charge > max_charge)
			{
				max_charge = charge;
			}
			if (charge < min_charge)
			{
				min_charge = charge;
			}
			// set partial charge as atom property
		}

		// this might be paranoid, but you never know
		if (max_charge > 0 && tot_pos > 0)
		{
			rel_pos = max_charge/tot_pos;
		}
		// this might be also paranoid, but you still never know
		if (min_charge < 0 && tot_neg < 0)
		{
			rel_neg = min_charge/tot_neg;
		}
		
		ac.setProperty("TotalPositivePartialCharge", tot_pos);
		ac.setProperty("TotalNegativePartialCharge", tot_neg);
		ac.setProperty("RelPositivePartialCharge", rel_pos);
		ac.setProperty("RelNegativePartialCharge", rel_neg);
	}

} // namespace BALL
