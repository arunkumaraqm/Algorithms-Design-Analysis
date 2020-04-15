// Matrix Chain Multiplication 

// Input format:
// No. of matrices (always 1 less than no. of dimensions)
// List of dimensions

// Output format:
// Cost Matrix, K-values matrix and expression with correct paranthesization.

// Time complexity:
// O(n^3)

#include <stdio.h>
#include <limits.h>

#define maxint INT_MAX

void read_arr(int size, int arr[size])
{
	for (int i = 0; i < size; scanf("%d", &arr[i]), ++i);
}

void print_arr(int size, int arr[size])
{
	for (int i = 0; i < size; printf("%d ", arr[i]), ++i);
	printf("\n");
}

// Fills matrix with '-1's
void initialize_mat(int rows, int cols, int mat[rows][cols])
{
	int i, j;
	for (i = 0; i < rows; ++i)
	for (j = 0; j < cols; ++j)
		mat[i][j] = -1;
}

// Prints a matrix with one-based indexing
void print_mat_onebasedidx(int rows, int cols, int mat[rows + 1][cols + 1])
{
	int i, j;
	for (i = 1; i <= rows; ++i, printf("\n"))
	for (j = 1; j <= cols; ++j)
		printf("%d\t", mat[i][j]);
	printf("\n");
}

// Modifies the cost and kvals matrices.
// Returns the optimal no. of multiplicatins.
int optimal_noof_muls(int noof_mats, int* dims, \
					   int cost[noof_mats + 1][noof_mats + 1], \
					   int kvals[noof_mats + 1][noof_mats + 1])
{
	int i, j, k, dif, min, noof_muls;

	// Fills up main diag with zeros
	for (i = 1; i <= noof_mats; ++i)
	{
		cost[i][i] = 0;
	}

	for (dif = 1; dif <= noof_mats - 1; ++dif) // _ * theta(n)
	{
		for (i = 1, j = i + dif; j <= noof_mats; ++i, ++j)// _ * O(n)
		{
			min = maxint;
			
			for (k = i; k < j; ++k) // for k in [i, j) // _ * O(n)
			{
				// The formula
				noof_muls = cost[i][k] + cost[k + 1][j] + \
						    dims[i - 1] * dims[k] * dims[j];

				if (noof_muls < min)
				{
					min = noof_muls;
					cost[i][j] = noof_muls;
					kvals[i][j] = k;
				}
			}
		}
	}

	return cost[1][noof_mats];
}

void infix_display(int start, int end, 
	         int noof_mats, int kvals[noof_mats + 1][noof_mats + 1])

{
	if (start == end)
	{
		//buffer[(*bufind)++] = start;
		printf("A%d", start);
		return;
	}
	int barr = kvals[start][end];

	printf("(");
	infix_display(start, barr, noof_mats, kvals);
	printf(" * ");
	infix_display(barr + 1, end, noof_mats, kvals);
	printf(")");
}

void main()
{
	int noof_mats;
	scanf("%d", &noof_mats);
	int noof_dimensions = noof_mats + 1;
	int dims[noof_dimensions];
	read_arr(noof_dimensions, dims);

	int cost[noof_mats + 1][noof_mats + 1];
	int kvals[noof_mats + 1][noof_mats + 1];

	initialize_mat(noof_mats + 1, noof_mats + 1, cost);
	initialize_mat(noof_mats + 1, noof_mats + 1, kvals);
	
	optimal_noof_muls(noof_mats, dims, cost, kvals);

	printf("Cost Matrix: \n");
	print_mat_onebasedidx(noof_mats, noof_mats, cost);
	printf("k-vals Matrix: \n");
	print_mat_onebasedidx(noof_mats, noof_mats, kvals);

	infix_display(1, noof_mats, noof_mats, kvals);
	printf("\n");
}