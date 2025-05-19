#ifndef EXAMPLE_BLINK1_H_
#define EXAMPLE_BLINK1_H_

#include "app_main.h"
#include "task.h"
#include "timer.h"

enum Signals {
    TIMEOUT1_SIG,
    TIMEOUT2_SIG,
	BUTTON_INC_PRESSED,
	BUTTON_INC_RELEASE,
    /* ... */
    MAX_SIG  /* the last signal */
};


typedef struct {

	LTK_Task_t super;
	LTK_TimeEvt_t te;

} Blinky_1_t;

extern void Blinky1_instance(void);
extern LTK_Task_t * const AO_blinky1;


#endif /* EXAMPLE_BLINK1_H_ */
