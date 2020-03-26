#include <iostream>
#include <string>
#include <fstream>
using namespace std;


struct Date { int day, month, year; };

struct NecessaryData {
	int hour, min, sec;
	double angle = 0;
};

void moon();
void check_date(Date&);
char* read(const int);
void search_and_show(Date&, char*);
void findTimeZ(int&, int&);
void findHorizon(NecessaryData&, NecessaryData&, Date&);


int main() {
	moon();
	
	system("pause");
	return 0;
}

void moon() {
	Date date;
	check_date(date);

	char* buffer = read(date.year); // возвращает nullptr
	if (!buffer) 
		return;
	search_and_show(date, buffer);
	delete buffer;	
}

void check_date(Date& date) {
	char ch;
	cout << "Enter necessary date (DD.MM.YYYY): ";
	
	while (!(cin >> date.day >> ch) || !(cin >> date.month >> ch >> date.year) || 
		ch != '.' && ch != '/' || date.day < 1 || date.month < 1 || date.month > 12 ||
		(date.month == 2 && (date.day > 29 && date.year % 4 || date.day > 28 && date.year % 4 == 0 && date.year % 400 != 0 || date.day > 28 && date.year % 400 == 0)) ||
		(date.month < 8 && (date.month % 2 == 0 && date.day > 30 && date.month != 2 || date.month % 2 && date.day > 31)) || 
		(date.month > 7 && (date.month % 2 == 0 && date.day > 31 || date.month % 2 && date.day > 30))) {
		cout << "Input error!\nPlease, pay attention!\n";
		cin.clear();
		while (cin.get() != '\n');
		cout << "Enter necessary date (DD.MM.YYYY) again: ";
	}
}

char * read(const int year) {
	ifstream file("moon" + to_string(year) + ".dat", ios_base::binary | ios_base::in);
	if (!file.is_open())
		cout << "File is not found...\n";
	else {
		size_t sizeF = file.seekg(0, ios_base::end).tellg();
		char* buffer = new char[sizeF];

		if (!file.seekg(0, ios_base::beg).read(buffer, sizeF)) {
			cout << "Something went wrong...\nMaybe memory error\n";
			return nullptr;
		}
		file.close();
		return buffer;
	}
	return nullptr;
}

void search_and_show(Date& date, char* buffer) {
	char * ptrFile;
	date.day = date.year * 10000 + date.month * 100 + date.day;
	if (!(ptrFile = strstr(buffer, &(to_string(date.day)[0])))) { // переходим к необходимой дате
		cout << "There is no date which is equal to yours...\n";
		return;
	}

	printf("Your date:\t%04d/%02d/%02d\n", date.year, date.month, date.day%100);

	NecessaryData current, temp;
	int time_before = 0, stage = 0, zenith = 0; // stage для вывода всех 3-х состояний (восход, зенит, заход)
	double minimum = 360.0, maxZenith = 0.0;
	bool Mset = false;
	date.month = 0;
	do {
		sscanf_s(ptrFile, "%d %2d %2d %2d %*f %*f %lf %*f %*f %*f", &date.year, &current.hour, &current.min, &current.sec, &current.angle);

		if (current.angle * temp.angle < 0) {
			if (current.angle > 0) {
				cout << "Moonrise";
				findHorizon(current, temp, date);
				Mset = true;
				stage++;
			}
			else if (Mset && current.angle < 0) {
				cout << "Moonset";
				findHorizon(current, temp, date);
				stage++;
			}
		}
		// MAX
		else if (current.angle >= maxZenith && temp.angle > 0 && current.angle - temp.angle <= float(minimum < 0 ? -minimum : minimum)) {
			minimum = current.angle - temp.angle;
			maxZenith = current.angle;
			if (float(minimum) > 0.0)
				time_before = current.hour * 10000 + current.min * 100 + current.sec;
			else if (float(minimum) < 0.0) {
				date.month = temp.hour * 10000 + temp.min * 100 + temp.sec; // чтобы не создавать другую переменную используем неактивную month
				if (float(current.angle - temp.angle) == float(minimum))					
					findTimeZ(date.month, time_before);
			}
		}
		// обновляем данные
		// temp = current // Почему-то не работает...
		temp.angle = current.angle;
		temp.hour = current.hour;
		temp.min = current.min;
		temp.sec = current.sec;

		while ((ptrFile++)[0] != '\n'); // переходим на новую строку
	} while (stage < 2);

	printf("\"Zenith\":\t%02d:%02d:%02d\n", time_before / 10000, time_before / 100 % 100, time_before % 100);
}

void findTimeZ(int & month, int & time_before) { // время зенита
	month = ((((month - time_before) / 100 % 100) * 60 + (month - time_before) % 100)) / 2.0; // находим секунды
	time_before += month / 60 * 100 + month % 60; // добавляем секунды
	month = time_before / 100 % 100 + time_before % 100 / 60; // month выступает в качестве потенциальных лишних минут (для следующей операции)
	time_before = (time_before / 10000 + month / 60) * 10000 + month * 100 + time_before % 100 % 60; // считаем время "зенита"
}

void findHorizon(NecessaryData & current, NecessaryData & temp, Date& date) {
	temp.angle = temp.angle < 0 ? -temp.angle : temp.angle;
	temp.sec += temp.angle / (((current.angle < 0 ? -current.angle : current.angle) + temp.angle) / ((current.min - temp.min) * 60));
	temp.min += temp.sec / 60;
	temp.sec %= 60;
	temp.hour += temp.min / 60;
	temp.min %= 60;

	printf(":\t%02d:%02d:%02d", temp.hour, temp.min, temp.sec);
	if (date.day != date.year)
		printf(" of %04d/%02d/%02d\n", date.year / 10000, date.year / 100 % 100, date.year % 100);
	else
		cout << endl;
}
