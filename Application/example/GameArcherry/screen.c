#include "game.h"

typedef struct
{
	LTK_Task_t super;

	LTK_TimeEvt_t sTe;


	uint8_t x;
	uint8_t y;
	uint32_t bmp;
	uint32_t blink_ctr;
} screen_t ;

static screen_t screen;

LTK_Task_t * const AO_screen = &screen.super;

static void do_beep(void);
static void display_clear(void);
static void display_message(const char* s, uint8_t x, uint8_t y);
//static void display_time(uint32_t time);

static State Screen_initialize(screen_t * const me, LTK_Evt_t const * const e);
static State Screen_show_setup(screen_t * const me, LTK_Evt_t const * const e);
static State Screen_playing(screen_t * const me, LTK_Evt_t const * const e);
static void display_score(uint32_t score);




static State Screen_initialize(screen_t * const me, LTK_Evt_t const * const e)
{
	(void)e;
	me->blink_ctr = 0U;

	return FSM_TRAN(Screen_show_setup);
}

static State Screen_show_setup(screen_t * const me, LTK_Evt_t const * const e)
{
	State status;

	switch(e->sig)
	{
		case(ENTRY_SIG):
		{
			display_message("LOC Task kernel", 0U, 0U);
			display_message("Pressed BTN0", 2U, 1U);

			LTK_TimeEvt_arm( &me->sTe, 1000U, 0U); /* Pseudo to get TIMEOUT signal */
			status = HANDLED_STATUS;
			break;
		}
		case(EXIT_SIG):
		{
			LTK_TimeEvt_disarm(&me->sTe);
			display_clear();
			status = HANDLED_STATUS;
			break;
		}
		case(BLINK_TIMEOUT_SIG):
		{
			do_beep();
			me->blink_ctr ^= 1U;
			if(me->blink_ctr == 0U)
			{
				display_message("LOC Task kernel", 0, 0);
			}
			else
			{
				display_message("LoC Task keRnel", 0, 0);
			}
			LTK_TimeEvt_arm( &me->sTe, 500U, 0U);
			status = HANDLED_STATUS;
			break;
		}
		case(BUTTON_MODE_PRESSED):
		{
			status = FSM_TRAN( Screen_playing );
			break;
		}
		default:
			status = IGNORED_STATUS;
			break;
	}

	return status;
}

static State Screen_playing(screen_t * const me, LTK_Evt_t const * const e)
{
	State status;

	switch(e->sig)
	{
		case(ENTRY_SIG):
		{
			static LTK_Evt_t const archeryPlaying = { ARCHERY_PLAYING_SIG };
			LTK_Task_post(AO_archery, &archeryPlaying);
			status = HANDLED_STATUS;
			break;
		}
		case(EXIT_SIG):
		{
			status = HANDLED_STATUS;
			break;
		}
		case(SCORE_SIG):
		{
			display_score(((ScoreEvt *)e)->score);
			status = HANDLED_STATUS;
			break;
		}
		default:
			status = IGNORED_STATUS;
			break;
	}
	return status;
}








static void Screen_ctor(screen_t * const me)
{
	LTK_Task_ctor(&me->super, (StateHandler)&Screen_initialize);
	LTK_TimeEvt_ctor( &me->sTe , BLINK_TIMEOUT_SIG , &me->super );
}


void Screen_instance(void)
{
	Screen_ctor(&screen);
}


static void do_beep(void) {
	led_toggle(&led_red);
	led_toggle(&led_green);
	led_toggle(&led_yellow);
}
static void display_clear(void) {
	Lcd_clear_display();
}
static void display_message(const char* s, uint8_t x, uint8_t y)
{
    Lcd_gotoxy(x, y);
    Lcd_write_string((char*)s);
}
static void display_score(uint32_t score)
{
    char buf[4];  

    sprintf(buf, "%03lu", score);

    Lcd_gotoxy(15, 0);
    Lcd_write_string(buf);
}
