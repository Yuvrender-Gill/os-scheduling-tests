#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

int clock_hand; // Clock hand 

/* Page to evict is chosen using the clock algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int clock_evict() {

	while(1){

		if ((coremap[clock_hand].pte) -> frame & PG_REF) {

			// Reset reference flag if initially set
			(coremap[clock_hand].pte) -> frame &= ~PG_REF;
			//Increment the clock hand
			clock_hand++; 

		} else {

			return clock_hand;
		}	

		// Reset clock hand on complete cycle. 
		if (clock_hand >= memsize){
			clock_hand = 0;
		}
	}

	return clock_hand;
}

/* This function is called on each access to a page to update any information
 * needed by the clock algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void clock_ref(pgtbl_entry_t *p) {

	// Set the reference flag everytime clock refers it
	p->frame |= PG_REF;
}

/* Initialize any data structures needed for this replacement
 * algorithm. 
 */
void clock_init() {

	// Initially set clock hand to 0.
	clock_hand = 0;
}
