/*
Travelling Salesman Problem using dynamic programming
Held-Karp's algo 

References:
https://en.wikipedia.org/wiki/Held–Karp_algorithm
Bitmasking - https://www.geeksforgeeks.org/bitmasking-dynamic-programming-set-2-tsp/
https://cs.stackexchange.com/questions/16474/traveling-salesman-with-held-and-karp-algorithm
You may also want to read about memoization.

Note:
This program only has 0-based indexing.
Wikipedia uses the g(vertex, unvisited set) notation. 
Doing it that way is hard to implement.
My equivalent is h(vertex, visited set) = dp[vertex][visited set in bitmask]
where visited set = set of all vertices - unvisited set.
The equivalent of Wikipedia's g(2, {3, 4}) would be h(1, {0, 1}).
* h and tsp function are not exactly the same, parameters-wise.

Input Format:
No. of vertices, followed by all values of adj matrix 

Output Format:
Minimum tour distance, minimum tour, 
Intermediate calculations (optional) -- uncomment it out if you want to look at it

Time Complexity:
O(2^n * n^2) - same as brute force approach
Having said that, this algorithm is faster than brute force approach.
*/

#include <stdio.h>
#include <stdbool.h> // for bool data type
#include <limits.h> // for INT_MAX

const int maxint = INT_MAX/2; // A large value of my choosing.
typedef int set; // set is now an alias of int

// In my system, INT_MAX = (7fffffff)h = (2147483647)decimal
// That's 31 ones in binary. 
// But using such large values has been known to
// cause static memory allocation to fail.

// We'll use a maximum of 10. 
#define MAX_VERTICES (10) 
#define MAX_LIMIT (1<<MAX_VERTICES - 1)

// Global variables
int mat[MAX_VERTICES][MAX_VERTICES];
int verts; // no. of vertices
set limit; // A set containing all vertices.
int dp[MAX_VERTICES][MAX_LIMIT + 1]; // Dynamic programming table. 

int two_power(int exponent)
{
	return 1 << exponent; // pow(2, exponent)
}

void initialize_limit(int verts)
{
	limit = two_power(verts) - 1;
	// Suppose verts is 4,
	// 2^4 - 1 = 15 = (1111)bin
}

void initialize_dp(int verts, int limit)
{
	int i, j;
	for (i = 0; i < verts; ++i)
	for (j = 0; j <= limit; ++j) dp[i][j] = -1;
}

bool all_visited(set bitmask)
{
	return bitmask == limit;	
}

bool is_visited(set bitmask, int vertex)
{
	// pow(2, i) = a bit pattern where only ith bit is set
	return bitmask & two_power(vertex); // Checks whether `vertex`th bit is set or cleared in bitmask
}

void mark_visited(set* bitmask, int vertex)
{
	// 1 << i = pow(2, i) =* a bit pattern where only ith bit is set
	*bitmask = (*bitmask) | two_power(vertex); // Sets the `vertex`th bit in bitmask
}

void print_vx_and_set(int parent_vx, set cur_set)
{
	printf("(%d, ", parent_vx);
	printf("{");
	for (int i = 0; i < verts; ++i)
	{
		int res = (~cur_set) & two_power(i);
		if (res) printf("%d ", i);
	}
	printf("})");
}

void print_dp()
{
	int i, j;
	for (i = 0; i < verts; ++i)
	for (j = 0; j <= limit; ++j)
	{
		if (dp[i][j] != -1)
		{
			printf("g");
			print_vx_and_set(i, j);
			printf(" = ");
			printf("%d ", dp[i][j]);
			printf("\n");
		}
	}
}

// The most important function.
int tsp(int parent_vx, set cur_set)
{
	mark_visited(&cur_set, parent_vx);

	if (all_visited(cur_set)) 
	{
		dp[parent_vx][cur_set] = mat[parent_vx][0];	
		return mat[parent_vx][0]; 
	}

	// If value has already been calculated, then just return it
	if (dp[parent_vx][cur_set] != -1)
	{
		return dp[parent_vx][cur_set];
	}

	int distance, min_distance = maxint;

	// Calls tsp recursively on all non-visited vertices.
	// Since 0 is source, we don't start cur_vx at 0.
	for (int cur_vx = 1; cur_vx < verts; cur_vx++)
	{
		if (is_visited(cur_set, cur_vx) == false)
		{
			distance = mat[parent_vx][cur_vx] + tsp(cur_vx, cur_set); 
			if (min_distance > distance)
			{
				min_distance = distance;
			}
		}
	}

	dp[parent_vx][cur_set] = min_distance; // Storing result for later
	return min_distance;
}

// Prints out the tour looking at dp 
void traceback(int min_distance)
{
	set cur_set = 0;
	int cur_vx = 0;
	mark_visited(&cur_set, 0);
	int distance;

	// We start from g(1, {2, 3, 4, ... verts}) or h(0, {0})
	// and find out where the minimum came from. 

	// Say we have four vertices.
	// h(0, {0})              = min(mat[0][1] + h(1, {0, 1}),
	//		                    mat[0][2] + h(2, {0, 2}),
	//		                    mat[0][3] + h(3, {0, 3}))
	// Suppose the first one amounts to minimum ie min_distance.
	// Subtract mat[0][1] from min_distance
	// h(1, {0, 1}) =           min(mat[1][2] + h(1, {0, 1, 2}),
	//		                    mat[1][3] + h(3, {0, 1, 3}))
	// There are totally three of such iterations for four vertices.

	printf("Tour: 0 -> ");
	for (int i = 0; i < verts - 1; ++i)
	{
		for (int parent_vx = 1; parent_vx < verts; ++parent_vx)
		{
			if (is_visited(cur_set, parent_vx) == false)
			{
				set new_set = cur_set;
				mark_visited(&new_set, parent_vx);
			
				distance = mat[cur_vx][parent_vx] + dp[parent_vx][new_set];
				if (distance == min_distance)
				{
					printf("%d -> ", parent_vx);

					min_distance -= mat[cur_vx][parent_vx];

					// Update cur_vx and cur_set 
					cur_vx = parent_vx;
					cur_set = new_set;
					break;
				}
			}
		}
	}
	printf("0");
}

// Graphs for TSP are usually complete graphs.
void read_graph(int verts, int mat[MAX_VERTICES][MAX_VERTICES])
{
	int i, j;
	for (i = 0; i < verts; ++i)
	{
		for (j = 0; j < verts; ++j)
		{
			scanf("%d", &mat[i][j]);
		}
	}
}
void print_graph(int verts, int mat[MAX_VERTICES][MAX_VERTICES])
{
	int i, j;
	for (i = 0; i < verts; ++i, printf("\n"))
	for (j = 0; j < verts; ++j)
		printf("%d ", mat[i][j]);
}

void main()
{
	scanf("%d", &verts);
	read_graph(verts, mat);

	initialize_limit(verts);
	initialize_dp(verts, limit);

	set nullset = 0; 
	int min_dist = tsp(0, nullset); // source vertex = 0 
	// TODO Modify mat for any other source vertex

	printf("Minimum tour distance = %d\n", min_dist);
	traceback(min_dist);
	//print_dp();
}
