#include "String.h"

String::String() :DynamicArray<char>(1) {};

String::String(DynamicArray<char> const& arr) : DynamicArray<char>(arr) {};

String::String(const char str[]) : DynamicArray<char>(1) {
	for (int i = 0; str[i] != '\0'; i++) {
		this->push(str[i]);
	}
};

String String::concat(String str1, String str2) {
	String new_str = String(str1);

	for (int i = 0; i < str2.length(); i++) {
		new_str.push(str2.getElement(i));
	}
	return new_str;
};


String operator+(String str, String str2) {
	String result = String::concat(str, str2);
	return result;
};

String operator*(String str, int N) {
	String result = "";
	for (int i = 0; i < N; i++) {
		result = String::concat(result, str);
	}
	return result;
};

ostream& operator<<(ostream& os, const String& str) {
	for (int i = 0; i < str.length(); i++) {
		os << str.getElement(i);
	}
	return os;
};

istream& operator>>(istream& is, String& str) {
	str.empty();
	char input[MAX_INPUT_STRING_LENGTH];
	is >> input;
	for (int i = 0; input[i] != '\0'; i++) {
		str.push(input[i]);
	}
	return is;
};
