
#include "ecosia_video_parameters.h"

string WINAPI ecosia_video_parameters::get_resolution_parameter()
{
	return "&resolution=" + resolution;
}
string WINAPI ecosia_video_parameters::get_video_length_parameter()
{
	return "&videoLength=" + video_length;
}
string WINAPI ecosia_video_parameters::get_pricing_parameter()
{
	return "&pricing=" + pricing;
}

string WINAPI ecosia_video_parameters::get_string_parameter()
{
	return get_resolution_parameter() + get_video_length_parameter() + get_pricing_parameter() + ecosia_parameters::get_string_parameter();
}


ecosia_video_parameters::ecosia_video_parameters()
{
}


ecosia_video_parameters::~ecosia_video_parameters()
{
}
