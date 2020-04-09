#pragma once
#include <Windows.h>
#include <algorithm>
#include <string>

#include "StringHelper.h"

using namespace std;

class EcosiaResult
{
protected:

	string WINAPI clear_string(string toclear);

public:
	EcosiaResult();
	~EcosiaResult();
};

