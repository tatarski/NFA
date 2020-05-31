#pragma once
#include "String.h"
#include "NFA.h"
#include "DynamicArray.hpp"
class NFA_CLI
{
private:
	DynamicArray<NFA> list;
public:
	void readCommand(String command);
};

