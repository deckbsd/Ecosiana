
#include "ecosia_web_parameters.h"

string WINAPI ecosia_web_parameters::get_region_parameter()
{
	return "&region=" + region;
}

string WINAPI ecosia_web_parameters::get_language_parameter()
{
	return "&lang=" + language;
}

string WINAPI ecosia_web_parameters::get_string_parameter() {
	return get_region_parameter() + get_language_parameter() + ecosia_parameters::get_string_parameter();
}


ecosia_web_parameters::ecosia_web_parameters()
{
}


ecosia_web_parameters::~ecosia_web_parameters()
{
}
