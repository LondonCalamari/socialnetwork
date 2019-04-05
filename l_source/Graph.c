#include <Graph.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct _GraphRep {
   int numNodes;
   AdjList *Nodelist;
} GraphRep;

Graph newGraph(int noNodes) {
    Graph g = malloc(sizeof(Graph));
    g->numNode = noNodes;
    g->Nodelist = malloc(sizeof(adjListNode) * numNodes);
    return g;
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
