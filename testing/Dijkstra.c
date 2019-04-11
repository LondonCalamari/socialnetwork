// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define INF 999999

static PredNode * newPredNode(int vert);
static void appendNode(PredNode *base, PredNode *new); 
// static PredNode appendNode(PredNode old, PredNode new, int item);

ShortestPaths dijkstra(Graph g, Vertex v) {
    ShortestPaths paths;
    paths.dist = malloc(sizeof(int) * numVerticies(g));
    paths.pred = malloc(sizeof(PredNode) * numVerticies(g));
    paths.src = v;
	paths.noNodes = numVerticies(g); // is this it?
    PQ pq = newPQ();
  
    // initialise dist[] to all INF, pred[] to all NULL, except dist[v] = 0;
    for (int i = 0; paths.noNodes; i++) {
        paths.dist[i] = INF; 
        paths.pred[i]->next = NULL;
    }
    AdjList curr = outIncident(g, v);
    while (curr != NULL) {
        ItemPQ new;
        new.key = curr->w;
        new.value = curr->weight;
        addPQ(pq, new);
        curr = curr->next;
    }
    // for each vertex attached the v add it into the pq
    paths.dist[v] = 0;
    
    // add all vertices of v to pq
    while (!PQEmpty(pq)) {
        ItemPQ item = dequeuePQ(pq);
        AdjList adj = outIncident(g,item.key);
    
		// for each neighbour in AdjList adj (adjcent nodes)
		while (adj != NULL) {
			// int dest = adj->weight;
			int new_dist = adj->weight + paths.dist[item.key];
           	if (new_dist < paths.dist[adj->w]) {
           	    // makes this the new path
               	paths.dist[adj->w] = new_dist;
				PredNode * newPred = newPredNode(adj->w);
           		appendNode(paths.pred[item.key], newPred); 
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
static PredNode * newPredNode(int vert) {
	PredNode * new = malloc(sizeof(PredNode));
	new->v = vert;
	new->next = NULL;
	return new;
}

static void appendNode(PredNode *base, PredNode *new) {
     while (base->next != NULL){
         base = base->next;
     }
     base->next = new;
     base->next->next = NULL;
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
    free(paths.dist);
    for (int i =0; i < paths.noNodes; i++) {
        free(&paths.pred[i]);
    }
}







