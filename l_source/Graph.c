// Graph ADT

#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

AdjList newNode(int v, int weight);

typedef struct _GraphRep {
   int nV; // number of vertices
   int nE; // number of edges
   AdjList nodeList;
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
AdjList newNode(int v, int weight) {
    AdjList node = malloc(sizeof(struct _adjListNode));
    node->w = v;
    node->weight = weight;
    node->next = NULL;
    return node;
}  

// insert edge in increasing order of cost 
void  insertEdge(Graph g, Vertex src, Vertex dest, int weight) {
    // first check if the edge isn't already in g
    if (g->nV < src || src < 0 || g->nV < dest || dest < 0) { return; }
    if (adjacent(g, src, dest)) { return; }
    else {
        // adding the node to the end of the list
        if (g->nodeList[src]->next == NULL) {
            g->nodeList[src]->next = newNode(dest, weight);
        } else {
            // adding the node in order of cost
            AdjList prev = g->nodeList[src];
            AdjList curr = prev->next;
            while (curr != NULL && curr->weight < weight) {
                curr = curr->next;     
            }
            AdjList new = newNode(dest, weight);
            prev->next = new;
            new->next = curr;
        }
        g->nE++;
    }
}

void  removeEdge(Graph g, Vertex src, Vertex dest) {
    if (src > nV || dest > nV || dest < 0 || src < 0) {
        return;
    }
    AdjList prev = g->Nodelist[src - 1];
    AdjList curr = prev->next;
    while (curr != NULL) {
        if (curr->w == dest) {
            prev->next = curr->next;
            free(curr);
        }
        prev = curr;
        curr = curr->next;
    }
}

bool  adjacent(Graph g, Vertex src, Vertex dest) {
    if (src > g->nV || dest > g->nV || dest < 0 || src < 0) {
        return false;
    }
    AdjList curr = g->Nodelist[src - 1]; // not sure if -1 needed
    while (curr != NULL) {
        if ( curr->w == dest) {
            return true;
        }   
        curr = curr->next;
    }
    return false;
}

// is this it?
int numVerticies(Graph g) { 
    return g->nV;
}

AdjList outIncident(Graph g, Vertex v) { 

}

AdjList inIncident(Graph g, Vertex v) {

}

// Prints the graph as the adjacency list
void  showGraph(Graph g) {
    printf("nV: %d nE: %d\n", g->nV, g->nE);
    printf("The adjacency list is: \n");
    for (int i = 0; i < g->nV; i++) {
        AdjList curr = g->nodeList[i];
        printf("[%d] : ", curr->w);
        while (curr != NULL) {
            printf ("<%d> ($%d) --> ", curr->w, curr->weight);
            curr = curr->next;
        }
        printf ("NULL\n");
    }
}

void  freeGraph(Graph g) {
    // free all the nodes in the nodeList
    for (int i = 0; i < g->nV; i++) {
        AdjList curr = g->nodeList[i];
        while (curr != NULL) {
            AdjList temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(g->nodeList);
    free(g);
}
