#include "game.h"

static uint8_t border_[] = { 0x04,  0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04};

typedef struct
{
	LTK_Task_t super;
} border_t ;

static border_t border;

LTK_Task_t * const AO_border = &border.super;

static State Border_initialize(border_t * const, LTK_Evt_t const * const e);
static State Border_screen(border_t * const me, LTK_Evt_t const * const e);





static State Border_initialize(border_t * const me, LTK_Evt_t const * const e)
{
	Lcd_create_custom_char(LED_RAM_POS_0, border_);
	return FSM_TRAN( Border_screen );
}

static State Border_screen(border_t * const me, LTK_Evt_t const * const e)
{
	State status;

	switch(e -> sig)
	{
		case(ENTRY_SIG):
		{
//			Lcd_write_custom_char(1, 0, LED_RAM_POS_0);
//			Lcd_write_custom_char(1, 1, LED_RAM_POS_0);
			status = HANDLED_STATUS;
			break;
		}
		default:
			status = IGNORED_STATUS;
			break;


	}

	return status;
}

static void Border_ctor(border_t * const me)
{
	LTK_Task_ctor(&me->super, (StateHandler)&Border_initialize);
}


void Border_instance(void)
{
	Border_ctor(&border);
}
