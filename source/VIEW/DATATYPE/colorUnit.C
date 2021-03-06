// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#include <BALL/VIEW/DATATYPE/colorUnit.h>
#include <cstdio>
#include <BALL/COMMON/rtti.h>

using namespace std;

namespace BALL
{

	namespace VIEW
	{

		ColorUnit::NotInHexFormat::NotInHexFormat(const char* file, int line, const string& data)
			:	Exception::GeneralException(file, line, string("NotInHexFormat"), string("value was not in hex format: ") + data)
		{
		}

		ColorUnit::ColorUnit()
			:	value_((float)0)
		{
		}

		ColorUnit::ColorUnit(const ColorUnit& color)
			:	value_(color.value_)
		{
		}

		ColorUnit::ColorUnit(const char *char_ptr)
		{
			value_ = hexToFloat_(char_ptr);
		}

		ColorUnit::ColorUnit(const String& s)
		{
			value_ = hexToFloat_(s.c_str());
		}

		ColorUnit::ColorUnit(const unsigned char c)
		{
			value_ = (float)c / (float)255;
		}

		ColorUnit::ColorUnit(const short s)
		{
			if ((s < 0) || (s > 255))
			{
				throw ::BALL::Exception::InvalidRange(__FILE__, __LINE__, (float) s);
			}

			value_ = (float)s / (float)255;
		}

		ColorUnit::ColorUnit(const unsigned short us)
		{
			if (us > 255)
      {
				throw ::BALL::Exception::InvalidRange(__FILE__, __LINE__, us);
			}

			value_ = (float)us / (float)255;
		}

		ColorUnit::ColorUnit(const int i)
		{
			/*
			if ((i < 0) || (i > 255))
      {
				throw ::BALL::Exception::InvalidRange(__FILE__, __LINE__, i);
			}
			*/

			value_ = (float)i / (float)255;
		}

		ColorUnit::ColorUnit(const unsigned int ui)
		{
			/*
			if (ui > 255)
      {
				throw ::BALL::Exception::InvalidRange(__FILE__, __LINE__, ui);
			}
			*/

			value_ = (float)ui / (float)255;
		}

		ColorUnit::ColorUnit(const long l)
		{
			/*
			if ((l < 0) || (l > 255))
      {
				throw ::BALL::Exception::InvalidRange(__FILE__, __LINE__, l);
			}
			*/

			value_ = (float)l / (float)255;
		}

		ColorUnit::ColorUnit(const unsigned long ul)
		{
			/*
			if (ul > 255)
      {
				throw ::BALL::Exception::InvalidRange(__FILE__, __LINE__, ul);
			}
			*/
 
			value_ = (float)ul / (float)255;
		}

		ColorUnit::ColorUnit(const float f)
		{
			/*
			if ((f < 0.0) || (f > 1.0))
      {
				throw ::BALL::Exception::InvalidRange(__FILE__, __LINE__, f);
			}
			*/

			value_ = f;
		}

		ColorUnit::ColorUnit(const double d)
		{
			/*
			if ((d < 0.0) || (d > 1.0))
      {
				throw ::BALL::Exception::InvalidRange(__FILE__, __LINE__, d);
			}
			*/

			value_ = (float)d;
		}

		ColorUnit::~ColorUnit()
		{
			#ifdef BALL_VIEW_DEBUG
				cout << "Destructing object " << (void *)this << " of class " 
						 << RTTI::getName<ColorUnit>() << endl;
			#endif 
		}

		void ColorUnit::clear()
		{
			value_ = (float)0;
		}

		void ColorUnit::set(const ColorUnit& color)
		{
			value_ = color.value_;
		}

		const ColorUnit& ColorUnit::operator = (const ColorUnit& color)
		{
			set(color);

			return *this;
		}

		void ColorUnit::set(const char* char_ptr)
		{
			value_ = hexToFloat_(char_ptr);
		}

		const ColorUnit& ColorUnit::operator = (const char* char_ptr)
		{
			set(char_ptr);

			return *this;
		}
			
		void ColorUnit::get(char* char_ptr) const
		{
			sprintf(char_ptr, "%x", (unsigned char)(value_ * 255.0));
		}

		void ColorUnit::set(const String& s)
		{
			value_ = hexToFloat_(s.c_str());
		}

		const ColorUnit& ColorUnit::operator = (const String& s)
		{
			set(s);

			return *this;
		}
			
		void ColorUnit::get(String& values) const
		{
			char temp[4];

			sprintf(&temp[0], "%x", (unsigned char)(value_ * 255.0));

			values.set(&temp[0]);
		}

		void ColorUnit::set(const unsigned char c)
		{
			value_ = (float)c / (float)255;
		}

		const ColorUnit& ColorUnit::operator = (const unsigned char c)
		{
			set(c);

			return *this;
		}

		void ColorUnit::get(unsigned char& c) const
		{
			c = (unsigned char)(value_ * 255.0);
		}

		void ColorUnit::set(const short s)
		{
			/*
			if ((s < 0) || (s > 255))
			{
				throw ::BALL::Exception::InvalidRange(__FILE__, __LINE__, s);
			}
			*/

			value_ = (float)s / (float)255;
		}

		const ColorUnit& ColorUnit::operator = (const short s)
		{
			set(s);

			return *this;
		}

		void ColorUnit::get(short& s) const
		{
			s = (short)(value_ * 255.0);
		}

