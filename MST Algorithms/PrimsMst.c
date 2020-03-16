// Some code can be uncommented if you want to look at the result MST.

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>
#define Cap 100 // Maximum on noof vertices
#define maxint INT_MAX

typedef struct Graph
{
	int nfverts;
	int mat[Cap + 1][Cap + 1];
	int mst[Cap];
} Graph;

void g_read(Graph* gr)
{
	scanf("%d", &(gr->nfverts));
	int i, j;

	// Reading the adj mat
	for (i = 1; i <= gr->nfverts; ++i)
	{
		for (j = 1; j <= gr->nfverts; ++j)
		{
			scanf("%d", &(gr->mat[i][j]));
		}
		gr->mat[i][i] = 0; // Removing self loops
	}
}

void g_print(Graph* gr)
{
	int i, j;

	// Printing the adj mat
	for (i = 1; i <= gr->nfverts; ++i)
	{
		for (j = 1; j <= gr->nfverts; ++j)
		{
			printf("%d ", (gr->mat[i][j]));
		}

		printf("\n");
	}
}

int min_key(int nfverts, int* key, bool* visited)
{
	int min = maxint, min_ind;
	for (int v = 1; v <= nfverts; ++v)
	{
		if (key[v] < min && visited[v] == false)
		{	
			min = key[v];
			min_ind = v;
		}
	}
	return min_ind;
}

void g_print_mst(Graph* gr, int src)
{
	int total_cost = 0, i;
	int* mst = gr->mst;

	for (i = 1; i < src; ++i)
	{
//		printf("(%d, %d) ", i, mst[i]);
		total_cost += gr->mat[i][mst[i]];
	}
	for (i = src + 1; i <= gr->nfverts; ++i)
	{
//		printf("(%d, %d) ", i, mst[i]);
		total_cost += gr->mat[i][mst[i]];
	}
//	printf("\n");
	
	printf("Minimum cost by Prim's = %d\n", total_cost);
}

void g_prims_mst(Graph* gr, int src)
{
	int key[gr->nfverts + 1];
	bool visited[gr->nfverts + 1];
	int* mst = gr->mst;

	int i;
	for (i = 1; i <= gr->nfverts; ++i)
	{
		key[i] = maxint;
		visited[i] = false;
	} 
	
	key[src] = 0; // so that vertex 0 is picked first
	
	mst[src] = -1; // src node is root
	int u, v;
		
	#define cost(u, v) (gr->mat[u][v])
	
	for (i = 1; i <= gr->nfverts; ++i)
	{
		u = min_key(gr->nfverts, key, visited);
		visited[u] = true;
				
		for (v = 1; v <= gr->nfverts; ++v)
		{
			if (cost(u, v) > 0 && visited[v] == false && key[v] > cost(u, v))
			{
				key[v] = cost(u, v);
				mst[v] = u;
			}
		}
	}
}

void main()
{
	Graph gr;
	g_read(&gr);
	int src = 1;
	g_prims_mst(&gr, src); // Fills in mst
	g_print_mst(&gr, src);
}

/*
Tests

TESTS

#1
In: 6
0 4 0 0 6 5
4 0 1 0 0 4
0 1 0 6 0 4
0 0 6 0 8 5
6 0 0 8 0 2
5 4 4 5 2 0

Out:
{(1, 0), (2, 1), (3, 5), (4, 5), (5, 1), }
16

#2
In: 7
00 00 14 00 18 24 00
00 00 28 00 00 00 10
14 28 00 16 00 00 00
00 00 16 00 12 00 00
18 00 00 12 00 22 00
24 00 00 00 22 00 25
00 10 00 00 00 25 00

Out:
{(1, 6), (2, 0), (3, 2), (4, 3), (5, 4), (6, 5), }
99
*/

