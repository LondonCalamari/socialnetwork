// PQ ADT
#include "PQ.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

typedef struct _PQRep {
    ItemPQ *nodes;
    int len;
} PQRep;

// Creates new priority queue, that can store items of type ItemPQ.
PQ newPQ() {
    PQ pq = malloc(sizeof(PQRep));
    if (pq == NULL) { return NULL; }
    return pq;
}

// Adds item (ItemPQ) to the priority queue. If an item with 'key' exists, it's 'value' is updated.
void  addPQ(PQ, ItemPQ) {
    for (int i = 0; i < PQ->len; i++) {
        if (PQ->nodes[i]->key = Item)

    } 

}

//Removes and returns the item (ItemPQ) with smallest 'value'. Returns null if this queue is empty.
ItemPQ  dequeuePQ(PQ) {


}

// Updates item with a given 'key' value, by updating that item's value to the given 'value'.
// If item with 'key' does not exist in the queue, no action is taken
void  updatePQ(PQ, ItemPQ) {


}

// checks if PQ is empty
int PQEmpty(PQ) {

    return 1;
}

// displays PQ
void  showPQ(PQ) {


}

// free's PQ
void  freePQ(PQ) {


}


// Main for testing
int main (int argc, char *argv[]) {
    printf("Complete\n");
    return EXIT_SUCCESS;
}