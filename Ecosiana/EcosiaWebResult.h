#pragma once

#include "EcosiaResult.h"

class EcosiaWebResult : public EcosiaResult
{

public:

	string title_raw;
	string url_raw;
	string description_raw;

	string WINAPI title_cleared();
	string WINAPI description_cleared();

	EcosiaWebResult();
	~EcosiaWebResult();
};

