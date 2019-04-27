/*Lance-Williams Algorithm for Agglomerative Clustering
  Written by 
  COMP2521 2019 T1
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "LanceWilliamsHAC.h"
#include "Graph.h"
#define numVertices numVerticies
#define MAX 999

/* 
 * Finds Dendrogram using Lance-Williams algorithm (as discussed in the specs) 
   for the given graph g and the specified method for agglomerative clustering.
   Method value 1 represents 'Single linkage', and 2 represents 'Complete linkage'.
   For this assignment, you only need to implement the above two methods. 

   The function returns 'Dendrogram' structure (binary tree) with the required information.
 * 
 */

static Dendrogram newDNODE(int v); // creates new Dnode

Dendrogram LanceWilliamsHAC(Graph g, int method) {
    // create 2D array to hold all distances
    double distances[MAX][MAX] = {0}; // = {1};
     
    // Array to store dendro pointers 
    Dendrogram *dendA = malloc(sizeof(Dendrogram) * numVerticies(g));
    
    // Keep track on distances size 
    int distSize = numVerticies(g);

    // initalise the whole array to unreachable
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            distances[i][j] = -1;
        }
    }

    // calculate distances between each pair of vertices
    for (int i = 0; i < distSize; i++) {
        AdjList adj = outIncident(g, i);
        while (adj != NULL) {
            distances[i][adj->w] = 1.0/(double)adj->weight;
            adj = adj->next;
        }
    }    

    // get the max dist if there are two links
    for (int i = 0; i < distSize; i++) {
        for (int j = 0; j < distSize; j++) {
            if (distances[i][j] == -1 && distances[j][i] != -1) {
                distances[i][j] = distances[j][i];
            } else if (distances[j][i] > 0 && distances[i][j] > distances[j][i]) {
                distances[i][j] = distances[j][i];
            } else {
                distances[j][i] = distances[i][j];
            }
        }
    }

    // create clusters for every vertex i
    for (int i = 0; i < distSize; i++) {
        Dendrogram node = newDNODE(i);
        dendA[i] = node;
    }

    // Until the whole matrix is -1 we continue
    for (int i = 0; i < distSize; i++) {
        // find location of the two closest clusters using dist array
        int row, col; 
        double min = MAX;
        for (int x = 0; x < distSize; x++) {
            for (int y = 0; y < distSize; y++) {
                if (x > y && distances[x][y] > 0) { 
                    if (distances[x][y] < min)  { 
                        min = distances[x][y]; 
                        row = x;
                        col = y;
                    }
                }
            }
        } 
        if (min == MAX) break; // we are done if all is MAX 

        // create new col in dendA for cluster
        // && corresponding new row and col for distances[][]
        distSize++;
        dendA = realloc(dendA, distSize * sizeof(Dendrogram)); // make one more slot

        // Update dendrogram by merging the two trees
        Dendrogram new = newDNODE(-1);
        new->left = dendA[row]; new->right = dendA[col];
        dendA[distSize-1] = new; 

        // Update dist by find the smallest number of the two in each col
        for (int j = 0; j < distSize; j++) {
            if (distances[row][j] == -1 && distances[col][j] == -1) {
                distances[distSize-1][j] = -1;
            } else if (distances[row][j] == -1 && distances[col][j] != -1) {
                distances[distSize-1][j] = distances[col][j];
            } else if (distances[col][j] == -1 && distances[row][j] != -1) {
                distances[distSize-1][j] = distances[row][j];
            } else if (distances[row][j] < distances[col][j]) {
                distances[distSize-1][j] = distances[row][j];
            } else {
                distances[distSize-1][j] = distances[col][j];
            }
           
        }

        distances[distSize-1][row] = -1.0;
        distances[distSize-1][col] = -1.0;

        // make sure you cant reach nodes in the new cluster
        for (int cols = 0; cols < distSize; cols++) {
            // ROWS
            distances[row][cols] = -1;
            distances[col][cols] = -1;
            // COLS
            distances[cols][row] = -1;
            distances[cols][col] = -1;
        }

        // Copy the bottom triangle to the top triangle of the matrix
        for (int q = 0; q < distSize; q++) {
            for (int w = 0; w < distSize; w++) {
                if (q > w) {
                    distances[w][q] = distances[q][w];
                }
            }
        }
    }
    return dendA[distSize-1];
}

// creates new Dnode
Dendrogram newDNODE(int v) {
    Dendrogram node = malloc(sizeof(Dendrogram));
    node->vertex = v;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// recursively free the dendrogram
void freeDendrogram(Dendrogram d) {
    if (d == NULL) { return; }
    freeDendrogram(d->left);
    freeDendrogram(d->right);
    free(d);
	return;
}
/*
    // -------- PRINT FUNCTION FOR TESTING --------//
    for (int i = 0; i < distSize;i++) {

        for (int j = 0; j < distSize;j++) {
            if (i == j) { printf("[XXXX] "); continue; }
            printf("[%0.3f] ", distances[i][j]);
        }
        printf("\n");
    
    }
    // ------------------------------------------- // 
*/ 
