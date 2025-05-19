#include "observer.h"
#include "sys_assert.h"

void LTK_observerInit(obs_sub_t * sub, LTK_Signal sig)
{
	sub->super.sig = sig;
	sub->list_count = 0U;
}
bool LTK_observerAttach(obs_sub_t * sub, LTK_Task_t * node)
{
	if(sub->list_count > MAX_NODE - 1)
	{
		return false;
	}

	sub->list_node[sub->list_count++] = node;

	return true;
}
bool LTK_observerDetach(obs_sub_t * sub, LTK_Task_t * node)
{
	for(uint8_t i = 0; i <= sub->list_count; i++)
	{
		if(sub->list_node[i] == node)
		{
			for(uint8_t j = i; j <= sub->list_count; j++)
			{
				sub->list_node[j] = sub->list_node[j + 1];
			}
			--sub->list_count;
			return true;
			break;
		}
	}
	return false;
}

void LTK_observerNotify(obs_sub_t * sub, LTK_Evt_t const * const e)
{
	for(uint8_t i = 0; i <= sub->list_count; i++)
	{
		LTK_Task_post( sub->list_node[i] , e );
	}
}
