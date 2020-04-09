#include "EcosiaHtmlParser.h"

GumboOutput* WINAPI EcosiaHtmlParser::parse(char* sz_buffer)
{

	return gumbo_parse(sz_buffer);

}

EcosiaHtmlParser::EcosiaHtmlParser()
{
}


EcosiaHtmlParser::~EcosiaHtmlParser()
{
}
