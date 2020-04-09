#pragma once

#include "Cookie.h"

class Session
{

private :
	Cookie* session_cookie;

public:
	Session();
	~Session();

	void set_cookie(wchar_t* cookie_txt);
	const std::wstring get_cookie();
	int get_total_searches();
	
};

