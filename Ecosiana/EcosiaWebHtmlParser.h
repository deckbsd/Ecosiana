#pragma once

#include <list>

#include "EcosiaHtmlParser.h"
#include "EcosiaWebResult.h"

class EcosiaWebHtmlParser : public EcosiaHtmlParser
{
public:
	void parse(char* sz_buffer, list<EcosiaWebResult> &ls);
	void WINAPI parse_web_results(GumboNode* html, list<EcosiaWebResult> &ls);

	EcosiaWebHtmlParser();
	~EcosiaWebHtmlParser();
};

