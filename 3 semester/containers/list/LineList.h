#pragma once
#include <iostream>
#include "LineListItem.h"
#include "LineListException.h"
using std::ostream;

template<typename T>
class LineList
{
	LineList(const LineList&);
	LineList& operator=(const LineList&);
	int list_size;

protected:
	LineListItem<T>* start;
	
public:
	LineList();
	~LineList();

	LineListItem<T>* get_start() const;
	int size() const;

	void delete_first();
	void delete_after(LineListItem<T>*);
	void insert_first(const T&);
	void insert_after(LineListItem<T>*, const T&);

	template<typename T> friend ostream& operator<<(ostream&, const LineList&);
	
	T operator[](int);
};


template<typename T>
LineList<T>::LineList() { start = nullptr; list_size = 0; }

template<typename T>
LineList<T>::~LineList() {
	while (start) 
		delete_first();
}

template<typename T>
LineListItem<T>* LineList<T>::get_start() const { return start; }

template<typename T>
void LineList<T>::delete_first() {
	if (start) {
		LineListItem<T>* temp = start->next;
		delete start;
		start = temp;
		list_size--;
	}
	else throw LineListException();
}

template<typename T>
void LineList<T>::insert_first(const T& data) {
	LineListItem<T>* second_item = start;
	start = new LineListItem<T>(data, second_item);
	list_size++;
}

template<typename T>
void LineList<T>::delete_after(LineListItem<T>* ptr) {
	if (ptr && ptr->next) {
		LineListItem<T>* temp = ptr->next;
		ptr->next = ptr->next->next;
		delete temp;
		list_size--;
	}
	else throw LineListException();
}

template<typename T>
void LineList<T>::insert_after(LineListItem<T>* ptr, const T& data) {
	if (ptr) {
		LineListItem<T>* temp = ptr->next;
		ptr->next = new LineListItem<T>(data, temp);
		list_size++;
	}
	else throw LineListException();
}

template<typename T>
ostream& operator<<(ostream& out, const LineList<T>& list) {
	LineListItem<T>* ptr = list.get_start();
	if (!ptr) out << "Empty\n";
	else {
		int list_size = list.size();
		for (int i = 0; i < list_size && ptr; i++) {
			out << ptr->get_data() << ' ';
			ptr = ptr->get_next();
		}
	}

	return out;
}

template<typename T>
T LineList<T>::operator[](int index) {
	if (index < 0 || index >= list_size) throw LineListException();
	else {
		LineListItem<T>* ptr = start;
		while (index-- > 0) ptr = ptr->get_next();
		return ptr->data;
	}
}

template<typename T>
int LineList<T>::size() const { return list_size; }
