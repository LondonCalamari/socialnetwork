// Graph ADT

#include "Graph.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

AdjList newNode(int v, int weight);

// Graph struct
struct GraphRep {
    int nV; // number of vertices
    int nE; // number of edges
    AdjList *nodeList; // adjacency list
};

// creates new graph
Graph newGraph(int noNodes) {
    assert(noNodes >= 0);
    Graph g = malloc(sizeof(Graph));
    if (g == NULL) { return NULL; }

    g->nV = noNodes;
    g->nE = 0;
    g->nodeList = malloc(sizeof(AdjList) * noNodes);
    // for each node it costs 0 to reach itself
    for (int i = 0; i < noNodes; i++) {
        g->nodeList[i] = newNode(i, 0);
    }

    /*  for testing we will fill the graph randomly */
    for (int i = 0; i < noNodes; i++) {
        int r = rand()%(noNodes*2);
        for (int j = 0; j < r; j++) {
            insertEdge(g, i, rand()%noNodes, rand()%50);
        }
    }

    return g;
}

// Creates a new adjListNode
AdjList newNode(int v, int weight) {
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
    /*
    // add the first vertex in the list to outward
    AdjList outward = newNode(g->nodeList[v]->next->w, g->nodeList[v]->next->weight);
    AdjList curr = g->nodeList[v]->next;

    // add every vertex in the curr list
    while (curr->next != NULL) {
        outward->next = newNode(curr->w, curr->weight);
        outward->next->next = NULL;
        curr = curr->next;
    }
    return outward;
    */
   return g->nodeList[v]->next;
}

// Retuns an AdjList of the vertices incoming to vertex V
AdjList inIncident(Graph g, Vertex v) {
    AdjList inward = NULL;
    //AdjList curr;
    int firstNodeFlag = 0;

    // Look through every nodeList in the graph for vertex V
    for (int i = 0; i < g->nV; i++) {
        printf("1\n");
        if (i == v) { printf("continue\n"); continue; }
        AdjList curr = g->nodeList[i];
        printf("after con\n");
        while (curr->next != NULL) {
            // if we find the node in the list we add it 
            if (curr->w == v) {
                printf("2\n");
                if (firstNodeFlag == 0) {
                    printf("3\n");
                    inward = newNode(curr->w, curr->weight);
                    inward->next = NULL;
                    firstNodeFlag = 1;
                } else {          
                    printf("4\n");    
                    inward->next = newNode(curr->w, curr->weight);
                    inward->next->next = NULL;
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


// Main for testing purposes 
int main(int argc, char *argv[]) {

    // Test with nV = 5 
    printf("Enter nV: ");
    int nV;
    scanf("%d", &nV);
    Graph g = newGraph(nV);
    
    // Test Show graph
    showGraph(g);

    // Insert Edge tests 
    insertEdge(g, 3, 2, 11);
    assert(adjacent(g, 3, 2) == true);
    insertEdge(g, 1, 2, 19);
    assert(adjacent(g, 1, 2) == true);
    insertEdge(g, 4, 1, 11);
    assert(adjacent(g, 4, 1) == true);
    insertEdge(g, 19, 1, 1);
    assert(adjacent(g, 19,1) == false);
  
    // Remove Edge tests
    removeEdge(g, 3, 2);
    assert(adjacent(g, 3, 2) == false);
    removeEdge(g, 4, 1);
    assert(adjacent(g, 4, 1) == false);

    // outIncident tests
    printf("--- outIncident test ---\n[1]: ");
    for (AdjList t1 = outIncident(g,1); t1 != NULL; t1 = t1->next) {
        printf ("<%d> ($%d) --> ", t1->w, t1->weight);
    }
    printf("NULL\n");
    printf("[2]: ");
    for (AdjList t3 = outIncident(g,2); t3 != NULL; t3 = t3->next) {
        printf ("<%d> ($%d) --> ", t3->w, t3->weight);
    }
    printf("NULL\n");

    // inIncident tests
    printf("--- inIncident test ---\n[0]: ");
    for (AdjList t2 = inIncident(g,0); t2 != NULL; t2 = t2->next) {
        printf ("<%d> ($%d) --> ", t2->w, t2->weight);
    }
    printf("NULL\n");

    printf(" --- All tests passed ---\n");

    freeGraph(g);
    return EXIT_SUCCESS;
}
