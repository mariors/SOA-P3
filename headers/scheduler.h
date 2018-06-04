//
// Created by mario on 31/05/18.
//

#ifndef PROJECT3_RM_H
#define PROJECT3_RM_H

#include "../headers/scheduler_result.h"
#include "../headers/tests.h"

typedef enum {RM = 0, EDF = 1, LLF = 2} Algorithm;

typedef struct scheduler_temp_result {

    scheduler_result_item* simulation;
    int simulation_length;

    int* interest_times;


} scheduler_temp_result;

results schedule(task_set* set);
scheduler_result schedule_old(task_set* set, Algorithm algorithm);
scheduler_result scheduler_simulator(task_set* set, Algorithm algorithm);
int scheduled_idx(int periods[], int waiting[], int left_c[], int left_p[], int size, Algorithm algorithm);
int scheduled_idx_rm(int periods[], int waiting[], int size);
int scheduled_idx_edf(int left_p[], int waiting[], int size);
int scheduled_idx_llf(int left_c[], int left_p[], int waiting[], int size);
scheduler_result_item make_moment(int arrivals[], int ids[], int size, int time, int current_idx, int crashed_idx, Status status);
int is_schedulable(task_set* set, Algorithm algorithm);


#endif //PROJECT3_RM_H
