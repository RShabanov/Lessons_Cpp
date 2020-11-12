#include <iostream>
#include "LineList.h"
#include "CircularLineList.h"
using namespace std;


void lineList_test();

void circular_lineList_test();

void Josephus_problem();

int main() {

	//circular_lineList_test();

	//lineList_test();
	Josephus_problem();
	
	cin.get();
	cin.get();
	return 0;
}


void Josephus_problem() {
	int people = 0, step = 0;
	while (people < 2) {
		cout << "Enter number of people (people >= 2): ";
		cin >> people;
	}

	while (step < 2) {
		cout << "Enter step (step >= 2): ";
		cin >> step;
	}

	CircularLineList<int> circle;
	for (int i = people; i > 0; i--)
		circle.insert_first(i);

	cout << "\nPeople: " << circle << endl;

	step -= 2;
	// это работает только из-за 1 строчки в delete_after():
	// start = ptr->next;
	// которая выполняется после удаления
	// delete_after() возвращает итератор, указывающий на новый старт
	for (auto it = circle.begin() + step; circle.size() > 1; it = circle.delete_after(it) + step);
	
	cout << "Only person who can servive: " << circle << endl;
}



void circular_lineList_test() {
	CircularLineList<int> list;
	cout << "Start: " << list << endl;
	list.insert_first(10);
	LineListItem<int>* ptr = list.get_start();
	list.insert_after(ptr, 15);
	list.insert_after(ptr->get_next(), 12);
	list.insert_first(7);

	cout << "End: " << list << endl;
	cout << "Start: " << list.get_start()->get_data() << endl;
	cout << "Size of the list: " << list.size() << endl;
	cout << "List[2]: " << list[2] << endl;

	list.delete_after(ptr);
	cout << "Remove list[2]: " << list << endl;

	list.delete_first();
	cout << "Delete first element: " << list << endl;
	cout << "Start: " << list.get_start()->get_data() << endl;
	cout << "Size of the list: " << list.size() << endl;
	ptr = list.get_start();
	cout << "Pointer of last element: " << ptr->get_next()->get_next()->get_data() << endl;

	list.insert_first(5);
	cout << "Insert first: " << list << endl;
	cout << "Start: " << list.get_start()->get_data() << endl;
	cout << "Size of the list: " << list.size() << endl;
	ptr = list.get_start();
	cout << "Pointer of last element: " << ptr->get_next()->get_next()->get_next()->get_data() << endl;


}


void lineList_test() {
	LineList<int> list; // Óêàçûâàåì, ñïèñîê êàêîãî òèïà
	cout << "Start: " << list << endl;
	list.insert_first(10);
	LineListItem<int>* ptr = list.get_start();
	list.insert_after(ptr, 15);
	list.insert_after(ptr->get_next(), 12);
	list.insert_first(7);

	cout << "End: " << list << endl;
	cout << "Length of the list: " << list.size() << endl;
	cout << "List[2]: " << list[2] << endl;
	//cout << "List[6]: " << list[6] << endl;

}
