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
	struct frame *recent_mru = &coremap[frame_num];

	// If the frame for p is same as most recently used then return 
	// immediately. 
	if (recent_mru == mru_frame) {
		return;
	}

	recent_mru->prev_frame->next_frame = recent_mru->next_frame;
	
	// remove the mru_frame
    if (recent_mru == lru_frame) {
		// reset the last_frame if mru_frame is the current last_frame
		lru_frame = lru_frame->prev_frame;
	} else {
		// if mru_frame is not the current last_frame, update the prev pointer of the node after mru_frame
		recent_mru->next_frame->prev_frame = recent_mru->prev_frame;
	}

	recent_mru->frame_num = frame_num;
	recent_mru->next_frame = mru_frame;
    recent_mru->prev_frame = NULL;
    recent_mru->next_frame->prev_frame = recent_mru;
	mru_frame = recent_mru;
}


/* Initialize any data structures needed for this 
 * replacement algorithm 
 */
void lru_init() {
	
	for (int i = 0; i < memsize; i++) {
		if (i < memsize - 1) {
			
			(&coremap[i])->next_frame = &coremap[i+1];
            
            if (i == 0){
                
                (&coremap[i])->prev_frame = NULL;
            } else {
                
                (&coremap[i])->prev_frame = &coremap[i-1];
            }

         
		} else {
			
			(&coremap[i])->next_frame = NULL;
            (&coremap[i])->prev_frame = &coremap[i-1];
         
		}
	}

	// Set MRU and LRU frames 
	mru_frame = &coremap[0];
	lru_frame = &coremap[memsize - 1];
}
