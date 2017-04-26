#pragma once

#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 10

typedef  enum { FREE, ALLOCATED } STATUS;

typedef struct tag_mem_chunk {
	int id;
	int size;
	STATUS status;
	struct tag_mem_chunk* next; // pointer to the next memory block
	//
} mem_chunk;

typedef struct {
	int last_id_used;
	mem_chunk* first; // pointer to the first memory block
} mem_dispatcher;

void init(mem_dispatcher *md); // creates a heap as a single free block with id 0 and HEAP_SIZE size
int allocate(mem_dispatcher *md, int size); // returns block id if allocated and -1 otherwise
int deallocate(mem_dispatcher *md, int block_id); // returns nonnegative value if block is deallocated and -1 otherwise
void defragment(mem_dispatcher *md); // reunites free blocks that were previously stored in various parts of a heap into one successive block
void show_memory_map(mem_dispatcher *md); // displays heap status