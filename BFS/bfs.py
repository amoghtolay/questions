#!/usr/bin/env python

# Code to do a BFS on a graph represented in the form
# of an adjacency list

t = int(raw_input())

for numCases in range(t):
	s = raw_input()
	numCities,numEdges = [int(i) for i in s.split(' ')]
	
	graph = {}
	 
	# Defining each node's adjacency list as empty
	for node in range(numCities):
		graph[node + 1] = []
	
	# Now populating the adjacency list of nodes as they are encountered	

	for countEdge in range(numEdges):
		s = raw_input()
		vert1,vert2 = [int(i) for i in s.split(' ')]
		graph[vert1].append(vert2)
	
	#print graph
	
	# Now adjacency list of graph has been made, now do a BFS on this graph
	
	numQues = int(raw_input())
	for countQues in range(numQues):
		q = []
		unmarkedVert  = [ x+1 for x in range(numCities) ]
		routeExists = 0
		
		s = raw_input()
		quesVert1,quesVert2 = [int(i) for i in s.split('?')]
		
		q.append(quesVert1)
		unmarkedVert.remove(quesVert1)
		
		while q:
			test = q.pop()

			if test == quesVert2:
				routeExists = 1
			
			for dest in graph[test]:
				if dest in unmarkedVert:
					unmarkedVert.remove(dest)
					q.append(dest)
		
		if routeExists:
			print "Route Exists"
		else:
			print "Route Doesn't Exist"
