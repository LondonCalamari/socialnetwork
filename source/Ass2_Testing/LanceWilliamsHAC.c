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
// static void smallestDist(double *row, double *col, double *dist);
static Dendrogram newDNODE(int v);

Dendrogram LanceWilliamsHAC(Graph g, int method) {
    // create 2D array to hold all distances
    double distances[numVerticies(g)][numVerticies(g)]; // = {1};
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
    
    // Array to store dendro pointers 
    int dendASize = numVerticies(g);
    Dendrogram *dendA = malloc(sizeof(Dendrogram) * dendASize);

    // Array to know which cols to skip in dendA
    int skip[MAX] = {0};
    // create clusters for every vertex i
    for (int i = 0; i < numVerticies(g); i++) {
        Dendrogram node = newDNODE(i);
        dendA[i] = node;
    }

    // For K=1 to N-1 ?? 
    for (int i = 0; i < numVerticies(g); i++) {
        // find two closest clusters using dist array
        int row, col; 
        double min = MAX;
        for (int x; x < numVerticies(g); x++) {
            for (int y; y < numVerticies(g); y++) {
                // only need to look half of matrix
                if (x > y) {
                    if (distances[x][y] < min) { 
                        min = distances[x][y]; 
                        row = x;
                        col = y;
                    }
                }
            }
        }

        // Create new col in dendA for cluster
        dendASize++;
        skip[row] = 1; skip[col] = 1;
        dendA = realloc(dendA, dendASize * sizeof(Dendrogram));
        Dendrogram new = newDNODE(MAX);
        new->left = dendA[row]; new->right = dendA[col];
        dendA[dendASize-1] = new;

        // Update distance using LW Single-link Method
        double new_dist = distances[0][0];

        // Update dendrogram

    }
    


    return dendA[0];
}

Dendrogram newDNODE(int v) {
    Dendrogram node = malloc(sizeof(Dendrogram));
    node->vertex = v;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/*
// Find the smallest value in distance[][] 
static void smallestDist(double *row, double *col, double *dist) {
    double min = 9999;
    for (int x; x < numVerticies(g); i++) {
        for (int y; y < numVerticies(g); y++) {
            // only need to look half of matrix
            if (x > y) {
                if (dist[x][y] < min) { 
                    min = dist[x][y]; 
                    row = x;
                    col = y;
                }
            }
        }
    }
    
}
*/

// recursively free the dendrogram
void freeDendrogram(Dendrogram d) {
    if (d == NULL) { return; }
    freeDendrogram(d->left);
    freeDendrogram(d->right);
    free(d);
	return;
}



