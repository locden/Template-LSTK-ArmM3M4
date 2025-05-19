#include "game.h"


typedef struct
{
	LTK_Task_t super;


	uint8_t x;
	uint8_t y;
	uint32_t bmp;
} arrow_t ;

static arrow_t arrow;

LTK_Task_t * const AO_arrow = &arrow.super;

static State arrow_initialize(arrow_t * const, LTK_Evt_t const * const e);






State arrow_initialize(arrow_t * const, LTK_Evt_t const * const e)
{
//	LTK_observerAttach(&sysTickSubject , AO_arrow);
	return HANDLED_STATUS;
}

static void arrow_ctor(arrow_t * const me)
{
	LTK_Task_ctor(&me->super, (StateHandler)&arrow_initialize);
}


void Arrow_instance(void)
{
	arrow_ctor(&arrow);
}
