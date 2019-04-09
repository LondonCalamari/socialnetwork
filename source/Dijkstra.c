// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define INF 999999

static PredNode newPredNode(int vert);
static PredNode appendNode(PredNode old[item], PredNode new);

ShortestPaths dijkstra(Graph g, Vertex v) {
    ShortestPaths s_paths = malloc(sizeof(ShortestPaths));
    s_paths->dist = malloc(sizeof(int) * g->nV));
    s_paths->pred = malloc(sizeof(PredNode) * g->nV);
    s_paths->src = v;
	s_paths->noNodes = g->nV; // is this it?

    PQ pq = newPQ();
    // initialise dist[] to all INF, pred[] to all -1, except dist[v] = 0;
    for (int i = 0; g->nV; i++) {
        s_paths->dist[i] = INF; 
        s_paths->pred[i] = -1;
    }
    // for each vertex attached the v add it into the pq
   
    dist[v] = 0;
    // add all vertices of v to pq
    AdjList curr = g->nodes[v]->next;
    while (curr != NULL) {
        ItemPQ new;
        new.key = curr->w;
        new.value = curr->weight;
        s_paths->dist[new.key] = new.value;
        addPQ(pq, first);
        curr = curr->next;
    }

    while (!PQEmpty(pq)) {
        item = dequeue(pq);
        AdjList adj = g->nodes[item->key];
    
		// for each neighbour in AdjList adj (adjcent nodes)
		while (adj != NULL) {
			// int dest = adj->weight;
			int new_dist = adj->weight + s_paths->dist[item->key];

           	if (new_dist < item.weight) {
               	s_paths->dist[adj] = new_dist;
				newPred = newPredNode(adj->w);
           		s_paths->pred[item] = appendNode(s_paths->pred[item], newPred); 
				ItemPQ new;
           		new.key = node->w;
           		new.value = node->weight;
				addPQ(new);
           	}
           	adj = adj->next;
        }
   	}
    return s_paths;
}

// creates a new PreNode
static PredNode newPredNode(int vert) {
	new = malloc(sizeof(PredNode));
	new->v = vert;
	new->next = NULL;
	return new;
}

// appends a PreNode to pred linked list
static PredNode appendNode(PredNode old[item], PredNode new) {
	if (old[item]->next == NULL) {
		old[item]->next = new;
		old[item]->next->next = NULL;
		return old[item];
	}
	return appendNode(old[item]->next, new);
}


void showShortestPaths(ShortestPaths paths) {

}


void  freeShortestPaths(ShortestPaths paths) {

}







