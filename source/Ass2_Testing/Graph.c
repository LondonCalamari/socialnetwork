// Graph ADT

#include "Graph.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

AdjList createNode(int v, int weight);

// Graph struct
typedef struct GraphRep {
    int nV; // number of vertices
    int nE; // number of edges
    AdjList *nodeList; // adjacency list
}GraphRep;

// creates new graph
Graph newGraph(int noNodes) {
    assert(noNodes >= 0);
    Graph g = malloc(sizeof(GraphRep));
    if (g == NULL) { return NULL; }

    g->nV = noNodes;
    g->nE = 0;
    g->nodeList = malloc(sizeof(AdjList) * noNodes);
    // for each node it costs 0 to reach itself
    for (int i = 0; i < noNodes; i++) {
        g->nodeList[i] = createNode(i, 0);
    }

    return g;
}

// Creates a new adjListNode
AdjList createNode(int v, int weight) {
    AdjList node = malloc(sizeof(AdjList));
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
            g->nodeList[src]->next = createNode(dest, weight);
            g->nodeList[src]->next->next = NULL;

        } else {
            // adding the node in order of cost
            AdjList prev; 
            AdjList curr = g->nodeList[src]; 
            while (curr != NULL && curr->weight <= weight) {
                prev = curr;
                curr = curr->next;     
            }
            AdjList new = createNode(dest, weight);
            new->next = curr;
            prev->next = new;
        }
        g->nE++;
    }
}

// removes edge between two vertices
void  removeEdge(Graph g, Vertex src, Vertex dest) {
    // first check if the edge exists or not
    if (src > g->nV || dest > g->nV || dest < 0 || src < 0) {
        return;
    }

    // if it does exist, remove it
    AdjList prev = g->nodeList[src];
    AdjList curr = prev->next;
    while (curr != NULL) {
        if (curr->w == dest) {
            // if it is the last node we just remove it
            if (curr->next == NULL) {
                prev->next = NULL;
                free(curr);
                break;
            } else {
                prev->next = curr->next;
                free(curr);
                break;
            }
        }
        prev = curr;
        curr = curr->next;
    }
}

// checks if two vertices are connected
bool  adjacent(Graph g, Vertex src, Vertex dest) {
    if (src > g->nV || dest > g->nV || dest < 0 || src < 0) {
        return false;
    }
    AdjList curr = g->nodeList[src]; 
    while (curr != NULL) {
        if (curr->w == dest) {
            return true;
        }   
        curr = curr->next;
    }
    return false;
}

// returns number of verticies in a graph
int numVerticies(Graph g) { 
    return g->nV;
}

// Returns an AdjList of the vertices outgoing from vertex V
AdjList outIncident(Graph g, Vertex v) {
   return g->nodeList[v]->next;
}

// Retuns an AdjList of the vertices incoming to vertex V
AdjList inIncident(Graph g, Vertex v) {
    AdjList inward = malloc(sizeof(AdjList)); 
    inward = NULL;
    int firstNodeFlag = 0;
    // Look through every nodeList in the graph for vertex V
    for (int i = 0; i < g->nV; i++) {
        if (i == v) { continue; }
        AdjList curr = g->nodeList[i];
        while (curr != NULL) {
            // if we find the node in the list we add it 
            if (curr->w == v) {
                if (firstNodeFlag == 0) {
                    firstNodeFlag = 1;
                    inward = createNode(i, curr->weight);
                    inward->next = NULL;
                } else {       
                    AdjList curr = inward;
                    while (curr->next != NULL){
                        curr = curr->next;
                    }   
                    curr->next = createNode(i, curr->weight);
                    curr->next->next = NULL;
                }   
            }
            curr = curr->next;
        }
    }
    return inward;
}

// Prints the graph as the adjacency list
void  showGraph(Graph g) {
    printf("nV: %d nE: %d\n", g->nV, g->nE);
    printf("The adjacency list is: \n");
    for (int i = 0; i < g->nV; i++) {
        AdjList curr = g->nodeList[i];
        printf("[%d]: ", curr->w);
        while (curr != NULL) {
            printf ("<%d> ($%d) --> ", curr->w, curr->weight);
            curr = curr->next;
        }
        printf ("NULL\n");
    }
}

// free's the graph
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

