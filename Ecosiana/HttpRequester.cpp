#include "HttpRequester.h"

void WINAPI HttpRequester::WinHttpSetup(WCHAR *DestURL)
{
	WINHTTP_CURRENT_USER_IE_PROXY_CONFIG ProxyConfig;
	WINHTTP_PROXY_INFO ProxyInfoTemp, ProxyInfo;
	WINHTTP_AUTOPROXY_OPTIONS OptPAC;
	DWORD dwOptions = SECURITY_FLAG_IGNORE_CERT_CN_INVALID | SECURITY_FLAG_IGNORE_CERT_DATE_INVALID | SECURITY_FLAG_IGNORE_UNKNOWN_CA | SECURITY_FLAG_IGNORE_CERT_WRONG_USAGE;

	ZeroMemory(&ProxyInfo, sizeof(ProxyInfo));
	ZeroMemory(&ProxyConfig, sizeof(ProxyConfig));

	http_local_session = WinHttpOpen(L"Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko)", WINHTTP_ACCESS_TYPE_NO_PROXY, 0, WINHTTP_NO_PROXY_BYPASS, 0);

	if (http_local_session && WinHttpGetIEProxyConfigForCurrentUser(&ProxyConfig)) {
		if (ProxyConfig.lpszProxy) {
			ProxyInfo.lpszProxy = ProxyConfig.lpszProxy;
			ProxyInfo.dwAccessType = WINHTTP_ACCESS_TYPE_NAMED_PROXY;
			ProxyInfo.lpszProxyBypass = NULL;
		}

		if (ProxyConfig.lpszAutoConfigUrl) {
			// Script proxy pac
			OptPAC.dwFlags = WINHTTP_AUTOPROXY_CONFIG_URL;
			OptPAC.lpszAutoConfigUrl = ProxyConfig.lpszAutoConfigUrl;
			OptPAC.dwAutoDetectFlags = 0;
			OptPAC.fAutoLogonIfChallenged = TRUE;
			OptPAC.lpvReserved = 0;
			OptPAC.dwReserved = 0;

			if (WinHttpGetProxyForUrl(http_local_session, DestURL, &OptPAC, &ProxyInfoTemp))
				memcpy(&ProxyInfo, &ProxyInfoTemp, sizeof(ProxyInfo));
		}

		if (ProxyConfig.fAutoDetect) {
			// Autodetect proxy
			OptPAC.dwFlags = WINHTTP_AUTOPROXY_AUTO_DETECT;
			OptPAC.dwAutoDetectFlags = WINHTTP_AUTO_DETECT_TYPE_DHCP | WINHTTP_AUTO_DETECT_TYPE_DNS_A;
			OptPAC.fAutoLogonIfChallenged = TRUE;
			OptPAC.lpszAutoConfigUrl = NULL;
			OptPAC.lpvReserved = 0;
			OptPAC.dwReserved = 0;

			if (WinHttpGetProxyForUrl(http_local_session, DestURL, &OptPAC, &ProxyInfoTemp))
				memcpy(&ProxyInfo, &ProxyInfoTemp, sizeof(ProxyInfo));
		}

		if (ProxyInfo.lpszProxy)
			WinHttpSetOption(http_local_session, WINHTTP_OPTION_PROXY, &ProxyInfo, sizeof(ProxyInfo));
	}

	WinHttpSetOption(http_local_session, WINHTTP_OPTION_SECURITY_FLAGS, &dwOptions, sizeof(DWORD));
}

