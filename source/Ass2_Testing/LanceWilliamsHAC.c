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
//static Dendrogram newDNODE(int v);

Dendrogram LanceWilliamsHAC(Graph g, int method) {
printf("INJN!\n");
    // create 2D array to hold all distances
    double distances[MAX][MAX]; // = {1};
     
    // Array to store dendro pointers 
    //Dendrogram *dendA = malloc(sizeof(Dendrogram) * numVerticies(g));
    
    // holds info on nodes in each cluster
    //int dendAKey[MAX][MAX] = {0};

    // holds information on which index each cluster is at
    int clusterKey[MAX][MAX] = {0};
    int distSize = numVerticies(g);

    // initalise the whole array to MAX
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            distances[i][j] = MAX;
            clusterKey[i][j] = -1;
        //    dendAKey[i][j] = -1;
        }
        clusterKey[i][0] = i;
      //  dendAKey[i][0] = -1;
    }

    // calculate distances between each pair of vertices
    for (int i = 0; i < distSize; i++) {
        AdjList adj = outIncident(g, i);
        int col = 0;
        while (adj->next != NULL) {
            distances[i][col] = 1/(double)adj->weight;
            col++;
        }
    }    
    // get the max dist if there are two links
    for (int i = 0; i < distSize; i++) {
        for (int j = 0; j < distSize; j++) {
            if (distances[i][j] <= distances[j][i]) {
                distances[i][j] = distances[j][i];
            } else {
                distances[j][i] = distances[i][j];
            }
        }
    }
    for (int i = 0; i < distSize+5;i++) {
        for (int j = 0; j < distSize+5;j++) {
            printf("[%f] ", distances[i][j]);
        }
        printf("\n");
    
    }
       // create clusters for every vertex i
    for (int i = 0; i < numVerticies(g); i++) {
        //Dendrogram node = newDNODE(i);
     //   dendA[i] = node;
        //dendAKey[i][0] = i;
    }

    // For K=1 to N-1 ?? 
    for (int i = 0; i < numVerticies(g); i++) {
        // find two closest clusters using dist array
        int row, col; 
        double min = MAX;
        for (int x = 0; x < distSize; x++) {
            for (int y = 0; y < distSize; y++) {
                if (x > y) { // only need to look at 'half' of matrix
                    if (distances[x][y] < min) { 
                        min = distances[x][y]; 
                        row = x;
                        col = y;
                    }
                }
            }
        } 
        if (min == MAX) break; // we are done if all is MAX // TODO

        // Create new col in dendA for cluster
        distSize++;
//        dendA = realloc(dendA, distSize * sizeof(Dendrogram)); // make one more slot
        //Dendrogram new = newDNODE(MAX);
 //       new->left = dendA[row]; new->right = dendA[col];
        //dendA[distSize-1] = new; 

        // copy the 'row cluster key'
        int newCluster[MAX] = {0};
        int count = 0;
        for (int count = 0; count < MAX; count++) {
            if (clusterKey[row][count] == -1) break;
            newCluster[i] = clusterKey[row][i];
        }

        // add the 'col cluster key' to row to make new key
        while (clusterKey[col][count] != -1) {
            newCluster[count] = clusterKey[col][count];
            count++;
        }
        newCluster[count+1] = -1;

        // Make new cluster key 
        count = 0;
        while (newCluster[count] != -1) {
            clusterKey[distSize-1][count] = newCluster[count];
         //   dendAKey[distSize-1][count] = newCluster[count];
            count++;
        }

        // Change new cluster nodes to MAX
        distances[row][col] = MAX;

        // Update distance using LW Single-link Method
        for (int j = 0; j < distSize; j++) {
            for (int k = 0; k < distSize; k++) {
                if (j > k) {
                    // TODO
                    if (j == row && k == col) {
                        double row_dist = distances[row][j];
                        double col_dist = distances[col][j];
                        double abs_dist = fabs(row_dist - col_dist);
                        double new_dist = 0.5 * (row_dist + col_dist - abs_dist); 

                        distances[j][k] = new_dist; // TODO
                        // TODO for every new row/col of the new cluster
                        // we need to calculate the distnaces for those
                        clusterKey[distSize-1][distSize-1] = new_dist;
                    }
                
                }
            }


        }

        // Update dendrogram
    }
    
    return NULL;
}
/*

Dendrogram newDNODE(int v) {
    Dendrogram node = malloc(sizeof(Dendrogram));
    node->vertex = v;
    node->left = NULL;
    node->right = NULL;
    return node;
}
*/

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



