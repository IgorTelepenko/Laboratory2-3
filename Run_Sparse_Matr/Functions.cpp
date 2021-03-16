#include"Lib.h"
#include <fstream>
#include <iostream>

using namespace std;

void append(struct matr_list** head, double new_data, int ind_i, int ind_j)
{
	struct matr_list* new_node = new matr_list;
	new_node->data = new_data;
	new_node->ind_n = ind_i;
	new_node->ind_m = ind_j;
	new_node->next = NULL;
	struct matr_list* last = *head;

	if ((*head) == NULL)
	{
		(*head) = new_node;
		return;
	}

	while (last->next != NULL)
	{
		last = last->next;
	}

	last->next = new_node;
	return;
}

double get_el_value_from_matr_by_ids(struct matr_list* head, int ind_i, int ind_j)
{

	while (head != NULL && head->ind_n <= ind_i)
	{
		if (head->ind_n == ind_i)
		{
			if (head->ind_m == ind_j)
			{
				return head->data;
			}
		}
		head = head->next;
	}

	return 0;
}

double** read_matrix(const char* file_path, int& n, int& m)
{
	ifstream in(file_path);

	if (in.is_open())
	{
		//how many numbers in the file (matrix)
		int count = 0;//quantity of numbers
		int temp;

		while (!in.eof())//till the end of the file
		{
			in >> temp;//reading of numbers without saving
			count++;
		}

		//to find out how many numbers in the first row
		in.seekg(0, ios::beg);//to the file beginning
		in.clear();

		int count_space = 0;//number of spaces
		char symbol;
		while (!in.eof())//to be on the save side - no longer than end of the file
		{
			in.get(symbol);//reading each next symbol
			if (symbol == ' ') count_space++;
			if (symbol == '\n') break;//if the row is finished, than stop
		}
		//cout << count_space << endl;

		//beginning of the file
		in.seekg(0, ios::beg);
		in.clear();

		int _n = count / (count_space + 1);//number of rows
		n = _n;
		int _m = count_space + 1;//number of columns
		m = _m;
		double** x;//the matrix
		x = new double* [_n];
		for (int i = 0; i < _n; i++) x[i] = new double[_m];

		//reading the matrix
		for (int i = 0; i < _n; i++)
			for (int j = 0; j < _m; j++)
				in >> x[i][j];

		in.close();
		return x;
	}
	else
	{
		cout << "Error: wrong file path";
	}
}

void simple_saving_sparse(double** matrix, int n, int m, matr_list** head)
{
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < m;j++)
		{
			if (matrix[i][j] != 0)
			{
				append(head, matrix[i][j], i, j);
			}
		}
	}

	for (int i = 0; i < n; i++) delete[] matrix[i];
	delete[] matrix;
}

void display_short_matr_info(struct matr_list* head)
{

	while (head != NULL)
	{
		cout << "the element: " << head->data << " index 1: " << head->ind_n << " index 2: " << head->ind_m << endl;
		head = head->next;
	}

	if (head == NULL)
		cout << "null";
}

void display_matr_from_short(struct matr_list* head, int n, int m)
{
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < m;j++)
		{
			if (head == NULL)
				cout << "0 ";
			else
				if (i == head->ind_n && j == head->ind_m)
				{
					cout << head->data << " ";
					head = head->next;
				}
				else cout << "0 ";
		}
		cout << endl;
	}
}

matr_list* sum_of_matrices(struct matr_list* head1, struct matr_list* head2, int n, int m)
{
	double** sum_matrix_temp = new double* [n];
	for (int i = 0;i < n;i++)
	{
		sum_matrix_temp[i] = new double[m];
		for (int j = 0;j < m;j++)
			sum_matrix_temp[i][j] = 0;
	}

	while (head1 != NULL)
	{
		sum_matrix_temp[head1->ind_n][head1->ind_m] += head1->data;
		head1 = head1->next;
	}
	while (head2 != NULL)
	{
		sum_matrix_temp[head2->ind_n][head2->ind_m] += head2->data;
		head2 = head2->next;
	}
	matr_list* res = NULL;
	simple_saving_sparse(sum_matrix_temp, n, m, &res);

	return res;
}

matr_list* mult_of_matrices(struct matr_list* head1, struct matr_list* head2, int n1, int m1, int n2, int m2)
{
	if (m1 != n2)
	{
		cout << "Wrong sizes for multiplying!" << endl;
		return NULL;
	}

	int n_res = n1;
	int m_res = m2;

	double** mult_matrix_temp = new double* [n_res];
	for (int i = 0;i < n_res;i++)
	{
		mult_matrix_temp[i] = new double[m_res];
		for (int j = 0;j < m_res;j++)
			mult_matrix_temp[i][j] = 0;
	}

	//i,j - main loop for choosing each next cell of the result matrix
	for (int i = 0;i < n_res;i++)
	{
		for (int j = 0;j < m_res;j++)
		{
			//k - elements in chosen row of matrix1

			for (int k = 0; k < m1;k++)
			{
				mult_matrix_temp[i][j] += get_el_value_from_matr_by_ids(head1, i, k) * get_el_value_from_matr_by_ids(head2, k, j);

			}
		}
	}

	matr_list* res = NULL;
	simple_saving_sparse(mult_matrix_temp, n_res, m_res, &res);

	return res;
}