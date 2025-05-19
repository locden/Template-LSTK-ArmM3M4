#ifndef APP_H_
#define APP_H_

#include "main.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>




#include "button_init.h"
#include "led_init.h"
#include "lcd_16x2.h"


extern button_t btn_inc;
extern button_t btn_dec;
extern button_t btn_startPause;

extern led_t led_red;
extern led_t led_green;
extern led_t led_yellow;



#endif /* APP_H_ */
