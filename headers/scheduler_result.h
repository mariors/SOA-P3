//
// Created by mario on 01/06/18.
//

#ifndef SOA_P3_SCHEDULER_RESULT_H
#define SOA_P3_SCHEDULER_RESULT_H

#include "task_set.h"

typedef enum {RUNNING = 0, ARRIVAL = 1, FINISHED = 2, CRASHED = 3} Status;

typedef struct scheduler_result_item {
    int time;
    int running_task_id;
    Status status;
    int crashed_task_id;
    int* arriving_tasks;
    int arriving_task_size;

} scheduler_result_item;

typedef struct scheduler_result {

    int is_schedulable;
    task_set *tasks;
    int task_size;

    scheduler_result_item* simulation;
    int simulation_length; // could be calculated as MCM of task's lapse
    int fix_length;

} scheduler_result;

typedef struct results {

    int is_rm;
    int is_edf;
    int is_llf;

    scheduler_result rm_result;
    scheduler_result edf_result;
    scheduler_result llf_result;

    int all_same_sile;

} results;

scheduler_result_item* create_result_item (int,int*,int);
void add_scheudler_result_item(scheduler_result*,scheduler_result_item*);

void free_scheduler_result_item();
void free_scheduler_result();

#endif //SOA_P3_SCHEDULER_RESULT_H
