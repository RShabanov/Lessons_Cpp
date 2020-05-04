#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <string>
constexpr auto ERROR_DIV_BY_ZERO = -2;
using namespace std;


//---------1----------
double area(double R) { return R * R * M_PI; }
void fst_sample() {
	double r = 1.0;
	cout << "��� ����� � �������� " << r << " ������� = " << area(r) << endl;
	double(*pfunc)(double);
	pfunc = area;
	cout << "��� ����� � �������� " << r << " ������� = " << (*pfunc)(r) << endl;
}


//---------2----------
float add(float a, float b) { return a + b; }
void snd_sample() {
	float x = 2.1, y = 4.8;
	float(*pfunc)(float, float);
	printf("Sum of %.3f and %.3f is equal to %.3f\n", x, y, add(x, y));
	pfunc = add;
	printf("Sum of %.3f and %.3f is equal to %.3f\n", x, y, pfunc(x, y));
}


//---------3----------
void check(char*, char*, int(*cmp)(const char*, const char*));

void thd_sample() {
	char s1[80], s2[80];
	int(*pfunc)(const char*, const char*);
	pfunc = strcmp;
	printf("������� ��� ������\n");

	cin.getline(s1, 80);
	cin.getline(s2, 80);

	check(s1, s2, pfunc);
}

void check(char*a, char*b, int(*cmp)(const char*, const char*)) {
	cout << "�������� �� ����������\n";
	if (!(cmp(a, b))) cout << "�����\n";
	else cout << "�� �����\n";
}


//---------5----------
void test1() { cout << "����������� ���� �1" << endl; }
void test2() { cout << "����������� ���� �2" << endl; }
void test3() { cout << "����������� ���� �3" << endl; }

void(*tests[])() = { test1, test2, test3 };

void fifth_sample() { for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) tests[i](); }


//---------6----------
int calculate(int op1, int op2, int(*func)(int, int)) { return func(op1, op2); }

int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) {
	if (!b) exit(ERROR_DIV_BY_ZERO);
	return a / b;
}
int bals(int a, int b) { return a % b; }
int fastpow(int a, int b) {
	if (!b) return 1;
	if (b % 2) return a * fastpow(a, b - 1);
	else return fastpow(a*a, b / 2);
}

typedef int(*fint_t)(int, int);
fint_t foper[] = { add, subtract, multiply, divide, bals, fastpow };

void sth_sample() {
	char coper[] = { '+','-','*','/','%','^' };
	int noper = sizeof(coper) / sizeof(coper[0]);
	do {
		char buff[120];
		char* str = buff;
		char* endptr;
		char oper;

		cout << "��������� ��� ���������� (<������ �����><����><������ �����>): " << flush;
		cin >> buff;

		int fst, snd;

		fst = strtod(str, &endptr);
		oper = *endptr++;
		snd = strtod(str = endptr, &endptr);

		int i;
		for (i = 0; i < noper; i++)
			if (oper == coper[i]) {
				cout << fst << ' ' << oper << ' ' << snd << " = " << calculate(fst, snd, foper[i]) << endl;
				break;
			}
		if (i == noper) cout << "�������� ���� ��������: " << oper << endl;
	} while (true);
}


int main() {
	setlocale(LC_ALL, "ru");

	void(*func_array[])() = { fst_sample, snd_sample, thd_sample, fifth_sample, sth_sample };
	for (void(*current_func)() : func_array) current_func();

	system("pause");
	return 0;
}