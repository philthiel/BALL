// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#include <BALL/FORMAT/commandlineParser.h>

#ifdef BALL_OS_WINDOWS
	#include <winsock2.h>
#endif

using namespace BALL;
using namespace std;

const String BALL::CommandlineParser::NOT_FOUND = "parameter_not_found";
const list<String> BALL::CommandlineParser::EMTPY_LIST(0);

CommandlineParser::CommandlineParser(String tool_name, String tool_description, String tool_version, String build_date, String category)
{
	max_parname_length_ = 0;
	max_flagname_length_ = 0;
	tool_name_ = tool_name;
	tool_description_ = tool_description;
	tool_version_ = tool_version;
	build_date_ = build_date;
	tool_manual_ = "";
	tool_category_ = category;

	hostname_ = "";
	start_time_ = "";

	char hn[1024];
	hn[1023] = '\0';
	gethostname(hn, 1023);
	hostname_ = String(hn);

	time_t rawtime;
	tm* ptm;
	time(&rawtime);
	ptm = localtime(&rawtime);
	char buffer[150];
	strftime (buffer, 150, "%Y-%m-%d, %X (%Z)", ptm);
	start_time_ = String(buffer);

	// For the moment, register Galaxy's char-escapes here.
	// If necessary, we could create a function to allow switching to other char-escape schemes ...
	escaped_chars_.push_back(make_pair("__gt__", ">"));
	escaped_chars_.push_back(make_pair("__lt__", "<"));
	escaped_chars_.push_back(make_pair("__sq__", "i'"));
	escaped_chars_.push_back(make_pair("__dq__", "\""));
	escaped_chars_.push_back(make_pair("__ob__", "["));
	escaped_chars_.push_back(make_pair("__cb__", "]"));
	escaped_chars_.push_back(make_pair("__oc__", "{"));
	escaped_chars_.push_back(make_pair("__cc__", "}"));
	escaped_chars_.push_back(make_pair("__at__", "@"));
	escaped_chars_.push_back(make_pair("__cn__", "\n"));
	escaped_chars_.push_back(make_pair("__cr__", "\r"));
	escaped_chars_.push_back(make_pair("__tc__", "\t"));

	// init the blacklist
	// "write_par", "par", "help", "ini", "env"
	// write_ini is allowed to be used, but some tools might ignore it
	reserved_params_.insert("write_par");
	reserved_params_.insert("par");
	reserved_params_.insert("h");
	reserved_params_.insert("help");
	reserved_params_.insert("quiet");
	reserved_params_.insert("ini");
	reserved_params_.insert("env");
}

void CommandlineParser::checkAndRegisterParameter(String name, String description, ParameterType type, bool mandatory, String default_value, bool perform_check, bool hidden)
{
	checkParameterName(name, perform_check);

	ParameterDescription pardes;
	pardes.name        = name;
	pardes.description = description;
	pardes.mandatory   = mandatory;
	pardes.type        = type;
	pardes.hidden      = hidden;

	registered_parameters_.insert(make_pair(name, pardes));
	original_parameter_order_.push_back(registered_parameters_.find(name));
	if (default_value != "")
	{
		list<String> alist;
		alist.push_back(default_value);
		parameter_map_[name] = alist;
	}
	Size size = name.size();
	if (type == INFILE)
	{
		size += 9;
	}
	else if (type == OUTFILE)
	{
		size += 10;
	}
	else if (type == BALL::INT)
	{
		size += 6;
	}
	else if (type == DOUBLE || type == STRING)
	{
		size += 9;
	}
	if (size > max_parname_length_) 
  {
		max_parname_length_ = size;
	}
}

void CommandlineParser::registerParameter(String name, String description, ParameterType type, bool mandatory, String default_value, bool hidden)
{
	// add parameter and check if the parameter name is valid
	checkAndRegisterParameter(name, description, type, mandatory, default_value, true, hidden);
}

