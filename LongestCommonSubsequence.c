// Longest common subsequence using dp.

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define max(a, b) (a > b? a: b)
#define MAX_STR_LEN 100

void print_mat(int rows, int cols, int mat[rows][cols])
{
	for (int i = 0; i < rows; ++i, printf("\n"))
	for (int j = 0; j < cols; ++j)
		printf("%d ", mat[i][j]);
}

void print_in_reverse(int len, char stri[len])
{
	for (int i = len - 1; i >= 0; --i)
		printf("%c", stri[i]);
	printf("\n");
}

int lcs(int sizeone, char* one, int sizetwo, char* two, int dp[sizeone + 1][sizetwo + 1])
{
	int i, j;
	for (i = 0; i <= sizeone; ++i) dp[i][0] = 0;
	for (j = 0; j <= sizetwo; ++j) dp[0][j] = 0;

	for (i = 1; i <= sizeone; ++i)
	{
		for (j = 1; j <= sizetwo; ++j)
		{
			if (one[i - 1] == two[j - 1])
			{
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else
			{
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}

	return dp[sizeone][sizetwo];
}

void traceback(int sizeone, char* one, int sizetwo, char* two, int i, int j, \
	           int dp[sizeone + 1][sizetwo + 1], char* buffer, int buf_ind)
{	
	if (i == 0 || j == 0)
	{
		print_in_reverse(buf_ind, buffer);
		// Output may be duplicated.
		return;
	}

	if (one[i - 1] == two[j - 1])
	{
		buffer[buf_ind] = one[i - 1];
		traceback(sizeone, one, sizetwo, two, i - 1, j - 1,\
		          dp, buffer, buf_ind + 1);
	}

	else
	{
		if (dp[i - 1][j] == dp[i][j - 1])
		{
			traceback(sizeone, one, sizetwo, two, i - 1, j,\
		          dp, buffer, buf_ind);
			traceback(sizeone, one, sizetwo, two, i, j - 1,\
		          dp, buffer, buf_ind);
		}
		else if (dp[i - 1][j] > dp[i][j - 1])
		{
			traceback(sizeone, one, sizetwo, two, i - 1, j,\
		          dp, buffer, buf_ind);
		}
		else
		{
			traceback(sizeone, one, sizetwo, two, i, j - 1,\
		          dp, buffer, buf_ind);
		}
	}
}

void traceback_setup(int sizeone, char* one, int sizetwo, char* two, int dp[sizeone + 1][sizetwo + 1])
{
	int len_lcs = dp[sizeone][sizetwo];
	char buffer[len_lcs + 1];
	traceback(sizeone, one, sizetwo, two, sizeone, sizetwo, dp, buffer, 0);
}

void main()
{
	char one[MAX_STR_LEN + 1];
	char two[MAX_STR_LEN + 1];
	scanf("%s", one);
	scanf("%s", two);

	int sizeone = strlen(one);
	int sizetwo = strlen(two);

	int dp[sizeone + 1][sizetwo + 1];	
	int len_lcs = lcs(sizeone, one, sizetwo, two, dp);
	printf("%d\n", len_lcs);	
	traceback_setup(sizeone, one, sizetwo, two, dp);
}

/* TESTS:
#1
In: 
bacbffcb
dabeabfbc

Out:
5
babfc
babfc
babfb

#2
In:
abcbdab
bdcaba

Out:
4
bcba
bcab
bdab

#3
In:
bdcaba
abcbdab
Out:
4
bdab
bcab
bcba

#5
In:
abracadabra
yabbadabbad

Out:
7
abadaba
abadaba
abadaba
abadaba
abadaba
abadaba
abadaba
abadaba
/
*int naive_lcs(char* curone, char* curtwo)
{
	if (*curone == '\0' || *curtwo == '\0')
		return 0;
	else if (*curone == *curtwo)
		return 1 + naive_lcs(curone + 1, curtwo + 1);
	else 
		return max(naive_lcs(curone + 1, curtwo), naive_lcs(curone, curtwo + 1));
}
*/