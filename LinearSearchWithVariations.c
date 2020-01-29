// Linear search using sentinel on 1D array
// And Linear search on 2D array
#include <stdio.h>

void read_arr(int size, int arr[])
{
	for (int i = 0; i < size; ++i)
		scanf("%d", arr + i);
}

void print_arr(int size, int arr[])
{
	printf("[");
	for (int i = 0; i < size; ++i)
		printf("%d ", *(arr + i));
	printf("]\n");
}

int linear_search(int size, int arr[], int search_key) // With sentinel
{
	int last_elem = arr[size - 1];
	arr[size - 1] = search_key;
	
	int i;
	for (i = 0; arr[i] != search_key; ++i);
	
	if (i == size - 1 && last_elem != search_key) return -1;
	else return i;
}

void main_linear_search()
{
	int size;
	scanf("%d", &size);
	int arr[size];
	read_arr(size, arr);
	int search_key;
	scanf("%d", &search_key);
	
	int res = linear_search(size, arr, search_key);
	if (res == -1)
	{
		printf("Not found.\n");
	}
	else
	{
		printf("First occurence at %d.\n", res);
	}
}

void print_matrix(int rows, int cols, int mat[rows][cols])
{
	printf("[\n");
	for (int i = 0; i < rows; ++i, printf("\n"))
	for (int j = 0; j < cols; ++j)
		printf("%d ", mat[i][j]);
	printf("]\n");
}

void matrix_search(int rows, int cols, int mat[rows][cols], int search_key, int* rpos, int* cpos) 
{
	for (int i = 0; i < rows; ++i)
	for (int j = 0; j < cols; ++j)
		if (mat[i][j] == search_key)
		{
			*rpos = i;
			*cpos = j;
			return;
		}
}
void main_matrix_search()
{
	int rows, cols;
	scanf("%d %d", &rows, &cols);
	int mat[rows][cols];

	read_arr(rows*cols, &mat[0][0]);
	int search_key;
	scanf("%d", &search_key);

	int rpos = -1, cpos;
	matrix_search(rows, cols, mat, search_key, &rpos, &cpos);
	if (rpos == -1)
	{
		printf("Not found.\n");
	}
	else
	{
		printf("First occurence at (%d, %d).\n", rpos, cpos);
	}
	
	print_matrix(rows, cols, mat);
}
void main()
{
	main_matrix_search();
}
