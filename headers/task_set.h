//
// Created by mario on 31/05/18.
//

#ifndef PROJECT3_TASK_SET_H
#define PROJECT3_TASK_SET_H

#include <stdlib.h>
#include <stdio.h>


typedef struct task{
    int id; // task id
    int e; // execution time
    int p; // task's lapse
} task;

typedef struct task_set{

    int is_rm;
    int is_edf;
    int is_llf;

    int size;
    task* tasks;
} task_set;

void add_task(task_set*, task);
task* get_as_array(const task_set*);
void free_set(task_set*);

#endif //PROJECT3_TASK_SET_H
