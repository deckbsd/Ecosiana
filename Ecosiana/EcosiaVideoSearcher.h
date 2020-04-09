#pragma once
#include <list>

#include "EcosiaSearcher.h"
#include "EcosiaVideoResult.h"
#include "EcosiaVideoHtmlParser.h"
#include "ecosia_video_parameters.h"

#define ECOSIA_VIDEO_PAGE "/videos?q="

class EcosiaVideoSearcher : public EcosiaSearcher
{
	EcosiaVideoHtmlParser _video_parser;

	list<EcosiaVideoResult> WINAPI do_search(string research, string parameters);

public:

	list<EcosiaVideoResult> WINAPI simple_video_research(string research);
	list<EcosiaVideoResult> WINAPI video_research(string research, ecosia_video_parameters params);

	EcosiaVideoSearcher();
	~EcosiaVideoSearcher();
};

