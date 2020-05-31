#include "NFA.h"

NFA::State::State(String name = "", bool isFinal = false, bool isInitial = false) {
	this->setName(name);
	this->setIsFinal(isFinal);
	this->setIsInitial(isInitial);
}

NFA::State::State(DynamicArray<State>const& stateList, bool isFinal, bool isInitial) {
	NFA::State("", isFinal, isInitial);
	for (int i = 0; i < stateList.length(); i++) {
		this->setName(this->getName() + stateList[i].name);
	}
}

NFA::State::State(const NFA::State& other) : NFA::State(other.getName(), other.getIsFinal(), other.getIsInitial()) {
}

NFA::State& NFA::State::operator=(const NFA::State& other) {
	if (this != &other) {
		this->name = other.getName();
		this->isFinal = other.getIsFinal();
		this->isInitial = other.getIsInitial();
	}
	return *this;
}

ostream& operator<<(ostream& os, const NFA& other) {
	os << "Automata\n";
	for (int i = 0; i < other.getStateList().length(); i++) {
		os << other.getStateList()[i].getName() << " ";
		if (other.getStateList()[i].getIsFinal()) {
			os << (String)"final :";
		}
		if (other.getStateList()[i].getIsInitial()) {
			os << (String)"initial :";
		}
		for (int j = 0; j < other.getTransitionList()[i].length(); j++) {
			os << (String)"(" << other.getTransitionList()[i][j].letter << (String)", " << other.getStateList()[other.getTransitionList()[i][j].destination].getName() << (String)")  ";
		}
		os << (String)"\n";
	}
	return os;
}
bool NFA::State::operator==(const NFA::State& other) const {
	return
		this->getName() == other.getName() &&
		this->getIsInitial() == other.getIsInitial() &&
		this->getIsFinal() == other.getIsFinal();
}

String NFA::State::getName() const {
	return this->name;
}

bool NFA::State::getIsInitial() const {
	return this->isInitial;
}

bool NFA::State::getIsFinal() const {
	return this->isFinal;
}

void NFA::State::setName(String name) {
	this->name = name;
}

void NFA::State::setIsFinal(bool value) {
	this->isFinal = value;
}

void NFA::State::setIsInitial(bool value) {
	this->isInitial = value;
}

NFA::State::~State() {}

NFA::Edge::Edge() {
	this->destination = -1;
	this->letter = '\0';
}

NFA::Edge::Edge(int destination, char letter) {
	this->destination = destination;
	this->letter = letter;
}

bool NFA::Edge::operator==(const NFA::Edge& other) const {
	return (
		this->destination == other.destination &&
		this->letter == other.letter
		);
}

NFA::Edge& NFA::Edge::operator=(const NFA::Edge& other) {
	if (this != &other) {
		this->destination = other.destination;
		this->letter = other.letter;
	}
	return *this;
}

NFA::Edge::~Edge() {}

DynamicArray<int> NFA::makeEpsilonTransition(int from) const {
	DynamicArray<int> reachedStates;
	bool areAllStatesReached = false;
	reachedStates.pushUnique(from);
	while (!areAllStatesReached) {
		DynamicArray<int> newReachedStates;
		for (int i = 0; i < reachedStates.length(); i++) {
			int currentState = reachedStates[i];
			DynamicArray<Edge> possibleTransitionList = this->getTransitionList()[currentState];
			for (int j = 0; j < possibleTransitionList.length(); j++) {
				Edge currentTransition = possibleTransitionList[j];
				if (currentTransition.letter == '\0') {
					newReachedStates.pushUnique(currentTransition.destination);
				}
			}

		}
		if (reachedStates.getUnion(newReachedStates).length() == reachedStates.length()) {
			areAllStatesReached = true;
		}
		else {
			reachedStates = reachedStates.getUnion(newReachedStates);
		}
	}
	return reachedStates;
}

NFA NFA::getNFAFromRegex(const String regex)
{
	if (regex.length() == 1) {
		NFA result;
		result.addState("S", false, true);
		result.addState("S1", true, false);
		result.addTransition(0, 1, regex[0]);
		result.setAlphabet(regex);
		return result;
	}
	return NFA();
}

NFA::NFA() {
	this->stateList = DynamicArray<State>(1);
	this->transitionList = DynamicArray<DynamicArray<Edge>>(1);
	this->alphabet = "";
}

