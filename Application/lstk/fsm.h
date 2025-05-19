#ifndef LTK_FSM_H_
#define LTK_FSM_H_

#include "task.h"

typedef struct fsm_t fsm_t;

typedef enum { TRAN_STATUS, HANDLED_STATUS, IGNORED_STATUS, INIT_STATUS } State;

typedef State (*StateHandler)(fsm_t * const me, LTK_Evt_t const * const e);

#define FSM_TRAN(target_) (((fsm_t *)me)->State = (StateHandler *)target_ , TRAN_STATUS)

struct fsm_t
{
	StateHandler State; /* the "State variable" */
};

void Fsm_ctor(fsm_t * const me, StateHandler initialize);
void Fsm_dispatcher(fsm_t * const me, LTK_Evt_t const * const e);
void Fsm_init(fsm_t * const me, LTK_Evt_t const * const e);

#endif /* LTK_FSM_H_ */
