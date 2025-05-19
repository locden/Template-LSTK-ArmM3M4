#ifndef LTK_TIMER_H_
#define LTK_TIMER_H_

#include "task.h"
#include "sys_assert.h"

typedef struct LTK_TimeEvt_t LTK_TimeEvt_t;



struct LTK_TimeEvt_t{

	LTK_Evt_t super;

	LTK_Task_t * task;
	LTK_TimeEvt_t * next;

	uint32_t ctr;
	uint32_t interval;
};


void LTK_TimeEvt_ctor(struct LTK_TimeEvt_t * me, LTK_Signal sig, LTK_Task_t * task);
void LTK_TimeEvt_arm(struct LTK_TimeEvt_t * me, uint32_t, uint32_t interval);
bool LTK_TimeEvt_disarm(struct LTK_TimeEvt_t * me);
void LTK_TimeEvt_tick();


#endif /* LTK_TIMER_H_ */
