// Graph ADT interface for Ass2 (COMP2521)
#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>

#define INF 9999

// Contains number of out going edges from every vertice 
NodeValues outDegreeCentrality(Graph g){
	NodeValues outDegree;
    outDegree.noNodes = numVerticies(g);
    outDegree.values = malloc(sizeof(double) * outDegree.noNodes);

    // for every values[i] we input the number of adjacent vertices
    for (int i = 0; i < outDegree.noNodes; i++) {
        // Look through AdjList outIncident for every vertex
        int outEdges = 0;
        AdjList curr = outIncident(g, i);
        // count the number of adjacent vertices
        while (curr != NULL) {
            outEdges++;
            curr = curr->next;
        }
        outDegree.values[i] = outEdges;
    }
	return outDegree;
}


// Contains number of in coming edges from every vertice
NodeValues inDegreeCentrality(Graph g){
	NodeValues inDegree;
    inDegree.noNodes = numVerticies(g);
    inDegree.values = malloc(sizeof(double) * numVerticies(g));

    // for every values[i] we input the number of adjacent vertices
    for (int i = 0; i < inDegree.noNodes; i++) {
        // Look through AdjList outIncident for every vertex
        int inEdges = 0;
        AdjList curr = inIncident(g, i);
        // count the number of adjacent vertices
        while (curr != NULL) {
            inEdges++;
            curr = curr->next;
        }
        inDegree.values[i] = inEdges;
    }
	return inDegree; 
}

// Contains number of out going and in coming edges from every vertice
NodeValues degreeCentrality(Graph g) {
	NodeValues degree;
    degree.noNodes = numVerticies(g);
    degree.values = malloc(sizeof(double) * degree.noNodes);

    NodeValues out = outDegreeCentrality(g);
    NodeValues in = inDegreeCentrality(g);
    
    // total the number of in and out for every vertex
    for (int i = 0; i < degree.noNodes; i++) {
        degree.values[i] = in.values[i] + out.values[i];
    }

	return degree;
}

// Contains the 'closeness' of each node to every other node
NodeValues closenessCentrality(Graph g){
	NodeValues close;
    close.noNodes = numVerticies(g);
    close.values = malloc(sizeof(double) * close.noNodes);

    for (int i = 0; i < close.noNodes; i++) {
        ShortestPaths paths = dijkstra(g, i);
        //showShortestPaths(paths);
        // find the number of reachable nodes
        double reachable = 0;
        for (int k = 0; k < paths.noNodes; k++) {
            if (paths.dist[k] != 0 || paths.src == k) { reachable++; }
        }

        // sum all the shortest distances for reachable nodes
        double sum = 0;
        for (int j = 0; j < paths.noNodes; j++) {
            if (paths.dist[j] == 0) { continue; }
            sum += paths.dist[j];
        }
       
        // make sure we are not dividing by 0
        if (close.noNodes-1 == 0 || sum == 0) {
            close.values[i] = 0;
        } else {
            // apply Wasserman and Faust formula
            double closeness = ((reachable-1)/(close.noNodes-1))*((reachable-1)/(sum));
            close.values[i] = closeness;
        }
    }
	return close;
}

// The node that is on the most shortest routes is the most central
NodeValues betweennessCentrality(Graph g){
    int i = 0;
    int split = 0;
    NodeValues close;
    close.noNodes = numVerticies(g);
    close.values = malloc(sizeof(double) * close.noNodes);
    for (i = 0; i < numVerticies(g); i++) {
        ShortestPaths paths = dijkstra(g, i);
        for (int j = 0; j < paths.noNodes; j++) {
            split = 0;
            PredNode * count = paths.pred[j];
            // if multiple pred worth half each
            while (count != NULL) { 
                split++;
                count = count->next;
            }
            while (paths.pred[j] != NULL) {
                if (paths.pred[j]->v != i) {
                    close.values[paths.pred[j]->v] = close.values[paths.pred[j]->v] + 1.0/split;
                }
                paths.pred[j] = paths.pred[j]->next;
            }
        }
    }
	return close;
}

//
NodeValues betweennessCentralityNormalised(Graph g){
	//NodeValues close = betweennessCentrality(g);
	NodeValues throwAway = {0};
	return throwAway;
}

//
void showNodeValues(NodeValues values){
    //printf("values.noNodes is %d\n", values.noNodes);
    for (int i = 0; i < values.noNodes; i++) {
        printf("%d: %f\n", i, values.values[i]);
    }
}

//
void freeNodeValues(NodeValues values){
    free(values.values);
}










