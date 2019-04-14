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

        // find the number of reachable nodes
        double reachable = 0;
        for (int k = 0; k < close.noNodes; i++) {
            if (paths.dist[i] != INF) { reachable++; }
        }

        // sum all the shortest distances for reachable nodes
        double sum = 0;
        for (int j = 0; j < paths.noNodes; j++) {
            if (paths.dist[j] == INF) { continue; }
            sum += paths.dist[j];
        }
       
        // apply Wasserman and Faust formula
        double closeness = ((reachable-1)/(close.noNodes-1))*((reachable-1)/(sum));
        
        close.values[i] = closeness;
    }

	return close;
}

//
NodeValues betweennessCentrality(Graph g){
	NodeValues throwAway = {0};
	return throwAway;
}

//
NodeValues betweennessCentralityNormalised(Graph g){
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










