#pragma once
#include "MatrixException.h"
#include "Rational.h"


template<typename T>
class Matrix {
	size_t row, column;
	T** matrix;

	T minor(int, int) const;
	
public:
	Matrix();

	Matrix(size_t x, size_t y, const T = 0);
	Matrix(size_t x, size_t y, T**);
	Matrix(const Matrix&);

	~Matrix();

	Matrix<Rational> invert() const;
	Matrix transpose() const;
	T determinant() const;
	bool is_singular() const;

	Matrix operator+(const T&) const;
	template<typename T> friend Matrix operator+(const T& value, const Matrix& M);
	Matrix operator+(const Matrix&) const;
	Matrix& operator+=(const T&);
	Matrix& operator+=(const Matrix&);

	Matrix operator-(const T&) const;
	template<typename T> friend Matrix operator-(const T&, const Matrix&);
	Matrix operator-(const Matrix&) const;
	Matrix& operator-=(const T&);
	Matrix& operator-=(const Matrix&);
	Matrix operator-() const;

	Matrix operator*(const T&) const;
	template<typename T> friend Matrix operator*(const T&, const Matrix&);
	Matrix operator*(const Matrix&) const;
	Matrix& operator*=(const T&);
	Matrix& operator*=(const Matrix&);

	Matrix operator/(const T&) const;
	Matrix& operator/=(const T&);

	Matrix& operator=(const Matrix&);


	operator bool() const { return matrix != nullptr; }

	size_t get_row() const { return row; }
	size_t get_column() const { return column; }
	
	template<typename T> friend std::ostream& operator<<(std::ostream&, const Matrix<T>&);
	template<typename T> friend std::istream& operator>>(std::istream&, Matrix<T>&);
	void print(std::ostream&, bool = true) const; // единственное отличие функции print
												  // от перегруженного оператора << в том, что
												  // print выводит подробную информацию

	T* operator[](int);
};


template<typename T>
Matrix<T>::Matrix() {
	row = column = 0;
	matrix = nullptr;
}

template<typename T>
Matrix<T>::Matrix(size_t x, size_t y, const T value) { // нулевая матрица
	row = x;
	column = y;
	matrix = new T*[row];
	for (int i = 0; i < row; i++) {
		matrix[i] = new T[column];
		for (int j = 0; j < column; j++)
			matrix[i][j] = value;
	}
}

template<typename T>
Matrix<T>::Matrix(size_t x, size_t y, T** ptr) {
	if (ptr) {
		row = x;
		column = y;
		matrix = new T*[row];
		for (int i = 0; i < row; i++) {
			matrix[i] = new T[column];
			for (int j = 0; j < column; j++)
				matrix[i][j] = ptr[i][j];
		}
	}
	else throw MatrixException();
}

template<typename T>
Matrix<T>::Matrix(const Matrix& M) {
	if (M) {
		row = M.row;
		column = M.column;
		matrix = new T*[row];
		for (int i = 0; i < row; i++) {
			matrix[i] = new T[column];
			for (int j = 0; j < column; j++)
				matrix[i][j] = M.matrix[i][j];
		}
	}
	else throw MatrixException();
}

template<typename T>
Matrix<T>::~Matrix() {
	if (matrix) {
		for (int i = 0; i < row; i++)
			delete[] matrix[i];
		delete[] matrix;
	}
	else throw MatrixException();
}


template<typename T>
Matrix<T> Matrix<T>::operator+(const T& value) const {
	if (matrix) {
		Matrix<T> M(*this);
		return M += value;
	}
	else throw MatrixException();
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const T& value) {
	if (matrix) {
		for (int i = 0; i < row; i++)
			for (int j = 0; j < column; j++)
				matrix[i][j] += value;
		return *this;
	}
	else throw MatrixException();
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& M) const {
	if (matrix && M) {
		Matrix temp(*this);
		return temp += M;
	}
	else throw MatrixException();
}


template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& M) {
	if (matrix && M) {
		for (int i = 0; i < row; i++)
			for (int j = 0; j < column; j++)
				matrix[i][j] += M.matrix[i][j];
		return *this;
	}
	else throw MatrixException();
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const T& value) const {
	if (matrix) return *this + value;
	else throw MatrixException();
}

template<typename T>
Matrix<T>& Matrix<T>::operator-=(const T& value) {
	if (matrix) return *this += value;
	else throw MatrixException();
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& M) const {
	if (matrix && M) return *this + M;
	else throw MatrixException();
}

template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& M) {
	if (matrix && M) return *this += M;
	else throw MatrixException();
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T& value) const {
	if (matrix) {
		Matrix<T> M(*this);
		return M *= value;
	}
	else throw MatrixException();
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const T& value) {
	if (matrix) {
		for (int i = 0; i < row; i++)
			for (int j = 0; j < column; j++)
				matrix[i][j] *= value;
		return *this;
	}
	else throw MatrixException();
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& M) const {
	if (matrix && M) {
		Matrix temp(*this);
		return temp *= M;
	}
	else throw MatrixException();
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& M) {
	if (column == M.row && matrix && M) {
		Matrix res(row, M.column); 
		for (int i = 0; i < row; i++)
			for (int j = 0; j < M.column; j++)
				for (int k = 0; k < column; k++)
					res[i][j] += matrix[i][k] * M.matrix[k][j];
		
		return *this = res;
	}
	else throw MatrixException();
}

