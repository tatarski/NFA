#pragma once

template <class T>
class DynamicArray {
public:
	DynamicArray(int initialSize = 0, const T initialArr[] = nullptr);
	DynamicArray(DynamicArray<T> const& old_object);
	
	int length() const;
	T getLastElement() : getElement(this->element_count-1);
	T getElement(int index);

	void push(T new_element);
	T pop();

	operator [](int index) : getElement(index);

	~DynamicArray();
private:
	int max_element_count,
		element_count;
	T arr[];
	void realocate_arr() {

	}
};