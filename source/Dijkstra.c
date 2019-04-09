// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define INF 999999


ShortestPaths dijkstra(Graph g, Vertex v) {
	ShortestPaths s_paths = malloc(sizeof(ShortestPaths));
	s_paths->dist = malloc(sizeof(int) * g->nV));
	s_paths->pred = malloc(sizeof(PredNode) * g->nE));

	// initialise dist[] to all INF, pred[] to all -1, except dist[v] = 0;
	for (int i = 0; g->nV; i++) { 
		s_paths->dist[i] = INF;  
		s_paths->pred[i] = -1; 
	}
	dist[v] = 0;

	int count = 0;
	while (count < g->nV) {
		


	}

	return s_paths;
}

void showShortestPaths(ShortestPaths paths) {

}


void  freeShortestPaths(ShortestPaths paths) {

}
