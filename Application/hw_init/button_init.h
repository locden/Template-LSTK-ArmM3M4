#ifndef BUTTON_POLLING_H_
#define BUTTON_POLLING_H_

#include "button.h"
#include "main.h"

extern void btn_inc_init();
extern uint8_t btn_inc_read();


extern void btn_dec_init();
extern uint8_t btn_dec_read();


extern void btn_startPause_init();
extern uint8_t btn_startPause_read();

#endif /* BUTTON_POLLING_H_ */