NFA::NFA(const String regex) {
	NFA res = NFA::getNFAFromRegex(regex);
	this->stateList = res.getStateList();
	this->transitionList = res.getTransitionList();
	this->setAlphabet(res.getAlphabet());
}

NFA::NFA(const NFA& other) : NFA() {
	DynamicArray<DynamicArray<Edge>> t = DynamicArray<DynamicArray<Edge>>(other.getTransitionList());
	for (int i = 0; i < other.stateList.length(); i++) {
		this->addState(other.getStateList()[i].getName(), other.getStateList()[i].getIsFinal(), other.getStateList()[i].getIsInitial());
		for (int j = 0; j < other.getTransitionList()[i].length(); j++) {
			this->addTransition(i, other.getTransitionList()[i][j].destination, other.getTransitionList()[i][j].letter);
		}
	}
	this->alphabet = other.getAlphabet();
}

NFA& NFA::operator=(const NFA& other) {
	
	if (this != &other) {
		this->transitionList = other.getTransitionList();
		this->stateList = other.getStateList();
		this->alphabet = other.getAlphabet();
	}
	return *this;
}

/*bool NFA::operator==(const NFA& other) const {
	/*return this->getTransitionList() == other.getTransitionList() &&
		this->getAlphabet() == other.getAlphabet() &&
		this->getStateList() == other.getStateList();
}*/

String NFA::getAlphabet() const {
	return this->alphabet;
}

DynamicArray<int> NFA::getInitialStates() const {
	DynamicArray<int> result;
	DynamicArray<State> stateList = this->getStateList();
	for (int i = 0; i < stateList.length(); i++) {
		if (stateList[i].getIsInitial()) {
			result.push(i);
		}
	}
	return result;
}

DynamicArray<int> NFA::getFinalStates() const {
	DynamicArray<int> result;
	DynamicArray<State> stateList = this->getStateList();
	for (int i = 0; i < stateList.length(); i++) {
		if (stateList[i].getIsFinal()) {
			result.push(i);
		}
	}
	return result;
}

DynamicArray<int> NFA::deltaFunction(int from, char letter) const {
	DynamicArray<int> newStates;
	DynamicArray<Edge> possibleTransitions = this->getTransitionList()[from];
	for (int tI = 0; tI < possibleTransitions.length(); tI++) {
		Edge currentTransition = possibleTransitions[tI];
		if (currentTransition.letter == '\0') {
			DynamicArray<int> epsilonReachedStates = this->makeEpsilonTransition(currentTransition.destination);
			for (int i = 0; i < epsilonReachedStates.length(); i++) {
				possibleTransitions = possibleTransitions.getUnion(this->getTransitionList()[epsilonReachedStates[i]]);
			}
		}
	}
	for (int tI = 0; tI < possibleTransitions.length(); tI++) {
		Edge currentTransition = possibleTransitions[tI];
		if (letter == currentTransition.letter) {
			if (letter != '\0') {
				// Normal letter transition
				newStates.pushUnique(currentTransition.destination);
			}
			else {
				// Epsilon transition
				newStates = newStates.getUnion(this->makeEpsilonTransition(currentTransition.destination));
			}
		}
	}
	return newStates;
}

DynamicArray<int> NFA::deltaFunction(DynamicArray<int> from, char letter) const {
	DynamicArray<int> newStates;
	for (int i = 0; i < from.length(); i++) {
		int currentState = from[i];
		newStates = newStates.getUnion(this->deltaFunction(currentState, letter));
	}
	return newStates;
}

