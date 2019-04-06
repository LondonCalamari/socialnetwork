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
    pq->len = 0;
    pq->nodes = NULL;
    return pq;
}

// Adds item (ItemPQ) to the priority queue. If an item with 'key' exists, it's 'value' is updated.
void  addPQ(PQ, ItemPQ) {
    for (int i = 0; i < PQ->len; i++) {
        if (PQ->nodes[i]->key = ItemPQ->key) {
            PQ->nodes[i]->value = ItemPQ->value;
            return;
        }
    } 
    // just adds to the end of the queue not sure if this is efficent or not
    PQ->nodes[i]->next = ItemPQ;
    PQ->len++;
}

//Removes and returns the item (ItemPQ) with smallest 'value'. Returns null if this queue is empty.
ItemPQ  dequeuePQ(PQ) {
    if (PQ == NULL) { return NULL; }

}

// Updates item with a given 'key' value, by updating that item's value to the given 'value'.
// If item with 'key' does not exist in the queue, no action is taken
void  updatePQ(PQ, ItemPQ) {
    for (int i = 0; i < PQ->len; i++) {
        if (PQ->nodes[i]->key = ItemPQ->key) {
            PQ->nodes[i]->value = ItemPQ->value;
            return;
        }
    } 
}

// checks if PQ is empty
int PQEmpty(PQ) {
    if (PQ == NULL) { return 1; }
    if (PQ->len == 0) { return 1; }
    if (PQ->nodes == NULL) { return 1; }
    return 0;
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
