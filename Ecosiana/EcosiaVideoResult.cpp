
#include "EcosiaVideoResult.h"

string WINAPI EcosiaVideoResult::title_cleared()
{
	return EcosiaResult::clear_string(title_raw);
}

string WINAPI EcosiaVideoResult::description_cleared()
{
	return EcosiaResult::clear_string(description_raw);
}

EcosiaVideoResult::EcosiaVideoResult()
{
}


EcosiaVideoResult::~EcosiaVideoResult()
{
}
