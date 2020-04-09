
#include "ecosia_parameters.h"

string WINAPI ecosia_parameters::get_page_parameter()
{
	return "&p=" + to_string(page - 1);
}

string WINAPI ecosia_parameters::get_filter_parameter()
{
	return "&f=true";
}

string WINAPI ecosia_parameters::get_string_parameter()
{
	return get_page_parameter() + get_filter_parameter();
}

ecosia_parameters::ecosia_parameters()
{
}


ecosia_parameters::~ecosia_parameters()
{
}
