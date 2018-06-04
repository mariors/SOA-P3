//
// Created by mario on 01/06/18.
//

#ifndef SOA_P3_SCHEDULER_RESULT_H
#define SOA_P3_SCHEDULER_RESULT_H

#include "task_set.h"

typedef struct scheduler_result_item {
    int running_task_id;

    int* arriving_tasks;
    int arriving_task_size;

} scheduler_result_item;

typedef struct scheduler_result {

    int is_schedulable;
    task_set *tasks;

    scheduler_result_item* simulation;
    int simulation_length; // could be calculated as MCM of task's lapse

} scheduler_result;

scheduler_result_item* create_result_item (int,int*,int);
void add_scheudler_result_item(scheduler_result*,scheduler_result_item*);

void free_scheduler_result_item();
void free_scheduler_result();

#endif //SOA_P3_SCHEDULER_RESULT_H
