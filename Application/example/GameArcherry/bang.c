#include "game.h"

typedef struct
{
	LTK_Task_t super;

	uint32_t bmp;
} bang_t ;

static bang_t bang;

LTK_Task_t * const AO_bang = &bang.super;

static State Bang_initialize(bang_t * const, LTK_Evt_t const * const e);






State Bang_initialize(bang_t * const, LTK_Evt_t const * const e)
{
	return HANDLED_STATUS;
}

static void Bang_ctor(bang_t * const me)
{
	LTK_Task_ctor(&me->super, (StateHandler)&Bang_initialize);
}


void Bang_instance(void)
{
	Bang_ctor(&bang);
}

