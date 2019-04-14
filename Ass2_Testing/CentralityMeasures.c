// Graph ADT interface for Ass2 (COMP2521)
#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>

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

NodeValues closenessCentrality(Graph g){
	NodeValues throwAway = {0};
	return throwAway;
}

NodeValues betweennessCentrality(Graph g){
	NodeValues throwAway = {0};
	return throwAway;
}

NodeValues betweennessCentralityNormalised(Graph g){
	NodeValues throwAway = {0};
	return throwAway;
}

void showNodeValues(NodeValues values){
    //printf("values.noNodes is %d\n", values.noNodes);
    for (int i = 0; i < values.noNodes; i++) {
        printf("%d: %f\n", i, values.values[i]);
    }
}

void freeNodeValues(NodeValues values){
    free(values.values);
}
