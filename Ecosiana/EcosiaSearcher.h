#pragma once
#include <Windows.h>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <string>
#include <list>

#include "EcosiaHttpRequester.h"
#include "EcosiaWebHtmlParser.h"
#include "EcosiaVideoHtmlParser.h"
#include "EcosiaWebResult.h"
#include "EcosiaVideoResult.h"
#include "Session.h"

#define ECOSIA_SEARCH_PAGE "/search?q="

using namespace std;

class EcosiaSearcher
{

protected :
	EcosiaHttpRequester _requester;
	Session _session;

	string WINAPI url_encode(const string &value);

	template <typename T, typename M>
	list<T> WINAPI do_search(string research, string parameters, string page, M& parser, void (M::*parse)(char* , list<T> &));

	int get_total_searches();

public:

	EcosiaSearcher();
	~EcosiaSearcher();
};

