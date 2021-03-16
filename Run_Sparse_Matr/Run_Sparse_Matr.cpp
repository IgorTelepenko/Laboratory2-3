#include <iostream>
#include"Lib.h"
using namespace std;

int main()
{
	int n = 0, m = 0;
	int n2 = 0, m2 = 0;
	double** matrix = NULL;
	double** matrix2 = NULL;

	const char* f_path = "matr.txt";
	const char* f_path2 = "matr2.txt";

	matrix = read_matrix(f_path, n, m);
	matrix2 = read_matrix(f_path2, n2, m2);

	matr_list* short_matrix = NULL;
	matr_list* short_matrix2 = NULL;
	simple_saving_sparse(matrix, n, m, &short_matrix);
	simple_saving_sparse(matrix2, n2, m2, &short_matrix2);
	//display_short_matr_info(short_matrix);
	display_matr_from_short(short_matrix, n, m);
	cout << endl;
	display_matr_from_short(short_matrix2, n2, m2);
	cout << endl;
	display_matr_from_short(sum_of_matrices(short_matrix, short_matrix2, n, m), n, m);
	cout << endl;
	display_matr_from_short(mult_of_matrices(short_matrix, short_matrix2, n, m, n2, m2), n, m2);

	return 0;
}
