#include "Session.h"



Session::Session()
{
	session_cookie = nullptr;
}


Session::~Session()
{
	delete session_cookie;
}

void Session::set_cookie(wchar_t* cookie_txt)
{
	if (session_cookie != nullptr)
	{
		delete session_cookie;

		session_cookie = nullptr;
	}

	session_cookie = new Cookie(cookie_txt);
}

const std::wstring Session::get_cookie()
{
	if (session_cookie != nullptr)
	{
		return L"Cookie: " + session_cookie->get_cookie_txt_unicode();
	}

	return std::wstring();
}

int Session::get_total_searches()
{
	return session_cookie->get_total_searches();
}