void CommandlineParser::checkAndRegisterFlag(String name, String description, bool default_gui_value, bool perform_check, bool hidden)
{
	checkParameterName(name, perform_check);

	ParameterDescription pardes;
	pardes.name = name;
	pardes.description = description;
	pardes.mandatory   = false;
	pardes.hidden      = hidden;

	list<String> values;
	values.push_back("0");
	values.push_back("1");

	pardes.type = BALL::INT;

	registered_flags_.insert(make_pair(name, pardes));
	registered_flags_.find(name)->second.allowed_values = values;
	original_flag_order_.push_back(registered_flags_.find(name));

	if (name.size() > max_flagname_length_)
	{
		max_flagname_length_ = name.size();
	}
	if (default_gui_value)
	{
		list<String> alist;
		alist.push_back("1");
		parameter_map_[name] = alist;
	}
}

void CommandlineParser::registerFlag(String name, String description, bool default_gui_value, bool hidden)
{
	checkAndRegisterFlag(name, description, default_gui_value, true, hidden);
}

/// TODO: figure out the meaning of the hard-coded prefixes and remove them!
void CommandlineParser::registerAdvancedParameters(Options& options)
{
	if (   options.getName().hasPrefix("ReferenceArea")
			|| options.getName().hasPrefix("PharmacophoreConstraint") )
	{
		return;
	}

	String category = options.getName();
	if ((category != "") && category != "Docking-Settings")
	{
		for (Options::ConstIterator it = options.begin(); it != options.end(); it++)
		{
			const String& name = it->first;
			checkParameterName(name, true);

			const ParameterDescription* pardes = options.getParameterDescription(name);
			if (!pardes)
			{
				continue;
			}

			registerParameter(name, pardes->description, pardes->type, false, it->second);
			registered_parameters_[name].advanced = true;
			registered_parameters_[name].allowed_values = pardes->allowed_values;
			registered_parameters_[name].category = category;
		}
	}

	for (StringHashMap<Options*>::Iterator it = options.beginSubcategories();
			 it != options.endSubcategories(); it++)
	{
		registerAdvancedParameters(*it->second);
	}
}

void CommandlineParser::setParameterAsAdvanced(String name)
{
	registered_parameters_[name].advanced = true;
}

void CommandlineParser::setParameterRestrictions(String par_name, double min_value, double max_value)
{
	map<String, ParameterDescription>::iterator it = registered_parameters_.find(par_name);
	if (it == registered_parameters_.end())
	{
		throw BALL::Exception::GeneralException(__FILE__,__LINE__,"setParameterRestrictions error","You need to register a parameter before you can set restrictions for it!");
	}
	it->second.allowed_values.clear();
	it->second.allowed_values.push_back(String(min_value));
	it->second.allowed_values.push_back(String(max_value));
}

void CommandlineParser::setParameterRestrictions(String par_name, list<String>& allowed_values)
{
	map<String, ParameterDescription>::iterator it = registered_parameters_.find(par_name);
	if (it == registered_parameters_.end())
	{
		throw BALL::Exception::GeneralException(__FILE__,__LINE__,"setParameterRestrictions error","You need to register a parameter before you can set restrictions for it!");
	}
	it->second.allowed_values.clear();
	it->second.allowed_values = allowed_values;
}

void CommandlineParser::setSupportedFormats(String par_name, String supported_formats)
{
	vector<String> formats;
	supported_formats.split(formats, ",");
	map<String, ParameterDescription>::iterator it = registered_parameters_.find(par_name);
	if (it == registered_parameters_.end())
	{
		throw BALL::Exception::GeneralException(__FILE__,__LINE__,"setSupportedFormats error","You need to register a parameter before you can set supported formats for it!");
	}
	it->second.supported_formats.clear();
	for (Size i=0; i<formats.size(); i++)
	{
		it->second.supported_formats.push_back(formats[i].trim());
	}
}


