#pragma once

#include <string>
#include <regex>

#include "StringHelper.h"

#define COOKIE_ITEM_REGEX ".*:t=([0-9]+)[:;].*"
#define COOKIE_ITEM_REGEX_BEGIN_CASE "ECFG=t=([0-9]+):.*"


class Cookie_create
{
public :
	std::string Message;

	Cookie_create(std::string message);
};

class Cookie
{
private:
	std::wstring content;
	std::string c_content;
	int cookie_len;
	int total_searches = 0;

	std::string Cookie::get_match(const char* find, const std::string str);

public:
	Cookie(const wchar_t * text);
	~Cookie();

	int get_total_searches();
	std::wstring get_cookie_txt_unicode();
	std::string get_cookie_txt_c();

};

