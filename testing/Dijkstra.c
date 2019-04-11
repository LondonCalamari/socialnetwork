// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define INF 999999

static PredNode newPredNode(int vert);
static void appendNode(PredNode base, PredNode new); 
// static PredNode appendNode(PredNode old, PredNode new, int item);

ShortestPaths dijkstra(Graph g, Vertex v) {
    ShortestPaths paths = malloc(sizeof(ShortestPaths));
    paths->dist = malloc(sizeof(int) * g->nV);
    paths->pred = malloc(sizeof(PredNode) * g->nV);
    paths->src = v;
	paths->noNodes = g->nV; // is this it?

  
    // initialise dist[] to all INF, pred[] to all NULL, except dist[v] = 0;
    for (int i = 0; g->nV; i++) {
        paths->dist[i] = INF; 
        paths->pred[i]->next = NULL;
    }
    // for each vertex attached the v add it into the pq
   
    paths->dist[v] = 0;
    PQ pq = newPQ();
    // add all vertices of v to pq
    /*
    int i  = 0;
    while (i < g->nV) {
        ItemPQ new;
        new.key = g->nodelist[i]->w;
        new.value = g->nodelist[i]->INF;
        paths->dist[new.key] = new.value;
        addPQ(pq, new);
        curr = curr->next;
    }
    */
    while (!PQEmpty(pq)) {
        ItemPQ item = dequeuePQ(pq);
        AdjList adj = g->nodes[item->key];
    
		// for each neighbour in AdjList adj (adjcent nodes)
		while (adj != NULL) {
			// int dest = adj->weight;
			int new_dist = adj->weight + paths->dist[item->key];
           	if (new_dist < paths->dist[adj->w]) {
           	    // makes this the new path
               	paths->dist[adj] = new_dist;
				PredNode newPred = newPredNode(adj->w);
           		paths->pred[item] = appendNode(paths->pred[item], newPred); 
				ItemPQ new;
           		new.key = adj->w; 
           		new.value = adj->weight;
				addPQ(pq, new);
           	}
           	adj = adj->next;
        }
   	}
    return paths;
}

// creates a new PreNode
static PredNode newPredNode(int vert) {
	PredNode new = malloc(sizeof(PredNode));
	new->v = vert;
	new->next = NULL;
	return new;
}

 static void appendNode(PredNode base, PredNode new) {
     PredNode curr = base;
     while (curr->next != NULL){
         curr = curr->next;
     }
     curr->next = new;
     curr->next->next = NULL;
     return;

 }

/*
// appends a PreNode to pred linked list
static PredNode appendNode(PredNode old, PredNode new, int item) {
	if (old[item]->next == NULL) {
		old[item]->next = new;
		old[item]->next->next = NULL;
		return old[item];
	}
	return appendNode(old[item]->next, new, item);
}
*/

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
    free(paths->dist);
    for (int i =0; i < noNodes; i++) {
        free(&pred[i]);
    }
    free(paths);
}







