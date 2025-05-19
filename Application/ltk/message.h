#ifndef LTK_MESSAGE_H_
#define LTK_MESSAGE_H_

#include <stdint.h>
#include <stddef.h>

#define POOL_NUM_BLOCKS        10 /* Number of memory blocks */
#define POOL_BLOCK_SIZE        64 /* Size of each memory block in bytes */
#define ALIGNMENT               4  /* Align memory blocks to 4-byte boundaries */


#define BLOCK_IS_NOT_ALLOCATED  0
#define BLOCK_IS_ALLOCATED      1



typedef struct memBlock
{
	struct memBlock * next;
} mem_block_t;

typedef struct {

	uint8_t pool[POOL_NUM_BLOCKS][POOL_BLOCK_SIZE];
	mem_block_t * free_list;

} memory_pool_t;

#endif /* LTK_MESSAGE_H_ */
