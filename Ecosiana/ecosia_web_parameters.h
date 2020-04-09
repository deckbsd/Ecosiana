#pragma once

#include "ecosia_parameters.h"

class ecosia_web_parameters : public ecosia_parameters
{
private:

	string WINAPI get_region_parameter();
	string WINAPI get_language_parameter();

public:

	string region;
	string language;

	string WINAPI get_string_parameter();

	ecosia_web_parameters();
	~ecosia_web_parameters();
};