void CommandlineParser::setOutputFormatSource(String output_parname, String input_parname)
{
	map<String, ParameterDescription>::iterator it = registered_parameters_.find(output_parname);
	if (it == registered_parameters_.end())
	{
		throw BALL::Exception::GeneralException(__FILE__,__LINE__,"setOutputFormatSource error","You need to register a parameter before you can set its format-source!");
	}
	it->second.output_format_source = input_parname;
}


void CommandlineParser::printToolInfo()
{
	if (parameter_map_.find("quiet") != parameter_map_.end())
	{
		return;
	}

	String tool = "| " + tool_name_ + " -- " + tool_description_;
	String version = "| Version: " + tool_version_;
	String build = "| build date: " + build_date_;
	String host = "| execution host: " + hostname_;
	String time = "| execution time: " + start_time_;

	Size max_len = tool.size();

	if (max_len < version.size())
	{
		max_len = version.size();
	}
	if (max_len < build.size())
	{
		max_len = build.size();
	}
	if (max_len < host.size())
	{
		max_len = host.size();
	}
	if (max_len < time.size())
	{
		max_len = time.size();
	}

	Log << endl;
	Log << " " << String('=', max_len) << endl; 
	Log << tool << String(' ', max_len - tool.size()) << " |" << endl;
	Log << "|" << String('=', max_len) << "|" << endl; 
	Log << "|" << String(' ', max_len) << "|" << endl;
	Log << version << String(' ', max_len - version.size()) << " |" << endl;
	Log << build   << String(' ', max_len - build.size()) <<" |" << endl;
	Log << host    << String(' ', max_len - host.size()) << " |" << endl;
	Log << time    << String(' ', max_len - time.size()) << " |" << endl;
	Log << " "     << String('-', max_len) << endl << endl; 
}


