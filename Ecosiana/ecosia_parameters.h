#pragma once

#include <Windows.h>
#include <string>

using namespace std;

class ecosia_parameters
{

	string WINAPI get_page_parameter();
	string WINAPI get_filter_parameter();
protected :
	string WINAPI get_string_parameter();
public:
	int page;

	ecosia_parameters();
	~ecosia_parameters();
};

