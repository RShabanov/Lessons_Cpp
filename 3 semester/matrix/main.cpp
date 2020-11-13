#include <iostream>
#include "Matrix.h"
#include "Rational.h"
using namespace std;


void solve_linear_equations();
void matrix_test();

int main() {
	
	//solve_linear_equations();
	
	matrix_test();
	
	cin.get();
	cin.get();
	return 0;
}

void matrix_test() {
	Matrix<int> M;
	cout << M << endl;
	cin >> M;
	M.print(cout); // единственное отличие функции print
					// от перегруженного оператора << в том, что
					// print выводит подробную информацию
	
	int row, column;
	cout << "Enter another matrix (by array):\n";
	cout << "Enter row: ";
	cin >> row;
	cout << "Enter column: ";
	cin >> column;
	int** arr = new int*[row];
	for (int i = 0; i < row; i++) {
		arr[i] = new int[column];
		for (int j = 0; j < column; j++) {
			cin >> arr[i][j];
		}
	}
	Matrix<int> M1(row, column, arr);
	cout << M1;

	cout << "Operations:\n\n";
	cout << "M + M1:\n" << M + M1 << endl;
	cout << "M * M1:\n" << M * M1 << endl;
	cout << "M + 5:\n" << M + 5 << endl;

	cout << "M[0][0]:\t" << M[0][0] << endl;

	cout << "Other:\n\n";
	cout << "Transposed M:\n" << M.transpose() << endl;
	cout << "Is M a singular matrix?\t" << M.is_singular() << endl;

}

void solve_linear_equations() {
	/***

		A.X = B => X = (A^-1).B

		Пусть система уравнений будет следующая:
		3*x + 2*y + z = 5
		2*x + 3*y + z = -1
		2*x + y + 3*z = 4

	***/
	cout << "A*X = B" << endl << endl;
	int size;
	cout << "Enter matrix size: ";
	cin >> size;

	int** arr = new int*[size];
	int** temp = new int*[size];
	Rational** ans = new Rational*[size];

	for (int i = 0; i < size; i++) {
		arr[i] = new int[size];
		ans[i] = new Rational[1];
		temp[i] = new int[1];
	}

	cout << "Enter coefficients for A matrix:\n";
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) {
			cout << "A[" << i << "][" << j << "]: ";
			cin >> arr[i][j];
		}

	cout << "Enter coefficients for B matrix:\n";
	for (int i = 0; i < size; i++) {
		cout << "B[" << i << "][0]: ";
		cin >> temp[i][0];
		ans[i][0] = temp[i][0];
	}
	cout << endl << endl;

	Matrix<int> A(size, size, arr);
	Matrix<Rational> B(size, 1, ans);

	cout << "Matrix A:\n" << A << endl;
	cout << "Vector B:\n" << B << endl;

	cout << "Vector X:\n" << A.invert() * B << endl;

	for (int i = 0; i < size; i++) {
		delete[] arr[i];
		delete[] ans[i];
	}
	delete[] arr;
	delete[] ans;
}
