#pragma once

#include <Windows.h>

#include "gumbo\gumbo.h"

class EcosiaHtmlParser
{
protected :
	GumboOutput* WINAPI parse(char* sz_buffer);
public:
	EcosiaHtmlParser();
	~EcosiaHtmlParser();
};

