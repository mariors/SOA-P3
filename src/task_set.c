//
// Created by mario on 31/05/18.
//


#include "../headers/task_set.h"

void add_task(task_set * set, task t) {
    set->size++;
    task* out = realloc(set->tasks,set->size * sizeof(task));
    if(!out)
        perror("An error should be handled! add_task func");
    set->tasks = out;
}

task* get_as_array(const task_set * set) {
    return set->tasks;
}

void free_set(task_set * set) {
    free(set->tasks);
    free(set);
}
