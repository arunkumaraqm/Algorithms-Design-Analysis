#include <stdio.h>

/////////////////////////////////////////
// DISJOINT SET OPERATIONS
void d_construct(int* d_arr, int noof_ele)
{
	d_arr[0] = 0;
	for (int i = 1; i <= noof_ele; ++i)
	{
		d_arr[i] = -1;
	}
}

int d_find(int* d_arr, int ele)
{
	while(d_arr[ele] >= 0)
	{
		ele = d_arr[ele];
	}
	return ele;
}

void d_union(int* d_arr, int anc1, int anc2)
{
	// We need d_arr[anc1] to be <= d_arr[anc2]
	if (d_arr[anc1] > d_arr[anc2])
	{
		// Swapping anc1 and anc2
		int temp = anc1;
		anc1 = anc2;
		anc2 = temp;
	}

	d_arr[anc1] += d_arr[anc2];
	d_arr[anc2] = anc1;	
}
//////////////////////////////////////

void arr_print(int size, int* arr)
{
	for (int i = 0; i < size; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}
/////////////////////////////////////
#define Cap 50
typedef struct Graph
{
	int mat[Cap + 1][Cap + 1];
	int compact[Cap * Cap][3]; // Sparse Matrix. [0] -> row ind, 
						   // [1] -> col ind, [2] -> edge weight
	int nfverts; // noof vertices
	int nfedges; // noof edges
	int mst_mat[Cap + 1][Cap + 1]; 
	int mst_cost;
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

void g_print_sparse(Graph* gr)
{
	for (int i = 0; i < gr->nfedges; ++i)
	{
		printf("(%d, %d, %d) ", gr->compact[i][0], gr->compact[i][1], gr->compact[i][2]);
	}
	printf("\n");
}

void g_print_mst(Graph* gr)
{
	int i, j;

	// Printing the adj mat
	for (i = 1; i <= gr->nfverts; ++i)
	{
		for (j = 1; j <= gr->nfverts; ++j)
		{
//			printf("%d ", (gr->mst_mat[i][j]));
		}

//		printf("\n");
	}

	printf("Minimum cost by Kruskal's = %d\n", gr->mst_cost);
}

void g_sparsify_mat(Graph* gr)
{
	int i, j, cur = 0;
	for (i = 1; i <= gr->nfverts; ++i)
	{
		for (j = i + 1; j <= gr->nfverts; ++j)
		{
			if (gr->mat[i][j])
			{
				gr->compact[cur][0] = i;
				gr->compact[cur][1] = j;
				gr->compact[cur][2] = gr->mat[i][j];
				cur += 1;
			}
		}
	}	
	gr->nfedges = cur;
}

#define swap(one, two) \
	do{\
		int temp = one;\
		one = two;\
		two = temp;\
	}while(0);

void g_selection_sort_edges(Graph* gr)
{
	int i, j, small, pos;
	for (i = 0; i < gr->nfedges; ++i)
	{
		small = gr->compact[i][2];
		pos = i;

		for (j = i + 1; j < gr->nfedges; ++j)
		{
			if (gr->compact[j][2] < small)
			{
				small = gr->compact[j][2];
				pos = j;
			}
		}

		swap(gr->compact[i][0], gr->compact[pos][0]);
		swap(gr->compact[i][1], gr->compact[pos][1]);
		swap(gr->compact[i][2], gr->compact[pos][2]);
	}
}

void g_construct_mst_mat(Graph* gr)
{
	int i, j;

	for (i = 1; i <= gr->nfverts; ++i)
	{
		for (j = 1; j <= gr->nfverts; ++j)
		{
			gr->mst_mat[i][j] = 0;
		}
	}	

	gr->mst_cost = 0;
}

void g_kruskals_mst(Graph* gr)
{
	int u, v, wt, anc1, anc2, cur = 0; 
	g_construct_mst_mat(gr);
	
	int d_arr[gr->nfverts + 1];
	d_construct(d_arr, gr->nfverts);

	g_sparsify_mat(gr);
	g_selection_sort_edges(gr);	
	
	for (int i = 1; i <= gr->nfverts - 1; ++i)
	{
		u = gr->compact[cur][0];
		v = gr->compact[cur][1];
		wt = gr->compact[cur][2];
		cur += 1;

		anc1 = d_find(d_arr, u);
		anc2 = d_find(d_arr, v);

		if (anc1 != anc2)
		{
			d_union(d_arr, anc1, anc2);
			gr->mst_cost += wt;
			gr->mst_mat[u][v] = gr->mst_mat[v][u] = wt;
		}

		else 
		{
			--i; // Since we found a cycle, we can't let \
			this i count towards (nfverts - 1)
		}
	}
}

void main()
{
	Graph gr;
	g_read(&gr);
	g_kruskals_mst(&gr);
	g_print_mst(&gr);
}
