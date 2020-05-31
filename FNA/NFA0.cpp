#include "DynamicArray.hpp"
#include "String.h"
#include "Pair.hpp"

class NFA1 {
	class State {
	public:
		String name;
		bool isFinal;
		bool isInitial;
		State(
			String name = "",
			bool isFinal = false,
			bool isInitial = false) {
			this->name = name;
			this->isFinal = isFinal;
			this->isInitial = isInitial;
		}
		State(DynamicArray<State> states, bool isFinal = false, bool isInitial = false) :
			State("", isFinal, isInitial) {
			this->name = this->name + "{";
			for (int i = 0; i < states.length(); i++) {
				name = name + states[i].name;
			}
			this->name = this->name + "}";
		}
		bool operator==(const State& other) {
			return (this->name == other.name && this->isFinal == other.isFinal && this->isInitial == other.isInitial);
		}
		State& operator=(const State& other) {
			if (!(this == &other)) {
				this->name = String(other.name);
				this->isFinal = other.isFinal;
				this->isInitial = other.isInitial;
			}
			return *this;
		}
		State(const State& other) : State(other.name, other.isFinal, other.isInitial) {};
	};
	struct Edge {
		int destination;
		char letter;
		Edge(int destination = -1, char letter = '\0') {
			this->destination = destination;
			this->letter = letter;
		}
		bool operator==(const Edge& other) const {
			return other.destination == this->destination && other.letter == this->letter;
		}
	};
private:
	DynamicArray<State> stateList;
	DynamicArray < DynamicArray < Edge > > transitionList;
	String alphabet;
public:
	NFA(DynamicArray<State> stateList = DynamicArray<State>(),
		String alphabet = "") {
		this->stateList = stateList;
		this->alphabet = alphabet;
		this->transitionList = DynamicArray<DynamicArray<Edge>>();
	}
	static NFA getDFAFrom(NFA &A) {
		DynamicArray<DynamicArray<Edge>> newTransitionList = DynamicArray<DynamicArray<Edge>>(1);
		DynamicArray<State> newStateList;
		NFA result;
		result.setAlphabet(A.getAlphabet());
		String alphabet = A.getAlphabet();
		for (int i = 0; i < pow(2, A.transitionList.length()); i++) {
			DynamicArray<int> currentStates = A.stateList.getSubsetIndecies(i);
			bool isNewStateInitial = currentStates.length() > 0, isNewStateFinal = false;
			int nOfInitial = 0;
			for (int k = 0; k < currentStates.length(); k++) {
				nOfInitial += A.stateList[currentStates[k]].isInitial;
				isNewStateFinal = isNewStateFinal || A.stateList[currentStates[k]].isFinal;
			}
			result.addState(State(A.stateList.getSubset(i), isNewStateFinal, nOfInitial == A.getInitialStates().length()));
		}
		for (int i = 0; i < pow(2, A.transitionList.length()); i++) {
			DynamicArray<int> currentStates = A.stateList.getSubsetIndecies(i);
			newTransitionList.push(DynamicArray<Edge>(1));

			for (int j = 0; j < alphabet.length(); j++) {
				DynamicArray<int> newStates = A.makeTransition(currentStates, alphabet[j]);
				//cout << i << " " << A.stateList.getSubsetNumber(newStates) << " "<<alphabet[i] << endl;
				A.printStates(newStates);
				cout << "Subset Number: " << A.stateList.getSubsetNumber(newStates) << endl;
				result.addTransition(i, A.stateList.getSubsetNumber(newStates), alphabet[j]);
			}
		}
		return result;
	}

	static NFA getUnion(NFA A, NFA B) {
		NFA result;
		result.setAlphabet(String::concat(A.getAlphabet(), B.getAlphabet()).getUnique());
		for (int Ai = 0; Ai < A.getStates().length(); Ai++) {
			for (int Bi = 0; Bi < B.getStates().length(); Bi++) {
				result.addState(A.getStates()[Ai].name + B.getStates()[Bi].name,
					A.getStates()[Ai].isFinal || B.getStates()[Bi].isFinal,
					A.getStates()[Ai].isInitial && B.getStates()[Bi].isInitial);
			}
		}
		for (int Ai = 0; Ai < A.getStates().length(); Ai++) {
			for (int Bi = 0; Bi < B.getStates().length(); Bi++) {
				for (int i1 = 0; i1 < A.getTransitions()[Ai].length(); i1++) {
					for (int i2 = 0; i2 < B.getTransitions()[Bi].length(); i2++) {
						DynamicArray<int> newState;
						newState.push(Ai);
						newState.push(Bi);
					}
				}
			}
		}
		return result;
	}

