#include "EcosiaVideoSearcher.h"

list<EcosiaVideoResult> WINAPI EcosiaVideoSearcher::simple_video_research(string research)
{
	string parameters;

	return do_search(research, parameters);
}

list<EcosiaVideoResult> WINAPI EcosiaVideoSearcher::video_research(string research, ecosia_video_parameters params)
{
	return do_search(research, params.get_string_parameter());
}

list<EcosiaVideoResult> WINAPI EcosiaVideoSearcher::do_search(string research, string parameters)
{
	return EcosiaSearcher::do_search<EcosiaVideoResult>(research, parameters, ECOSIA_VIDEO_PAGE, _video_parser, &EcosiaVideoHtmlParser::parse);
}


EcosiaVideoSearcher::EcosiaVideoSearcher()
{
}


EcosiaVideoSearcher::~EcosiaVideoSearcher()
{
}
