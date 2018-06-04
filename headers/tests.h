//
// Created by jdsalazar on 03/06/18.
//

#ifndef SOA_P3_TESTS_H
#define SOA_P3_TESTS_H

#include "task_set.h"
#include "scheduler_result.h"
#include <math.h>

int test_rm(task_set* set);
int test_edf(task_set* set);
int test_bini(task_set* set);
float calculate_U(int set_size);
float calculate_sum(task_set* set);
float calculate_prod(task_set* set);
int lcm(task_set* set);
int are_divisible(task_set* set, int max);

#endif //SOA_P3_TESTS_H