void CommandlineParser::parse(int argc, char* argv[])
{
	checkAndRegisterFlag("h", "show program help (also -help)", false, false);
	checkAndRegisterFlag("help", "show help about parameters and flags of this program", false, false);
	checkAndRegisterFlag("quiet", "suppress log messages (error messages are printed)", false, false);
	checkAndRegisterParameter("write_par", "write xml parameter file for this tool", OUTFILE, false, "", false);
	checkAndRegisterParameter("par", "read parameters from parameter-xml-file", INFILE, false, "", false);
	setSupportedFormats("par", "xml");
	setSupportedFormats("write_par", "xml");

	checkAndRegisterParameter("env", "set runtime environment (default cmdline) ", STRING, false, "cmdline", false);

	validateRegisteredFilesHaveFormats();

	// Make a copy of default parameters
	map<String, list<String> > default_values = parameter_map_;
	parameter_map_.clear();

	map<String, vector<String> > keys;
	pair<map<String, vector<String> >::iterator, bool> keys_inserter;
	map<Size, vector<String> > invalids;
	pair<map<Size, vector<String> >::iterator, bool> invalids_inserter;

	String token, key;
	bool key_found = false;

	for (Size index=1; index!=argc; ++index)
	{
		token = argv[index];

		if (token.hasPrefix("-"))
		{
			// Token is a key

			key = token(1);
			keys_inserter = keys.insert(pair<String, vector<String> >(key, vector<String>()));

			if (!keys_inserter.second)
			{
				// Duplicate of an already discovered key - this ambiguouity is invalid
				invalids_inserter = invalids.insert(pair<Size, vector<String> >(1, vector<String>(1, key)));
				if (!invalids_inserter.second)
				{
					(invalids_inserter.first)->second.push_back(key);
				}
			}

			key_found = true;
		}
		else
		{
			// Token is not a key

			if (!key_found)
			{
				// Leading token(s) not being a key is an error

				invalids_inserter = invalids.insert(pair<Size, vector<String> >(2, vector<String>(1, token)));
				if (!invalids_inserter.second)
				{
					(invalids_inserter.first)->second.push_back(token);
				}
			}
			else
			{
				// Token is a value

				keys[key].push_back(token);
			}
		}
	}

	// Check for 'quiet' flag to suppress output
	if (keys.find("quiet") != keys.end())
	{
		parameter_map_.insert(make_pair("quiet", list<String>(1, "1")));
	}

	printToolInfo();

	// Check if errors occurred in parameter parsing
	if (argc < 2)
	{
		printHelp();
		exit(1);
	}

	if (invalids.find(2) != invalids.end())
	{
		Log.error() << "Error [101]: the following parameter is invalid: '" << invalids[2][0] << "'" << endl;
		exit(1);
	}
	if (invalids.find(1) != invalids.end())
	{
		Log.error() << "Error [102]: the following parameter occurs multiple times: '" << invalids[1][0] << "'" << endl;
		exit(1);
	}

	String value;
	vector<String> values;
	map<String, vector<String> >::iterator key_iter;
	pair<map<String, list<String> >::iterator, bool> param_inserter;
	for(key_iter=keys.begin(); key_iter!=keys.end(); ++key_iter)
	{
		key = key_iter->first;
		values = key_iter->second;

		if (registered_flags_.find(key) != registered_flags_.end())
		{
			// Key is a registered flag

			if (values.size() == 0)
			{
				// Valid flag (no parameter values given)
				parameter_map_.insert(make_pair(key, list<String>(1, "1")));
			}
			else
			{
				// Invalid flag (parameter values given)
				Log.error() << "Error [103]: Flag '" << key << "' does not take parameter values." << endl;

				if (parameter_map_.find("quiet") == parameter_map_.end())
				{
					Log << "Use '-help' to display available parameters and flags." << endl;
				}

				exit(1);
			}
		}
		else if (registered_parameters_.find(key) != registered_parameters_.end())
		{
			// Key is a registered parameter

			if (values.size() != 0)
			{
				// Valid parameter (parameter values given)
				param_inserter = parameter_map_.insert(pair<String, list<String> >(key, list<String>()));
				for (Size i=0; i!=values.size(); ++i)
				{
					value = values[i];
					replaceEscapedCharacters_(value);
					param_inserter.first->second.push_back(value);
				}
			}
			else
			{
				// Invalid parameter (no parameter values given)
				Log.error() << "Error [104]: Parameter '" << key << "' has no value(s)." << endl;

				if (parameter_map_.find("quiet") == parameter_map_.end())
				{
					Log << "Use '-help' to display available parameters and flags." << endl;
				}

				exit(1);
			}
		}
		else
		{
			// Key is not registered
			Log.error() << "Error [105]: Key '" << key << "' is unknown (no flag or parameter)." << endl;

			if (parameter_map_.find("quiet") == parameter_map_.end())
			{
				Log << "Use '-help' to display available parameters and flags." << endl;
			}

			exit(1);
		}
	}


	// Do not complain about missing parameters if the user just wants to see the help page.
	if (parameter_map_.find("help") != parameter_map_.end() || parameter_map_.find("h") != parameter_map_.end())
	{
		printHelp();
		exit(0);
	}

	// Do not complain about missing parameters if the user just wants to write ini-file/default values.
	if (parameter_map_.find("write_ini") != parameter_map_.end())
	{
		return;
	}

	String par = get("par");
	String write_par = get("write_par");
	if (par != NOT_FOUND && par != "")
	{
		ParamFile pf(par, ios::in);
		list<pair<String, ParameterDescription> > descriptions;
		String par_toolname = "";
		String par_description = "";
		String par_version = "";
		String par_helptext = "";
		String category = "";
		pf.readSection(par_toolname, par_description, par_version, par_helptext, category, descriptions, parameter_map_);

		if (par_toolname != tool_name_)
		{
			Log.error() << "Error [106]: The specified parameter-file was created for tool '"
						<< par_toolname << "' not for '" << tool_name_
						<< "'. Please make sure to use the correct type of parameter-file!" << endl;
			exit(1);
		}
		pf.close();
	}

	bool write_par_file = false;
	if (write_par != NOT_FOUND && write_par != "")
	{
		write_par_file = true;
	}

	// If no value for a parameter was specified on the command-line, but the 
	// parameter has a default-value, then make sure to use that default-value.
	for (map<String, list<String> >::iterator it = default_values.begin(); it != default_values.end(); it++)
	{
		map<String, list<String> >::iterator search_it = parameter_map_.find(it->first);
		if (search_it == parameter_map_.end() || search_it->second.empty())
		{
			// Default values for flags would make no sense, so ignore them here
			if (!write_par_file && registered_flags_.find(it->first) != registered_flags_.end())
			{
				continue;
			}

			// Mandatory parameters by definition have to be specified ...
			if (!write_par_file && registered_parameters_.find(it->first)->second.mandatory)
			{
				continue;
			}

			parameter_map_[it->first] = it->second;
		}
	}

	if (write_par_file)
	{
		ParamFile pf(write_par, ios::out);
		parameter_map_.erase("write_par");
		list<pair<String, ParameterDescription> > descriptions;

		for (list<MapIterator>::iterator it = original_parameter_order_.begin(); it != original_parameter_order_.end(); it++)
		{
			descriptions.push_back(make_pair((*it)->first, (*it)->second));
		}

		for (list<MapIterator>::iterator it = original_flag_order_.begin(); it != original_flag_order_.end(); it++)
		{
			descriptions.push_back(make_pair((*it)->first, (*it)->second));
		}

		pf.writeSection(tool_name_, tool_description_, tool_version_, tool_manual_, tool_category_, descriptions, parameter_map_);
		pf.close();

		if (parameter_map_.find("quiet") == parameter_map_.end())
		{
			Log << "Tool-parameter file has been written to '" << write_par << "'. Goodbye!" << endl;
		}

		exit(0);
	}

	set<String> missing_parameters;
	for (map < String, ParameterDescription > :: iterator it = registered_parameters_.begin(); it != registered_parameters_.end(); it++)
	{
		if (it->second.mandatory == false) 
		{
			continue;
		}

		if (parameter_map_.find(it->second.name) == parameter_map_.end())
		{
			missing_parameters.insert(it->first);
		}
	}
	if (missing_parameters.size() > 0)
	{
		Log.error() << "Error [107]: The following mandatory parameters are missing:" << endl;

		printHelp(missing_parameters, false);
		exit(1);
	}
}


