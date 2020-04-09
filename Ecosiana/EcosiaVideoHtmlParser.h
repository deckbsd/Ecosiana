#pragma once

#include <list>

#include "EcosiaHtmlParser.h"
#include "EcosiaVideoResult.h"

class EcosiaVideoHtmlParser : public EcosiaHtmlParser
{
public:

	void parse(char* sz_buffer, list<EcosiaVideoResult> &ls);
	void WINAPI parse_video_results(GumboNode* html, list<EcosiaVideoResult> &ls);

	EcosiaVideoHtmlParser();
	~EcosiaVideoHtmlParser();
};

