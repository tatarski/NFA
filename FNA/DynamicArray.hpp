#pragma once
#include<cmath>
#include<iostream>
using namespace std;

template <typename T>
class DynamicArray {
protected:
	int max_element_count,
		element_count;

	T* arr;
public:
	static DynamicArray<T> getConcatenation(DynamicArray<T> const arr1, DynamicArray<T> const arr2);
	static DynamicArray<T> getUnion(DynamicArray<T> const arr1, DynamicArray<T> const arr2);

	DynamicArray(int initial_size = 1, const T initial_arr[] = nullptr);
	DynamicArray(const DynamicArray<T>& old_object);
	DynamicArray<T>& operator=(const DynamicArray<T>& other);
	bool operator==(const DynamicArray<T>& other) const;
	T& operator [](int index);
	T operator [](int index) const;

	void empty();
	void push(T new_element);
	void reverse();
	T remove(int index);
	T pop();
	bool pushUnique(T el);

	//Getters
	DynamicArray<DynamicArray<T>> getPowerset() const;
	int indexOf(const T& el) const;
	int indexOf(const DynamicArray<T>& el) const;

	int lastIndexOf(const T& el) const;
	int length() const;

	T getElement(int index) const;
	T getLastElement() const;

	DynamicArray<T> getUnion(DynamicArray<T>const& other) const;
	DynamicArray<T> getConcatenation(DynamicArray<T> arr) const;
	DynamicArray<T> getIntersection(DynamicArray<T>const& other) const;
	DynamicArray<T> getUnique() const;

	// The bit for the first element is the leftmost bit
	DynamicArray<T> getSubset(int subsetNumber) const;
	DynamicArray<int> getSubsetIndecies(int subsetNumber) const;
	int getSubsetNumber(DynamicArray<int> subset) const;
	bool contains(const DynamicArray<T>& other) const;

	DynamicArray<T> getSubset(int begin, int end) const;

	~DynamicArray();
private:

	void realocate_arr(int new_max_size);
	int get_next_power_of_2(int N);
};


template <typename T>
DynamicArray<T> DynamicArray<T>::getConcatenation(DynamicArray<T> arr1, DynamicArray<T> arr2) {
	DynamicArray<T> resultArr = arr1;
	for (int i = 0; i < arr2.length(); i++) {
		resultArr.push(arr2[i]);
	}

	return resultArr;
}
template <typename T>
DynamicArray<T> DynamicArray<T>::getUnion(DynamicArray<T>const arr1, DynamicArray<T>const arr2) {
	DynamicArray<T> result = DynamicArray(arr1);
	for (int i = 0; i < arr2.length(); i++) {
		result.pushUnique(arr2[i]);
	}
	return result;
}
template <typename T>
DynamicArray<T>::DynamicArray(int initialSize, const T initialArr[]) {
	this->element_count = 0;
	this->realocate_arr(this->get_next_power_of_2(initialSize));
	if (initialArr != nullptr) {
		for (int i = 0; i < initialSize; i++) {
			this->arr[i] = initialArr[i];

		}
		this->element_count = initialSize;
	}
}



template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray<T> const& old_object) : DynamicArray<T>(old_object.length(), old_object.arr) {
}

template <typename T>
int DynamicArray<T>::length() const {
	return this->element_count;
}

template <typename T>
T DynamicArray<T>::getElement(int index) const {
	return this->arr[index];
}

template <typename T>
T DynamicArray<T>::getLastElement() const {
	return this->getElement(this->length() - 1);
}

template <typename T>
void DynamicArray<T>::empty() {
	this->element_count = 0;
	this->realocate_arr(1);
}

template <typename T>
DynamicArray<T> DynamicArray<T>::getConcatenation(DynamicArray<T> arr) const {
	return DynamicArray<T>::getConcatenation(*this, arr);
}


template <typename T>
void DynamicArray<T>::push(T element) {
	if (this->element_count == this->max_element_count) {
		this->realocate_arr(get_next_power_of_2(element_count));
	}
	arr[element_count] = element;
	this->element_count++;
}

template<typename T>
inline void DynamicArray<T>::reverse()
{
	for (int i = 0; i < this->length()/2; i++) {
		T temp = this->getElement(i);
		this->operator[](i) = this->getElement(this->length() - i - 1);
		this->operator[](this->length() - i - 1) = temp;
	}
}

template <typename T>
T DynamicArray<T>::remove(int index) {
	this->arr[index] = this->pop();
}

template <typename T>
int DynamicArray<T>::indexOf(const T& el) const {
	for (int i = 0; i < this->length(); i++) {

		T curEl = (this->getElement(i));
		if (el == curEl) {
			return i;
		}
	}
	return -1;
}

template<typename T>
inline int DynamicArray<T>::indexOf(const DynamicArray<T>& list) const
{
	int consequtiveEqualCount = 0;
	for (int i = 0; i < this->length(); i++) {
		if (list[consequtiveEqualCount] == this->arr[i]) {
			consequtiveEqualCount++;
			if (consequtiveEqualCount == list.length()) {
				return i - consequtiveEqualCount + 1;
			}
		}
		else {
			consequtiveEqualCount = 0;
		}
	}
	return -1;
}

