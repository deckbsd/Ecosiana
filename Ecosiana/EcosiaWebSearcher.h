#pragma once
#include <list>

#include "ecosia_web_parameters.h"
#include "EcosiaSearcher.h"
#include "EcosiaWebHtmlParser.h"
#include "EcosiaWebResult.h"

class EcosiaWebSearcher : public EcosiaSearcher
{
	EcosiaWebHtmlParser _web_parser;

	list<EcosiaWebResult> WINAPI do_search(string research, string parameters);

public:

	int get_total_searches();

	list<EcosiaWebResult> WINAPI simple_web_research(string research);
	list<EcosiaWebResult> WINAPI web_research(string research, ecosia_web_parameters params);

	EcosiaWebSearcher();
	~EcosiaWebSearcher();
};

