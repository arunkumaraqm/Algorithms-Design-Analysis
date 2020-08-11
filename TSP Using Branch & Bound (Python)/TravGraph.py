from collections import defaultdict
class Graph:

	def __init__(self, nfverts = None, representation = None):
		self.nfverts = nfverts # no. of vertices

		self.representation = representation if representation else "matrix"
		if self.representation == "matrix":
			self.graph = [] # list of lists

		elif self.representation == "lists":
			self.graph = defaultdict(dict) # dict of dicts
		
		else:
			raise ValueError("Invalid representation.")

	
	def read_from_file(self, input_file): 
		# The input should be an adjacency matrix either way.

		self.nfverts = int(input_file.readline())
		
		if self.representation == "matrix": 
			def inner_loop(u):
				self.graph.append([int(number) for number in input_file.readline().split()])
		else:
			def inner_loop(u):
				for v, number in enumerate(input_file.readline().split()):
					number = float(number)
					if number != 0: self.graph[u][v] = number


		for u in range(self.nfverts): 
			inner_loop(u)

	def change_diag_to_infs(self):
		if self.representation == "matrix":
			for i in range(self.nfverts):
				self.graph[i][i] = float('inf')

	def read_from_stdin(self):
		import sys
		self.read_from_file(sys.stdin)
		self.change_diag_to_infs()

	def __str__(self):
		if self.representation == "matrix":
			return "\n".join(str(row) for row in self.graph)
		else: # You expect that it prints edges but that's not what it does.
			return '\n'.join(str(adj_list) for adj_list in self.graph.items())
