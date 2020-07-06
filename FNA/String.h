#pragma once
#include<cmath>
#include<iostream>
#include "DynamicArray.hpp"

using namespace std;

const int MAX_INPUT_STRING_LENGTH = 100;

class String :public DynamicArray<char> {
public:
	// Static method that does the concatenation of two strings
	static String concat(const String& str1, const String& str2);

	// Create empty string
	String();

	// Create string from char array
	String(const char str[]);

	// Create string from DynamicArray<char>
	String(DynamicArray<char> const& arr);

	// Create string from only one symbol
	String(char symbol);

	// Create a string from number
	String(int number);

	// Returns the value of the string interpeted as an int
	int parseInt() const;

	bool operator==(const char word[]) const;

	bool operator==(const String& s) const;

	// Returns a new string - concatenation of str and str2
	friend String operator+(const String& str, const String& str2);

	// Returns a new string - str concatenated N times
	friend String operator*(const String& str, int N);

	friend ostream& operator<<(ostream& io, const String& str);
	friend istream& operator>>(istream& io, String& str);
};