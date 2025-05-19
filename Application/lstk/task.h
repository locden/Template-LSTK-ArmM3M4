#ifndef LTK_TASK_H_
#define LTK_TASK_H_

#include <stdint.h>
#include <stdbool.h>
#include "ports/ltk_port.h"


typedef uint16_t LTK_Signal;

enum ReservedSignals {
	INIT_SIG,		/* dispatched to AO before entering event-loop */
	ENTRY_SIG,		/* for triggering the entry action in a state */
	EXIT_SIG,		/* for triggering the exit action from a state */
	USER_SIG		/* first signal available to the users */
};

typedef struct {

	LTK_Signal sig;
} LTK_Evt_t;


typedef struct LTK_Task_t LTK_Task_t;

typedef void (*LTK_Handler)(LTK_Task_t * const me, LTK_Evt_t const * const e);


struct LTK_Task_t {

	LTK_Handler init;
	LTK_Handler dispatcher;
	uint8_t prio;

	LTK_Evt_t const ** qBuff;
	uint8_t end;
	uint8_t head;
	uint8_t tail;
	uint8_t nUsed;
};

void LTK_Task_ctor(LTK_Task_t * const me, LTK_Handler init, LTK_Handler dispatcher);
void LTK_Task_start(LTK_Task_t * const me,
					uint8_t prio,
					LTK_Evt_t const **qBuff, uint8_t qLen,
					LTK_Evt_t const * const e);
void LTK_Task_post(LTK_Task_t * const me, LTK_Evt_t const * const e);
int LTK_Task_run(void);
#endif /* LTK_TASK_H_ */
