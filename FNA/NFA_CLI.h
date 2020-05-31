#pragma once
#include "String.h"
#include "NFA.h"
#include "DynamicArray.hpp"
class NFA_CLI
{
private:
	DynamicArray<NFA> automatonList;
	String listIdentifiers() const;
public:
	String readCommand(const String& command);
};

