#include "Cookie.h"

Cookie_create::Cookie_create(std::string message)
{
	Message = message;
}

Cookie::Cookie(const wchar_t * text)
{
	string total;

	content = text;

	c_content = narrow(content);

	total = Cookie::get_match(COOKIE_ITEM_REGEX, c_content);

	if ( !total.empty() )
	{
		total_searches = stoi(total);
	}
	else
	{
		total = Cookie::get_match(COOKIE_ITEM_REGEX_BEGIN_CASE, c_content);
		if (!total.empty())
		{
			total_searches = stoi(total);
		}
		else
		{
			total_searches = 0;
		}
	}
}

std::string Cookie::get_match(const char* find, const std::string str)
{
	std::smatch match;
	std::regex const reg(find);

	if (!std::regex_search(str.begin(), str.end(), match, reg))
	{
		return std::string();
	}
	return match[1];
}

std::wstring Cookie::get_cookie_txt_unicode()
{
	return content;
}

std::string Cookie::get_cookie_txt_c()
{
	return c_content;
}

int Cookie::get_total_searches()
{
	return total_searches;
}


Cookie::~Cookie()
{
}