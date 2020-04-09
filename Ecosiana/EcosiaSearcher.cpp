#include "EcosiaSearcher.h"


string WINAPI EcosiaSearcher::url_encode(const string &value) {
	ostringstream escaped;
	size_t index = 0;
	escaped.fill('0');
	escaped << hex;

	for (string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
		string::value_type c = (*i);

		// Keep alphanumeric and other accepted characters intact
		if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
		{
			escaped << c;
			continue;
		}
		if (c == ' ')
		{
			escaped << '+';
			continue;
		}

		// Any other characters are percent-encoded
		escaped << uppercase;
		escaped << '%' << setw(2) << int((unsigned char)c);
		escaped << nouppercase;
	}

	return escaped.str();
}

template <typename T, typename M>
list<T> WINAPI EcosiaSearcher::do_search(string research, string parameters, string page, M& parser, void (M::*parse)(char*, list<T> &))
{
	BYTE* r_buffer;
	DWORD response_len;
	string web_research;
	LPWSTR w_web_research;
	DWORD dw_w_research_len;
	DWORD cookie_len = 250;
	wchar_t* cookie;
	list<T> results;
	int ret_req;

	web_research = url_encode(research);

	web_research.insert(0, page);

	if (!parameters.empty())
	{
		web_research += parameters;
	}

	dw_w_research_len = (web_research.length() + 1) * sizeof(WCHAR);

	w_web_research = new WCHAR[dw_w_research_len];

	MultiByteToWideChar(CP_ACP, NULL, web_research.c_str(), -1, w_web_research, dw_w_research_len);

	if (!_session.get_cookie().empty())
	{
		cookie_len = _session.get_cookie().length();
		cookie_len++;
		//cookie_len *= sizeof(wchar_t);

		cookie = new wchar_t[cookie_len];
		*cookie = { 0 };

		wcsncpy_s(cookie, cookie_len, _session.get_cookie().c_str(), cookie_len);

	}
	else
	{
		cookie = new wchar_t[cookie_len];
		*cookie = { 0 };
	}
	

	if (ret_req = _requester.EcosiaGetHttpRequest(w_web_research, NULL, 0, &r_buffer, &response_len, cookie, &cookie_len) == ERROR_INSUFFICIENT_BUFFER)
	{
		delete cookie;
		cookie = new wchar_t[cookie_len];

		*cookie = { 0 };
		ret_req = _requester.EcosiaGetHttpRequest(w_web_research, NULL, 0, &r_buffer, &response_len, cookie, &cookie_len);
	}

	if (*(cookie) != 0)
	{
		_session.set_cookie(cookie);
	}

	if (ret_req == REQUEST_SUCCESS && *((char*)r_buffer) != 0)
	{
		(parser.*parse)((char*)r_buffer, results);
	}

	delete cookie;
	delete w_web_research;

	return results;
}


int EcosiaSearcher::get_total_searches()
{
	return _session.get_total_searches();
}

template list<EcosiaVideoResult> WINAPI EcosiaSearcher::do_search(string research, string parameters, string page, EcosiaVideoHtmlParser &parser, void (EcosiaVideoHtmlParser::*parse)(char*, list<EcosiaVideoResult> &));
template list<EcosiaWebResult> WINAPI EcosiaSearcher::do_search(string research, string parameters, string page, EcosiaWebHtmlParser &parser, void (EcosiaWebHtmlParser::*parse)(char*, list<EcosiaWebResult> &));

EcosiaSearcher::EcosiaSearcher()
{
}


EcosiaSearcher::~EcosiaSearcher()
{
}
