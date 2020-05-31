#include "DynamicArray.hpp"
#include "String.hpp"
#include "Pair.hpp"

class NFA1 {

public:
	class State {
	private:
		String name;
		bool isInitial;
		bool isFinal;
	public:
		State(String name , bool isFinal, bool isInitial);
		State(DynamicArray<State> const &stateList, bool ifFinal, bool isInitial);
		State(const State& other);

		bool operator==(const State& other) const;
		NFA::State& operator=(State const& other);
		
		String getName() const;
		bool isInitial() const;
		bool isFinal() const;

		void setName(String name);
		void setIsInitial(bool val);
		void setIsFinal(bool val);

		~State();
	};
	struct Edge {
	char letter;
	int destination;
	Edge(int destination, char letter);

	bool operator==(const Edge& other) const;
	Edge& operator=(const Edge& other);

	~Edge();
	};

private:

	DynamicArray<State> stateList;
	DynamicArray<DynamicArray<Edge>> transitionList;
	String alphabet;

public:
	NFA(String alphabet) {
		this->stateList = DynamicArray<State>();
		this->transitionList = DynamicArray<DynamicArray<Edge>>();
		this->setAlphabet(alphabet);
	}
	NFA(const NFA& other);
	
	NFA& operator=(const NFA& other);

	// Are the two automaton isomorphic
	bool operator==(const NFA& other) const;
	DynamicArray<int> getInitialStates() const;
	DynamicArray<int> getFinalStates() const;
	DynamicArray<int> deltaFunction(int from, char letter) const;
	DynamicArray<int> deltaFunction(DynamicArray<int> from, char letter) const;
	DynamicArray<int> deltaStarFunction(int from, String word) const;
	DynamicArray<int> deltaStarFunction(DynamicArray<int> from, String word) const;
	NFA getDetermined() const;
	bool isDetermined() const;
	NFA getKleeneStar() const;
	NFA getUnion(const NFA other) const;
	NFA getIntersection(const NFA other) const;
	NFA getConcatenation(const NFA other) const;
	NFA getMinimal() const;
	bool isMinimal() const;


	DynamicArray<State> getStateList() const;
	DynamicArray<DynamicArray<Edge>> getTransitionList() const;

	bool contains(String const word) const;

	void addState(String name, bool isInitial, bool isFinal);
	void addTransition(int fromState, int toState, char letter);
	void setAlphabet(String newAlphabet);

	~NFA();

};

NFA::State::State(String name = "", bool isFinal = false, bool isInitial = false) {
	this->setName(name);
	this->setIsFinal(isFinal);
	this->setIsInitial(isInitial);
}

NFA::State::State(DynamicArray<State>const &stateList, bool isFinal, bool isInitial) {
	NFA::State("", isFinal, isInitial);
	for (int i = 0; i < stateList.length(); i++) {
		this->setName(this->getName() + stateList[i].name);
	}
}

NFA::State::State(const NFA::State& other) {
	NFA::State(other.getName(), other.isFinal, other.isInitial);
}

NFA::State& NFA::State::operator=(const NFA::State& other) {
	if (this != &other) {
		*this = NFA::State(other);
	}
	return *this;
}

bool NFA::State::operator==(const NFA::State& other) const {
	return (
		this->getName() == other.getName() &&
		this->isInitial() == other.isInitial() &&
		this->isFinal() == other.isFinal()
		);
}

String NFA::State::getName() const {
	return this->name;
}

bool NFA::State::isInitial() const{
	return this->isInitial;
}

bool NFA::State::isFinal() const {
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

NFA::Edge::Edge(int destination = -1, char letter = '\0') {
	this->destination = destination;
	this->letter = letter;
}

bool NFA::Edge::operator==(const NFA::Edge& other) const{
	return (
		this->destination == other.destination &&
		this->letter == other.letter
		);
}

NFA::Edge& NFA::Edge::operator=(const NFA::Edge& other) {
	this->destination = other.destination;
	this->letter = other.letter;
}

NFA::Edge::~Edge() {}

