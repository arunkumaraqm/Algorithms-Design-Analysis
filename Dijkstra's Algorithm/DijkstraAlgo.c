// Prints All Pair Shortest Paths using Dijkstra's Algorithm

// Input Format:
// Line 1 - no of vertices
// Next "no of vertices" lines - rows of adjacency matrix

// Output format:
// "no. of vertices lines" - each row is list of shortest distances for a vertex

// Time complexity: O(|V|cubed)

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define inf (INT_MAX)

int extract_min_key(int verts, int key[verts + 1], bool visited[verts + 1]) // Call with key + 1
{
	int i, min, pos = 0;

	// Assigning min the key value of first non-visited vertex.
	for (i = 1; i <= verts; ++i)
	{
		if (!visited[i])
		{
			min = key[i];
			pos = i;
			break;
		}
	}

	for ( ; i <= verts; ++i)
	{
		if (!visited[i] && min > key[i])
		{
			min = key[i];
			pos = i;
		}
	}

	return pos;
}

void print_key(int verts, int key[verts + 1])
{
	for (int i = 1; i <= verts; ++i)
		if (key[i] == inf) printf("inf ");
		else printf("%d ", key[i]);
	printf("\n");
}

void read_graph(int verts, int mat[verts + 1][verts + 1])
{
	int i, j;
	for (i = 1; i <= verts; ++i)
	{
		for (j = 1; j <= verts; ++j)
		{
			scanf("%d", &mat[i][j]);
			if (mat[i][j] == 0) mat[i][j] = inf;
		}

		mat[i][i] = 0;
	}
}

void print_graph(int verts, int mat[verts + 1][verts + 1])
{
	int i, j;
	for (i = 1; i <= verts; ++i, printf("\n"))
	for (j = 1; j <= verts; ++j)
		if (mat[i][j] == inf) printf("0 ");
		else printf("%d ", mat[i][j]);
}

void initialize_key(int verts, int key[verts + 1], int src)
{
	int i;
	for (i = 1; i < src; ++i) key[i] = inf;
	key[src] = 0;
	for (i = src + 1; i <= verts; ++i) key[i] = inf;
}

void initialize_visited(int verts, bool visited[verts + 1])
{
	for (int i = 1; i <= verts; ++i) visited[i] = false;
}

void dijkstra(int verts, int mat[verts + 1][verts + 1], int key[verts + 1], int src)
{
	initialize_key(verts, key, src); // O(|V|)
	//print_key(verts, key);

	bool visited[verts + 1];
	initialize_visited(verts, visited); // O(|V|)

	int u, v;

	for (int i = 1; i <= verts; ++i) // ___ * O(|V|) = O(|V|*|V|) = O(|V|squared)
	{
		u = extract_min_key(verts, key, visited); // O(|V|)
		visited[u] = true;
		if (key[u] == inf) continue;
		//printf("Selected vert %d\n", u);//

		// Relaxing every unvisited edge connected to u.
		for (v = 1; v <= verts; ++v) // O(|V|)
		{
			if (mat[u][v] != inf && visited[v] == false)
			{
				if (key[u] + mat[u][v] < key[v])
				{
					key[v] = mat[u][v] + key[u];
				}
			}
		}
		//print_key(verts, key); //
	}
}

void all_pairs_shortest_paths(int verts, int mat[verts + 1][verts + 1])
{
	int key[verts + 1];
	for (int i = 1; i <= verts; ++i) // __ * O(|V|) = O(|V|squared) * O(|V|) = O(|V|cubed)
	{
		dijkstra(verts, mat, key, i);
		print_key(verts, key);
	}
}

void main()
{
	int verts;
	scanf("%d", &verts);
	int mat[verts + 1][verts + 1];
	read_graph(verts, mat);
	all_pairs_shortest_paths(verts, mat);
}