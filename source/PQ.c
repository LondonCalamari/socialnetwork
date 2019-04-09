// PQ ADT
#include "PQ.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>


// Heap structure
struct PQRep {
    ItemPQ *nodes;
    int nitems;
    int size;
};

// Creates new priority queue, that can store items of type ItemPQ.
PQ newPQ() {
    PQ pq = malloc(sizeof(PQ));
    if (pq == NULL) { return NULL; }
    pq->nitems = 0;
    pq->size = 0;
    pq->nodes = NULL;
    return pq;
}

// Adds item (ItemPQ) to the priority queue. If an item with 'key' exists, it's 'value' is updated.
void  addPQ(PQ pq, ItemPQ item) {
    // go through to see if item with key exists, update if it does
    // im so confused because this is the only way to do this in a heap but it
    // essentially makes our heap pointless as it makes the complexity worse
    for (int i = 1; i <= pq->nitems; i++) {
        if (pq->nodes[i].key == item.key) {
            pq->nodes[i].value = item.value;
            return;
        }
    }
    // Make sure our array has enough space
    if (pq->nitems + 1 >= pq->size) {
        pq->size = pq->size * 2;
        pq->nodes = realloc(pq->nodes, pq->size * sizeof(ItemPQ));
    }

    // Insert in order (smallest at the front of the q)
    // this is the just the basic implementation 
    for (int i = 0; i < pq->nitems; i++) {
        if (pq->nodes[i].value > item.value) {
            // shuffle all the items down the array
            for (int curr = pq->nitems - 1; curr >= i; curr--) {
                pq->nodes[curr+1] = pq->nodes[curr];
            }
            pq->nodes[i] = item;
            pq->nitems++;
            printf("adding node\n");
            return;
        }
    }

/*
    // Insert the item into last place
    pq->nodes[pq->nitems] = item;

    // Put it into the correct position
    int child = pq->nitems; // start from [1]
    int parent = child / 2;
    while (child > 1 && pq->nodes[parent].value > item.value) {
        pq->nodes[child] = pq->nodes[parent];
        child = parent;
        parent = parent / 2;
    }
    pq->nodes[child] = item;
    pq->nitems++;
*/
}

//Removes and returns the item (ItemPQ) with smallest 'value'. Returns null if this queue is empty.
ItemPQ  dequeuePQ(PQ pq) {
    /*
    ItemPQ minItem, lastItem;
    int child, curr;
    minItem = pq->nodes[1];
    lastItem = pq->nodes[pq->nitems];

    // replace nodes[1] with new minimum by comparing the value to its children
    for (curr = 1; curr*2 <= pq->nitems; curr = child) {
        child = curr * 2;
        if (child != pq->nitems && pq->nodes[child+1].value < pq->nodes[child].value) {
            child++;
        }
        if (lastItem.value > pq->nodes[child].value) {
            pq->nodes[curr] = pq->nodes[child];
        } else { break; }
    }
    pq->nodes[child] = lastItem;
    return minItem;
    */


 //  if (pq == NULL) { printf("wtf\n");ItemPQ *null = NULL; return null; }
 //  if (pq->nodes == NULL || pq->nitems == 0) { ItemPQ *null = NULL; return null; }
    
   // how tf are we meant to return NULL if the function has to return an ITEMPQ (ie not a pointer)

    int smallest_node = pq->nodes[0].value;
    for (int i = 0; i < pq->nitems; i++) {
        if (pq->nodes[i].value < pq->nodes[smallest_node].value) {
            smallest_node = i;
        }
    } 

    ItemPQ smallest = pq->nodes[smallest_node];
    // Shuffle everything up the array from the smallest node
    for (int i = smallest_node; i < pq->nitems; i++) {
        pq->nodes[i] = pq->nodes[i+1];
    }
    return smallest;
    
}

// Updates item with a given 'key' value, by updating that item's value to the given 'value'.
// If item with 'key' does not exist in the queue, no action is taken
void  updatePQ(PQ pq, ItemPQ item) {
    for (int i = 0; i < pq->nitems; i++) {
        if (pq->nodes[i].key == item.key) {
            pq->nodes[i].value = item.value;
            return;
        }
    } 
}

// checks if PQ is empty
int PQEmpty(PQ pq) {
    if (pq == NULL) { return 1; }
    if (pq->nitems == 0) { return 1; }
    return 0;
}

// displays PQ
void  showPQ(PQ pq) {
    printf("in\n");
    for (int i = 0; i <= pq->nitems; i++) {
        printf("wtf\n");
        printf("[%d](%d)->", pq->nodes[i].value, pq->nodes[i].key);
    }
    printf("[X]\n");
}

// free's PQ
void  freePQ(PQ pq) {
    /*
    for (int i = 0; i < pq->nitems; i++) {
        free(pq->nodes[i]);
    }
    */
    free(pq->nodes);
    free(pq);
}

/*
// Main for testing
int main (int argc, char *argv[]) {
    printf("Complete\n");
    return EXIT_SUCCESS;
}

*/
