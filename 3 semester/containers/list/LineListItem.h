#pragma once

template<typename T>
class LineListItem {
	T data;
	LineListItem* next = nullptr;
public:
	LineListItem(const T& data_next, LineListItem* next);
	~LineListItem();

	const T& get_data() const;
	LineListItem* get_next() const;
	template<typename T> friend class LineList;
	template<typename T> friend class CircularLineList;
};

template<typename T> 
LineListItem<T>::LineListItem(const T& item_data, LineListItem<T>* item_next) {
	data = item_data;
	next = item_next;
}

template<typename T>
LineListItem<T>* LineListItem<T>::get_next() const {
	return next;
}

template<typename T>
const T& LineListItem<T>::get_data() const {
	return data;
}

template<typename T>
LineListItem<T>::~LineListItem() {}