DWORD WINAPI HttpRequester::HttpRequest(WCHAR *Host, WCHAR *verb, WCHAR *resource, DWORD port, BYTE *s_buffer, DWORD sbuf_len, BYTE **r_buffer, DWORD *response_len, wchar_t *cookies_w, DWORD* cookie_len)
{
	DWORD dwStatusCode = 0;
	DWORD dwTemp = sizeof(dwStatusCode);
	DWORD n_read;
	char *types[] = { "*\x0/\x0*\x0",0 };
	HINTERNET hConnect, hRequest;
	BYTE *ptr;
	DWORD flags = 0;
	BYTE temp_buffer[8 * 1024];
	DWORD dwCookieSize =0;
	DWORD dwIndex =0;
	int iret;

	if (port == 443)
		flags = WINHTTP_FLAG_SECURE;

	if (!(hConnect = WinHttpConnect(http_local_session, (LPCWSTR)Host, (INTERNET_PORT)port, 0))) {
		//SAFE_FREE(cookies_w);
		return REQUEST_NETWORK_PROBLEM;
	}
	if (!(hRequest = WinHttpOpenRequest(hConnect, verb, resource, NULL, WINHTTP_NO_REFERER, (LPCWSTR *)types, flags))) {
		//SAFE_FREE(cookies_w);
		WinHttpCloseHandle(hConnect);
		return REQUEST_NETWORK_PROBLEM;
	}
	if (!WinHttpAddRequestHeaders(hRequest, L"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8", -1, WINHTTP_ADDREQ_FLAG_REPLACE | WINHTTP_ADDREQ_FLAG_ADD)) {
		//SAFE_FREE(cookies_w);
		WinHttpCloseHandle(hRequest);
		WinHttpCloseHandle(hConnect);
		return REQUEST_NETWORK_PROBLEM;
	}

	if (cookies_w != nullptr && *cookies_w !=0)
	{
		if (!WinHttpAddRequestHeaders(hRequest, cookies_w, -1, WINHTTP_ADDREQ_FLAG_REPLACE | WINHTTP_ADDREQ_FLAG_ADD))
		{
			WinHttpCloseHandle(hRequest);
			WinHttpCloseHandle(hConnect);
			return REQUEST_NETWORK_PROBLEM;
		}
	}

	if (!WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, s_buffer, sbuf_len, sbuf_len, NULL)) {
		//SAFE_FREE(cookies_w);
		WinHttpCloseHandle(hRequest);
		WinHttpCloseHandle(hConnect);
		return REQUEST_NETWORK_PROBLEM;
	}
	//	SAFE_FREE(cookies_w);

	if (!WinHttpReceiveResponse(hRequest, 0)) {
		WinHttpCloseHandle(hRequest);
		WinHttpCloseHandle(hConnect);
		return REQUEST_NETWORK_PROBLEM;
	}

	if (!WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, NULL, &dwStatusCode, &dwTemp, NULL)) {
		WinHttpCloseHandle(hRequest);
		WinHttpCloseHandle(hConnect);
		return REQUEST_NETWORK_PROBLEM;
	}

	if (dwStatusCode != HTTP_STATUS_OK) {
		WinHttpCloseHandle(hRequest);
		WinHttpCloseHandle(hConnect);
		return REQUEST_NETWORK_PROBLEM;
	}

	do
	{
		dwCookieSize = *(cookie_len)*sizeof(wchar_t);

		if (!WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_SET_COOKIE, WINHTTP_HEADER_NAME_BY_INDEX, cookies_w, &dwCookieSize, &dwIndex) && (iret = GetLastError()) == ERROR_INSUFFICIENT_BUFFER)
		{
			*cookie_len = (dwCookieSize/sizeof(wchar_t));
			return ERROR_INSUFFICIENT_BUFFER;
		}

	} while (iret != ERROR_HTTP_HEADER_NOT_FOUND);

	*response_len = 0;
	*r_buffer = NULL;
	for (;;) {
		if (!WinHttpReadData(hRequest, temp_buffer, sizeof(temp_buffer), &n_read) || n_read == 0 || n_read>sizeof(temp_buffer))
			break;
		if (!(ptr = (BYTE *)realloc((*r_buffer), (*response_len) + n_read + sizeof(WCHAR))))
			break;
		*r_buffer = ptr;
		memcpy(((*r_buffer) + (*response_len)), temp_buffer, n_read);
		*response_len = (*response_len) + n_read;

		memset(((*r_buffer) + (*response_len)), 0, sizeof(WCHAR));
	}

	if (!(*r_buffer)) {
		WinHttpCloseHandle(hRequest);
		WinHttpCloseHandle(hConnect);
		return REQUEST_NETWORK_PROBLEM;
	}

	WinHttpCloseHandle(hRequest);
	WinHttpCloseHandle(hConnect);
	return REQUEST_SUCCESS;
}

void WINAPI HttpRequester::OpenRequester(WCHAR *DestURL)
{
	WinHttpSetup(DestURL);
}

BOOL WINAPI HttpRequester::WinHttpClose()
{
	return WinHttpCloseHandle(HttpRequester::http_local_session);
}

HttpRequester::HttpRequester()
{
}


HttpRequester::~HttpRequester()
{
	HttpRequester::WinHttpClose();
}
