#include "mem_dispatcher.h"

void init(mem_dispatcher *md)
{
	if (NULL != (md->first = (mem_chunk*)malloc(sizeof(mem_chunk))))
	{
		md->first->id = 0;
		md->first->next = NULL;
		md->first->size = HEAP_SIZE;
		md->first->status = FREE;
		md->last_id_used = 0;
	}
};

int allocate(mem_dispatcher *md, int size)
{
	mem_chunk *min = md->first;
	mem_chunk *buff = NULL;
	mem_chunk *curr;
	
	for (curr = md->first->next; NULL != curr; curr=curr->next)
	{
		if (curr->status == FREE && curr->size <= min->size)
		{
			min = curr;
		}
	}

	if ((min == md->first && min->size < size) || NULL == (buff = (mem_chunk*)malloc(sizeof(mem_chunk))))
		return -1;

	if (min->size == size)
	{
		min->status = ALLOCATED;
		return min->id;
	}
	
	buff->size = size;
	min->size -= size;
	buff->id = ++(md->last_id_used);
	buff->next = min->next;
	min->next = buff;
	buff->status = ALLOCATED;

	return buff->id;
};

int deallocate(mem_dispatcher *md, int block_id)
{
	mem_chunk *curr = NULL;
	mem_chunk *buff = NULL;


	for (curr = md->first; NULL != curr; curr = curr->next)
	{
		if (block_id == curr->id)
			break;
	}

	if (NULL == curr)
		return -1;

	curr->status = FREE;

	curr = md->first;

	while (NULL != curr->next)
	{
		if (curr->status == FREE && curr->next->status == FREE)
		{
			curr->size += curr->next->size;
			buff = curr->next->next;
			free(curr->next);
			curr->next = buff;
		}
		else curr = curr->next;
	}

	return 1;
};

void defragment(mem_dispatcher *md)
{
	mem_chunk *curr = md->first->next;
	mem_chunk *end = md->first;
	mem_chunk *buff = NULL;
	
	while (NULL != curr)
	{
		if (end->status != curr->status)
		{
			if (FREE == curr->status)
			{
				if (FREE == md->first->status)
				{
					md->first->size += curr->size;
					end->next = curr->next;
					free(curr);
					curr = end;
				}
				else
				{
					end->next = curr->next;
					curr->next = md->first;
					md->first = curr;
					curr = end;
				}
			}
			else
			{
				end = curr;
			}

			curr = curr->next;

			continue;
		}

		if (curr->status == FREE)
		{
			md->first->size += curr->size;
			end->next = curr->next;
			buff = curr;
			curr = curr->next;
			free(buff);
		}
		else
		{
			end = curr;
			curr = curr->next;
		}
	}
};

void show_memory_map(mem_dispatcher *md)
{
	mem_chunk *curr = md->first;

	while (NULL != curr)
	{
		printf("block id: %d\n", curr->id);
		printf("                size: %d   status: %s\n", curr->size, curr->status == FREE ? "free" : "allocated");
		curr = curr->next;
	}
};