#pragma once
#include "DynamicArray.hpp"
#include "String.h"

class NFA {

public:
	class State {
	private:
		String name;
		bool isInitial;
		bool isFinal;
	public:
		State(String name, bool isFinal, bool isInitial);
		State(DynamicArray<State> const& stateList, bool ifFinal, bool isInitial);
		State(const State& other);

		bool operator==(const State& other) const;
		NFA::State& operator=(State const& other);

		String getName() const;
		bool getIsInitial() const;
		bool getIsFinal() const;

		void setName(String name);
		void setIsInitial(bool val);
		void setIsFinal(bool val);

		~State();
	};
	struct Edge {
		char letter;
		int destination;
		
		Edge();
		Edge(int destination, char letter);

		bool operator==(const Edge& other) const;
		Edge& operator=(const Edge& other);

		~Edge();
	};

private:

	DynamicArray<State> stateList;
	DynamicArray<DynamicArray<Edge>> transitionList;
	String alphabet;

	DynamicArray<int> makeEpsilonTransition(int from) const;
	static int getNextClosingBracketIndex(const String& str, int from);
	static NFA getNFAFromRegex(const String regex);
public:
	NFA();
	NFA(const String regex);
	NFA(const NFA& other);

	NFA& operator=(const NFA& other);
	friend ostream& operator<<(ostream& os, const NFA& A);
	//TODO
	// Are the two automaton isomorphic
	//bool operator==(const NFA& other) const;

	String getAlphabet() const;

	DynamicArray<int> getInitialStates() const;
	DynamicArray<int> getFinalStates() const;
	DynamicArray<int> deltaFunction(int from, char letter) const;
	DynamicArray<int> deltaFunction(DynamicArray<int> from, char letter) const;
	DynamicArray<int> deltaStarFunction(int from, String word) const;
	DynamicArray<int> deltaStarFunction(DynamicArray<int> from, String word) const;
	NFA getDetermined() const;
	bool isDetermined() const;
	bool contains(String const word) const;
	NFA getKleeneStar() const;
	NFA getUnion(const NFA other) const;
	NFA getIntersection(const NFA other) const;
	NFA getConcatenation(const NFA other) const;
	NFA getMinimal() const;
	bool isMinimal() const;
	String toString() const;



	DynamicArray<State> getStateList() const;
	DynamicArray<DynamicArray<Edge>> getTransitionList() const;

	int addState(String name, bool isFinal, bool isInitial);
	void addTransition(int fromState, int toState, char letter);
	void setAlphabet(const String& newAlphabet);

	void setNameFor(int sI, String name);
	void setIsInitialFor(int sI, bool value);
	void setIsFinalFor(int sI, bool value);


	~NFA();

};