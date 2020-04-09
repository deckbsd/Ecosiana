#pragma once
#include <string>

#include "EcosiaResult.h"
#include "StringHelper.h"

using namespace std;

class EcosiaVideoResult : public EcosiaResult
{
public:

	string title_raw;
	string video_url_raw;
	string image_url_raw;
	string description_raw;

	string WINAPI title_cleared();
	string WINAPI description_cleared();

	EcosiaVideoResult();
	~EcosiaVideoResult();
};

