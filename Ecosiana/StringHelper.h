#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <locale>

using namespace std;

// trim from left
inline std::string ltrim(std::string s, const char* t = " \t\n\r\f\v")
{
	s.erase(0, s.find_first_not_of(t));
	return s;
}

// trim from right
inline std::string rtrim(std::string s, const char* t = " \t\n\r\f\v")
{
	s.erase(s.find_last_not_of(t) + 1);
	return s;
}

// trim from left & right
inline std::string trim(std::string s, const char* t = " \t\n\r\f\v")
{
	return ltrim(rtrim(s, t), t);
}

static std::string narrow(const std::wstring& str)
{
	ostringstream stm;
	const ctype<char>& ctfacet =
		use_facet< ctype<char> >(stm.getloc());
	for (size_t i = 0; i<str.size(); ++i)
		stm << ctfacet.narrow(str[i], 0);
	return stm.str();
}
