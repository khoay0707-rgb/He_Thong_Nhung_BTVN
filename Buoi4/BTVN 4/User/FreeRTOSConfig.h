
#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "stm32f10x.h"

#define configUSE_PREEMPTION                 1
#define configUSE_TIME_SLICING               1

#define configCPU_CLOCK_HZ                   (SystemCoreClock)
#define configTICK_RATE_HZ                   1000U
#define configTICK_TYPE_WIDTH_IN_BITS        TICK_TYPE_WIDTH_32_BITS

#define configMAX_PRIORITIES                 5
#define configMINIMAL_STACK_SIZE             128
#define configMAX_TASK_NAME_LEN              16
#define configIDLE_SHOULD_YIELD              1

#define configTOTAL_HEAP_SIZE                (10 * 1024)
#define configSUPPORT_DYNAMIC_ALLOCATION     1
#define configSUPPORT_STATIC_ALLOCATION      0

#define configUSE_IDLE_HOOK                  0
#define configUSE_TICK_HOOK                  0
#define configUSE_MUTEXES                    0
#define configUSE_TIMERS                     0
#define configCHECK_FOR_STACK_OVERFLOW       0
#define configUSE_TRACE_FACILITY             0
#define configUSE_QUEUES                     1

#define configPRIO_BITS                      4

#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY 15
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 5

#define configKERNEL_INTERRUPT_PRIORITY \
    (15 << (8 - configPRIO_BITS))

#define configMAX_SYSCALL_INTERRUPT_PRIORITY \
    (5 << (8 - configPRIO_BITS))

#define INCLUDE_vTaskDelay                   1
#define INCLUDE_xTaskDelayUntil              1
             
#define INCLUDE_vTaskDelete                  1
#define INCLUDE_vTaskSuspend                 1

#define vPortSVCHandler       SVC_Handler
#define xPortPendSVHandler    PendSV_Handler
#define xPortSysTickHandler   SysTick_Handler

#endif
