#ifndef LTK_OBSERVER_H_
#define LTK_OBSERVER_H_

#include <stdint.h>
#include <stddef.h>
#include "task.h"


#define MAX_NODE			10

typedef struct
{
	LTK_Evt_t super;
	LTK_Task_t * list_node[MAX_NODE];
	uint8_t list_count;
}obs_sub_t;

extern void LTK_observerInit(obs_sub_t * sub, LTK_Signal sig);
extern bool LTK_observerAttach(obs_sub_t * sub, LTK_Task_t * node);
extern bool LTK_observerDetach(obs_sub_t * sub, LTK_Task_t * node);
extern void LTK_observerNotify(obs_sub_t * sub, LTK_Evt_t const * const e);

#endif /* LTK_OBSERVER_H_ */
