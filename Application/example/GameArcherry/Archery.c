
#include "game.h"
#include "fsm.h"
#include "message.h"

typedef struct
{
	/* protected */
	LTK_Task_t super;

	/* public */
	uint8_t x;
	uint8_t y;
	uint16_t score;
} archery_t ;

static archery_t archery;

LTK_Task_t * const AO_archery = &archery.super;

static State Archery_initialize(archery_t * const me, LTK_Evt_t const * const e);
static State Archery_playing(archery_t * const me, LTK_Evt_t const * const e);
static State Archery_parked(archery_t * const me, LTK_Evt_t const * const e);




static State Archery_initialize(archery_t * const me, LTK_Evt_t const * const e)
{
//	LTK_observerAttach( &sysTickSubject , AO_archery );

//	Lcd_create_custom_char(LED_RAM_POS_1, archery_);
	return FSM_TRAN(Archery_parked);
}

static State Archery_parked(archery_t * const me, LTK_Evt_t const * const e)
{
	State status;

    switch (e->sig)
    {
        case ENTRY_SIG: {
        	status = FSM_TRAN(Archery_playing);
            break;
        }
        case (EXIT_SIG):
        	break;
        default:
        {
        	status = IGNORED_STATUS;
            break;
        }

    }
    return status;
}

static State Archery_playing(archery_t * const me, LTK_Evt_t const * const e)
{
	State status;
	switch(e->sig)
	{
		case(ENTRY_SIG):
		{
			ScoreEvt *sev = (ScoreEvt *)Event_allocate(SCORE_SIG);
			printf("%ld\n", mem_pool_getFreeBlockCount());
			sev->score = 0U;

			LTK_Task_post(AO_screen, (LTK_Evt_t *)sev);

			me->x = GAME_ARCHERY_X;
			me->y = GAME_ARCHERY_Y;

			status = HANDLED_STATUS;
			break;
		}
		case(EXIT_SIG):
		{
			status = HANDLED_STATUS;
			break;
		}
		case (TIME_TICK_SIG):
		{
			ObjectImageEvt *oie = (ObjectImageEvt *)Event_allocate(ARCHERY_IMG_SIG);

			oie->x = me->x;
			oie->y = me->y;
			oie->bmp = ARCHERY_BMP;
			LTK_Task_post(AO_screen, (LTK_Evt_t *)oie);

			++me->score;
			if(me->score % 10U == 0U)
			{
				ScoreEvt *sev = (ScoreEvt *)Event_allocate(SCORE_SIG);
				sev->score = me->score;
				LTK_Task_post(AO_screen, (LTK_Evt_t *)sev);
			}

			status = HANDLED_STATUS;
			break;
		}
		case(ARCHERY_PLAYING_SIG):
		{

			status = HANDLED_STATUS;
			break;
		}
		default:
			status = IGNORED_STATUS;
			break;

	}
	return status;
}

static void Archery_ctor(archery_t * const me)
{
	LTK_Task_ctor(&me->super, (StateHandler)&Archery_initialize);

}


void Archery_instance(void)
{
	Archery_ctor(&archery);
}
