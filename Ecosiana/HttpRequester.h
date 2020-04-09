#pragma once
#include <Windows.h>
#include <winhttp.h>

#pragma comment(lib,"Winhttp")

#define REQUEST_SUCCESS 0
#define REQUEST_BAD_COOKIE 1
#define REQUEST_NETWORK_PROBLEM 2
#define ERROR_HTTP_HEADER_NOT_FOUND 12150

class HttpRequester
{
private:
	void WINAPI HttpRequester::WinHttpSetup(WCHAR *DestURL);
	BOOL WINAPI HttpRequester::WinHttpClose();
protected:
	HINTERNET http_local_session;

	void WINAPI HttpRequester::OpenRequester(WCHAR *DestURL);
	DWORD WINAPI HttpRequest(WCHAR *Host, WCHAR *verb, WCHAR *resource, DWORD port, BYTE *s_buffer, DWORD sbuf_len, BYTE **r_buffer, DWORD *response_len, wchar_t *cookies_w, DWORD* cookie_len);

public:
	HttpRequester();
	~HttpRequester();
};

