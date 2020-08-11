// Kosaraju's Algo
#include <iostream>
#include <deque>
#include <array>
#include <vector>

using namespace std;
const int MAX_VERTICES = 20;
const bool DEBUG = true;
#define labelize(v) ((char)(v +'a'))

void debug_print(vector <int> &something)
{
	if (not DEBUG) return;
	for (auto i: something) cout << char(i + 'a')<< ' ';
	cout << endl;
}

void debug_print(deque <int> &something, bool with_labels = true)
{
	if (not DEBUG) return;
	if (with_labels)
		for (auto i: something) cout << labelize(i) << ' ';
	else
		for (auto i: something) cout << i << ' ';
	cout << endl;
}

void fill_zeros(int nfverts, bool mat[][MAX_VERTICES])
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

void transpose(int nfverts, bool mat[][MAX_VERTICES])
{
	int i, j;
	for (i = 0; i < nfverts; ++i)
	{
		for (j = i + 1; j < nfverts; ++j)
		{
			swap(mat[i][j], mat[j][i]);
		}
	}
}

void read_matrix(int &nfverts, bool mat[][MAX_VERTICES])
{
	int i, j, nfedges;
	char u_label, v_label;
	int u, v;

	cin >> nfverts;
	cin >> nfedges;

	fill_zeros(nfverts, mat);

	for (i = 0; i < nfedges; ++i)
	{
		cin >> u_label >> v_label;
		u = u_label - 'a';
		v = v_label - 'a';
		mat[u][v] = 1;
	}
}

void print_matrix(int rows, bool mat[][MAX_VERTICES])
{
	int i, j;
	for (i = 0; i < rows; ++i, cout << '\n')
		for (j = 0; j < rows; ++j)
			cout << mat[i][j] << ' ';
	cout << endl;
}

void recursive_forward_dfs(int nfverts, bool mat[][MAX_VERTICES], int curvx,\
							deque <int> &stack_verts, vector <bool> &visited)
{
	visited[curvx] = true;
	//cout << char(curvx + 'a') << ' ';

	for (int v = 0; v < nfverts; ++v)
	{
		if (mat[curvx][v] and not visited[v])
		{
			recursive_forward_dfs(nfverts, mat, v, stack_verts, visited);
		}
    }
	stack_verts.push_back(curvx);
	//debug_print(stack_verts);
}

void forward_dfs(int nfverts, bool mat[][MAX_VERTICES], \
					deque <int> &stack_verts)
{
	vector <bool> visited(nfverts);

	//cout << "Inside forward_dfs" <<endl;

	for (int v = 0; v < nfverts; ++v)
	{	
		if (visited[v]) continue;
		else recursive_forward_dfs(nfverts, mat, v, stack_verts, visited);
		// cout << endl;
		//for (auto i: visited) cout << i; cout << endl;
	}
	//debug_print(stack_verts);
}

void recursive_reverse_dfs(int nfverts, bool mat[][MAX_VERTICES], int curvx,\
							deque <int> &stack_verts, vector <bool> &visited,\
							vector <int> &components)
{
	visited[curvx] = true;
	components.push_back(curvx);
	//debug_print(components);
	//cout << "Just pushed to components " << char(curvx + 'a') << endl;

	for (int v = 0; v < nfverts; ++v)
	{
		if (mat[curvx][v] and not visited[v])
		{
			recursive_reverse_dfs(nfverts, mat, v, stack_verts, visited, components);
		}
	}

}

void reverse_dfs(int nfverts, bool mat[][MAX_VERTICES], \
					deque <int> &stack_verts, vector <int> &components, \
					deque <int> &tails_for_components)
{
	vector <bool> visited(nfverts);
	int v;
	//cout << "Inside reverse dfs" <<endl;
	while (not stack_verts.empty())
	{	
		v = stack_verts.back();
		stack_verts.pop_back();

		//cout << "Just popped from stack_verts " << labelize(v) << endl;

		if (visited[v]) continue;
		
		recursive_reverse_dfs(nfverts, mat, v, stack_verts, visited, components);
		tails_for_components.push_back(components.size() - 1);

		// cout << endl;
		//for (auto i: visited) cout << i; cout << endl;
	}
	//debug_print(stack_verts);
}

void print_strongly_connected_components\
	(vector <int> &components, deque <int> &tails_for_components)
{
	int i = 0;
	auto terminator = tails_for_components.begin();
	for (auto vx: components)
	{
		cout << labelize(vx) << ' ';

		if (i == *terminator)
		{
			cout << '\n';
			++terminator;
		}
		++i;
	}
}
int main()
{
	bool mat[MAX_VERTICES][MAX_VERTICES];
	int nfverts = MAX_VERTICES;

	read_matrix(nfverts, mat);

	deque <int> stack_verts;
	forward_dfs(nfverts, mat, stack_verts);

	transpose(nfverts, mat);

	vector <int> components;
	components.reserve(nfverts);

	// Each ele of this is the index of the last vertex of a component in `components`
	deque <int> tails_for_components; 

	reverse_dfs(nfverts, mat, stack_verts, components, tails_for_components);
	print_strongly_connected_components(components, tails_for_components);
/*
	debug_print(components);
	debug_print(tails_for_components);*/
}

