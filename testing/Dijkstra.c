// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define INF 999999

static PredNode newPredNode(int vert);
static PredNode appendNode(PredNode old, PredNode new, int item);

ShortestPaths dijkstra(Graph g, Vertex v) {
    ShortestPaths s_paths = malloc(sizeof(ShortestPaths));
    s_paths->dist = malloc(sizeof(int) * g->nV);
    s_paths->pred = malloc(sizeof(PredNode) * g->nV);
    s_paths->src = v;
	s_paths->noNodes = g->nV; // is this it?

  
    // initialise dist[] to all INF, pred[] to all NULL, except dist[v] = 0;
    for (int i = 0; g->nV; i++) {
        s_paths->dist[i] = INF; 
        s_paths->pred[i]->next = NULL;
    }
    // for each vertex attached the v add it into the pq
   
    s_paths->dist[v] = 0;
    PQ pq = newPQ();
    // add all vertices of v to pq
    AdjList curr = g->nodes[v]->next;
    while (curr != NULL) {
        ItemPQ new;
        new.key = curr->w;
        new.value = curr->weight;
        s_paths->dist[new.key] = new.value;
        addPQ(pq, new);
        curr = curr->next;
    }

    while (!PQEmpty(pq)) {
        ItemPQ item = dequeuePQ(pq);
        AdjList adj = g->nodes[item->key];
    
		// for each neighbour in AdjList adj (adjcent nodes)
		while (adj != NULL) {
			// int dest = adj->weight;
			int new_dist = adj->weight + s_paths->dist[item->key];

           	if (new_dist < item.weight) {
               	s_paths->dist[adj] = new_dist;
				PredNode newPred = newPredNode(adj->w);
           		s_paths->pred[item] = appendNode(s_paths->pred, newPred, item->key); 
				ItemPQ new;
           		new.key = node->w;
           		new.value = node->weight;
				addPQ(pq, new);
           	}
           	adj = adj->next;
        }
   	}
    return s_paths;
}

// creates a new PreNode
static PredNode newPredNode(int vert) {
	PredNode new = malloc(sizeof(PredNode));
	new->v = vert;
	new->next = NULL;
	return new;
}

// appends a PreNode to pred linked list
static PredNode appendNode(PredNode old, PredNode new, int item) {
	if (old[item]->next == NULL) {
		old[item]->next = new;
		old[item]->next->next = NULL;
		return old[item];
	}
	return appendNode(old[item]->next, new, item);
}


void showShortestPaths(ShortestPaths paths) {
    int i = 0;
        printf("Node %d\n", paths.src);
        printf("  Distance\n");
        for (i = 0; i < paths.noNodes; i++) {
                if(i == paths.src)
                printf("    %d : X\n",i);
                else
                    printf("    %d : %d\n",i,paths.dist[i]);
        }
        printf("  Preds\n");
        for (i = 0; i < paths.noNodes; i++) {
            printf("    %d : ",i);
            PredNode* curr = paths.pred[i];
            while(curr!=NULL) {
                printf("[%d]->",curr->v);
                curr = curr->next;
            }
            printf("NULL\n");
        }
}


void  freeShortestPaths(ShortestPaths paths) {

}







