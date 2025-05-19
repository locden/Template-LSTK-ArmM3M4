#include "timer.h"

static LTK_TimeEvt_t *timeEvt_head = (LTK_TimeEvt_t *)0;

void LTK_TimeEvt_ctor(struct LTK_TimeEvt_t * me, LTK_Signal sig, LTK_Task_t * task)
{
	me->super.sig = sig;
	me->task = task;
	me->ctr = 0U;
	me->interval = 0U;

	me->next = timeEvt_head;
	timeEvt_head = me;
}
void LTK_TimeEvt_arm(struct LTK_TimeEvt_t * me, uint32_t ctr, uint32_t interval)
{
	LTK_PORT_CRIT_ENTRY();

	me->ctr = ctr;
	me->interval = interval;

	LTK_PORT_CRIT_EXIT();
}
bool LTK_TimeEvt_disarm(struct LTK_TimeEvt_t * me)
{
	LTK_PORT_CRIT_ENTRY();

	bool status = (me->ctr != 0U);
	me->ctr = 0U;
	me->interval = 0U;

	LTK_PORT_CRIT_EXIT();

	return status;
}
void LTK_TimeEvt_tick()
{
	for(LTK_TimeEvt_t * t = timeEvt_head; t != (LTK_TimeEvt_t*)0; t = t->next )
	{
		LTK_PORT_CRIT_ENTRY();

		if(t->ctr == 0U)
		{

			LTK_PORT_CRIT_EXIT();

		}
		else if(t->ctr == 1U)
		{
			t->ctr = t->interval;
			LTK_PORT_CRIT_EXIT();

			LTK_Task_post( t->task , &t->super);
		}
		else
		{
			--t->ctr;
			LTK_PORT_CRIT_EXIT();
		}

		LTK_PORT_CRIT_EXIT();
	}
}
