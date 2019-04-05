#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char *argv[]) {
    printf("Enter nV: ");
    int nV;
    scanf("%d", &nV);
    Graph g = newGraph(nV);
    
    // Test Show graph
    showGraph(g);

    freeGraph(g);
    return EXIT_SUCCESS;
}

/*
Graph newGraph(int noNodes);
void  insertEdge(Graph g, Vertex src, Vertex dest, int weight);
void  removeEdge(Graph g, Vertex src, Vertex dest);
bool  adjacent(Graph g, Vertex src, Vertex dest);
int  numVerticies(Graph g);
AdjList outIncident(Graph g, Vertex v);
AdjList inIncident(Graph g, Vertex v);
void  showGraph(Graph g);
void  freeGraph(Graph g);
*/
