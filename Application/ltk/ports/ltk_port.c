#include "ltk_port.h"
#include "app_main.h"
#include "timer.h"
void LTK_onIdleCond()
{

#ifdef NDEBUG
    /* Put the CPU and peripherals to the low-power mode.
    * you might need to customize the clock management for your application,
    * see the datasheet for your particular Cortex-M MCU.
    */
    __WFI(); /* Wait-For-Interrupt */
#endif
    LTK_PORT_INT_ENABLE(); /* NOTE: enable interrupts for LTK */
}

void LTK_onStart()
{
	SysTick_Config((SystemCoreClock / BSP_TICKS_PER_SEC) + 1U);

    /* set priorities of ISRs used in the system */
    NVIC_SetPriority(SysTick_IRQn, 0U);
}

void SysTick_Handler(void)
{
	LTK_TimeEvt_tick();
}

