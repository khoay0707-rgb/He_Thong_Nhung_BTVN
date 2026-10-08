
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdint.h>

/* Thong tin LED */
typedef struct
{
    uint16_t pin;
    uint32_t frequency_x10;
} LED_Config_t;

/* Khoi tao PA0, PA1, PA2 */
void LED_Init(void)
{
    /* Cap clock cho GPIOA */
    RCC->APB2ENR |= (1U << 2);

    /* PA0, PA1, PA2: output push-pull 2MHz */
    GPIOA->CRL &= ~0x00000FFFU;
    GPIOA->CRL |=  0x00000222U;

    /* Tat 3 LED ban dau */
    GPIOA->BRR = (1U << 0) |
                 (1U << 1) |
                 (1U << 2);
}

/*
 * Ham nhap nhay LED
 * pin: chan LED
 * frequency_x10: tan so nhan 10
 *
 * 1  = 0.1Hz
 * 10 = 1Hz
 * 100 = 10Hz
 */
void LED_Blink(uint16_t pin, uint32_t frequency_x10)
{
    uint32_t half_ms;
    TickType_t half_ticks;
    TickType_t last_wake;

    if (frequency_x10 == 0U)
    {
        vTaskDelete(NULL);
        return;
    }

    half_ms = 5000U / frequency_x10;
    half_ticks = pdMS_TO_TICKS(half_ms);

    if (half_ticks == 0)
        half_ticks = 1;

    last_wake = xTaskGetTickCount();

    while (1)
    {
        /* Bat LED */
        GPIOA->BSRR = pin;
        vTaskDelayUntil(&last_wake, half_ticks);

        /* Tat LED */
        GPIOA->BRR = pin;
        vTaskDelayUntil(&last_wake, half_ticks);
    }
}

/* Task 1: PA0 - 0.1Hz */
void Task_LED1(void *pvParameters)
{
    (void)pvParameters;
    LED_Blink(1U << 0, 1);
}

/* Task 2: PA1 - 1Hz */
void Task_LED2(void *pvParameters)
{
    (void)pvParameters;
    LED_Blink(1U << 1, 10);
}

/* Task 3: PA2 - 10Hz */
void Task_LED3(void *pvParameters)
{
    (void)pvParameters;
    LED_Blink(1U << 2, 100);
}

int main(void)
{
    BaseType_t status1;
    BaseType_t status2;
    BaseType_t status3;

    SystemCoreClockUpdate();
    LED_Init();

    /* Tao 3 task doc lap */
    status1 = xTaskCreate(
        Task_LED1,
        "LED_0.1Hz",
        128,
        NULL,
        1,
        NULL
    );

    status2 = xTaskCreate(
        Task_LED2,
        "LED_1Hz",
        128,
        NULL,
        1,
        NULL
    );

    status3 = xTaskCreate(
        Task_LED3,
        "LED_10Hz",
        128,
        NULL,
        1,
        NULL
    );

    if ((status1 == pdPASS) &&
        (status2 == pdPASS) &&
        (status3 == pdPASS))
    {
        vTaskStartScheduler();
    }

    /* Loi tao task hoac scheduler */
    while (1)
    {
    }
}