template<typename T>
inline int DynamicArray<T>::lastIndexOf(const T& el) const
{
	for (int i = this->length()-1; i>=0; i--) {

		T curEl = (this->getElement(i));
		if (el == curEl) {
			return i;
		}
	}
}

template <typename T>
T DynamicArray<T>::pop() {
	this->element_count--;
	T el = arr[element_count];
	return el;
}
template <typename T>
bool DynamicArray<T>::pushUnique(T el) {
	if (this->indexOf(el) == -1) {
		this->push(el);
		return true;
	}
	else {
		return false;
	}
}


template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other) {
	if (this != &other) {
		this->empty();
		for (int i = 0; i < other.element_count; i++) {
			this->push(other.getElement(i));
		}
	}
	return *this;
}


template <typename T>
T& DynamicArray<T>::operator[](int index) {
	return arr[index];
}

template <typename T>
T DynamicArray<T>::operator[](int index) const {
	return arr[index];
}
template <typename T>
DynamicArray<DynamicArray<T>> DynamicArray<T>::getPowerset() const {
	DynamicArray<DynamicArray<T>> powerset;
	for (int i = 0; i < pow(2, this->length()); i++) {
		DynamicArray<T> subset;
		for (int j = 0; j < this->length(); j++) {
			if ((int)i & (int)pow(2, j)) {
				subset.push(this->getElement(j));
			}
		}
		powerset.push(subset);
	}
	return powerset;
}
template <typename T>
DynamicArray<T> DynamicArray<T>::getUnion(DynamicArray<T>const& other) const {
	DynamicArray<T> result = DynamicArray(*this);
	for (int i = 0; i < other.length(); i++) {
		result.pushUnique(other[i]);
	}
	return result;
}

template <typename T>
DynamicArray<T> DynamicArray<T>::getIntersection(DynamicArray<T>const& other) const {
	DynamicArray<T> result;
	for (int i = 0; i < this->length(); i++) {
		for (int j = 0; j < other.length(); j++) {
			T currentEl = this->getElement(i);
			if (this->indexOf(currentEl) != -1 && other.indexOf(currentEl) != -1) {
				result.pushUnique(currentEl);
			}
		}
	}
	return result;
}

template<typename T>
DynamicArray<T> DynamicArray<T>::getSubset(int subsetNumber) const {
	DynamicArray<T> subset = DynamicArray<T>();
	for (int i = 0; subsetNumber != 0; subsetNumber /= 2, i++) {
		if (subsetNumber % 2) {
			subset.push(this->getElement(i));
		}
	}
	return subset;
}
template <typename T>
DynamicArray<T> DynamicArray<T>::getUnique() const {
	DynamicArray<T> uniqueArr;
	for (int i = 0; i < this->length(); i++) {
		if (uniqueArr.indexOf(this->getElement(i)) == -1) {
			uniqueArr.push(this->getElement(i));
		}
	}
	return uniqueArr;
}
template <typename T>
DynamicArray<int> DynamicArray<T>::getSubsetIndecies(int subsetNumber) const {
	DynamicArray<int> subset;
	for (int i = 0; subsetNumber != 0; subsetNumber /= 2, i++) {
		if (subsetNumber % 2) {
			subset.push(i);
		}
	}
	return subset;
}

template <typename T>
int DynamicArray<T>::getSubsetNumber(DynamicArray<int> subset) const {
	int subsetNumber = 0;
	for (int i = 0; i < subset.length(); i++) {
		if (subset[i] != -1) {
			subsetNumber += (int)pow(2, subset[i]);
		}
		else {
			return -1;
		}
	}
	return subsetNumber;
};

template <typename T>
bool DynamicArray<T>::operator==(const DynamicArray<T>& other) const {
	if (this->length() != other.length()) {
		return false;
	}
	for (int i = 0; i < this->length(); i++) {
		if (!(this->getElement(i) == other.getElement(i))) {
			return false;
		}
	}
	return true;
}
// Returns a subset from index begin(inclusive) to index end(exclusive)
template <typename T>
DynamicArray<T> DynamicArray<T>::getSubset(int begin, int end) const {
	DynamicArray<T> result;
	for (int i = begin; i < end; i++) {
		result.push(this->getElement(i));
	}
	return result;
}

template <typename T>
bool DynamicArray<T>::contains(const DynamicArray<T>& other) const {
	for (int i = 0; i < other.length(); i++) {
		if (this->indexOf(other[i]) == -1) {
			return false;
		}
	}
	return true;
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
	delete[] this->arr;
}

template <typename T>
void DynamicArray<T>::realocate_arr(int new_max_size) {
	T* new_arr = new T[new_max_size];
	this->max_element_count = new_max_size;
	for (int i = 0; i < new_max_size; i++) {
		new_arr[i] = T();
	}
	for (int i = 0; i < this->length(); i++) {
		new_arr[i] = this->arr[i];
	}
	if (this->element_count > 0) {
		delete[] this->arr;
	}
	this->arr = new_arr;
}

template <typename T>
int DynamicArray<T>::get_next_power_of_2(int N) {
	if (N == 0) {
		return 1;
	}
	return (int)pow(2, (int)(log2(N) + 1));
}