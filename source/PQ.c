// PQ ADT
#include "PQ.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>


// Heap structure
typedef struct PQRep {
    ItemPQ *nodes;
    int nitems;
    int size;
}PQRep;

// Creates new priority queue, that can store items of type ItemPQ.
PQ newPQ() {
    PQ pq = malloc(sizeof(PQRep));
    if (pq == NULL) { return NULL; }
    pq->nitems = 0;
    pq->size = 0;
    pq->nodes = malloc(sizeof(ItemPQ));
    return pq;
}

// Adds item (ItemPQ) to the priority queue. 
// If an item with 'key' exists, it's 'value' is updated.
void  addPQ(PQ pq, ItemPQ item) {
    // go through to see if item with key exists, update if it does
     
    // Make sure our array has enough space
    if (pq->nitems + 1 >= pq->size) {
        pq->size = (pq->size + 1) * 2;
        pq->nodes = realloc(pq->nodes, pq->size * sizeof(ItemPQ));
    }
 
    // check if key exists
    for (int i = 1; i <= pq->nitems; i++) {
        if (pq->nodes[i].key == item.key) {
            updatePQ(pq, item);
            return;
        }
    }
    // adding the first item
    if (pq->nitems == 0) {
        pq->nodes[0] = item;
        pq->nitems++;
        return;
    }

    // Insert in order (smallest at the front of the q)
    for (int i = 0; i < pq->nitems; i++) {
        if (pq->nodes[i].value >= item.value) {
            // shuffle all the items down the array
            for (int curr = pq->nitems - 1; curr >= i; curr--) {
                pq->nodes[curr+1] = pq->nodes[curr];
            }
            pq->nodes[i] = item;
            pq->nitems++;
            return;
        }
    }

    // Insert the item into last place
    pq->nodes[pq->nitems] = item;
    pq->nitems++;
}

//Removes and returns the item (ItemPQ) with smallest 'value'. Returns null if this queue is empty.
ItemPQ  dequeuePQ(PQ pq) {
    assert(pq != NULL);
    ItemPQ smallest = pq->nodes[0];
    // Shuffle everything up the array from the smallest node
    for (int i = 0; i < pq->nitems; i++) {
        pq->nodes[i] = pq->nodes[i+1];
    }
    pq->nitems--;
    return smallest;
    
}

// Updates item with a given 'key' value, by updating that item's value to the given 'value'.
// If item with 'key' does not exist in the queue, no action is taken
void  updatePQ(PQ pq, ItemPQ item) {
    for (int i = 0; i < pq->nitems; i++) {
        if (pq->nodes[i].key == item.key) {
            pq->nodes[i].value = item.value;
       
            // remove the item and reinsert in correct position
            for (int j = i; j < pq->nitems; j++ ) {
                pq->nodes[j] = pq->nodes[j+1];
            }
            pq->nitems--;
            addPQ(pq, item);
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
    for (int i = 0; i < pq->nitems; i++) {
        printf("[%d](%d)->", pq->nodes[i].key, pq->nodes[i].value);
    }
//    printf("[X]\n");
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
ItemPQ newItemPQ(int a, int b){

  ItemPQ *p = malloc(sizeof(struct ItemPQ)) ;
  p->key = a;
  p->value = b;
  
  return *p;
}


// Main for testing
int main (int argc, char *argv[]) {
    printf("=== Testing ===\n");
    PQ pq = newPQ();
    addPQ(pq,newItemPQ(1,100));
    printf("addPQ: {1,100}\n");
    addPQ(pq,newItemPQ(2,15));
    printf("addPQ: {2,15}\n");
    addPQ(pq,newItemPQ(3,1));
    printf("addPQ: {3,1}\n");
    addPQ(pq,newItemPQ(4,4));
    printf("addPQ: {4,4}\n");
    addPQ(pq,newItemPQ(4,8));
    printf("addPQ: {4,8}\n");
    addPQ(pq,newItemPQ(5,3));
    printf("addPQ: {5,3}\n");
    addPQ(pq,newItemPQ(2,3));
    printf("addPQ: {2,3}\n");
    addPQ(pq,newItemPQ(7,4));
    printf("addPQ: {7,4}\n");
    addPQ(pq,newItemPQ(9,2));
    printf("addPQ: {9,2}\n");
    addPQ(pq,newItemPQ(2,6));
    printf("addPQ: {2,6}\n");
    addPQ(pq,newItemPQ(22,6));
    printf("addPQ: {22,6}\n");

    dequeuePQ(pq);
    showPQ(pq);

    dequeuePQ(pq);
    showPQ(pq);
    dequeuePQ(pq);
    showPQ(pq);
    dequeuePQ(pq);
    showPQ(pq);
    dequeuePQ(pq);
    showPQ(pq);
    dequeuePQ(pq);
    showPQ(pq);
    dequeuePQ(pq);
    showPQ(pq);

    free(pq);
    printf("END\n=== Complete ===\n");
    return EXIT_SUCCESS;
}
*/
