#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include "../headers/scheduler.h"

int main() {
/*
    printf("Hello, World!\n");
    init_documentation();

    return 0;
*/
    task tasks[3];

    tasks[0] = (task){.id = 1, .e = 1, .p = 6};
    tasks[1] = (task){.id = 2, .e = 2, .p = 9};
    tasks[2] = (task){.id = 3, .e = 6, .p = 18};

    task* p = tasks;

    task_set set = {.size = 3, .tasks = p};

//    scheduler_result res = schedule(&set, RM);
    scheduler_temp_result res = scheduler_simulator(&set, RM);

    scheduler_result_item* steps = res.simulation;
    int length = res.simulation_length;
    printf("Length = %d\n", length);

    for(int i = 0; i < length; i++){
        scheduler_result_item step = *(steps + i);
        printf("\nTiempo t = %d\n", step.time);
        printf("Current = %d\n", step.running_task_id);
        printf("Status = %d\n", step.status);
    }

}