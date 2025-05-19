#include <app_bsp.h>
#include "blink1.h"
#include "sys_assert.h"
void btn_inc_callback(void*  b)
{

	button_t* me_b = (button_t*)b;
	switch (me_b->state) {
		case BUTTON_SW_STATE_PRESSED:
		{
			LTK_Evt_t const buttonPressed = { BUTTON_INC_PRESSED };
			LTK_Task_post( AO_blinky1 , &buttonPressed);
			break;
		}

		case BUTTON_SW_STATE_LONG_PRESSED:
		{

			break;
		}

		case BUTTON_SW_STATE_RELEASED:
		{
			LTK_Evt_t const buttonRelease = { BUTTON_INC_RELEASE };
			LTK_Task_post( AO_blinky1 , &buttonRelease);
			break;
		}

		default:
			break;
	}
}

void btn_dec_callback(void*  b)
{

	button_t* me_b = (button_t*)b;

	switch (me_b->state) {
		case BUTTON_SW_STATE_PRESSED:
		{
			break;
		}

		case BUTTON_SW_STATE_LONG_PRESSED:
		{
			break;
		}

		case BUTTON_SW_STATE_RELEASED:
		{
			break;
		}

		default:
			break;
	}
}

void btn_startPause_callback(void*  b)
{

	button_t* me_b = (button_t*)b;

	switch (me_b->state) {
		case BUTTON_SW_STATE_PRESSED:
		{

			break;
		}

		case BUTTON_SW_STATE_LONG_PRESSED:
		{
			break;
		}

		case BUTTON_SW_STATE_RELEASED:
		{
			break;
		}

		default:
			break;
	}
}


/**
  * @brief This function handles TIM24 global interrupt.
  */
void TIM24_IRQHandler(void) // polling after 10ms
{

	button_timer_polling(&btn_inc);
	button_timer_polling(&btn_dec);
	button_timer_polling(&btn_startPause);

	led_blink_polling(&led_red);
	led_blink_polling(&led_green);
	led_blink_polling(&led_yellow);

	HAL_TIM_IRQHandler(&htim24);
}