	static bool isDetermined(NFA &A){
		String alphabet = A.getAlphabet();
		if (A.getInitialStates().length() != 1) {
			return false;
		}
		for (int i = 0; i < alphabet.length(); i++) {
			for (int j = 0; j < A.stateList.length(); j++) {
				if (A.transitionList[j].length() == alphabet.length()) {
					int nOfOccurances = 0;
					for (int k = 0; k < A.transitionList[j].length(); k++) {
						if (A.transitionList[j][k].letter == alphabet[i]) {
							nOfOccurances++;
						}
						if (A.transitionList[j][k].letter == '\0') {
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

	DynamicArray<int> deltaFunction(int from, char letter) {
		DynamicArray<int> newStates;
		DynamicArray<Edge> possibleTransitions = this->getTransitions()[from];
		for (int tI = 0; tI < possibleTransitions.length(); tI++) {
			Edge currentTransition = possibleTransitions[tI];
			if (letter == currentTransition.letter) {
				if (letter != '\0') {
					// Normal letter transition
					newStates.pushUnique(currentTransition.destination);
				} else {
					// Epsilon transition
					newStates = newStates.getUnion(this->makeEpsilonTransition(currentTransition.destination));
				}
			}
		}
		return newStates;
	}
	DynamicArray<int> deltaFunction(DynamicArray<int> from, char letter) {
		DynamicArray<int> newStates;
		for (int i = 0; i < from.length(); i++) {
			int currentState = from[i];
			newStates = newStates.getUnion(this->makeTransition(currentState, letter));
		}
		return newStates;
	}
	DynamicArray<int> deltaStarFunction(int from, String word) {
		DynamicArray<int> reachedStates;
		reachedStates.push(from);
		for (int i = 0; i < word.length(); i++) {
			reachedStates = this->makeTransition(reachedStates, word[i]);
		}
		return reachedStates;
	}
	DynamicArray<int> deltaStarFunction(DynamicArray<int> from, String word) {
		DynamicArray<int> reachedStates;
		for (int i = 0; i < from.length(); i++) {
			int currentState = from[i];
			reachedStates = reachedStates.getUnion(this->deltaStarFunction(currentState, word));
		}
		return reachedStates;
	}

	DynamicArray<int> makeEpsilonTransition(int from) {
		DynamicArray<int> reachedStates;
		bool areAllStatesReached = false;
		reachedStates.pushUnique(from);
		while (!areAllStatesReached) {
			DynamicArray<int> newReachedStates;
			for (int i = 0; i < reachedStates.length(); i++) {
				int currentState = reachedStates[i];
				DynamicArray<Edge> possibleTransitionList = this->getTransitions()[currentState];
				for (int j = 0; j < possibleTransitionList.length(); j++) {
					Edge currentTransition = possibleTransitionList[j];
					if (currentTransition.letter == '\0') {
						newReachedStates.pushUnique(currentTransition.destination);
					}
				}
			
			}
			//this->printStates(newReachedStates);
			//this->printStates(reachedStates);
			//cout << reachedStates.getUnion(newReachedStates).length() << " " << reachedStates.length() << endl;
			if (reachedStates.getUnion(newReachedStates).length() == reachedStates.length()) {
				areAllStatesReached = true;
			}
			else {
				reachedStates = reachedStates.getUnion(newReachedStates);
			}
		}
		return reachedStates;
	}
	DynamicArray<int> getInitialStates() const{
		DynamicArray<int> initialStates;
		for (int i = 0; i < this->getStates().length(); i++) {
			State currentState = this->getStates()[i];
			if (currentState.isInitial) {
				initialStates.push(i);
			}
		}
		return initialStates;
	}
	DynamicArray<int> getFinalStates() const {
		DynamicArray<int> finalStates;
		for (int i = 0; i < this->getStates().length(); i++) {
			State currentState = this->getStates()[i];
			if (currentState.isFinal) {
				finalStates.push(i);
			}
		}
		return finalStates;
	}

	DynamicArray<int> makeTransition(int from, char letter) {
		DynamicArray<int> states;
		DynamicArray<Edge> fromTransitionList = this->transitionList[from];
		cout << "Making transition for " << from << " with letter= " << (int)letter << endl;
		for (int i = 0; i < fromTransitionList.length(); i++) {
			Edge currentEdge = fromTransitionList[i];
			cout << "	Could transition to state " << currentEdge.destination << " with letter=" << (int)currentEdge.letter << endl;
			/// Letter transition
			if (letter == currentEdge.letter && letter != '\0') {
				cout << "letter transition" << endl;
				if (states.indexOf(currentEdge.destination) == -1) {
					states.push(currentEdge.destination);
				}
			}
			/// Epsilon transition
			if (letter == currentEdge.letter && letter == '\0') {
				cout << "Epsilon transition" << endl;
				DynamicArray<int> currentStates;
				currentStates.push(currentEdge.destination);

				while (containsEmptyTransitions(currentStates)) {
					cout << "Current states = ";
					this->printStates(currentStates);
					DynamicArray<int> newStates;
					for (int stateI = 0; stateI < currentStates.length(); stateI++) {
						if (!hasEmptyTransition(currentStates[stateI])) {
							states.push(currentStates[stateI]);
						}
						cout << "	Looking at currentState= " << this->stateList[currentStates[stateI]].name << endl;
						for (int tranI = 0; tranI < transitionList[currentStates[stateI]].length(); tranI++) {
							Edge currentTransition = transitionList[currentStates[stateI]][tranI];
							cout << "		Looking at potential transition to " << currentTransition.destination << " with letter = " << currentTransition.letter << endl;
							if (currentTransition.letter == '\0') {
								cout << "			Making transition" << endl;
								newStates.push(currentTransition.destination);
							}
						}
					}
					currentStates = newStates;
					this->printStates(currentStates);
				}
				this->printStates(currentStates);
				for (int j = 0; j < currentStates.length(); j++) {
					if (states.indexOf(currentStates[j]) == -1) {
						states.push(currentStates[j]);
					}
				}
			}
		}
		cout << endl;
		return states;
	}
	bool containsEmptyTransitions(DynamicArray<int> states) {
		for (int i = 0; i < states.length(); i++) {
			if (hasEmptyTransition(states[i])) {
				return true;
			}
		}
		return false;
	}
	bool hasEmptyTransition(int stateI) {
		for (int j = 0; j < this->transitionList[stateI].length(); j++) {
			if (this->transitionList[stateI][j].letter == '\0') {
				return true;
			}
		}
		return false;
	}
	DynamicArray<int> makeTransition(DynamicArray<int> from, char letter) {
		DynamicArray<int> states;
		for (int i = 0; i < from.length(); i++) {
			int currentStateIndex = from[i];
			DynamicArray<int> newStates = this->makeTransition(currentStateIndex, letter);
			for (int i = 0; i < newStates.length(); i++) {
				if (states.indexOf(newStates[i]) == -1) {
					states.push(newStates[i]);
				}
			}
		}
		return states;
	}
	static bool contains(NFA A, String word){
		return A.deltaStarFunction(A.getInitialStates(), word).getIntersection(A.getFinalStates()).length() >0;
	}

	int addTransition(int fromStateI, int toStateI, int letter = '\0') {
		if (fromStateI < 0 || fromStateI >= this->stateList.length() ||
			toStateI < 0 || toStateI >= this->stateList.length()) {
			cerr << "State indices out of bounds" << endl;
		}
		this->transitionList[fromStateI].push(Edge(toStateI, letter));
		return this->transitionList[fromStateI].length() - 1;
	}
	NFA determine() {
		
		
	}
	void setAlphabet(String newAlphabet) {
		for (int i = 0; i < transitionList.length(); i++) {
			for (int j = 0; j < transitionList[j].length(); j++) {
				if (-1 == newAlphabet.indexOf(transitionList[i][j].letter)) {
					cerr << "Automaton contains transitions with symbol outside newAlphabet!";
				}
			}
		}
		this->alphabet = newAlphabet;
	}
	DynamicArray<State> getStates() const{
		return this->stateList;
	}
	DynamicArray<DynamicArray<Edge>> getTransitions() const {
		return this->transitionList;
	}
	String getAlphabet() {
		String alphabet = "";
		for (int i = 0; i < this->transitionList.length(); i++) {
			for (int j = 0; j < this->transitionList[i].length(); j++) {
				char letter = this->transitionList[i][j].letter;
				if (alphabet.indexOf(letter) == -1 && letter != '\0') {
					alphabet.push(letter);
				}
			}
		}
		return this->alphabet;
	}
	int addState(String name, bool isFinal = false, bool isInitial = false) {
		this->stateList.push(State(name, isFinal, isInitial));
		this->transitionList.push(DynamicArray<Edge>());
		return this->stateList.length() - 1;
	}
	int addState(State s) {
		this->stateList.push(s);
		this->transitionList.push(DynamicArray<Edge>());
		return this->stateList.length() - 1;
	}

	void removeTransition(int fromStateI, Edge transition) {
		if (fromStateI < 0 || fromStateI >= this->stateList.length() ||
			transition.destination < 0 || transition.destination >= this->stateList.length()) {
			cerr << "State indices out of bounds" << endl;
		}
		DynamicArray<Edge> a = this->transitionList[fromStateI];
		int transitionIndex = a.indexOf(transition);
		if (transitionIndex > -1) {
			this->transitionList[fromStateI].remove(transitionIndex);
		}
	}

	bool contains(String word) {
		return NFA::contains(*this, word);
	}

	void printTransitions() {
		for (int i = 0; i < this->stateList.length(); i++) {
			cout << this->stateList[i].name << ": ";
			for (int j = 0; j < this->transitionList[i].length(); j++) {
				cout << this->stateList[this->transitionList[i][j].destination].name << " " << this->transitionList[i][j].letter << "    ";
			}
			if (this->stateList[i].isFinal) {
				cout << "final";
			}
			if (this->stateList[i].isInitial) {
				cout << "initial";
			}
			cout << endl;
		}
	}
	void printStates(DynamicArray<int> states) {
		for (int i = 0; i < states.length(); i++) {
			cout << this->stateList[states[i]].name << " ";
		}
		cout << endl;
	}
};