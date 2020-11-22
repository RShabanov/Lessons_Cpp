#include "RationalExp.h"


inline int max(const int& fst, const int& snd) {
	return fst > snd ? fst : snd;
}


/*

	BIG_INT

*/

BigInt::BigInt() {
	number = nullptr;
	capacity = size = 0;
}

BigInt::BigInt(const unsigned int value, const int& _capacity) {
	capacity = _capacity;
	number = new type[capacity];
	set_data(value);
}

BigInt::BigInt(const BigInt& N) {
	capacity = N.capacity;
	size = N.size;
	number = new type[capacity];
	for (int i = 0; i < capacity; i++)
		number[i] = N.number[i];
}

BigInt::~BigInt() {
	if (number != nullptr) delete[] number;
}


void BigInt::set_data(unsigned int value) {
	memset(number, 0, capacity * sizeof(type));
	for (int i = capacity - 1; i >= 0; i--) {
		size++;
		number[i] = value % BASE;
		value /= BASE;
		if (value == 0) break;
	}
}

void BigInt::clear() {
	memset(number, 0, capacity * sizeof(type));
}

void BigInt::add(const BigInt& addends) {
	register int carry = 0;
	size = max(size, addends.size);
	register int max_size = addends.capacity - size - 1;
	if (max_size < 0) max_size = 0;

	for (int i = capacity - 1; i >= max_size || carry; i--) {
		number[i] += addends.number[i] + carry;
		if (carry = (number[i] >= BASE)) {
			number[i] -= BASE;
			if (i <= max_size) size++;
		}
	}
}

void BigInt::subtract(const BigInt& subtrahend) {
	register int carry = 0;
	register long long temp = 0;
	register int max_size = subtrahend.capacity - max(size, subtrahend.size) - 1;

	if (max_size < 0) max_size = 0;

	for (int i = capacity - 1; i >= max_size || carry; i--) {
		temp = number[i] - (carry + subtrahend.number[i]);
		if (carry = temp < 0) temp += BASE;
		number[i] = temp;
	}

	for (size = 0; size < capacity; size++)
		if (number[size]) break;

	size = capacity - size;
}

void BigInt::multiply(const unsigned int& multiplier) {
	register int carry = 0;
	register int max_size = capacity - size - 1;
	if (max_size < 0) max_size = 0;

	for (int i = capacity - 1; i >= max_size || carry; i--) {
		type current = carry + number[i] * multiplier;
		carry = type(current / BASE);
		number[i] = current - BASE * carry;
		if (i < max_size) size++;
	}
}


std::ostream& operator<<(std::ostream& out, const BigInt& N) {
	bool flag = false;
	for (int i = 0; i < N.capacity; i++) {
		if (flag) {
			out.width(ORDER_OF_BASE);
			out.fill('0');
			out << N.number[i];
		}
		else if (N.number[i]) {
			out << N.number[i];
			flag = true;
		}
	}
	return out;
}


// COMPARISON

bool BigInt::operator<(const BigInt& B) const {
	int flag = 0;
	for (int i = 0; i < size; i++)
		if (flag = number[i] < B.number[i] ? -1 :
			number[i] > B.number[i] ? 1 : 0) break;
	return flag == -1;
}


/*
***********************************************************
***********************************************************
*/

/*

	RATIONAL NUMBER

*/

RationalExp::RationalExp(const unsigned int number) {
	floor = number;
	compute_capacity(number); // количество элементов массива

	numer = new BigInt(1, capacity);
	denom = new BigInt(number + 1, capacity);
}

RationalExp::RationalExp(const RationalExp& R) {
	floor = R.floor;

	capacity = numer->capacity = denom->capacity = R.capacity;
	numer->size = R.numer->size;
	denom->size = R.denom->size;

	numer->number = new type[R.capacity];
	denom->number = new type[R.capacity];

	register int max_size = R.capacity - max(numer->size, denom->size) - 1;
	if (max_size < 0) max_size = 0;

	for (int i = R.capacity - 1; i > max_size; i--) {
		numer->number[i] = R.numer->number[i];
		denom->number[i] = R.denom->number[i];
	}
}

RationalExp::~RationalExp() {
	if (numer) delete numer;
	if (denom) delete denom;
	if (irrational) delete irrational;
}


/*

	PRIVATE METHODS (RATIONAL NUMBER)

*/

void RationalExp::compute_capacity(const unsigned int& n) {
	int power = 10,
		digits = 1,
		current_n = 2;
	capacity = 0;
	while (current_n <= n) {
		if (current_n >= power) {
			power *= 10;
			digits++;
		}
		capacity += digits;
		current_n += 2;
	}

	capacity /= ORDER_OF_BASE;
	capacity++;
}


/*

	PUBLIC METHODS (RATIONAL NUMBER)

*/

void RationalExp::add_denom(const unsigned int& n) {
	BigInt temp(*denom); // temp_denom
	denom->size = temp.size;
	if (n > 1) temp.multiply(n);
	numer->add(temp);
}

void RationalExp::flip() {
	BigInt* temp_ptr = numer;
	numer = denom;
	denom = temp_ptr;
}

void RationalExp::compute() {
	register int cnt = 0;
	register int number = floor - 2;

	while (number) {
		if (cnt++ < 2) add_denom();
		else {
			add_denom(number);
			number -= 2;
			cnt = 0;
		}
		flip();
	}
	add_denom();
	flip();
}

std::ostream& operator << (std::ostream& out, const RationalExp& R) {
	out << "(" << *R.numer << ") / (" << *R.denom << ")";
	return out;
}


void RationalExp::compute_irrational() {
	if (irrational) delete irrational;
	irrational = new BigInt(0, (capacity << 1));

	BigInt divisor(0, capacity);
	BigInt dividend(*numer);

	for (int i = 0; i < irrational->capacity; i++)
		for (int j = 0, k = 0; j < ORDER_OF_BASE; j++, k = 0) {
			divisor.clear();

			// вычисляем коэффициент k, т.е.
			// насколько нужно умножить знаменатель, чтобы поделить его на числитель
			// с наименьшим остатком
			// при этом цикл do while возвращает k на единицу больше
			do {
				k++;
				divisor.add(*denom);
			} while (divisor < dividend); // пока делитель меньше делимого

			// вычитаем из divisor denom, т.к. коэффициент k на единицу больше
			divisor.subtract(*denom);

			// вычитаем из делимого (dividend) делитель
			dividend.subtract(divisor);

			// сдвигаем его влево (умножаем на 10, по-простому)
			//shift(dividend, size, 10);
			dividend.multiply(10);

			// записываем в массив для иррациональной формы числа е
			// результат деления
			irrational->number[i] = --k + (10 * irrational->number[i]);
		}
}

void RationalExp::output_irrational(std::ostream& out) {
	if (irrational == nullptr) compute_irrational();
	out << "2." << irrational[0];
	out.width(ORDER_OF_BASE);
	out.fill('0');
	for (int i = 1; i < irrational->capacity; i++)
		out << irrational->number[i];
	out << std::endl;
}
