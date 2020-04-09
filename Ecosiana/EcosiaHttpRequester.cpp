#include "EcosiaHttpRequester.h"

DWORD WINAPI EcosiaHttpRequester::EcosiaGetHttpRequest(WCHAR *resource, BYTE *s_buffer, DWORD sbuf_len, BYTE **r_buffer, DWORD *response_len, wchar_t* cookies, DWORD *cookie_len)
{
	return HttpRequester::HttpRequest(ECOSIA_REQUEST_URL, GET_REQUEST, resource, REQUEST_PORT, s_buffer, sbuf_len, r_buffer, response_len, cookies, cookie_len);
}

EcosiaHttpRequester::EcosiaHttpRequester()
{
	HttpRequester::OpenRequester(ECOSIA_HTTP_URL);
}


EcosiaHttpRequester::~EcosiaHttpRequester()
{
}
