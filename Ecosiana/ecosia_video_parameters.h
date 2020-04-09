#pragma once

#include "ecosia_parameters.h"

class ecosia_video_parameters : public ecosia_parameters
{

private:
	string WINAPI get_resolution_parameter();
	string WINAPI get_video_length_parameter();
	string WINAPI get_pricing_parameter();
public:

	string resolution;
	string video_length;
	string pricing;

	string WINAPI get_string_parameter();

	ecosia_video_parameters();
	~ecosia_video_parameters();
};

