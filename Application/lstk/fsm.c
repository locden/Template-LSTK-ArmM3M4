#include "fsm.h"
#include "sys_assert.h"
SYS_MODULE_NAME("Finite state machine")

static LTK_Evt_t const exitEvt = { EXIT_SIG };
static LTK_Evt_t const entryEvt = { ENTRY_SIG };

void Fsm_ctor(fsm_t * const me, StateHandler initialize)
{
	me->State = initialize;
}
void Fsm_dispatcher(fsm_t * const me, LTK_Evt_t const * const e)
{
	State status;

	StateHandler pre_state = me->State;

	SYS_ASSERT(100, me->State != (StateHandler)0);

	status = (*me->State)(me, e);

	if(status == TRAN_STATUS)
	{
		(*pre_state)(me, &exitEvt);
		(*me->State)(me, &entryEvt);
	}
}
void Fsm_init(fsm_t * const me, LTK_Evt_t const * const e)
{
	SYS_REQUIRE(200, me->State != (StateHandler)0);
	(*me->State)(me, e);
	(*me->State)(me, &entryEvt);
}
