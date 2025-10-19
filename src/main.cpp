#include <stdio.h>
#include "pico/stdlib.h"

#include "FreeRTOS.h"
#include "task.h"

void printThisTask() {
    TaskStatus_t task;
    vTaskGetInfo(NULL, &task, pdTRUE, eInvalid);
    printf("From task '%s' core %d affinity %08x", task.pcTaskName,
      get_core_num(), task.uxCoreAffinityMask);
    printf(" base priority %d HWM %d\n", task.uxBasePriority, task.usStackHighWaterMark);
}

void printTasks() {
    const int max_tasks = 20;
    static TaskStatus_t tasks[max_tasks];
    UBaseType_t task_count = uxTaskGetSystemState(
      tasks,
      max_tasks,
      NULL
    );
    printf("Task list, count: %d\n", task_count);
    for (UBaseType_t t = 0; t < task_count; t++) {
      printf("%d: '%s' affinity %08x priority %d\n", t,
        tasks[t].pcTaskName, tasks[t].uxCoreAffinityMask,
        tasks[t].uxBasePriority);
      printf("   stack base %08x high water %d\n", tasks[t].pxStackBase,
        tasks[t].usStackHighWaterMark);
    }

}

/* Example Application Tasks */
void firstTask(void *pvParameters)
{
    vTaskCoreAffinitySet(NULL, 1 << 0);
    while (true) {
        printThisTask();
        printTasks();
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}

void secondTask(void *pvParameters)
{
    vTaskCoreAffinitySet(NULL, 1 << 1);
    while (true)
    {
        printThisTask();
        vTaskDelay(pdMS_TO_TICKS(950));
    }
}
/* End of Example Application Tasks */

/* Hardware Setup */
void prvSetupHardware(void)
{
    stdio_init_all();
}

int main()
{
    /* Perform any hardware setup necessary. */
    prvSetupHardware();

    /* Example Application Tasks */
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
    /* End of Example Application Tasks */

    /* Start the created tasks running. */
    vTaskStartScheduler(); // Does not return

    /* Execution will only reach here if there was insufficient heap to start the scheduler. */
    for (;;);
    return 0;
}
