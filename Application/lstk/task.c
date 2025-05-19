#include "task.h"

#include "../sys/sys_assert.h"

SYS_MODULE_NAME("ltk Task") /* for DBC assertions in this module */

static LTK_Task_t * task_list[LTK_PORT_MAX_TASK];

static uint32_t task_readySetFlag = 0;

int LTK_Task_run(void)
{
	LTK_PORT_INT_DISABLE();
	for( ;; )
	{

		if(task_readySetFlag != 0U)
		{
			uint32_t p = LTK_LOG2(task_readySetFlag);

			LTK_Task_t * const task = task_list[p];

			 LTK_PORT_INT_ENABLE();

			/* the task must have some events in the queue */
			SYS_ASSERT(100, task->nUsed > 0U);

			LTK_Evt_t const * e = task->qBuff[task->tail];

            if (task->tail == 0U) { /* need to wrap the tail? */
                task->tail = task->end; /* wrap around */
            }
            else {
                --task->tail;
            }


            LTK_PORT_INT_DISABLE();

            if ((--task->nUsed) == 0U) {
            	task_readySetFlag &= ~(1U << (p - 1U));
            }

            LTK_PORT_INT_ENABLE();

            (*task->dispatcher)(task, e); /* NOTE: virtual call */
		}
		else
		{

			LTK_onIdleCond();
			LTK_PORT_INT_DISABLE(); /* disable before looping back */
		}
	}

#ifdef __GNUC__ /* GNU compiler? */
    return 0;
#endif
}

void LTK_Task_ctor(LTK_Task_t * const me, LTK_Handler init, LTK_Handler dispatcher)
{
	me->init = init;
	me->dispatcher = dispatcher;
}
void LTK_Task_start(LTK_Task_t * const me,
					uint8_t prio,
					LTK_Evt_t const **qBuff, uint8_t qLen,
					LTK_Evt_t const * const e)
{

	SYS_REQUIRE(200,
			    (0U < prio) && (prio <= LTK_PORT_MAX_TASK)
				&& (qBuff != (LTK_Evt_t const **)0) && (qLen > 0U)
				&& (task_list[prio] == (LTK_Task_t *)0));

	me->prio = prio;

	me->qBuff = qBuff;
	me->end = qLen - 1;
	me->head = 0U;
	me->tail = 0U;
	me->nUsed = 0U;

	task_list[me->prio] = me;


	(*me->init)(me, e);
}
void LTK_Task_post(LTK_Task_t * const me, LTK_Evt_t const * const e)
{

	SYS_REQUIRE(300, me->nUsed <= me->end);

	LTK_PORT_CRIT_ENTRY();

	me->qBuff[me->head] = e;

	if(me->head == 0)
	{
		me->head = me->end;
	}
	else
	{
		--me->head;
	}

	++me->nUsed;
	task_readySetFlag |= (1U << (me->prio - 1));

	LTK_PORT_CRIT_EXIT();
}
