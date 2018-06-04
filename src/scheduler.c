//
// Created by jdsalazar on 03/06/18.
//

#include "../headers/scheduler.h"
#include "../headers/scheduler_result.h"
#include "../headers/tests.h"

/*
scheduler_result_item* scheduler_simulator(task_set* set, Algorithm algorithm){

    int steps = lcm(set);
    int size = set->size;

    int ids[size], computes[size], periods[size], left_c[size], left_p[size], waiting[size];

    task* tasks = set->tasks;
    for(int i = 0; i < size; i++){
        task t = *(tasks + i);
        ids[i] = t.id;
        computes[i] = t.e;
        left_c[i] = t.e;
        periods[i] = t.p;
        left_p[i] = t.p;
        waiting[i] = 1;
    }

    int current_idx = scheduled_idx(periods, waiting, left_c, left_p, size, algorithm);

    int current_task_id = ids[current_idx];

    waiting[current_idx] = 0;

    int needs_schedule = 0;

    for(t = 1; t < steps; t++){

        //time management

        left_c[current_idx]--;

        for(int i = 0; i < size; i++){
            left_p[i]--;
        }

        //check for crashes in not current tasks

        for(int i = 0; i < size; i++){
            if(i == current_idx){
                continue;
            }
            if(left_p[i] == 0){
                if(waiting[i] == 1){
                    //CRASH
                    //TODO MAKE SIMULATION ENTRY
                }else{
                    waiting[i] = 1;
                    left_p[i] = periods[i];
                    needs_schedule = 1;
                }
            }
        }

        //current task handling

        if(left_c[current_idx] > 0){
            if(left_p[current_idx] == 0){
                //CRASH
                //TODO MAKE SIMULATION ENTRY
            }else{
                if(needs_schedule == 0) {
                    continue;
                }else{
                    waiting[current_idx] = 1;
                    current_idx = scheduled_idx(periods, waiting, left_c, left_p, size, algorithm);
                    needs_schedule = 0;
                    current_task_id = ids[current_idx];
                    waiting[current_idx] = 0;
                    //TODO MAKE SIMULATION ENTRY
                }
            }
        }else{
            left_c[current_idx] = computes[current_idx];
            if(left_p[current_idx] == 0){
                waiting[current_idx] = 1;
                left_p[current_idx] = periods[current_idx];
            }
            if((t + 1) == steps){
                int all_finished = 1;
                for(int i = 0; i < size; i++){
                    if(left_p[i] != periods[i]){
                        all_finished = 0;
                        break;
                    }
                }
                if(all_finished == 0){
                    //SOMETHING WRONG HAPPENED
                }else{
                    //FINISHED SUCCESSFULLY
                    //TODO MAKE SIMULATION ENTRY
                }
            }
            current_idx = scheduled_idx(periods, waiting, left_c, left_p, size, algorithm);
            needs_schedule = 0;
            current_task_id = ids[current_idx];
            waiting[current_idx] = 0;
            //TODO MAKE SIMULATION ENTRY
        }
    }
}

int scheduled_idx(int periods[], int waiting[], int left_c[], int left_p[], int size, Algorithm algorithm){
    switch (algorithm){
        case RM:
            return scheduled_idx_rm(periods, waiting, size);
        case EDF:
            return scheduled_idx_edf(left_p, waiting, size);
        case LLF:
            return scheduled_idx_llf(left_c, left_p, waiting, size);
    }
}

int scheduled_idx_rm(int periods[], int waiting[], int size){
    int min = -1;
    int idx = 0;
    for(int i = 0; i < size; i++){
        if(waiting[i] == 1){
            if(min == -1 || periods[i] < min){
                min = periods[i];
                idx = i;
            }
        }
    }
    return idx;
}

int scheduled_idx_edf(int left_p[], int waiting[], int size){
    int min = -1;
    int idx = 0;
    for(int i = 0; i < size; i++){
        if(waiting[i] == 1){
            if(min == -1 || left_p[i] < min){
                min = left_p[i];
                idx = i;
            }
        }
    }
    return idx;
}

int scheduled_idx_llf(int left_c[], int left_p[], int waiting[], int size){
    int min = -1;
    int idx = 0;
    for(int i = 0; i < size; i++){
        if(waiting[i] == 1){
            int lax = left_p[i] - left_c[i];
            if(min == -1 || lax < min){
                min = lax;
                idx = i;
            }
        }
    }
    return idx;
}
*/

