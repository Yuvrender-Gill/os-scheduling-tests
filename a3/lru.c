#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

struct frame * mru_frame; // Most recently used frame. 
struct frame * lru_frame; // Least recently used frame. 

/* Page to evict is chosen using the accurate LRU algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int lru_evict() {

	// If least recently used frame doesn't exist then exit. 
	if (lru_frame == NULL) { exit(1); };
	// Return the frame number
	return lru_frame->frame_num;

}

/* This function is called on each access to a page to update any information
 * needed by the lru algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void lru_ref(pgtbl_entry_t *p) {


	struct frame *recent_mru = &coremap[p->frame >> PAGE_SHIFT];

	// Remove the recently used frame from original position in linked list

	// If previous pointer is null then return immediately
	if (recent_mru->prev_frame == NULL){
		return;
	}
	// Remove the current frame from the linked list
	recent_mru->prev_frame->next_frame = recent_mru->next_frame; // Unlink from previous node
	
    if (recent_mru == lru_frame) {
		// If the current frame is the least used then it's at the end
		// of the linked list 
		lru_frame = lru_frame->prev_frame; // Unlink from previous node
	} else {
		
		recent_mru->next_frame->prev_frame = recent_mru->prev_frame; // Unlink from next node
	}

	// Add recently used frame at the head of linked list
	recent_mru->frame_num = p->frame >> PAGE_SHIFT; // Set frame number
	recent_mru->next_frame = mru_frame; // Update next pointer
    recent_mru->prev_frame = NULL; // Update previous pointer
    recent_mru->next_frame->prev_frame = recent_mru; // Set the back pointer of next node
	mru_frame = recent_mru; // Set the current node to head of the linked list
}


/* Initialize any data structures needed for this 
 * replacement algorithm 
 */
void lru_init() {

	// Set MRU and LRU frames 
	mru_frame = &coremap[0];
	lru_frame = &coremap[memsize - 1];
	
	// Initialize the doubly linked list as per given memory size
	for (int i = 0; i < memsize; i++) {

		// Last node in the linked list
		if (i == memsize - 1) {
			
			(&coremap[i])->next_frame = NULL; // Next pointer is NULL
            (&coremap[i])->prev_frame = &coremap[i-1]; // Prev pointer set to previous node

		} else {

			// First node in the linked list
			if (i == 0){
                (&coremap[i])->prev_frame = NULL; // Prev pointer is NULL
            } else {
                (&coremap[i])->prev_frame = &coremap[i-1]; // Prev pointer set to previous node
            }

			(&coremap[i])->next_frame = &coremap[i+1]; // Next pointer set to next node   
		}
	}
}
