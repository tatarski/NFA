#pragma once
#include<cmath>
#include<iostream>
#include "DynamicArray.hpp"

using namespace std;

const int MAX_INPUT_STRING_LENGTH = 100;

class String :public DynamicArray<char> {
public:
	static String concat(String str1, String str2);

	String();
	String(const char str[]);
	String(DynamicArray<char> const& arr);
	String(char symbol);
	String(int number);

	int parseInt() const;
	friend String operator+(String str, String str2);
	friend String operator*(String str, int N);
	friend ostream& operator<<(ostream& io, const String& str);
	friend istream& operator>>(istream& io, String& str);
};