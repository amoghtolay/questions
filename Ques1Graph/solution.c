#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

typedef struct _edge {
  int v;
  int weight;
  struct _edge *next;
} edge;

typedef struct _vertex {
  edge *edges;
} vertex;


// Constructs an adjacency list and returns it. Size holds the number of vertices in G
vertex* constructGraph(char *filename, int *size);
void addEdge(vertex *u, int v, int weight);

// Returns 0 on success, -1 on failure. The cost of the best route if
// connected is set in bestCost, and the length of the path in numberOfSteps
int dijkstras(int source, int destination, vertex *G, int numVertices, int *bestCost, int *numberOfSteps);

int main(int argc, char *argv[]) {

  int N;
  vertex *G = constructGraph(argv[1], &N);
  int bestDistance, numberOfSteps, success;

  success = dijkstras(0, N-1, G, N, &bestDistance, &numberOfSteps);
  if (success == 0)
    printf("%d\n", bestDistance);
  else
    printf("No path found\n");

  return 0;
}


vertex* constructGraph(char *filename, int *size) {

  char sizeBuff[100];
  scanf("%s", sizeBuff);
  int m = atoi(strtok(sizeBuff, ","));
  int n = atoi(strtok(NULL, ","));
  
  // Create matrices of size mxn for hodling values and another one for indicating burglars.
  int **grid = (int **)malloc(m * sizeof(int*));
  int **burglar = (int **)malloc(m * sizeof(int*));
  int i;
  for (i = 0; i < m; i++) {
    grid[i] = (int *)malloc(n * sizeof(int));
    burglar[i] = (int *)malloc(n * sizeof(int));
  }


  char *buff = (char *)malloc(15*n);
  int j;

  for (i = 0; i < m; i++) {
    scanf("%s", buff);
    for (j = 0; j < n; j++) {
      int value;
      if (j == 0) {
	value = atoi(strtok(buff, ","));
      } else {
	value = atoi(strtok(NULL, ","));
      }
      if (value >= 0) {
	grid[i][j] = value;
	burglar[i][j] = 0;
      } else {
	grid[i][j] = INT_MAX;
	burglar[i][j] = value;
      }
    }
  }
  free(buff);

  // Now reduce the values of neighbours of burglars.
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      if (burglar[i][j] < 0) {
	if (i-1 >= 0 && j-1 >= 0 && burglar[i-1][j-1] == 0)
	  grid[i-1][j-1] += burglar[i][j];
	if (i-1 >= 0 && burglar[i-1][j] == 0)
	  grid[i-1][j] += burglar[i][j];
	if (i-1 >= 0 && j+1 < n && burglar[i-1][j+1] == 0)
	  grid[i-1][j+1] += burglar[i][j];
	if (j+1 < n && burglar[i][j+1] == 0)
	  grid[i][j+1] += burglar[i][j];
	if (i+1 < m && j+1 < n && burglar[i+1][j+1] == 0)
	  grid[i+1][j+1] += burglar[i][j];
	if (i+1 < m && burglar[i+1][j] == 0)
	  grid[i+1][j] += burglar[i][j];
	if (i+1 < m && j-1 >= 0 && burglar[i+1][j-1] == 0)
	  grid[i+1][j-1] += burglar[i][j];
	if (j-1 >= 0 && burglar[i][j-1] == 0)
	  grid[i][j-1] += burglar[i][j];
      }
    }
  }


  vertex *G = (vertex *)malloc(m*n*sizeof(vertex));
  for (i = 0; i < m*n; i++)
    G[i].edges = NULL;

  // Now, creating edges is straightforward from the grid
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      if (grid[i][j] != INT_MAX) {
	int u = i*n + j;
	int v;
	if (j+1 < n && grid[i][j+1] != INT_MAX) {
	  v = u + 1;
	  addEdge(&G[u], v, grid[i][j+1]);
	}
	if (i+1 < m && grid[i+1][j] != INT_MAX) {
	  v = (i+1)*n + j;
	  addEdge(&G[u], v, grid[i+1][j]);
	}
      }
    }
  }
  
  // Now free the grids and burglar matrices
  for (i = 0; i < m; i++) {
    free(grid[i]);
    free(burglar[i]);
  }
  free(grid);
  free(burglar);

  *size = m*n;
  return G;
}


void addEdge(vertex *u, int v, int weight) {
  edge *ptr = u->edges;
  if (ptr == NULL) {
    u->edges = (edge *)malloc(sizeof(edge));
    ptr = u->edges;
  } else {
    while (ptr->next != NULL)
      ptr = ptr->next;
    ptr->next = (edge *)malloc(sizeof(edge));
    ptr = ptr->next;
  }
  ptr->v = v;
  ptr->weight = weight;
  ptr->next = NULL;
}


// Returns 0 on success, -1 on failure. The cost of the best route if
// connected is set in bestCost, and the length of the path in numberOfSteps
int dijkstras(int source, int destination, vertex *G, int numVertices, int *bestCost, int *numberOfSteps) {

  // Initialize
  int i;
  int *dist, *parent, *Q;
  dist = (int *)malloc(numVertices * sizeof(int));
  parent = (int *)malloc(numVertices * sizeof(int));
  Q = (int *)malloc(numVertices * sizeof(int));
  for (i = 0; i < numVertices; i++) {
    dist[i] = INT_MAX;
    parent[i] = -1;
    Q[i] = i;
  }
  dist[source] = 0;

  // Find the value that must be added to make all entries positive.
  // This essentially means finding the largest positive value as this will
  // be the most negative after sign reversal
  int delta = 0;
  edge *ptr;
  for (i = 0; i < numVertices; i++) {
    ptr = G[i].edges;
    while (ptr != NULL) {
      if (delta < ptr->weight)
	delta = ptr->weight;
      ptr = ptr->next;
    }
  }

  // Algorithm
  while (1) {
    // Repeat till Q not empty
    int u = -1;
    int minInQ = INT_MAX;
    for (i = 0; i < numVertices; i++) {
      if (Q[i] >= 0 && dist[i] != INT_MAX && dist[i] < minInQ) {
	minInQ = dist[i];
	u = i;
      }
    }
    if (u == -1) {
      // Vertex not reachable
      return -1;
    }
    if (u == destination) {
      // Reached destination
      break;
    }

    // Remove u from Q
    Q[u] = -1;

    int alt;
    ptr = G[u].edges;
    while (ptr != NULL) {
      alt = dist[u] - ptr->weight + delta; // Negate edge weight and add delta
      if (alt < dist[ptr->v]) {
	dist[ptr->v] = alt;
	parent[ptr->v] = u;
      }
      ptr = ptr->next;
    }
  }

  int pathLength = 0;
  int u = destination;
  while (parent[u] != -1) {
    u = parent[u];
    pathLength++;
  }

  *bestCost = (pathLength * delta) - dist[destination];
  *numberOfSteps = pathLength;

  return 0;
}
