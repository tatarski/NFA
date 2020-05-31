#include "NFA_CLI.h"

String NFA_CLI::listIdentifiers() const
{
	String result = "[";
	for (int i = 0; i < this->automatonList.length(); i++) {
		result = (result + ' ' + String(i));
	}
	return result + "]";
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
		int id1 = ((String)command.getSubset(15, command.length())).parseInt();
		return this->automatonList[id1].isDetermined();
	}
	if (command.indexOf((String)"determine") == 0) {
		int id1 = ((String)command.getSubset(15, command.length())).parseInt();
		this->automatonList.push(this->automatonList[id1].getDetermined());
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