template<typename T>
Matrix<T> Matrix<T>::operator/(const T& value) const {
	if (matrix) {
		Matrix M(*this);
		return M /= value;
	}
	else throw MatrixException();
}

template<typename T>
Matrix<T>& Matrix<T>::operator/=(const T& value) {
	if (matrix) {
		for (int i = 0; i < row; i++)
			for (int j = 0; j < column; j++)
				matrix[i][j] /= value;
		return *this;
	}
	else throw MatrixException();
}

template<typename T>
Matrix<T> Matrix<T>::operator-() const {
	if (matrix) return *this * -1;
	else throw MatrixException();
}

template<typename T> 
Matrix<T> operator+(const T& value, const Matrix<T>& M) { 
	if (M) return M + value; 
	else throw MatrixException();
}

template<typename T> 
Matrix<T> operator-(const T& value, const Matrix<T>& M) { 
	if (M) return -(M + value);
	else throw MatrixException();
}

template<typename T> 
Matrix<T> operator*(const T& value, const Matrix<T>& M) { 
	if (M) return M * value; 
	else throw MatrixException();
}


template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& M) {
	if (M) {
		if (&M == this)
			return *this;

		row = M.row;
		column = M.column;

		if (matrix) {
			for (int i = 0; i < row; i++)
				delete[] matrix[i];
			delete[] matrix;
		}

		matrix = new T*[row];
		for (int i = 0; i < row; i++) {
			matrix[i] = new T[column];
			for (int j = 0; j < column; j++)
				matrix[i][j] = M.matrix[i][j];
		}
	}
	else throw MatrixException();
}

template<typename T>
T* Matrix<T>::operator[](int index) {
	if (matrix && index >= 0 && index < row)
		return matrix[index];
	else throw MatrixException();
}



/*

	OUTPUT

*/

template<typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& M) {
	if (M) {
		out << "Matrix:\n";
		for (int i = 0; i < M.row; i++) {
			for (int j = 0; j < M.column; j++)
				out << M.matrix[i][j] << "\t";
			out << std::endl;
		}
	}
	else out << "Empty matrix";
	return out;
}

template<typename T>
void Matrix<T>::print(std::ostream& out, bool details) const {
	out << *this << std::endl;
	if (details) {
		out << "Size:\t\t(" << row << "x" << column << ")\n";
		T det = determinant();
		if (det) {
			out << "Determinant:\t" << det << std::endl;
			out << "Invertible matrix:\n" << invert() << std::endl;
		}
		else out << "This matrix doesn't have an invertible matrix\n";
	}
}

/*

	INPUT

*/

template<typename T> 
std::istream& operator>>(std::istream& in, Matrix<T>& M) {
	if (M) {
		for (int i = 0; i < M.row; i++)
			delete[] M.matrix[i];
		delete[] M.matrix;
	}

	in >> M.row >> M.column;
	if (M.row > 0 && M.column > 0) {
		M.matrix = new T*[M.row];
		for (int i = 0; i < M.row; i++)
			M.matrix[i] = new T[M.column];

		for (int i = 0; i < M.row; i++)
			for (int j = 0; j < M.column; j++)
				in >> M[i][j];
		return in;
	}
	else throw MatrixException();
}






/*

	OTHER MATRIX OPERATIONS

*/

template<typename T>
Matrix<Rational> Matrix<T>::invert() const {
	if (row == column) {
		T det = determinant();
		if (det) {
			Matrix<Rational> M(row, column); // тут можно было бы попробовать с Rational
			for (int i = 0; i < row; i++)
				for (int j = 0; j < column; j++)
					M[i][j] = minor(i, j) * ((i + j) % 2 ? -1 : 1);
			return M.transpose() * Rational(1, det);
		}
		else throw MatrixException();
	}
	else throw MatrixException();
}

template<typename T>
Matrix<T> Matrix<T>::transpose() const {
	Matrix<T> trans(column, row);
	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
			trans[j][i] = matrix[i][j];
	return trans;
}

template<typename T>
T Matrix<T>::determinant() const {
	if (row == column) {
		T det = 0;
		if (row == 1) return matrix[0][0];
		if (row == 2)
			return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
		for (int i = 0; i < row; i++) {			
			T temp_det = matrix[i][0] * minor(i, 0);	
			temp_det *= (i % 2 ? -1 : 1);
			det += temp_det;
		}
		return det;
	}
	else throw MatrixException();
}

template<typename T>
bool Matrix<T>::is_singular() const {
	if (row == column) {
		if (determinant()) return false;
		return true;
	}
	else throw MatrixException();
}


template<typename T>
T Matrix<T>::minor(int x, int y) const {
	if (row == column && row > 1) {
		if (row == 2)
			for (int i = 0; i < row; i++)
				if (i != x)
					for (int j = 0; j < row; j++)
						if (j != y) return matrix[i][j];
			
		Matrix<T> M(row - 1, column - 1);
		for (int i = 0, x_offset = 0; i < row; i++)
			if (i != x) {
				x_offset = i > x;
				for (int j = 0, y_offset = 0; j < row; j++) {
					y_offset = j > y;
					if (j != y) M.matrix[i - x_offset][j - y_offset] = matrix[i][j];
				}
			}

		return M.determinant();
	}
	else throw MatrixException();
}


template<typename T>
Matrix<T> pow(const Matrix<T>& matrix, int n) {
	if (n == 1) return matrix;
	if (n % 2) return matrix * pow(matrix, n - 1);
	else return pow(matrix*matrix, n >> 1);
}