DynamicArray<int> NFA::deltaStarFunction(int from, String word) const {
	DynamicArray<int> reachedStates;
	reachedStates.push(from);
	for (int i = 0; i < word.length(); i++) {
		reachedStates = this->deltaFunction(reachedStates, word[i]);
	}
	for (int i = 0; i < reachedStates.length(); i++) {
		for (int j = 0; j < this->getTransitionList()[i].length(); j++) {
			if (this->getTransitionList()[i][j].letter == '\0') {
				reachedStates = reachedStates.getUnion(this->makeEpsilonTransition(this->getTransitionList()[i][j].destination));
			}
		}
	}
	return reachedStates;
}
DynamicArray<int> NFA::deltaStarFunction(DynamicArray<int> from, String word) const {
	DynamicArray<int> reachedStates;
	for (int i = 0; i < from.length(); i++) {
		int currentState = from[i];
		reachedStates = reachedStates.getUnion(this->deltaStarFunction(currentState, word));
	}
	return reachedStates;
}
NFA NFA::getDetermined() const {
	DynamicArray<DynamicArray<Edge>> newTransitionList = DynamicArray<DynamicArray<Edge>>(1);
	DynamicArray<State> newStateList;
	NFA result(this->getAlphabet());
	result.setAlphabet(this->getAlphabet());
	String alphabet = this->getAlphabet();
	for (int i = 0; i < pow(2, this->transitionList.length()); i++) {
		DynamicArray<int> currentStates = this->stateList.getSubsetIndecies(i);
		bool isNewStateInitial = currentStates.length() > 0, isNewStateFinal = false;
		int nOfInitial = 0;
		for (int k = 0; k < currentStates.length(); k++) {
			nOfInitial += this->getStateList()[currentStates[k]].getIsInitial();
			isNewStateFinal = isNewStateFinal || this->getStateList()[currentStates[k]].getIsFinal();
		}
		State newState = State(this->getStateList().getSubset(i), isNewStateFinal, nOfInitial == this->getInitialStates().length());
		result.addState(newState.getName(), newState.getIsFinal(), newState.getIsInitial());
	}
	for (int i = 0; i < pow(2, this->getTransitionList().length()); i++) {
		DynamicArray<int> currentStates = this->getStateList().getSubsetIndecies(i);
		newTransitionList.push(DynamicArray<Edge>(1));

		for (int j = 0; j < alphabet.length(); j++) {
			DynamicArray<int> newStates = this->deltaFunction(currentStates, alphabet[j]);
			//cout << i << " " << A.stateList.getSubsetNumber(newStates) << " "<<alphabet[i] << endl;
			//this->printStates(newStates);
			//cout << "Subset Number: " << A.stateList.getSubsetNumber(newStates) << endl;
			result.addTransition(i, this->getStateList().getSubsetNumber(newStates), alphabet[j]);
		}
	}
	return result;
}

bool NFA::isDetermined() const {
	String alphabet = this->getAlphabet();
	if (this->getInitialStates().length() != 1) {
		return false;
	}
	for (int i = 0; i < alphabet.length(); i++) {
		for (int j = 0; j < this->getStateList().length(); j++) {
			if (this->getTransitionList()[j].length() == alphabet.length()) {
				int nOfOccurances = 0;
				for (int k = 0; k < this->getTransitionList()[j].length(); k++) {
					if (this->getTransitionList()[j][k].letter == alphabet[i]) {
						nOfOccurances++;
					}
					if (this->getTransitionList()[j][k].letter == '\0') {
						return false;
					}
				}
				if (nOfOccurances != 1) {
					return false;
				}
			}
			else {
				return false;
			}
		}
	}
	return true;
}

bool NFA::contains(String const word) const {
	return this->deltaStarFunction(this->getInitialStates(), word).getIntersection(this->getFinalStates()).length() != 0;
}

NFA NFA::getKleeneStar() const {
	NFA result = NFA(*this);
	result.setAlphabet(this->getAlphabet());
	int newStateIndex = result.addState("S_", false, false);
	for (int i = 0; i < result.getInitialStates().length(); i++) {
		result.setIsInitialFor(result.getInitialStates()[i], false);
		result.addTransition(newStateIndex, result.getInitialStates()[i], '\0');
	}
	for (int i = 0; i < result.getFinalStates().length(); i++) {
		result.addTransition(result.getFinalStates()[i], newStateIndex, '\0');
	}
	result.setIsInitialFor(newStateIndex, true);
	return result;
}

