#pragma once
#include<cmath>
#include<iostream>

template <class T>
class DynamicArray {
protected:
	int max_element_count,
		element_count;

	T* arr;
public:
	DynamicArray(int initial_size = 1, T initial_arr[] = nullptr);
	DynamicArray(const DynamicArray<T>& old_object);

	int length() const;
	T getElement(int index) const;
	T getLastElement() const;
	void empty();
	void push(T new_element);
	
	T remove(int index);
	T pop();

private:
	void realocate_arr(int new_max_size);
	int get_next_power_of_2(int N);
}