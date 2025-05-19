#include "blink1.h"





static void Blinky1_ctor(Blinky_1_t * const me);
static void Blinky1_init(Blinky_1_t * const me, LTK_Evt_t const * const e);
static void Blinky1_dispatcher(Blinky_1_t * const me, LTK_Evt_t const * const e);

static Blinky_1_t blinky1;

LTK_Task_t * const AO_blinky1 = &blinky1.super;


static void Blinky1_ctor(Blinky_1_t * const me)
{
	LTK_Task_ctor( &me->super, (LTK_Handler)&Blinky1_init, (LTK_Handler)&Blinky1_dispatcher);
	LTK_TimeEvt_ctor( &me->te , TIMEOUT1_SIG , AO_blinky1);

}
static void Blinky1_init(Blinky_1_t * const me, LTK_Evt_t const * const e)
{
	LTK_TimeEvt_arm(&me->te, 1000U, 1000U);
}
static void Blinky1_dispatcher(Blinky_1_t * const me, LTK_Evt_t const * const e)
{
	switch(e->sig)
	{
		case(BUTTON_INC_PRESSED):
		{
			led_on(&led_green);
			break;
		}
		case(BUTTON_INC_RELEASE):
		{
			led_off(&led_green);
			break;
		}
		case(TIMEOUT1_SIG):
		{
			led_toggle(&led_yellow);

			break;
		}

	}
}

void Blinky1_instance(void)
{
	Blinky1_ctor(&blinky1);
}
