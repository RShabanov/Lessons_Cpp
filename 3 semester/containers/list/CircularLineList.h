#pragma once
#include "LineList.h"

template<typename T>
class CircularLineList : public LineList<T> {

	CircularLineList(const CircularLineList&);
	CircularLineList& operator=(const CircularLineList&);

	LineListItem<T>* get_prestart();
public:
	using LineList<T>::start;

	CircularLineList();
	~CircularLineList();

	void delete_first();
	void delete_after(LineListItem<T>*);
	void insert_first(const T&);

};

template<typename T>
CircularLineList<T>::CircularLineList() : LineList<T>() {};

template<typename T>
CircularLineList<T>::~CircularLineList() {
	for (LineListItem<T>* ptr = start; ptr; ptr = start)
		delete_first();
}

// �.�. ������������ ���������������� ������
// ���������� ���������� �������� � ������� ��������
// ������������ �� ������� �������
template<typename T>
LineListItem<T>* CircularLineList<T>::get_prestart() {
	LineListItem<T>* ptr = start;
	if (ptr && ptr->next)
		while (ptr->next != start)
			ptr = ptr->get_next();
	return ptr;
}


template<typename T>
void CircularLineList<T>::delete_first() {
	if (start) {
		// ���� ��������� ��������� �������
		// ������� �����������
		if (start->next == start)
			start->next = nullptr;
		else {
			LineListItem<T>* ptr = get_prestart();
			if (ptr->next)
				ptr->next = start->next;
		}
		LineList<T>::delete_first();
	}
	else throw LineListException();
}

template<typename T>
void CircularLineList<T>::delete_after(LineListItem<T>* ptr) {
	if (ptr && ptr->next) {
		if (start->next == start)
			delete_first();
		else {
			LineList<T>::delete_after(ptr);
			start = ptr->next;
		}
	}
	else throw LineListException();
}

template<typename T>
void CircularLineList<T>::insert_first(const T& data) {
	// ������ ������, �.�. get_prestart() ��������� � ���� ������
	if (LineList<T>::size() == 0) {
		LineList<T>::insert_first(data);
		start->next = start;
	}
	else {
		LineListItem<T>* ptr = get_prestart();
		LineList<T>::insert_first(data);
		ptr->next = start;
	}
}