		void ColorUnit::set(const unsigned short us)
		{
			/*
			if (us > 255)
      {
				throw ::BALL::Exception::InvalidRange(__FILE__, __LINE__, us);
			}
			*/

			value_ = (float)us / (float)255;
		}

		const ColorUnit& ColorUnit::operator = (const unsigned short us)
		{
			set(us);

			return *this;
		}

		void ColorUnit::get(unsigned short& us) const
		{
			us = (unsigned short)(value_ * 255.0);
		}

		void ColorUnit::set(const int i)
		{
			/*
			if ((i < 0) || (i > 255))
			{
				throw ::BALL::Exception::InvalidRange(__FILE__, __LINE__, i);
			}
			*/

			value_ = (float)i / (float)255;
		}

		const ColorUnit& ColorUnit::operator = (const int i)
		{
			set(i);

			return *this;
		}

		void ColorUnit::get(int& i) const
		{
			i = (int)(value_ * 255.0);
		}

		void ColorUnit::set(const unsigned int ui)
		{
			/*
			if (ui > 255)
      {
				throw ::BALL::Exception::InvalidRange(__FILE__, __LINE__, ui);
			}
			*/

			value_ = (float)ui / (float)255;
		}

		const ColorUnit& ColorUnit::operator = (const unsigned int ui)
		{
			set(ui);

			return *this;
		}

		void ColorUnit::get(unsigned int& i) const
		{
			i = (unsigned int)(value_ * 255.0);
		}

		void ColorUnit::set(const long l)
		{
			/*
			if ((l < 0) || (l > 255))
      {
				throw ::BALL::Exception::InvalidRange(__FILE__, __LINE__, l);
			}
			*/

			value_ = (float)l / (float)255;
		}

		const ColorUnit& ColorUnit::operator = (const long l)
		{
			set(l);

			return *this;
		}

		void ColorUnit::get(long& l) const
		{
			l = (long)(value_ * 255.0);
		}

		void ColorUnit::set(const unsigned long ul)
		{
			/*
			if (ul > 255)
      {
				throw ::BALL::Exception::InvalidRange(__FILE__, __LINE__, ul);
			}
			*/

			value_ = (float)ul / (float)255;
		}

		const ColorUnit& ColorUnit::operator = (const unsigned long ul)
		{
			set(ul);

			return *this;
		}

		void ColorUnit::get(unsigned long& ul) const
		{
			ul = (unsigned long)(value_ * 255.0);
		}

		void ColorUnit::set(const float f)
		{
			/*
			if ((f < 0.0) || (f > 1.0))
      {
				throw ::BALL::Exception::InvalidRange(__FILE__, __LINE__, f);
			}
			*/

			value_ = f;
		}

		const ColorUnit& ColorUnit::operator = (const float f)
		{
			set(f);

			return *this;
		}

		void ColorUnit::get(float& f) const
		{
			f = (float)(value_ * 255.0);
		}

		void ColorUnit::set(const double d)
		{
			/*
			if ((d < 0.0) || (d > 1.0))
      {
				throw ::BALL::Exception::InvalidRange(__FILE__, __LINE__, d);
			}
			*/

			value_ = (float)d;
		}

		const ColorUnit& ColorUnit::operator = (const double d)
		{
			set(d);

			return *this;
		}

		void ColorUnit::get(double& d) const
		{
			d = (double)(value_ * 255.0);
		}

		void ColorUnit::swap(ColorUnit& color)
		{
			float temp = value_;
			value_ = color.value_;
			color.value_ = temp;
		}

		void ColorUnit::dump(ostream& s, Size depth) const
		{
			BALL_DUMP_STREAM_PREFIX(s);

			BALL_DUMP_DEPTH(s, depth);
			BALL_DUMP_HEADER(s, this, this);

			BALL_DUMP_DEPTH(s, depth);
			s << "unit : " << (int)(value_ * 255.0) << endl;

			BALL_DUMP_STREAM_SUFFIX(s);
		}

		istream& operator >> (std::istream& s, ColorUnit& color)
		{
			s >> color.value_;

			return s;
		}

		ostream& operator << (std::ostream& s, const ColorUnit& color)
		{
			s << (int)(color.value_ * 255.0);
			
			return s;
		}

		float ColorUnit::hexToFloat_(const char *char_ptr)
		{
			int number = 0;

			if (strlen(char_ptr) != 2)
			{
				throw ::BALL::Exception::InvalidRange(__FILE__, __LINE__, strlen(char_ptr));
			}

			char c = char_ptr[0];

			if (c >= '0' && c <= '9')
			{
				number += (c - 48) * 16;
			}
			else if (c >= 'a' && c <= 'f')
			{
				number += (c - 87) * 16;
			}
			else if (c >= 'A' && c <= 'F')
			{
				number += (c - 55) * 16;
			}
			else
			{
				throw NotInHexFormat(__FILE__, __LINE__, char_ptr);
			}

			c = char_ptr[1];

			if (c >= '0' && c <= '9')
			{
				number += (c - 48);
			}
			else if (c >= 'a' && c <= 'f')
			{
				number += (c - 97) + 10;
			}
			else if (c >= 'A' && c <= 'F')
			{
				number += (c - 65) + 10;
			}
			else
			{
				throw NotInHexFormat(__FILE__, __LINE__, char_ptr);
			}
			
			return (float)number / (float)255;
		}

#		ifdef BALL_NO_INLINE_FUNCTIONS
#			include <BALL/VIEW/DATATYPE/colorUnit.iC>
#		endif 

	} // namespace VIEW
} // namespace BALL
