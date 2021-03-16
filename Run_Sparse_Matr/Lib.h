#pragma once
#include<iostream>
struct matr_list
{
	double data;
	int ind_n, ind_m;
	struct matr_list* next;

	matr_list()
	{
		data = 0;
		ind_n = 0;
		ind_m = 0;
		next = NULL;
	}
};

void append(struct matr_list** head, double new_data, int ind_i, int ind_j);
void display_short_matr_info(struct matr_list* head);

double** read_matrix(const char* file_path, int& n, int& m);
void simple_saving_sparse(double** matrix, int n, int m, matr_list** head);
void display_matr_from_short(struct matr_list* head, int n, int m);
matr_list* sum_of_matrices(struct matr_list* head1, struct matr_list* head2, int n, int m);
matr_list* mult_of_matrices(struct matr_list* head1, struct matr_list* head2, int n1, int m1, int n2, int m2);
