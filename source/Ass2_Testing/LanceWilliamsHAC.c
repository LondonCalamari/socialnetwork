/*Lance-Williams Algorithm for Agglomerative Clustering
  Written by 
  COMP2521 2019 T1
*/
#include <stdlib.h>
#include <stdio.h>
#include "LanceWilliamsHAC.h"
#include "Graph.h"
#define numVertices numVerticies
#define MAX 9999

/* 
 * Finds Dendrogram using Lance-Williams algorithm (as discussed in the specs) 
   for the given graph g and the specified method for agglomerative clustering.
   Method value 1 represents 'Single linkage', and 2 represents 'Complete linkage'.
   For this assignment, you only need to implement the above two methods. 

   The function returns 'Dendrogram' structure (binary tree) with the required information.
 * 
 */
Dendrogram LanceWilliamsHAC(Graph g, int method) {
    double distances[10][10/*numVerticies(g)*/] = {0};
    for (int i = 0; i < numVerticies(g); i++) {
        for (int j = 0; j < numVerticies(g); j++) {
            distances[i][j] = MAX;
        }
    }
    // Calculate distances between each pair of vertices
    for (int i = 0; i < numVerticies(g); i++) {
        AdjList adj = outIncident(g, i);
        int col = 0;
        while (adj->next != NULL) {
            distances[i][col] = 1/(double)adj->weight;
            col++;
        }
    }    
    // get the max dist if there are two links
    for (int i = 0; i < numVerticies(g); i++) {
        for (int j = 0; j < numVerticies(g); i++) {
            if (distances[i][j] <= distances[j][i]) {
                distances[i][j] = distances[j][i];
            } else {
                distances[j][i] = distances[i][j];
            }
        }
    }
    // create clusters for every vertex i ????
    for (int i = 0; i < numVerticies(g); i++) {
        DNode *node = malloc(sizeof(DNode));
        node->vertex = i;
        node->left = node->right = NULL;
    }

    


    return NULL;
}

// recursively free the dendrogram
void freeDendrogram(Dendrogram d) {
    if (d == NULL) { return; }
    freeDendrogram(d->left);
    freeDendrogram(d->right);
    free(d);
	return;
}



