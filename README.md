# LSTK - The LOC Simple Task Kernel

**LSTK (LOC Simple Task Kernel)** is an event-driven kernel designed to manage tasks efficiently using the **Active Object** model and **priority-based preemption**. Each task maintains its own message queue, and messages are posted and handled asynchronously. Once a task receives and processes a message, it is automatically removed from the queue by the kernel.

### Key Concepts:
. Active Object and priority preemption  
. Per-task message queues  
. Automatic message handling and removal  
. Event-driven architecture  

To fully understand this model, learners should have basic knowledge of data structures such as linked lists, queues, memory pools, and object-oriented programming (OOP).

### Features:
. Memory pool management  
. Message posting and handling mechanisms  
. Timer list support  
. Observer pattern for decoupled communication  

## 1. Memory Pool
<!-- Add your description for memory pool here -->
