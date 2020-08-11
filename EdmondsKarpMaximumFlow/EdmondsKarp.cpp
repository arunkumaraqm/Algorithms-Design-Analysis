/*
Ford Fulkerson with BFS aka Edmonds-Karp 
Problem statement: Given network, source, destination, find total flow.
Time comp: O((|E| ^ 2) * |V|)
Author: Arun Kumar
*/
#include <iostream>
#include <queue>
#include <limits>
using namespace std;
#define MAX_VERTICES 25

void fill_zeros(int nfverts, int mat[][MAX_VERTICES])
{
	int i, j;
	for (i = 0; i < nfverts; ++i)
	{
		for (j = 0; j < nfverts; ++j)
		{
			mat[i][j] = 0;
		}
	}
}

void read_matrix(int &nfverts, int mat[][MAX_VERTICES])
{
	int i, j, nfedges, u, v, weight;

	cin >> nfverts;
	cin >> nfedges;

	fill_zeros(nfverts, mat);

	for (i = 0; i < nfedges; ++i)
	{
		cin >> u >> v >> weight;
		mat[u][v] = weight;
	}
}

void print_matrix(int rows, int mat[][MAX_VERTICES])
{
	int i, j;
	for (i = 0; i < rows; ++i, cout << '\n')
		for (j = 0; j < rows; ++j)
			cout << mat[i][j] << ' ';
	cout << endl;
}

void matcopy(int source[][MAX_VERTICES], int destination[][MAX_VERTICES], int rows)
{
	int i, j;
	for (i = 0; i < rows; ++i)
		for (j = 0; j < rows; ++j)
			destination[i][j] = source[i][j];
}

void print_arr(int size, int arr[])
{
	cout << "child_parent_map: ";
	for (int i = 0; i < size; ++i)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;
}

int* bfs(int mat[][MAX_VERTICES], int nfverts, int start = 0, int end = -1)
{
	if (end == -1) end = nfverts - 1;

	int i, j;
	queue <int> vertsq;
	int* child_parent_map = new int [nfverts];
	for (i = 0; i < nfverts; ++i) child_parent_map[i] = -1;
	bool visited[nfverts] = {};
	int parent; bool found;

	vertsq.push(start);

	while (not vertsq.empty())
	{
		parent = vertsq.front();
		vertsq.pop();
		visited[parent] = true;
		//cout << parent <<endl;

		for (j = 0; j < nfverts; ++j)
		{
			if (mat[parent][j] != 0 and visited[j] == false)
			{
				vertsq.push(j);
				if (child_parent_map[j] != -1) continue;
				else child_parent_map[j] = parent;
				
				if (j == end)
				{
					found = true;
					break;
				}
			}
		}
		if (found) break;
	}
	//print_arr(nfverts, child_parent_map);
	return child_parent_map;
}

int calculate_flow(int* child_parent_map, int nfverts, int mat[][MAX_VERTICES],\
				   int start = 0, int end = -1)
{
	if (end == -1) end = nfverts - 1;

	if (child_parent_map[end] == -1) return -1;

	int vertex, weight, parent;
	int flow = INT8_MAX;

	for (vertex = end; vertex != start; vertex = parent)
	{
		parent = child_parent_map[vertex];
		weight = mat[parent][vertex];
		
		cout << vertex << "<--" << parent << endl;		
		if (weight < flow)
		{
			flow = weight;
		}
	}

	return flow;
}

void augment_flow(int* child_parent_map, int nfverts, int mat[][MAX_VERTICES], int flow,\
				    int start = 0, int end = -1)
{
	if (end == -1) end = nfverts - 1;

	int vertex, parent;

	for (vertex = end; vertex != start; vertex = parent)
	{
		parent = child_parent_map[vertex];
		mat[parent][vertex] -= flow;
		mat[vertex][parent] += flow;
	}
}

int ford_fulkerson(int nfverts, int mat[][MAX_VERTICES], int start = 0, int end = -1)
{
	if (end == -1) end = nfverts - 1;
	int* child_parent_map;
	int flow, total_flow = 0;

	while (true)
	{
		child_parent_map = bfs(mat, nfverts);
		
		flow = calculate_flow(child_parent_map, nfverts, mat);
		
		if (flow == -1)
		{
			break;
		}
		else
		{
			total_flow += flow;
		}

		augment_flow(child_parent_map, nfverts, mat, flow);
		delete [] child_parent_map;
		
		print_matrix(nfverts, mat);
	}
	return total_flow;
}

void print_network(int rows, int mat[][MAX_VERTICES], int capacities[][MAX_VERTICES])
{
	int i, j, edge_flow;
	for (i = 0; i < rows; ++i, cout << '\n')
		for (j = 0; j < rows; ++j)
		{
			//cout << mat[i][j] << ' '<< mat[j][i]<<'\n';
			if (mat[i][j] == capacities[i][j]) edge_flow = 0;
			else if (mat[i][j] > capacities[i][j]) edge_flow = 0;
			else if (mat[j][i] > capacities[j][i]) edge_flow = mat[j][i];

			cout << edge_flow << '/' << capacities[i][j] << ' ';
		}
	cout << endl;
}

int main()
{
	int mat[MAX_VERTICES][MAX_VERTICES];
	int nfverts = MAX_VERTICES;

	read_matrix(nfverts, mat);
	print_matrix(nfverts, mat);
	int original_mat[MAX_VERTICES][MAX_VERTICES];
	matcopy(mat, original_mat, nfverts);

	int total_flow = ford_fulkerson(nfverts, mat);
	print_network(nfverts, mat, original_mat);
	cout << "Total Flow = "<< total_flow << endl;
	
}

