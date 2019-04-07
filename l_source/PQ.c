// PQ ADT
#include "PQ.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

struct PQRep {
    ItemPQ *nodes;
    int size;
};

// Creates new priority queue, that can store items of type ItemPQ.
PQ newPQ() {
    PQ pq = malloc(sizeof(PQ));
    if (pq == NULL) { return NULL; }
    pq->len = 0;
    pq->nodes = NULL;
    return pq;
}

// Adds item (ItemPQ) to the priority queue. If an item with 'key' exists, it's 'value' is updated.
void  addPQ(PQ pq, ItemPQ item) {
    // if same key exists, update the value
    for (int i = 0; i < pq->len; i++) {
        if (pq->nodes[i].key = item.key) {
            pq->nodes[i].value = item.value;
            return;
        }
        // find where in the pq we want to add
        if (pq->nodes[i].key > item.key) {
            pq->len++;
            pq->nodes = realloc(pq->nodes, pq->len * sizeof(ItemPQ));
            
            for (int j = i; j < len; j++) {
                pq->nodes[len-1] = pq->nodes[len-2];
            }
            pq->nodes[i] = item;
        }
    } 
    pq->nodes[len-1]->next = item;
    pq->len++;
}

//Removes and returns the item (ItemPQ) with smallest 'value'. Returns null if this queue is empty.
ItemPQ  dequeuePQ(PQ pq) {
    if (pq == NULL) { return NULL; }
    if (pq->nodes == NULL || pq->len == 0) { return NULL; }
    int smallest_node = pq->nodes[0].value;
    for (int i = 0; i < pq->len; i++) {
        if (pq->nodes[i].value < pq->nodes[smallest_node].value) {
            smallest_node = i;
        }
    } 
    /// NEEDS TO NOW REMOVE THE ITEM
    return pq->nodes[smallest_node];
}

// Updates item with a given 'key' value, by updating that item's value to the given 'value'.
// If item with 'key' does not exist in the queue, no action is taken
void  updatePQ(PQ pq, ItemPQ item) {
    for (int i = 0; i < pq->len; i++) {
        if (pq->nodes[i].key = item.key) {
            pq->nodes[i].value =item.value;
            return;
        }
    } 
}

// checks if PQ is empty
int PQEmpty(PQ pq) {
    if (pq == NULL) { return 1; }
    if (pq->len == 0) { return 1; }
    if (pq->nodes == NULL) { return 1; }
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
