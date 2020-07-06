#pragma once
#include<cmath>
#include<iostream>
using namespace std;

template <typename T>
class DynamicArray {
protected:
	// max_element_count*sizeof(T) = all available memory
	int max_element_count,
		// element_count*sizeof(T) = currently occupied memory
		element_count;

	// element_count is the number of elements that has been added to the this->arr
	// max_element_count is the maximum number of elements this->arr can hold

	// When element_count reaches max_element_count, then this->realocate_array(N)

	T* arr;
public:
	DynamicArray(int initial_size = 1, const T initial_arr[] = nullptr);

	// Copy constructor - creates a copy of old_object.arr
	DynamicArray(const DynamicArray<T>& old_object);

	DynamicArray<T>& operator=(const DynamicArray<T>& other);

	// Checks if this.arr and other.arr have the same elements and the same order
	bool operator==(const DynamicArray<T>& other) const;
	// Index operator for getting const element reference
	const T& operator [](int index) const;

	// Index operator for getting element value
	T& operator [](int index);

	// Empties and reallocates array
	void empty();

	// Add a new element on the right side of this->arr
	void push(const T& new_element);

	// Reverses the order of elements in this->arr
	void reverse();

	// Removes element
	void remove(int index);

	// Removes the last element and returns in
	T pop();

	// Adds el at the right of this->arr only if el is not in arr
	bool pushUnique(const T& el);

	// Get the powerset of this->arr
	DynamicArray<DynamicArray<T>> getPowerset() const;

	// Returns index of first occurence of el in this->arr
	int indexOf(const T& el) const;

	// Returns index of first occurence of sequence seq in this->arr
	int indexOf(const DynamicArray<T>& seq) const;

	// Returns index of last occurence of el in this->arr
	int lastIndexOf(const T& el) const;

	// Returns number of occupied cells in this->arr
	int length() const;

	// Returns the value of element in this->arr
	T getElement(int index) const;

	// Returns the value of the right-most element in this->arr
	T getLastElement() const;

	// Returns an array of unique elements
	// Represents the union between this->arr and other.arr
	DynamicArray<T> getUnion(const DynamicArray<T>& other) const;

	// Returns an array of unique elements
	// Represents the concatenation between this->arr and other.arr
	DynamicArray<T> getConcatenation(const DynamicArray<T>& arr) const;

	// Returns an array of unique elements
	// Represents the intersection between this->arr and other.arr
	DynamicArray<T> getIntersection(const DynamicArray<T>& other) const;

	// Returns set unique elements derived from this->arr
	DynamicArray<T> getUnique() const;

	// Receives a number raging from 0 to 2^this.length()-1 as input
	// Returns a subset of elements from this->arr
	// Each input number represents one subset of the dynamic array
	DynamicArray<T> getSubset(int subsetNumber) const;

	// Returns new array with elements of this.arr in range [begin, end)
	DynamicArray<T> getSubset(int begin, int end) const;

	// Receives a number raging from 0 to 2^this.length()-1 as input
	// Returns a subset of indecies for elements from this->arr
	// Each input number represents one subset of the dynamic array
	DynamicArray<int> getSubsetIndecies(int subsetNumber) const;

	// Receives array of indecies as input
	// Returns a number, ranging from 0 to 2^this.length()-1
	// Each number represents a unique subset of the dynamic array
	int getSubsetNumber(const DynamicArray<int>& subset) const;

	// Check whether each element of other array is in this array
	bool contains(const DynamicArray<T>& other) const;

	// Destrutor to remove arr
	~DynamicArray();

	//private:

		// Realocate heap memory for the dynamic array
		// Copies as much old elements to the new memory as it can
	void realocate_arr(int new_max_size);

	// Utility that returns the first power of 2, greater than N
	int get_next_power_of_2(int N);
};

template <typename T>
DynamicArray<T>::DynamicArray(int initialSize, const T initialArr[]) {
	this->element_count = 0;
	this->realocate_arr(this->get_next_power_of_2(initialSize));
	if (initialArr != nullptr) {
		for (int i = 0; i < initialSize; i++) {
			this->push(initialArr[i]);
		}
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
	this->realocate_arr(2);
	this->element_count = 0;
}

template <typename T>
DynamicArray<T> DynamicArray<T>::getConcatenation(const DynamicArray<T>& arr) const {
	return DynamicArray<T>::getConcatenation(*this, arr);
}

template <typename T>
void DynamicArray<T>::push(const T& element) {
	if (this->element_count == this->max_element_count) {
		this->realocate_arr(get_next_power_of_2(element_count));
	}
	arr[element_count] = element;
	this->element_count++;
}

template<typename T>
inline void DynamicArray<T>::reverse()
{
	for (int i = 0; i < this->length() / 2; i++) {
		T temp = this->getElement(i);
		this->operator[](i) = this->getElement(this->length() - i - 1);
		this->operator[](this->length() - i - 1) = temp;
	}
}

template <typename T>
void DynamicArray<T>::remove(int index) {
	this->arr[index] = this->pop();
}

template <typename T>
int DynamicArray<T>::indexOf(const T& el) const {
	for (int i = 0; i < this->length(); i++) {

		if (el == this->arr[i]) {
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
	for (int i = this->length() - 1; i >= 0; i--) {

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
bool DynamicArray<T>::pushUnique(const T& el) {
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
const T& DynamicArray<T>::operator[](int index) const {
	return arr[index];
}

template <typename T>
T& DynamicArray<T>::operator[](int index) {
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
			if (this->indexOf(currentEl) != -1 && other.indexOf(currentEl) != -1 && result.indexOf(currentEl) == -1) {
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
int DynamicArray<T>::getSubsetNumber(const DynamicArray<int>& subset) const {
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

	// Initialize each element
	for (int i = 0; i < new_max_size; i++) {
		new_arr[i] = T();
	}
	// Copy each element of current array
	int l = this->element_count;
	int new_element_count = 0;
	for (new_element_count = 0;
		new_element_count < l && new_element_count < new_max_size;
		new_element_count++
		) {
		new_arr[new_element_count] = this->arr[new_element_count];
	}
	// Delete current array
	if (this->element_count > 0) {
		delete[] this->arr;
	}
	// Array now points to the copied array
	this->arr = new_arr;
	this->element_count = new_element_count;
}

template <typename T>
int DynamicArray<T>::get_next_power_of_2(int N) {
	if (N == 0) {
		return 1;
	}
	return (int)pow(2, (int)(log2(N) + 1));
}