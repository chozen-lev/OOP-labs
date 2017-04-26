#include "mem_dispatcher.h"

int main()
{
	mem_dispatcher *md = (mem_dispatcher*)malloc(sizeof(mem_dispatcher));
	
	init(md);

	int key;

	while (1)
	{
		printf("1. Allocate\n2. Deallocate\n3. Show memory map\n4. Defragment\n5. Exit");
		printf("\nEnter command: ");
		scanf("%d", &key);

		switch (key)
		{
			case 1:
			{
				printf("Enter block size: ");
				scanf("%d", &key);
				if (-1 == allocate(md, key))
				{
					printf("Allocation failed\n");
				}
			}; break;
			case 2:
			{
				printf("Enter block id: ");
				scanf("%d", &key);
				if (-1 == deallocate(md, key))
				{
					printf("Such block doesn't exist\n");
				}
			}; break;
			case 3:
			{
				printf("\n");
				show_memory_map(md);
			}; break;
			case 4: defragment(md); break;
			case 5: return 0;
			default: printf("Wrong command\n");
		}

		printf("--------------------------------------------\n\n");
	}

	return 0;
}