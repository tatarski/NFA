#include "String.h"
#include "String.h"

String::String() :DynamicArray<char>(1) {};

String::String(DynamicArray<char> const& arr) : DynamicArray<char>(arr) {}

String::String(char symbol) : String()
{
	this->push(symbol);
}
String::String(int number)
{
	if (number == 0) {
		this->push('0');
	}
	else {
		for (; number > 0; number = number / 10) {
			this->push('0' + number % 10);
		}
		this->reverse();
	}
}
int String::parseInt() const
{
	int result = 0, l = this->length();
	for (int i = 0; i < l; i++) {
		result = (result + (this->getElement(i) - '0')) * 10;
	}
	return result / 10;
}
bool String::operator==(const char word[]) const
{
	int l = this->length();
	if (word[l] != '\0') {
		return false;
	}
	for (int i = 0; i < l; i++) {
		if (this->arr[i] != word[i]) {
			return false;
		}
	}
	return true;
};
bool String::operator==(const String& s) const {
	int l = this->length();
	if (l != s.length()) {
		return false;
	}
	for (int i = 0; i < l; i++) {
		if (this->arr[i] != s[i]) {
			return false;
		}
	}
	return true;
}

String::String(const char str[]) : DynamicArray<char>(1) {
	for (int i = 0; str[i] != '\0'; i++) {
		this->push(str[i]);
	}
};

String String::concat(const String& str1, const String& str2) {
	String new_str = String(str1);
	int l = str2.length();
	for (int i = 0; i < l; i++) {
		new_str.push(str2.getElement(i));
	}
	return new_str;
};


String operator+(const String& str1, const String& str2) {
	String result = String::concat(str1, str2);
	return result;
};

String operator*(const String& str, int N) {
	String result = "";
	for (int i = 0; i < N; i++) {
		result = String::concat(result, str);
	}
	return result;
};

ostream& operator<<(ostream& os, const String& str) {
	int l = str.length();
	for (int i = 0; i < l; i++) {
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
