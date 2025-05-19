# LSTK - The LOC Simple Task Kernel

**LSTK (LOC Simple Task Kernel)** is an event-driven kernel designed to manage tasks efficiently using the **Active Object** model and **priority-based preemption**. Each task maintains its own message queue, and messages are posted and handled asynchronously. Once a task receives and processes a message, it is automatically removed from the queue by the kernel.

### Key Concepts:
- Active Object and priority preemption  
- Per-task message queues  
- Automatic message handling and removal  
- Event-driven architecture  

To fully understand this model, learners should have basic knowledge of data structures such as linked lists, queues, memory pools, and object-oriented programming (OOP).

### Features:
- Memory pool management  
- Message posting and handling mechanisms  
- Timer list support  
- Observer pattern for decoupled communication  

## 1. Memory Pool:
<!-- Add your description for memory pool here -->
Efficient memory management is essential in embedded programming. Proper control of memory usage enhances system performance and helps reduce costs when selecting a microcontroller.
![Architecture Diagram](Image/pool_Memory.png)
In this kernel, memory is managed using a memory pool. A fixed block of memory is allocated during initialization to create the pool.

When memory is needed, the kernel automatically takes a block from the pool. After the task is completed, the kernel also automatically frees the memory and returns it to the pool for reuse.

```c
/* Allocate memory */
void * mem_pool_allocate(void)

/* Free memory */
void mem_pool_free(void * ptr);

/* Dump block */
uint32_t mem_pool_getFreeBlockCount();
```

## 1. Task post:
When the task post function is called, the kernel adds the message content to the task’s queue.
![Architecture Diagram](Image/Task.png)
```c
/* Post Event, Data to task's queue */
void LTK_Task_post(LTK_Task_t * const me, LTK_Evt_t const * const e);
```
The content of a message includes:
- Event.
- Data — if you want to post data along with the event, you need to use a mutable event or allocate memory from the pool before posting.
