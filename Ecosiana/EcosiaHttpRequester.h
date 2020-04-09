#pragma once

#include "HttpRequester.h"

#define ECOSIA_HTTP_URL L"http://www.ecosia.org"
#define ECOSIA_REQUEST_URL L"www.ecosia.org"
#define GET_REQUEST L"GET"
#define REQUEST_PORT 443

class EcosiaHttpRequester : protected HttpRequester
{
public:
	DWORD WINAPI EcosiaGetHttpRequest(WCHAR *resource, BYTE *s_buffer, DWORD sbuf_len, BYTE **r_buffer, DWORD *response_len, wchar_t *cookies, DWORD* cookie_len);
	EcosiaHttpRequester();
	~EcosiaHttpRequester();
};

