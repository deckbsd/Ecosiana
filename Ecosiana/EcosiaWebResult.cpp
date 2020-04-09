#include "EcosiaWebResult.h"

string WINAPI EcosiaWebResult::title_cleared()
{
	return EcosiaResult::clear_string(title_raw);
}

string WINAPI EcosiaWebResult::description_cleared()
{
	return EcosiaResult::clear_string(description_raw);
}

EcosiaWebResult::EcosiaWebResult()
{
}


EcosiaWebResult::~EcosiaWebResult()
{
}
