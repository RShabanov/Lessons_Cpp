#include "exp.h"


Exp::Exp(const unsigned int number) {
	// define_accuracy вычисляет количество знаков для знаменателя и числителя
	size = define_accuracy(number) / log10(BASE) + 1; // количество элементов массива

	numer = new ull[size];
	denom = new ull[size];

	set_data(numer, 1, size);
	set_data(denom, number + 1, size);
}

Exp::Exp(const Exp& source) {
	size = source.size;

	numer = new ull[size];
	denom = new ull[size];

	for (int i = 0; i < size; i++) {
		numer[i] = source.numer[i];
		denom[i] = source.denom[i];
	}
}

Exp::~Exp() {
	delete[] numer;
	delete[] denom;
	delete[] ir_number;
}

// устанавливаем все значения равными 0
// и инициализируем его числом number
void Exp::set_data(ull* arr, int number, const int size) {
	memset(arr, 0, size * sizeof(ull));
	for (int i = size - 1; i >= 0; i--) {
		arr[i] = number % BASE;
		number /= BASE;
		if (number == 0) break;
	}
}

// вычисляет значение числителя:
// numer + k * denom
// где k - либо 2n, либо 1
Exp Exp::add_denom(const unsigned int n) {
	Exp snd(*this);
	if (n > 1) snd.multiply_denom(n);
	register int carry = 0;
	int ttl = 0;
	for (int i = size - 1; i >= 0; i--) {
		numer[i] += snd.denom[i] + carry;
		if (carry = (numer[i] >= BASE)) numer[i] -= BASE;
	}
	return *this;
}

// умножаем знаменатель на n,
// где n - четное число
void Exp::multiply_denom(const unsigned int n) {
	register int carry = 0;

	for (int i = size - 1; i >= 0; i--) {
		ull current = carry + this->denom[i] * n;
		this->denom[i] = ull(current % BASE);
		carry = ull(current / BASE);
	}
}

// вывод в виде дроби
std::ostream& operator << (std::ostream& out, const Exp& e) {
	out << 2 << " + (";
	bool flag = false;

	int cnt_numer = 0, cnt_denom = 0;

	for (int i = 0; i < e.size; i++) {
		if (e.numer[i]) flag = true;
		if (flag) {
			out << std::setfill('0') << std::setw(log10(BASE)) << e.numer[i];
			cnt_numer++;
		}
	}
	out << ") / (";
	flag = false;
	for (int i = 0; i < e.size; i++) {
		if (e.denom[i]) flag = true;
		if (flag) {
			out << std::setfill('0') << std::setw(log10(BASE)) << e.denom[i];
			cnt_denom++;
		}
	}
	out << ")";

	return out;
}

// меняет числитель и знаменатель местами
void Exp::flip() {
	ull* ptr = numer;
	numer = denom;
	denom = ptr;
}

// рассчет иррационального числа
void Exp::irrational() {
	// выделяется память в 2 раза больше,
	// чем для numer или denom, т.к.
	// количество знаков у числа е примерно всегда в 2 раза больше
	// (при этом без потери точности)
	register int ir_size = 2 * size;
	ir_number = new ull[ir_size];
	set_data(ir_number, 0, ir_size);

	// рассчитываем число е в привычном виде
	div(ir_size);
}

// вывод в иррациональной форме
void Exp::output_irrational(std::ostream& out) {
	if (ir_number == nullptr) this->irrational();

	int order = log10(BASE);
	for (int i = 0; i < 2 * size; i++) {
		if (i > 0) out << std::setfill('0') << std::setw(order);
		out << this->ir_number[i];
	}
	out << std::endl;
}

// деление дроби числитель / знаменатель
void Exp::div(const int digits) {
	ull* divisor = new ull[size];
	ull* dividend = new ull[size];
	copy(numer, dividend, size);

	int order = log10(BASE);
	for (int i = 0; i < 2 * size; i++)
		for (int j = 0, k = 0; j < order; j++, k = 0) {
			set_data(divisor, 0, size);
			
			// вычисляем коэффициент k, т.е.
			// насколько нужно умножить знаменатель, чтобы поделить его на числитель
			// с наименьшим остатком
			// при этом цикл do while возвращает k на единицу больше
			do {
				k++;
				add(denom, divisor, size);
			} while (compare(divisor, dividend, size) == -1); // пока делитель меньше делимого
			
			// вычитаем из divisor denom, т.к. коэффициент k на единицу больше
			subtract(divisor, denom, size);
			
			// вычитаем из делимого (dividend) делитель
			subtract(dividend, divisor, size);
			
			// сдвигаем его влево (умножаем на 10, по-простому)
			shift(dividend, size, 10);

			// записываем в массив для иррациональной формы числа е
			// результат деления
			ir_number[i] = --k + (10 * ir_number[i]);
		}

	delete[] dividend;
	delete[] divisor;
}

// добавляет к одному длинному числу другое
void Exp::add(ull* source, ull* target, const int size) {
	register int carry = 0;
	for (int i = size - 1; i >= 0; i--) {
		target[i] += source[i] + carry;
		if (carry = (target[i] >= BASE)) target[i] -= BASE;
	}
}

// вычитает из одного длинного числа другое
void Exp::subtract(ull* minuend, ull* subtrahend, const int size) {
	register int carry = 0;
	register long long temp = 0;
	for (int i = size - 1; i >= 0; i--) {
		temp = minuend[i] - (carry + subtrahend[i]);
		if (carry = temp < 0) temp += BASE;
		minuend[i] = temp;
	}
}

// сравнивает 2 длинных числа и возвращает следующее:
// -1 - fst < snd, 
// 0 - fst == snd, 
// 1 - fst > snd
int Exp::compare(ull *fst, ull *snd, const int size) const {
	int flag = 0;
	for (int i = 0; i < size; i++)
		if (flag = fst[i] < snd[i] ? -1 :
			fst[i] > snd[i] ? 1 : 0) break;
	return flag;
}

// копирование длинных чисел
void Exp::copy(ull* source, ull* target, const int size) {
	for (int i = 0; i < size; i++) target[i] = source[i];
}

// домножение числа на 10
void Exp::shift(ull* number, const int size, const int shift) {
	if (size == 1 && number[0] < BASE / 10) {
		number[0] *= 10;
		return;
	}
	for (int i = 0; i < size - 1; i++) {
		number[i + 1] *= 10;
		number[i] += number[i + 1] / BASE;
		number[i + 1] %= BASE;
	}
}


// рассчитывает возможную точность для числа при 2n этажей
// алгоритм простой: 
// находим сумму количества цифр в числах до 2n:
// [1, 2, 1, 1, 4, 1, 1, ..., 2n]
int define_accuracy(int n) {
	int accuracy = 0,
		power = 10,
		digits = 1,
		current_n = 2;
	while (current_n <= n) {
		if (current_n >= power) {
			power *= 10;
			digits++;
		}
		accuracy += digits;
		current_n += 2;
	}

	return accuracy;
}
