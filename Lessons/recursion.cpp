#include <iostream>
using namespace std;

// for tasks 1, 4, 5
void input_single(unsigned long long& n) {
	cout << "Enter natural number: ";
	while (!(cin >> n) || n < 1) {
		system("cls");
		cout << "Pay attention, please!\nEnter natural number: ";
		cin.clear();
		while (!(cin.ignore()));
	}
	system("cls");
}


//////////////////////////////////////
int get_sum(unsigned long long n) { return (n < 10) ? n : (n % 10 + get_sum(n / 10)); }

void task_1() { // sum of number's digits
	unsigned long long n;
	cout << "Here you can get sum of number's digits\n";

	input_single(n);
	cout << "Sum of " << n << "'s digits: " << get_sum(n) << endl;
}


//////////////////////////////////////
double quick_power(double x, int n) { return (n ? (n % 2) ? x * quick_power(x, n - 1) : quick_power(x*x, n >> 1) : 1); }

void task_2() { // quick power
	double x;
	int n;
	cout << "Number x to the power of n\n";
	cout << "Enter numbers (x, n), separated by space (x - real number, n - narutal number): ";
	while (!(cin >> x >> n) || n < 0) {
		system("cls");
		cout << "Number x to the power of n\n";
		cout << "Pay attention, please!\nEnter numbers (x, n), separated by space (x - a real number, n - a narutal one): ";
		cin.clear();
		while (!(cin.ignore()));
	}
	cout << "\nYour number " << x << " to the power of " << n << ": " << quick_power(x, n) << endl;
}


//////////////////////////////////////
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

void task_3() { // Euclidean algorithm
	int n, m;
	cout << "Greatest common divisor (GCD) of n and m\n";
	cout << "Enter numbers (m, n), separated by space (m & n - integers): ";
	while (!(cin >> m >> n)) {
		system("cls");
		cout << "Greatest common divisor (GCD) of n and m\n";
		cout << "Pay attention, please!\nEnter numbers (m, n), separated by space (m & n - narutal numbers): ";
		cin.clear();
		while (!(cin.ignore()));
	}
	cout << "\nGCD of " << m << " and " << n << ": " << gcd(m, n) << endl;
}


//////////////////////////////////////
void Fibonnaci(unsigned long long prev, unsigned long long post, unsigned long long n) {
	if (prev > n && post > n) return;
	cout << prev << " ";
	Fibonnaci(post, post + prev, n);
}

void task_4() { // Fibonnaci numbers
	unsigned long long n;
	cout << "Fibonnaci numbers to number n\n";
	input_single(n);

	cout << "Fibonnaci numbers to " << n << ":\n";
	Fibonnaci(1, 1, n);
	cout << endl;
}


//////////////////////////////////////
void to_binary(unsigned long long n) {
	if (n == 0) return;
	to_binary(n >> 1);
	cout << n % 2;
}

void task_5() { // binary code
	unsigned long long n;
	cout << "Number n in binary code\n";
	input_single(n);

	cout << n << " in binary code: ";
	to_binary(n);
	cout << endl;
}


int main() {
	for (void(*func)() : { task_1, task_2, task_3, task_4, task_5 }) {
		func();
		system("pause");
		system("cls");
	}
	return 0;
}
