#include "DynamicArray.h"
#include<cmath>

template <class T>
DynamicArray<T>::DynamicArray<T>(int initialSize, T initialArr[]) {
	this->realocate_arr(initialSize);

	if (initialArr != nullptr) {
		for (int i = 0; i < initialSize; i++) {
			this->arr[i] = initialArr[i];
		}
	}
}

template <class T>
DynamicArray<T>::DynamicArray(DynamicArray<T> const& old_object):DynamicArray(old_object.length(), old_object.arr) {
	
}

template <class T>
int DynamicArray<T>::length() const{
	return this->element_count;
}

template <class T>
T DynamicArray<T>::getElement(int index) const{
	return this->arr[index];
}

template <class T>
T DynamicArray<T>::getLastElement() const {
	return this->getElement(this->length() - 1);
}

template <class T>
void DynamicArray<T>::push(T element) {
	if (this->element_count == this->max_element_count) {
		this->realocate_arr(getNextPowerOf2(element_count));
	}
	this->arr[element_count] = element;
	this->element_count++;
}

template <class T>
T DynamicArray<T>::pop() {
	this->element_count--;
	T el = arr[element_count];
	delete arr[element_count];
	return this->arr[el];
}


template <class T>
T& DynamicArray<T>::operator[](int index) {
	return this->arr[index];
}

template <class T>
DynamicArray<T>::~DynamicArray() {
	delete[] this->arr;
}

template <class T>
void DynamicArray<T>::realocate_arr(int new_max_size) {
	T* new_arr = new T[new_max_size];
	for (int i = 0; i < this->element_count; i++) {
		new_arr[i] = this->arr[i];
	}
	delete[] this->arr;
	this->arr = new_arr;
}

template <class T>
int DynamicArray<T>::getNextPowerOf2(int N) {
	return pow(2, log2(N) + 1);
}