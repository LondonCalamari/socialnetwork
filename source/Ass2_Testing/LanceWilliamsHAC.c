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

static Dendrogram newDNODE(int v);

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
    // we only need to use one half of the matrix
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

    // For K=1 to N-1 ?? TODO or we will do until all unreachable 
    for (int i = 0; i < numVerticies(g)+20; i++) {

    // -------- PRINT FUNCTION FOR TESTING --------//
    for (int i = 0; i < distSize;i++) {

        for (int j = 0; j < distSize;j++) {
            if (i == j) { printf("[X] "); continue; }
            printf("[%0.3f] ", distances[i][j]);
        }
        printf("\n");
    
    }
    // ------------------------------------------- // 
        // find location of the two closest clusters using dist array
        int row, col; 
        double min = MAX;
        for (int x = 0; x < distSize; x++) {
            for (int y = 0; y < distSize; y++) {
                if (x > y) { // only need to look at 'half' of matrix
                    if (distances[x][y] < min && distances[x][y] > 0)  { 
                        min = distances[x][y]; 
                        row = x;
                        col = y;
                    }
                }
            }
        } 
        if (min == MAX) break; // we are done if all is MAX // TODO
        printf("Min is at [%d][%d] =  %0.3f\n\n", row, col, min);

        // create new col in dendA for cluster
        // && corresponding new row and col for distances[][]
        distSize++;
        dendA = realloc(dendA, distSize * sizeof(Dendrogram)); // make one more slot

        // Updte dendrogram by merging the two trees
        Dendrogram new = newDNODE(-1);
        new->left = dendA[row]; new->right = dendA[col];
        dendA[distSize-1] = new; 

        // Change new cluster nodes to unreachable
        distances[row][col] = -1;
        distances[col][row] = -1; // we dont look here but just incase lmao

        // Update dist by find the smallest number in each column
        for (int j = 0; j < distSize; j++) {
            double new_dist = MAX;
            for (int k = 0; k < distSize; k++) {
                if (distances[k][j] < new_dist && distances[k][j] > 0) {
                    new_dist = distances[k][j];
                }
            }
            distances[distSize-1][j] = new_dist;
        }
        distances[distSize-1][row] = -1;
        distances[distSize-1][col] = -1;
        /*
        // Update distance for new cluster ROW
        for (int j = 0; j < distSize; j++) {
            double row_dist = distances[row][j];
            double col_dist = distances[col][j];
            double abs_dist = fabs(row_dist - col_dist);
            double new_dist = 0.5 * (row_dist + col_dist - abs_dist); 

            if (row_dist == -1 && col_dist == -1) {
                distances[distSize-1][j]= -1;
            } else if (row_dist == -1 && col_dist != -1) {
                distances[distSize-1][j] = col_dist;
            } else if (col_dist == -1 && row_dist != -1) {
                distances[distSize-1][j] = row_dist;
            } else {
                distances[distSize-1][j] = new_dist;
            }

        }

        // Update distance for new cluster COL
        for (int j = 0; j < distSize; j++) {
            double row_dist = distances[row][j];
            double col_dist = distances[col][j];
            double abs_dist = fabs(row_dist - col_dist);
            double new_dist = 0.5 * (row_dist + col_dist - abs_dist); 
            
            if (row_dist == -1 && col_dist == -1) {
                distances[j][distSize-1] = -1;
            } else if (row_dist == -1 && col_dist != -1) {
                distances[j][distSize-1] = col_dist;
            } else if (col_dist == -1 && row_dist != -1) {
                distances[j][distSize-1] = row_dist;
            } else {
                distances[j][distSize-1] = new_dist;
            }
        }
        */
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