void CommandlineParser::replaceEscapedCharacters_(String& parameter_value)
{
	for (list<pair<String, String> >::iterator it = escaped_chars_.begin(); it != escaped_chars_.end(); it++)
	{
		parameter_value.substituteAll(it->first, it->second);
	}
}


void CommandlineParser::copyAdvancedParametersToOptions(Options& options)
{
	for (list<MapIterator>::iterator it = original_parameter_order_.begin(); it != original_parameter_order_.end(); it++)
	{
		ParameterDescription& p = (*it)->second;

		if (!p.advanced) continue;

		map<String, list<String> >::iterator search_it = parameter_map_.find(p.name);
		if (search_it != parameter_map_.end())
		{
			Options* option_category = &options;
			if (p.category != "")
			{
				option_category = options.createSubcategory(p.category);
			}
			option_category->set(p.name, search_it->second.front());
		}
	}
}


void CommandlineParser::printHelp(const set<String>& parameter_names, bool show_manual)
{
	if (parameter_map_.find("quiet") != parameter_map_.end() && parameter_names.empty())
	{
		return;
	}

	if (parameter_names.size() == 0 && registered_parameters_.size() > 0)
	{
		Log << "Available parameters are ('*' indicates mandatory parameters): " << endl;
	}

	for (list<MapIterator>::iterator it = original_parameter_order_.begin(); it != original_parameter_order_.end(); it++)
	{
		ParameterDescription& p = (*it)->second;
		if (((parameter_names.size() > 0) && parameter_names.find(p.name) == parameter_names.end()) || p.advanced)
		{
			continue;
		}

		Log << "   ";

		if ((parameter_names.size() == 0) && p.mandatory)
		{
			Log << "*  ";
		}
		else 
		{
		  Log << "   ";
		}

		Log << "-" << p.name;

		String n = "";
		if (p.type == INFILE)
		{
			n = " <in.file>";
		}
		else if (p.type == OUTFILE)
		{
			n = " <out.file>";
		}
		else if (p.type == BALL::INT)
		{
			n = " <int>";
		}
		else if (p.type == DOUBLE)
		{
			n = " <double>";
		}
		else if (p.type == STRING)
		{
			n = " <string>";
		}

		Log << n;

		Size space_size = max_parname_length_+4-p.name.size()-n.size();
		for (Size j = 0; j < space_size; j++)
		{
			Log << " ";
		}
		Log << p.description << endl;
	}

	if (parameter_names.size() == 0 && registered_flags_.size() > 0)
	{
		Log << endl << "Available flags are: " << endl;
	}

	for (list<MapIterator>::iterator it = original_flag_order_.begin(); it != original_flag_order_.end(); it++)
	{
		ParameterDescription& p = (*it)->second;

		if (parameter_names.size() > 0 && parameter_names.find(p.name) == parameter_names.end())
		{
			continue;
		}

		if (p.name == "help")
		{
			continue;
		}

		Log << "      " << "-" << p.name << String(' ', max_flagname_length_ + 4 - p.name.size()) << p.description << endl;
	}

	Log << endl;

	if (show_manual && tool_manual_ != "")
	{
		Log << endl << tool_manual_ << endl << endl << endl;
	}
}


