# TSP using branch and bound.
# This program was written only to check whether changing the order of doing row reductions 
# and column reductions makes any difference in the final result.
# The conclusion was no. You can do the reductions either way for every node; the solution
# will be the same.

from TravGraph import Graph
inf = float('inf')
col_reduce_first = False

class Node:
	def __init__(self, cost, matrix, route):
		self.cost = cost
		self.matrix = matrix
		self.route = route

	def to_tuple(self):
		return tuple([self.cost, self.matrix, self.route])

	def __str__(self):
		return f"({self.cost}, {self.route})\n" + '\n'.join(str(row) for row in self.matrix) + '\n'


	def __lt__(self, other): return self.cost < other.cost
	def __le__(self, other): return self.cost <= other.cost
	def __gt__(self, other): return self.cost > other.cost
	def __ge__(self, other): return self.cost >= other.cost
	def __eq__(self, other): return self.cost == other.cost

class MinPriorityQueue:

	def __init__(self):
		self.route_node_map = dict()

	def extract_min(self):
		min_node = min(self.route_node_map.values())
		del self.route_node_map[min_node.route]
		return min_node

	def insert(self, cost, matrix, route):
		route = tuple(route)
		self.route_node_map[route] = Node(cost, matrix, route)

	def isempty(self):
		return len(self.route_node_map) == 0

	def __str__(self):
		return '\n'.join(str(route_node_map[route]) for route in self.routes)

def adjust_matrix(initial_mat, route):
	# Fills inf wherever required based on route
	mat = initial_mat
	nfverts = len(mat)

	if len(route) == 1:
		return mat

	current = route[-1]
	previous = route[-2]
	for ind in range(nfverts):
		mat[previous][ind] = inf
		mat[ind][current] = inf
	mat[current][previous] = inf

	return mat

def reduce_matrix(mat):
	# Makes row and column reductions
	nfverts = len(mat)

	def row_reduction():
		nonlocal mat
		other_mat = []
		reduction_cost = 0
		
		for row in mat:
			minval = min(row)
			if minval != inf:
				other_mat.append([val - minval for val in row])
				reduction_cost += minval
			else:
				other_mat.append(row)

		mat = other_mat
		return reduction_cost

	def column_reduction():
		reduction_cost = 0
		for j in range(nfverts):
			minval = inf
			for i in range(nfverts):
				if mat[i][j] < minval:
					minval = mat[i][j]
			if minval != inf:
				for i in range(nfverts):
					mat[i][j] -= minval
				reduction_cost += minval
		return reduction_cost

	global col_reduce_first
	if col_reduce_first == True:
		reduction_cost = column_reduction() + row_reduction()
	else:
		reduction_cost = row_reduction() + column_reduction()

	return mat, reduction_cost

def compute_node(parent_cost, parent_mat, route):
	mat = [row.copy() for row in parent_mat]
	mat = adjust_matrix(mat, route)
	mat, cost = reduce_matrix(mat)	
	
	try: new_edge_weight = parent_mat[route[-2]][route[-1]]
	except IndexError: new_edge_weight = 0

	return cost + parent_cost + new_edge_weight, mat


def trav_bnb(grf):
	node_queue = MinPriorityQueue()

	route = tuple([0])
	cost, mat = compute_node(0, grf.graph, route)
	node_queue.insert(cost, mat, route)

	while not node_queue.isempty():
		node = node_queue.extract_min()
		#print(node)
		parent_cost, parent_mat, parent_route = node.to_tuple()

		flag = False
		for i in range(grf.nfverts):
			if i not in parent_route:
				flag = True
				route = tuple(list(parent_route)+ [i])
				cost, mat = compute_node(parent_cost, parent_mat, route)
				node_queue.insert(cost, mat, route)

		if flag == False:
			return parent_cost, route

if __name__ == '__main__':
	grf = Graph()
	grf.read_from_stdin()	
	print(trav_bnb(grf))
	col_reduce_first = True
	print(trav_bnb(grf))













