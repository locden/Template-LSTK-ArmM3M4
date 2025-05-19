#ifndef LTK_PORTS_LTK_PORT_H_
#define LTK_PORTS_LTK_PORT_H_

#include "app_main.h"

#define BSP_TICKS_PER_SEC 1000U

#define LTK_PORT_TASK_ATTR 				LTK_TaskPrio prio;

#define LTK_PORT_MAX_TASK 				32U

#define LTK_PORT_INT_DISABLE()			__asm volatile ("cpsid i")
#define LTK_PORT_INT_ENABLE()			__asm volatile ("cpsie i")

#define LTK_PORT_CRIT_ENTRY()			LTK_PORT_INT_DISABLE()
#define LTK_PORT_CRIT_EXIT()			LTK_PORT_INT_ENABLE()

typedef uint32_t LTK_ReadySet;

/* special idle callback to handle the "idle condition" in LTK0 */
extern void LTK_onIdleCond(void);
extern void LTK_onStart();

#if (__ARM_ARCH == 6) /* ARMv6-M? */

/* LTK_LOG2() implementation for ARMv6-M (no CLZ instruction) */
static inline uint_fast8_t LTK_LOG2(uint32_t x) {
    static uint8_t const log2LUT[16] = {
        0U, 1U, 2U, 2U, 3U, 3U, 3U, 3U,
        4U, 4U, 4U, 4U, 4U, 4U, 4U, 4U
    };
    uint_fast8_t n = 0U;
    LTK_ReadySet tmp;

    #if (LTK_PORT_MAX_TASK > 16U)
    tmp = (LTK_ReadySet)(x >> 16U);
    if (tmp != 0U) {
        n += 16U;
        x = tmp;
    }
    #endif
    #if (LTK_PORT_MAX_TASK > 8U)
    tmp = (x >> 8U);
    if (tmp != 0U) {
        n += 8U;
        x = tmp;
    }
    #endif
    tmp = (x >> 4U);
    if (tmp != 0U) {
        n += 4U;
        x = tmp;
    }
    return n + log2LUT[x];
}

#else /* ARMv7-M+ have CLZ instruction for fast LOG2 computations */

#if defined __ARMCC_VERSION
    #define LTK_LOG2(x_) ((uint_fast8_t)(32U - __builtin_clz((unsigned)(x_))))
#elif defined __GNUC__
    #define LTK_LOG2(x_) ((uint_fast8_t)(32U - __builtin_clz((unsigned)(x_))))
#elif defined __ICCARM__
    #include <intrinsics.h>
    #define LTK_LOG2(x_) ((uint_fast8_t)(32U - __CLZ((unsigned long)(x_))))
#endif /* compiler type */

#endif

#endif /* LTK_PORTS_LTK_PORT_H_ */
