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
	NFA_CLI();
	NFA_CLI(const NFA_CLI& other);
	NFA_CLI operator=(const NFA_CLI& other);
	String readCommand(const String& command);
	~NFA_CLI();
};

