//
// Created by jdsalazar on 03/06/18.
//

#include "../headers/tests.h"


int test_rm(task_set* set){
    float sum = calculate_sum(set);
    float u = calculate_U(set->size);
    if(sum <= u){
        return 1;
    }else{
        return 0;
    }
}

int test_edf(task_set* set){
    float sum = calculate_sum(set);
    if(sum <= 1f){
        return 1;
    }else{
        return 0;
    }
}

int test_bini(task_set* set){
    float prod = calculate_prod(set);
    if(prod <= 2f){
        return 1;
    }else{
        return 0;
    }
}

float calculate_U(int set_size){
    return (float)set_size * (pow(2.0,(1/(float)set_size))-1);
}

float calculate_sum(task_set* set){
    float sum = 0f;
    task* tasks = set->tasks;
    for(int i = 0; i < set->size; i++){
        task t = *(tasks + i);
        sum += (float)t.e/(float)t.p;
    }
    return sum;
}

float calculate_prod(task_set* set){
    float prod = 1f;
    task* tasks = set->tasks;
    for(int i = 0; i < set->size; i++){
        task t = *(tasks + i);
        prod *= ((float)t.e/(float)t.p) + 1;
    }
    return prod;
}

int lcm(task_set* set){
    int max, step;

    max = 0;
    step = 0;

    task* tasks = set->tasks;
    for(int i = 0; i < set->size; i++){
        task t = *(tasks + i);
        if(t.p > max){
            max = t.p;
            step = t.p;
        }
    }

    while(1) {
        int decision = are_divisible(set, max);
        if(decision == 1) {
            return max;
        }

        max += step;
    }
}

int are_divisible(task_set* set, int max){
    task* tasks = set->tasks;
    for(int i = 0; i < set->size; i++){
        task t = *(tasks + i);
        if(max%t.p != 0){
            return 0;
        }
    }
    return 1;
}