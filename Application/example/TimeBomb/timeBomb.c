#include "timeBomb.h"



static void TimeBomb_ctor( TimeBomb_t * const me );
static State TimeBomb_initial(TimeBomb_t * const me, LTK_Evt_t const * const e);
static State Timebomb_wait4button(TimeBomb_t * const me, LTK_Evt_t const * const e);
static State TimeBomb_blink(TimeBomb_t * const me, LTK_Evt_t const * const e);
static State TimeBomb_pause(TimeBomb_t * const me, LTK_Evt_t const * const e);
static State TimeBomb_boom(TimeBomb_t * const me, LTK_Evt_t const * const e);



static TimeBomb_t timeBomb;

LTK_Task_t * const AO_timeBomb = &timeBomb.super;

static State TimeBomb_initial(TimeBomb_t * const me, LTK_Evt_t const * const e) {
	(void)e;
	return FSM_TRAN(Timebomb_wait4button);
}
static State Timebomb_wait4button(TimeBomb_t * const me, LTK_Evt_t const * const e) {
	State status;
	switch( e->sig ) {

		case (ENTRY_SIG) : {
			led_on(&led_green);
			status = HANDLED_STATUS;
			break;
		}
		case (EXIT_SIG) : {
			led_off(&led_green);
			status = HANDLED_STATUS;
			break;
		}
		case (BUTTON1_PRESSED_SIG) : {
			me->blink_ctr = 5U;
			status = FSM_TRAN(TimeBomb_blink);
			break;
		}
		case (BUTTON1_RELEASED_SIG): {
			status = IGNORED_STATUS;
			break;
		}
		default:
			status = IGNORED_STATUS;
			break;
	}

	return status;
}
static State TimeBomb_blink(TimeBomb_t * const me, LTK_Evt_t const * const e) {
	State status;
	switch( e->sig ) {

		case (ENTRY_SIG) : {
			led_on(&led_red);
			LTK_TimeEvt_arm(&me->te, 500U, 0U);
			status = HANDLED_STATUS;
			break;
		}
		case (EXIT_SIG) : {
			led_off(&led_red);
			status = HANDLED_STATUS;
			break;
		}
		case (TIMEOUT_SIG) : {
			status = FSM_TRAN(TimeBomb_pause);
			break;
		}
		default:
			status = IGNORED_STATUS;
			break;
	}
	return status;
}
static State TimeBomb_pause(TimeBomb_t * const me, LTK_Evt_t const * const e) {
	State status;
	switch( e->sig ) {

		case (ENTRY_SIG) : {
			LTK_TimeEvt_arm(&me->te, 500U, 0U);
			status = HANDLED_STATUS;
			break;
		}
		case (EXIT_SIG) : {
			status = IGNORED_STATUS;
			break;
		}

		case (TIMEOUT_SIG) : {
			me->blink_ctr--;

			if(me->blink_ctr > 0U) {
				status = FSM_TRAN(TimeBomb_blink);

			}
			else {
				status = FSM_TRAN(TimeBomb_boom);
			}
			break;
		}
		default:
			status = IGNORED_STATUS;
			break;
	}
	return status;
}
static State TimeBomb_boom(TimeBomb_t * const me, LTK_Evt_t const * const e) {
	State status;
	switch( e->sig ) {

		case (ENTRY_SIG) : {
			led_on(&led_red);
			led_on(&led_green);
			led_on(&led_yellow);

		    status = HANDLED_STATUS;
			break;
		}
		case (EXIT_SIG) : {
			led_off(&led_red);
			led_off(&led_green);
			led_off(&led_yellow);
			status = HANDLED_STATUS;
			break;
		}
		default:
			status = IGNORED_STATUS;
			break;
	}
	return status;
}






void TimeBomb_ctor( TimeBomb_t * const me ) {

	LTK_Task_ctor(&me->super, (StateHandler)&TimeBomb_initial);
	LTK_TimeEvt_ctor(&me->te, TIMEOUT_SIG, &me->super);
}

void TimeBome_instance(void)
{
	TimeBomb_ctor(&timeBomb);
}
