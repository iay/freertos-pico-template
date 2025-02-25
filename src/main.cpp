#include <stdio.h>
#include "pico/stdlib.h"

#include "FreeRTOS.h"
#include "task.h"

void firstTask(void *pvParameters)
{
    while (true) {
        printf("First task\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void secondTask(void *pvParameters)
{
    while (true) {
        printf("Second task\n");
        vTaskDelay(pdMS_TO_TICKS(950));
    }
}

int main()
{
    stdio_init_all();

    auto result1 = xTaskCreate(firstTask, "First Task", 1024, NULL, 1, NULL);
    if (result1 != pdPASS) {
        printf("Failed to create task\n");
        return 1;
    }
    
    auto result = xTaskCreate(secondTask, "Second Task", 1024, NULL, 1, NULL);
    if (result != pdPASS) {
        printf("Failed to create task\n");
        return 1;
    }

    /* Start the tasks and timer running. */
    vTaskStartScheduler(); // Does not return

    return 0;
}