NFA NFA::getUnion(const NFA other) const
{
	NFA result;
	int unionInitialStateIndex = result.addState("SU", false, true);
	DynamicArray<int> thisStateIndecies, otherStateIndecies,
		thisInitialStateIndecies, otherInitialStateIndecies;
	for (int i = 0; i < this->getStateList().length(); i++) {
		int stateIndex = result.addState("A1_" + this->getStateList()[i].getName(), this->getStateList()[i].getIsFinal(), false);
		thisStateIndecies.push(stateIndex);
		if (this->getStateList()[i].getIsInitial()) {
			result.addTransition(unionInitialStateIndex, stateIndex, '\0');
		}
	}
	for (int i = 0; i < other.getStateList().length(); i++) {
		int stateIndex = result.addState("A2_" + other.getStateList()[i].getName(), other.getStateList()[i].getIsFinal(), false);
		otherStateIndecies.push(stateIndex);
		if (other.getStateList()[i].getIsInitial()) {
			result.addTransition(unionInitialStateIndex, stateIndex, '\0');
		}
	}
	for (int i = 0; i < this->getStateList().length(); i++) {
		for (int j = 0; j < this->getTransitionList()[i].length(); j++) {
			result.addTransition(thisStateIndecies[i], thisStateIndecies[this->getTransitionList()[i][j].destination], this->getTransitionList()[i][j].letter);
		}
	}
	for (int i = 0; i < other.getStateList().length(); i++) {
		for (int j = 0; j < other.getTransitionList()[i].length(); j++) {
			result.addTransition(otherStateIndecies[i], otherStateIndecies[other.getTransitionList()[i][j].destination], other.getTransitionList()[i][j].letter);
		}
	}
	return result;
}

NFA NFA::getConcatenation(const NFA other) const
{
	NFA result;
	DynamicArray<int> thisStateIndecies, otherStateIndecies,
		thisFinalStateIndecies, otherInitialStateIndecies;
	for (int i = 0; i < this->getStateList().length(); i++) {
		int stateIndex = result.addState("A1_" + this->getStateList()[i].getName(), false , this->getStateList()[i].getIsInitial());
		if (this->getStateList()[i].getIsFinal()) {
			thisFinalStateIndecies.push(stateIndex);
		}
		thisStateIndecies.push(stateIndex);
	}
	for (int i = 0; i < other.getStateList().length(); i++) {
		int stateIndex = result.addState("A2_" + other.getStateList()[i].getName(), other.getStateList()[i].getIsFinal(), false);
		otherStateIndecies.push(stateIndex);
		if (other.getStateList()[i].getIsInitial()) {
			for (int j = 0; j < thisFinalStateIndecies.length(); j++) {
				result.addTransition(thisFinalStateIndecies[j], stateIndex, '\0');
			}
		}
	}
	for (int i = 0; i < this->getStateList().length(); i++) {
		for (int j = 0; j < this->getTransitionList()[i].length(); j++) {
			result.addTransition(thisStateIndecies[i], thisStateIndecies[this->getTransitionList()[i][j].destination], this->getTransitionList()[i][j].letter);
		}
	}
	for (int i = 0; i < other.getStateList().length(); i++) {
		for (int j = 0; j < other.getTransitionList()[i].length(); j++) {
			result.addTransition(otherStateIndecies[i], otherStateIndecies[other.getTransitionList()[i][j].destination], other.getTransitionList()[i][j].letter);
		}
	}
	return result;
}


DynamicArray<NFA::State> NFA::getStateList() const {
	return this->stateList;
}

DynamicArray<DynamicArray<NFA::Edge>> NFA::getTransitionList() const {
	return this->transitionList;
}

int NFA::addState(String name, bool isFinal, bool isInitial) {
	this->stateList.push(State(name, isFinal, isInitial));
	this->transitionList.push(DynamicArray<NFA::Edge>());
	return this->stateList.length() - 1;
}

void NFA::addTransition(int fromState, int toState, char letter) {
	this->transitionList[fromState].push(NFA::Edge(toState, letter));
}

void NFA::setAlphabet(String newAlphabet) {
	/*for (int i = 0; i < transitionList.length(); i++) {
		for (int j = 0; j < transitionList[j].length(); j++) {
			if (-1 == newAlphabet.indexOf(transitionList[i][j].letter) && transitionList[i][j].letter!='\0') {
				//TODO throw esc
				cerr << "Automaton contains transitions with symbol outside newAlphabet!";
			}
		}
	}*/
	this->alphabet = newAlphabet;
}

void NFA::setNameFor(int sI, String name) {
	this->stateList[sI].setName(name);
}

void NFA::setIsFinalFor(int sI, bool value) {
	this->stateList[sI].setIsFinal(value);
}

void NFA::setIsInitialFor(int sI, bool value) {
	this->stateList[sI].setIsInitial(value);
}
NFA::~NFA() {}