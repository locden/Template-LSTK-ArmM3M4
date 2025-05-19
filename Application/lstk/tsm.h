#ifndef LTK_TSM_H_
#define LTK_TSM_H_

#include "app_main.h"
#include "task.h"

typedef enum { TRAN_STATUS, HANDLED_STATUS, IGNORED_STATUS, INIT_STATUS } State;

typedef struct tsm_t tsm_t;

#define TSM_TRAN(target_) (((fsm_t *)me)->State = (StateHandler *)target_ , TRAN_STATUS)

typedef State (* StateHandlerTable)(struct tsm_t * const me, LTK_Evt_t const * const e);


struct tsm_t
{
	uint8_t State;
	StateHandlerTable **table;
};

void Tsm_ctor(struct tsm_t * const me, StateHandlerTable ** table, uint8_t firstState);

void Tsm_dispatcher(struct tsm_t * const me, LTK_Evt_t const * const e);




#endif /* LTK_TSM_H_ */
