// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define INF 9999

static PredNode *newPredNode(int vert);
//static void appendNode(PredNode *base, PredNode *new); 
// static PredNode appendNode(PredNode old, PredNode new, int item);

ShortestPaths dijkstra(Graph g, Vertex v) {
    ShortestPaths paths;
    paths.noNodes = numVerticies(g); // is this it?
    paths.src = v;
    paths.dist = malloc(sizeof(int) * numVerticies(g));
    assert(paths.dist != NULL);
    paths.pred = malloc(sizeof(PredNode *) * numVerticies(g));
    assert(paths.pred != NULL);
    PQ pq = newPQ();
    AdjList curr = outIncident(g, v);
    ItemPQ new; 
    new.key = v;
    new.value = 0;
    addPQ(pq, new);
    while (curr != NULL) {
        new.key = curr->w;
        printf("added node %d\n", new.key);
        new.value = curr->weight;
        addPQ(pq, new);
        curr = curr->next;
    }
    
    // initialise dist[] to all INF, pred[] to all NULL, except dist[v] = 0;
    for (int i = 0; i < paths.noNodes; i++) {
        paths.dist[i] = INF; 
        paths.pred[i] = NULL; 
    }
    // for each vertex attached the v add it into the pq
    paths.dist[v] = 0;
    // add all vertices of v to pq
    int distance = 0;
    while (!PQEmpty(pq)) {
        // will dequeue the shortest
        ItemPQ item = dequeuePQ(pq);
        printf("deq'd %d\n", item.key);
        distance = item.value;
        AdjList adj = outIncident(g,item.key);
        
		// for each neighbour in AdjList adj (adjcent nodes)
		// already ordered from smallest weight
        while (adj != NULL) {
			int new_dist = adj->weight + distance;
           	if (new_dist <= paths.dist[adj->w]) {
           	    // makes this the new path
               /* 
                PredNode *curr = paths.pred[item.key];
                if (curr != NULL) {
                    printf("in here\n");
                    paths.pred[adj->w]= newPredNode(curr->v);
                    while (curr->next != NULL) {
                        paths.pred[adj->w]->next = newPredNode(curr->next->v);
                        curr = curr->next;
                        paths.pred[adj->w] = paths.pred[adj->w]->next;
                    }
                }
                */
                // copy the path from item.key into adj
                PredNode *curr = paths.pred[item.key];
                PredNode *curr_adj = paths.pred[adj->w];
                while (curr_adj != NULL) {
                    curr_adj = curr_adj->next;
                }

                printf("item.key is %d, ", item.key);
                printf("NEW PATH adj->w is %d\n", adj->w);
                while (curr != NULL) {
                printf("curr->v is %d\n", curr->v);
                    curr_adj = newPredNode(curr->v);
                    paths.pred[adj->w] = curr_adj;
                    curr_adj = curr_adj->next;
                    curr = curr->next;
                }

                
                curr_adj = newPredNode(item.key);
                curr_adj->next = NULL;
                
                paths.pred[adj->w] = curr_adj;
                //paths.pred[adj->w] = newPredNode(item.key);
                //paths.pred[adj->w]->next = NULL;
			    paths.dist[adj->w] = new_dist;
                
			    ItemPQ new;
           		new.key = adj->w; 
           		new.value = new_dist;
                printf("new dist pq add %d\n", new.key);
			    addPQ(pq, new);	
           	}
           	adj = adj->next;
        }
   	}

    // If node is unreachable change dist to 0
   	int i = 0;
   	while (i < paths.noNodes) {
   	    if (paths.dist[i] == INF) {
   	        paths.dist[i] = 0;
   	    }
   	    i++;
   	}
    //showShortestPaths(paths);
    return paths;
}

// creates a new PreNode
static PredNode * newPredNode(int vert) {
	PredNode * new = malloc(sizeof(PredNode));
	new->v = vert;
	new->next = NULL;
	return new;
}

/*
static void appendNode(PredNode *base, PredNode *new) {
     while (base->next != NULL){
         base = base->next;
     }
     base->next = new;
     base->next->next = NULL;
     return;

 }
*/

/*
// appends a PreNode to pred linked list
static PredNode appendNode(PredNode old, PredNode new, int item) {
	if (old[item]->next == NULL) {
		old[item]->next = new;
		old[item]->next->next = NULL;
		return old[item];
	}
	return appendNode(old[item]->next, new, item);
/
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
    for (int i =0; i < paths.noNodes; i++) {
        PredNode *curr = paths.pred[i];
        while (curr != NULL) {
            PredNode *temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(paths.pred);
    free(paths.dist);
}