const String& CommandlineParser::get(String name)
{
	map<String, list<String> >::iterator it = parameter_map_.find(name);
	if (it != parameter_map_.end())
	{
		return it->second.front();
	}
	else
	{
		return NOT_FOUND;
	}
}


bool CommandlineParser::has(String name)
{
	if (get(name) != NOT_FOUND)
	{
		return true;
	}
	else
	{
		return false;
	}
}


const list<String>& CommandlineParser::getList(String name)
{
	map<String, list<String> >::iterator it = parameter_map_.find(name);
	if (it != parameter_map_.end())
	{
		return it->second;
	}
	else
	{
		return EMTPY_LIST;
	}
}

const String& CommandlineParser::getStartTime()
{
	return start_time_;
}

void CommandlineParser::setToolManual(const String& manual)
{
	tool_manual_ = manual;
}

const String& CommandlineParser::getStartCommand()
{
	return start_command_;
}

void CommandlineParser::checkParameterName(const String& name, bool perform_check)
{
	if (perform_check && reserved_params_.count(name) != 0)
		{
			throw BALL::Exception::GeneralException(__FILE__,__LINE__,"registerParameter error","The parameter [" + name + "] is part of the reserved parameters. Reserved parameters are: [write_par, par, help, ini, env]");
		}
}

void CommandlineParser::validateRegisteredFilesHaveFormats()
{
	for (map<String, ParameterDescription> :: iterator it = registered_parameters_.begin(); it != registered_parameters_.end(); it++)
	{
		ParameterDescription& p = it->second;
		if (p.type == INFILE || p.type == OUTFILE)
		{
			if (p.supported_formats.empty())
			{
				throw BALL::Exception::GeneralException(__FILE__,__LINE__,"registerParameter error",
						"The parameter [" + p.name + "] has been registerd as a file " +
						"but does not have any supported formats registered.\n"+
						"You can set the supported formats by using CommandlineParser::setSupportedFormats.");
			}
		}

	}
}
