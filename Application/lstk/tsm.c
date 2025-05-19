#include "tsm.h"
#include "sys_assert.h"

SYS_MODULE_NAME("Table state machine")


void Tsm_ctor(struct tsm_t * const me, StateHandlerTable ** table, uint8_t firstState)
{
	SYS_REQUIRE(100, me != (struct tsm_t *)0);

	me->table = table;

	me->State = firstState;
}

void Tsm_dispatcher(struct tsm_t * const me, LTK_Evt_t const * const e)
{
	State stat;
	uint8_t pre_state = me->State;

	stat = (* me->table[me->State][e->sig])(me, e);

	if(stat == TRAN_STATUS)
	{
		(*me->table[pre_state][EXIT_SIG])(me, (LTK_Evt_t *)0);
		(*me->table[me->State][ENTRY_SIG])(me, (LTK_Evt_t *)0);
	}
	else if(stat == INIT_STATUS)
	{
		(*me->table[me->State][ENTRY_SIG])(me, (LTK_Evt_t *)0);
	}
}

