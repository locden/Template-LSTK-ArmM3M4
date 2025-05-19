#include <app_bsp.h>
#include <app_main.h>
#include "task.h"
#include "blink1.h"
#include "ltk_port.h"
button_t btn_inc;
button_t btn_dec;
button_t btn_startPause;

led_t led_red;
led_t led_green;
led_t led_yellow;


int main () {

	System_init();
	Lcd_Init();

	button_init(&btn_inc, 10U , BUTTON_HW_PRESSED_LOW , btn_inc_init, btn_inc_read, btn_inc_callback);
	button_init(&btn_dec, 10U , BUTTON_HW_PRESSED_LOW , btn_dec_init, btn_dec_read, btn_dec_callback);
	button_init(&btn_startPause, 10U , BUTTON_HW_PRESSED_HIGH , btn_startPause_init, btn_startPause_read, btn_startPause_callback);

	button_enable(&btn_inc);
	button_enable(&btn_dec);
	button_enable(&btn_startPause);

	led_init(&led_red, LedRedInit, LedRedOn, LedRedOff);
	led_init(&led_green, LedGreenInit, LedGreenOn, LedGreenOff);
	led_init(&led_yellow, LedYellowInit, LedYellowOn, LedYellowOff);


	Blinky1_instance();
	static LTK_Evt_t const * blink1QSto[10];
	LTK_Task_start( AO_blinky1,
					2,
			        blink1QSto ,
					sizeof(blink1QSto) / sizeof(blink1QSto[0]),
					(void *)0);



	LTK_onStart();
	return LTK_Task_run();
}
