#include "game.h"

typedef struct
{
	LTK_Task_t super;


	uint8_t x;
	uint8_t y;
	uint32_t bmp;
} meteoroid_t ;

static meteoroid_t meteoroid;

LTK_Task_t * const AO_meteoroid = &meteoroid.super;

static State Meteoroid_initialize(meteoroid_t * const, LTK_Evt_t const * const e);






State Meteoroid_initialize(meteoroid_t * const, LTK_Evt_t const * const e)
{
	return HANDLED_STATUS;
}

static void Meteoroid_ctor(meteoroid_t * const me)
{
	LTK_Task_ctor(&me->super, (StateHandler)&Meteoroid_initialize);
}


void Meteoroid_instance(void)
{
	Meteoroid_ctor(&meteoroid);
}
