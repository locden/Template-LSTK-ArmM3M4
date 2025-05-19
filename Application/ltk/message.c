#include "message.h"


static memory_pool_t memPool;

void mem_pool_init(void)
{
	memPool.free_list = (mem_block_t *)memPool.pool;

	mem_block_t * block = (mem_block_t *)(memPool.pool);

	for(uint8_t i = 0; i < POOL_NUM_BLOCKS; i++)
	{
		(block + i)->next = block + i + 1;
	}

	(block + POOL_NUM_BLOCKS - 1)->next = (mem_block_t *)0;
}

void * mem_pool_allocate(void)
{
	if( memPool.free_list == (mem_block_t *)0)
	{
		return NULL;
	}

	mem_block_t * new_block;

	new_block = memPool.free_list;
	memPool.free_list = new_block->next;

	return (void *)new_block;
}

void mem_pool_free(void * ptr)
{
	if (ptr == (mem_block_t *)0)
	{
		return;
	}

	mem_block_t * free_block = (mem_block_t *)ptr;

	free_block = memPool.free_list;

	memPool.free_list = free_block;
}

uint32_t mem_pool_getFreeBlockCount()
{
	uint32_t count = 0;

	mem_block_t * current_free = memPool.free_list;

	while(current_free != (mem_block_t *)0)
	{
		++count;
		current_free = current_free->next;
	}

	return count;
}
