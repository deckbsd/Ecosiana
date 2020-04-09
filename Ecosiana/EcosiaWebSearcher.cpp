#include "EcosiaWebSearcher.h"

list<EcosiaWebResult> WINAPI EcosiaWebSearcher::simple_web_research(const string research)
{
	string parameters;

	return do_search(research, parameters);
}

list<EcosiaWebResult> WINAPI EcosiaWebSearcher::web_research(string research, ecosia_web_parameters params)
{
	return do_search(research,params.get_string_parameter());
}

list<EcosiaWebResult> WINAPI EcosiaWebSearcher::do_search(string research, string parameters)
{
	return EcosiaSearcher::do_search<EcosiaWebResult>(research, parameters, ECOSIA_SEARCH_PAGE, _web_parser, &EcosiaWebHtmlParser::parse);
}

int EcosiaWebSearcher::get_total_searches()
{
	return EcosiaSearcher::get_total_searches();
}

EcosiaWebSearcher::EcosiaWebSearcher()
{
}


EcosiaWebSearcher::~EcosiaWebSearcher()
{
}
