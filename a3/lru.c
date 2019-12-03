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

	// Get the frame number. 
	int frame_num = lru_frame->frame_num;

	// Evict 
	struct frame *curr = mru_frame;
	struct frame *prev = NULL;

	while (curr) {
		
		if (curr->frame_num == frame_num) {

			if (curr == mru_frame) {

				mru_frame = curr->next_frame; // Update head of list
			} else {

				if (curr == lru_frame) {
					lru_frame = prev; 
				}

				prev->next_frame = curr->next_frame;
			}

			free(curr);
			break;
		}

		// Move to the next node
		prev = curr;
		curr = curr->next_frame;
	}
	return frame_num;

}

/* This function is called on each access to a page to update any information
 * needed by the lru algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void lru_ref(pgtbl_entry_t *p) {

	int frame_num = p->frame >> PAGE_SHIFT;

	// Check if the most recently used frame is similar to the given frame
	// for the given page table enty. 
	struct frame *first_frame = &coremap[frame_num];

	// If the frame for p is same as most recently used then return 
	// immediately. 
	if (first_frame == mru_frame) {
		return;
	}

	// Evict 
	struct frame *curr = mru_frame;
	struct frame *prev = NULL;

	while (curr) {
		
		if (curr->frame_num == frame_num) {

			if (curr == mru_frame) {

				mru_frame = curr->next_frame; // Update head of list
			} else {

				if (curr == lru_frame) {
					lru_frame = prev; 
				}
				
				prev->next_frame = curr->next_frame;
			}

			free(curr);
			break;
		}

		// Move to the next node
		prev = curr;
		curr = curr->next_frame;
	}
	// Update the most recently used frame with the more recent one
	// that is the frame for page table entry p. 
	struct frame * recent_mru = (struct frame*) malloc(sizeof(struct frame));

	recent_mru->frame_num = frame_num;
	recent_mru->next_frame = mru_frame;
	mru_frame = recent_mru;

	
	if (!lru_frame) {
		lru_frame = recent_mru;
	}

	return;
}


/* Initialize any data structures needed for this 
 * replacement algorithm 
 */
void lru_init() {
	
	for (int i = 0; i < memsize; i++) {

		if (i < memsize - 1) {
			
			(&coremap[i])->next_frame = &coremap[i+1];
		} else {
			
			(&coremap[i])->next_frame = NULL;
		}
	}

	// Set MRU and LRU frames 
	mru_frame = &coremap[0];
	lru_frame = &coremap[memsize - 1];
}
