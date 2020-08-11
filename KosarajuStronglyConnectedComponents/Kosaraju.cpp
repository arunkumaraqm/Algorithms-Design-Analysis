/*
Kosaraju's Algo
Problem statement: Given a graph, find the strongly connected components.
Input: Noof vertices, noof edges, all the edges (no weights, 
vertices are lowercase alphabetically labeled)
Output: All strongly connected components
Time comp: O(V + E) using adjacency lists
But O(V^2) since we're using adjacency matrix
*/
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

class DirectedUnweightedGraph
{
protected:
	int nfverts;
	bool mat[MAX_VERTICES][MAX_VERTICES];
public:
	void read_graph();
	void print_graph() const;
	void transpose_graph();
	void fill_zeros();
};

void DirectedUnweightedGraph:: fill_zeros()
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

void DirectedUnweightedGraph:: transpose_graph()
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

void DirectedUnweightedGraph:: read_graph()
{
	int i, j, nfedges;
	char u_label, v_label;
	int u, v;

	cin >> nfverts;
	cin >> nfedges;

	fill_zeros();

	for (i = 0; i < nfedges; ++i)
	{
		cin >> u_label >> v_label;
		u = u_label - 'a';
		v = v_label - 'a';
		mat[u][v] = 1;
	}
}

void DirectedUnweightedGraph:: print_graph() const
{
	int i, j;
	for (i = 0; i < nfverts; ++i, cout << '\n')
		for (j = 0; j < nfverts; ++j)
			cout << mat[i][j] << ' ';
	cout << endl;
}

class Kosaraju : public DirectedUnweightedGraph
{
private:
	deque <int> stack_verts;
	vector <int> components;
	vector <bool> visited;
	deque <int> tails_for_components;

	void forward_dfs();
	void reverse_dfs();
	void recursive_forward_dfs(int curvx);
	void recursive_reverse_dfs(int curvx);
	void print_strongly_connected_components() const;

public:	
	void run_algorithm();

};

void Kosaraju:: run_algorithm()
{
	forward_dfs();
	transpose_graph();
	components.reserve(nfverts);
	reverse_dfs();
	print_strongly_connected_components();
}

void Kosaraju:: recursive_forward_dfs(int curvx)
{
	visited[curvx] = true;

	for (int v = 0; v < nfverts; ++v)
	{
		if (mat[curvx][v] and not visited[v])
		{
			recursive_forward_dfs(v);
		}
    }
	stack_verts.push_back(curvx);
}

void Kosaraju:: forward_dfs()
{
	visited.assign(nfverts, false);

	for (int v = 0; v < nfverts; ++v)
	{	
		if (visited[v]) continue;
		else recursive_forward_dfs(v);
	}
}

void Kosaraju:: recursive_reverse_dfs(int curvx)
{
	visited[curvx] = true;
	components.push_back(curvx);
	//debug_print(components);
	//cout << "Just pushed to components " << char(curvx + 'a') << endl;

	for (int v = 0; v < nfverts; ++v)
	{
		if (mat[curvx][v] and not visited[v])
		{
			recursive_reverse_dfs(v);
		}
	}
}

void Kosaraju:: reverse_dfs()
{
	visited.assign(nfverts, false);
	int v;
	while (not stack_verts.empty())
	{	
		v = stack_verts.back();
		stack_verts.pop_back();

		if (visited[v]) continue;
		
		recursive_reverse_dfs(v);
		tails_for_components.push_back(components.size() - 1);
	}
}

void Kosaraju:: print_strongly_connected_components() const
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
	Kosaraju obj;
	obj.read_graph();
	obj.run_algorithm();
}

