// FNA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


#include "String.h"
#include "NFA.h"

using namespace std;
int main() {
	NFA A;
	A.addState("S1", false, true);
	A.addState("S2", true, false);
	A.addState("S3", true, false);

	A.addTransition(0, 1, 'a');
	A.addTransition(1, 2, 'a');

	NFA B;
	B.addState("S1", false, true);
	B.addState("S2", false, false);
	B.addState("S3", true, false);
	B.addTransition(0, 1, 'b');
	B.addTransition(1, 2, 'b');

	cout << A;
	cout << B;
	cout << NFA("a+a").contains("a");
	return 0;
}
/*
void test1()
{
	NFA A;
	A.addState("S1", false, true);
	A.addState("S2", true, false);
	A.addTransition(0, 0, 'a');
	A.addTransition(0, 1, 'a');
	A.addTransition(1, 1, 'b');
	A.printTransitions();
	cout << endl;
	NFA A_ = NFA::getDFAFrom(A);
	A_.printTransitions();
	cout << "Contains?" << endl;
	cout << A.contains("a") << " a" << endl;
	cout << A.contains("b") << " b" << endl;

	cout << A.contains("aa") << " aa" << endl;
	cout << A.contains("ab") << " ab" << endl;
	cout << A.contains("ba") << " bb" << endl;
	cout << A.contains("bb") << " ba" << endl;

	cout << A.contains("aaa") << "aaa" << endl;
	cout << A.contains("aab") << "aab" << endl;
	cout << A.contains("aba") << "aba" << endl;
	cout << A.contains("abb") << "abb" << endl;
	cout << A.contains("baa") << "baa" << endl;

	cout << A.contains("bab") << "bab" << endl;

	cout << A.contains("bba") << "bba" << endl;
	cout << A.contains("bbb") << "bbb" << endl;

	cout << endl;
	cout << A_.contains("a") << " a" << endl;
	cout << A_.contains("a") << " b" << endl;

	cout << A_.contains("aa") << " aa" << endl;
	cout << A_.contains("ab") << " ab" << endl;
	cout << A_.contains("ba") << " bb" << endl;
	cout << A_.contains("bb") << " ba" << endl;

	cout << A_.contains("aaa") << "aaa" << endl;
	cout << A_.contains("aab") << "aab" << endl;
	cout << A_.contains("aba") << "aba" << endl;
	cout << A_.contains("abb") << "abb" << endl;
	cout << A_.contains("baa") << "baa" << endl;
	cout << A_.contains("bab") << "bab" << endl;
	cout << A_.contains("bba") << "bba" << endl;
	cout << A_.contains("bbb") << "bbb" << endl;
	/*DynamicArray<int> pesho;
	pesho.push(10);
	pesho.push(20);
	pesho.push(30);
	for (int i = 0; i < 8; i++) {
		cout << pesho.getSubsetNumber(pesho.getSubsetIndecies(i)) << " :";
		for (int j = 0; j < pesho.getSubset(i).length(); j++) {
			cout << pesho.getSubset(i)[j] << " ";
		}
		cout << endl;
	}
	pesho.getSubset(0);

	cout << endl;
	A.printTransitions();
	A.printStates(A.makeTransition(0, 'b'));
}
int main() {
	NFA Ae;
	Ae.addState("s0", false, true);
	Ae.addState("s1", false, false);
	Ae.addState("s2");
	Ae.addState("s3");
	Ae.addState("s4");

	Ae.addTransition(0, 1, '\0');
	Ae.addTransition(1, 2, '\0');
	Ae.addTransition(1, 4, '\0');
	Ae.addTransition(2, 3, '\0');
	Ae.addTransition(4, 3, '\0');
	Ae.printStates(Ae.deltaFunction(0, '\0'));
}*/