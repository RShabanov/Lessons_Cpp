#pragma once
#include <climits>
#include <iostream>
#include "VectorException.h"
//using std::ostream;
using namespace std;
//using ull = unsigned long long;


const int DEFAULT_CAPACITY = 8;

template<typename T>
class Vector
{

	int _size, _capacity;
	static const int _max_size = INT_MAX;
	T* ptr = nullptr;

	void common_constructor(int);
	void increase_capacity(const int);

public:
	Vector(int = 0);
	Vector(int, const T&);
	Vector(const Vector& other);
	~Vector();

	// access
	T& operator[](const int) const;
	T& at(const int) const;

	// modification
	void insert(const int, const T&);
	void insert(const int index, const Vector& other);
	void push_back(const T&);
	void remove(const int);
	void pop_back();
	void clear();

	// check
	bool is_empty() const;

	// size stuff
	void resize(const int);
	int max_size() const;
	int size() const;
	int capacity() const;

	// operators
	const Vector& operator=(const Vector&);
	bool operator==(const Vector&) const;

	// output
	friend ostream& operator<< (ostream&, const Vector&);

};



template<typename T>
void Vector<T>::common_constructor(int start_capacity) {
	if (start_capacity <= 0)
		_capacity = DEFAULT_CAPACITY;
	else
		_capacity = start_capacity;
	ptr = new T[_capacity];
	_size = 0;
}

template<typename T>
Vector<T>::Vector(const int start_capacity) {
	common_constructor(start_capacity);
}


template<typename T>
Vector<T>::Vector(const int start_capacity, const T& value) {
	common_constructor(start_capacity);

	for (T* temp_ptr = ptr; temp_ptr != (ptr + start_capacity); temp_ptr++)
		*temp_ptr = value;
}

// конструктор копирования
template<typename T>
Vector<T>::Vector(const Vector<T>& other) {
	_size = other._size;
	_capacity = other._capacity;
	ptr = new T[_capacity];

	for (int i = 0; i < _capacity; i++)
		ptr[i] = other.ptr[i];
}


// деструктор
template<typename T>
Vector<T>::~Vector() {
	if (ptr != nullptr)
		delete[] ptr;
}


template<typename T>
T& Vector<T>::operator[](const int index) const {
	if (index < 0 || index >= _size)
		throw VectorException();
	else
		return ptr[index];
}

template<typename T>
T& Vector<T>::at(const int index) const {
	return (*this)[index];
}



// modifications

template<typename T>
void Vector<T>::insert(const int index, const T& value) {
	if (index < 0 || index > _size)
		throw VectorException();
	if (_size == _capacity)
		increase_capacity(_size + 1);
	for (int i = _size - 1; i >= index; i--)
		ptr[i + 1] = ptr[i];
	_size++;
	ptr[index] = value;
}

template<typename T>
void Vector<T>::insert(const int index, const Vector<T>& other) {
	if (index < 0 || index > _size)
		throw VectorException();
	if ((_size + other._size) == _capacity)
		increase_capacity(_size + other._size + 1);

	for (int i = _size + other._size - 1; i >= index + other._size; i--)
		ptr[i] = ptr[i - other._size];

	for (int i = other._size - 1; i >= 0; i--)
		ptr[index + i + 1] = other.ptr[i];

	size += other._size;
}

template<typename T>
void Vector<T>::push_back(const T& value) {
	insert(_size, value);
}

template<typename T>
void Vector<T>::increase_capacity(const int new_capacity) {
	_capacity = new_capacity < (_capacity << 1) ?
		(_capacity << 1) : new_capacity;
	
	T* new_ptr = new T[_capacity];
	for (int i = 0; i < _size; i++)
		new_ptr[i] = ptr[i];
	delete[] ptr;
	ptr = new_ptr;
}

template<typename T>
void Vector<T>::remove(const int index) {
	if (index < 0 || index >= _size)
		throw VectorException();
	for (int i = index; i < _size - 1; i++)
		ptr[i] = ptr[i + 1];
	ptr[size - 1] = 0;
	size--;
}

template<typename T>
void Vector<T>::pop_back() {
	remove(_size - 1);
}

template<typename T>
void Vector<T>::clear() {
	for (T* temp = ptr; temp != (ptr + _size); temp++)
		*temp = 0;
}


template<typename T>
int Vector<T>::size() const {
	return _size;
}

template<typename T>
int Vector<T>::max_size() const {
	return _max_size;
}

template<typename T>
int Vector<T>::capacity() const {
	return _capacity;
}

template<typename T>
bool Vector<T>::is_empty() const {
	return (_size) ? true : false;
}

template<typename T>
void Vector<T>::resize(const int new_size) {
	if (new_size < 0)
		throw VectorException();
	if (new_size <= _size)
		for (int i = new_size + 1; i < _size; i++)
			ptr[i] = 0;
	else {
		if (new_size > _capacity)
			increase_capacity(new_size + 1);
		_size = new_size;
	}
}

template<typename T>
const Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
	if (this == &other)
		return *this;
	if (_capacity != other._capacity) {
		delete[] ptr;
		ptr = new T[other._capacity];
		_capacity = other._capacity;
	}
	size = other._size;
	for (int i = 0; i < _size; i++)
		ptr[i] = other.ptr[i];
	return *this;
}

template<typename T>
bool Vector<T>::operator==(const Vector& other) const {
	if (_size == other._size) {
		for (int i = 0; i < _size; i++)
			if (ptr[i] != other.ptr[i]) return false;
		return true;
	}
	return false;
}




template<typename T>
ostream& operator<< (ostream& out, const Vector<T>& obj) {
	out << "Total size: " << obj._size << std::endl;
	for (int i = 0; i < obj._size; i++)
		out << obj.ptr[i] << std::endl;
	return out;
}
