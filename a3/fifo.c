#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

int head; // FIFO head

/* Page to evict is chosen using the fifo algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */
int fifo_evict() {

	// Store the current value of the FIFO head. 
	int prev = head;

	// Increment the FIFO head. 
	head = (head + 1) % memsize;
	
	// Reset FIFO head if page number reaches the memsize. 
	if (head == memsize){
		head = 0;
	}
	
	return prev;
}

/* This function is called on each access to a page to update any information
 * needed by the fifo algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void fifo_ref(pgtbl_entry_t *p) {

	// Nothing to change
	return;
}

/* Initialize any data structures needed for this 
 * replacement algorithm 
 */
void fifo_init() {

	// Initialize the fifo head with 0
	head = 0;
}
