// Graph ADT

#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct _GraphRep {
   int nV; // number of vertices
   int nE; // number of edges
   AdjList *Nodelist;
} GraphRep;

// Graph struct
Graph newGraph(int noNodes) {
    assert(noNodes >= 0);
    Graph g = malloc(sizeof(Graph));
    g->nV = noNodes;
    g->nE = 0;
    g->Nodelist = malloc(sizeof(adjListNode) * nV);
    
    // for each node it costs 0 to reach itself
    for (int i = 0; i < nV; i++) {
        g->Nodelist[i] = newNode(i, 0);
    }
    return g;
}

// Creates a new adjListNode
adjListNode newNode(int v, int weight) {
    adjListNode node = malloc(sizeof(struct adjListNode));
    node->w = v;
    node->weight = weight;
    node->next = NULL;
    return node;
}  

void  insertEdge(Graph g, Vertex src, Vertex dest, int weight) {
    
}
void  removeEdge(Graph g, Vertex src, Vertex dest) {
    
}
bool  adjacent(Graph g, Vertex src, Vertex dest) {
    
    return ;
}
int  numVerticies(Graph g) { 

}

AdjList outIncident(Graph g, Vertex v) { 

}

AdjList inIncident(Graph g, Vertex v) {

}

void  showGraph(Graph g) {

}

void  freeGraph(Graph g) {

}
