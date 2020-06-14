#include "NFA_CLI.h"

String NFA_CLI::listIdentifiers() const
{
	String result = "[";
	for (int i = 0; i < this->automatonList.length(); i++) {
		result = (result + ' ' + String(i));
	}
	return result + "]";
}

NFA_CLI::NFA_CLI()
{
	this->automatonList = DynamicArray<NFA>();
}

NFA_CLI::NFA_CLI(const NFA_CLI& other)
{
	this->automatonList = other.automatonList;
}

NFA_CLI NFA_CLI::operator=(const NFA_CLI& other)
{
	if (this != &other) {
		this->automatonList = other.automatonList;
	}
	return *this;
}

String NFA_CLI::readCommand(const String& command)
{
	if (command == (String) "exit") {
		return "exiting...";
	}
	if (command == (String) "list") {
		return this->listIdentifiers();
	}
	if (command.indexOf((String)"reg") == 0) {
		String operand = command.getSubset(4, command.length());
		NFA newAutomaton = NFA(operand);
		this->automatonList.push(newAutomaton);
		return String((int)this->automatonList.length() - 1);
	}
	if (command.indexOf((String)"empty") == 0) {
		int id1 = ((String)command.getSubset(6, command.length())).parseInt();
		return "Not empty";
	}
	if (command.indexOf((String)"print") == 0) {
		int id1 = ((String)command.getSubset(6, command.length())).parseInt();
		return this->automatonList[id1].toString();
	}
	if (command.indexOf((String)"deterministic") == 0) {
		int id1 = ((String)command.getSubset(14, command.length())).parseInt();
		return this->automatonList[id1].isDetermined();
	}
	if (command.indexOf((String)"determine") == 0) {
		int id1 = ((String)command.getSubset(10, command.length())).parseInt();
		NFA determined = this->automatonList[id1].getDetermined();
		this->automatonList.push(determined);
		return this->automatonList.length() - 1;
	}
	if (command.indexOf((String)"recognize") == 0) {
		String operandPart = command.getSubset(command.indexOf(' ') + 1, command.length());
		int id1 = ((String)(operandPart.getSubset(0, operandPart.indexOf(' ')))).parseInt();
		String word = operandPart.getSubset(operandPart.indexOf(' ') + 1, operandPart.length());
		return this->automatonList[id1].contains(word);
	}
	if (command.indexOf((String)"union") == 0) {
		String operandPart = command.getSubset(command.indexOf(' ') + 1, command.length());
		int id1 = ((String)(operandPart.getSubset(0, operandPart.indexOf(' ')))).parseInt();
		int id2 = ((String)operandPart.getSubset(operandPart.indexOf(' ') + 1, operandPart.length())).parseInt();
		this->automatonList.push(this->automatonList[id1].getUnion(this->automatonList[id2]));
		return this->automatonList.length() - 1;
	}
	if (command.indexOf((String)"concat") == 0) {
		String operandPart = command.getSubset(command.indexOf(' ') + 1, command.length());
		int id1 = ((String)(operandPart.getSubset(0, operandPart.indexOf(' ')))).parseInt();
		int id2 = ((String)operandPart.getSubset(operandPart.indexOf(' ') + 1, operandPart.length())).parseInt();
		this->automatonList.push(this->automatonList[id1].getConcatenation(this->automatonList[id2]));
		return this->automatonList.length() - 1;
	}
	return "";
}

NFA_CLI::~NFA_CLI()
{
}
