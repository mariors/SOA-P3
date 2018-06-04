//
// Created by jdsalazar on 03/06/18.
//

#include "../headers/scheduler.h"

#define FINISHED 2
#define CRASHED 3

void calculate_fix_length(scheduler_result *r){
    r->fix_length = r->simulation_length;
    for(int i = 0; i < r->simulation_length; i++){
        if(r->simulation[i].status == FINISHED || r->simulation[i].status == CRASHED){
            r->fix_length = i;
            break;
        }
        printf("%d\n",r->simulation[i].status);
    }

}

results schedule(task_set *set) {
    scheduler_result res_rm, res_edf, res_llf;
    if (set->is_rm == 1) {
        res_rm = scheduler_simulator(set, RM);
        calculate_fix_length(&res_rm);
    }
    if (set->is_edf == 1) {
        res_edf = scheduler_simulator(set, EDF);
        calculate_fix_length(&res_edf);
    }
    if (set->is_llf == 1) {
        res_llf = scheduler_simulator(set, LLF);
        calculate_fix_length(&res_llf);
    }
    results res = {.is_rm = set->is_rm, .is_edf = set->is_edf, .is_llf = set->is_llf, .rm_result = res_rm, .edf_result = res_edf, .llf_result = res_llf};
    return res;
}

scheduler_result schedule_old(task_set *set, Algorithm algorithm) {
    scheduler_result res = scheduler_simulator(set, algorithm);
    int is_sched = is_schedulable(set, algorithm);
    scheduler_result result = {.simulation = res.simulation, .simulation_length = res.simulation_length, .tasks = set, .is_schedulable = is_sched, .task_size = set->size};
    return result;
}

scheduler_result scheduler_simulator(task_set *set, Algorithm algorithm) {

    int steps = lcm(set);
    int size = set->size;

    int is_sched = is_schedulable(set, algorithm);

    scheduler_result_item *moments = (scheduler_result_item *) calloc(steps - 1, sizeof(scheduler_result));
    int interesting_moments[steps - 1];

    int ids[size], computes[size], periods[size], left_c[size], left_p[size], waiting[size], arriving[size];

    task *tasks = set->tasks;
    for (int i = 0; i < size; i++) {
        task t = *(tasks + i);
        ids[i] = t.id;
        computes[i] = t.e;
        left_c[i] = t.e;
        periods[i] = t.p;
        left_p[i] = t.p;
        waiting[i] = 1;
        arriving[i] = 0;
    }

    int current_idx = scheduled_idx(periods, waiting, left_c, left_p, size, algorithm);

//    int current_task_id = ids[current_idx];

    waiting[current_idx] = 0;

    int needs_schedule = 0;

    for (int t = 1; t <= steps; t++) {

//        printf("SCH Tiempo t = %d\n", t);

        //time management

        left_c[current_idx]--;

        for (int i = 0; i < size; i++) {
            left_p[i]--;
        }

        //check for crashes in not current tasks

        int crashed = 0;
        int crashed_idx = -1;

        for (int i = 0; i < size; i++) {
            if (i == current_idx) {
                continue;
            }
            if (left_p[i] == 0) {
                if (waiting[i] == 1) {
                    //CRASH
                    //TODO MAKE SIMULATION ENTRY
                    crashed = 1;
                    crashed_idx = i;
                } else {
                    arriving[i] = 1;
                    waiting[i] = 1;
                    left_p[i] = periods[i];
                    needs_schedule = 1;
                }
            } else {
                arriving[i] = 0;
            }
        }

        if (crashed == 1) {
            scheduler_result_item moment = make_moment(arriving, ids, size, t, current_idx, crashed_idx, CRASHED);
            moments[t - 1] = moment;
            interesting_moments[t - 1] = 1;
//            scheduler_temp_result result = {.interest_times = interesting_moments, .simulation = moments, .simulation_length = steps};
            scheduler_result result = {.simulation = moments, .simulation_length = steps, .tasks = set, .is_schedulable = is_sched, .task_size = size};
            return result;
        }

        //current task handling

        if (left_c[current_idx] > 0) {
            if (left_p[current_idx] == 0) {
                //CRASH
                //TODO MAKE SIMULATION ENTRY
                scheduler_result_item moment = make_moment(arriving, ids, size, t, current_idx, current_idx, CRASHED);
                moments[t - 1] = moment;
                interesting_moments[t - 1] = 1;
//                scheduler_temp_result result = {.interest_times = interesting_moments, .simulation = moments, .simulation_length = steps};
                scheduler_result result = {.simulation = moments, .simulation_length = steps, .tasks = set, .is_schedulable = is_sched, .task_size = size};
                return result;
            } else {
                scheduler_result_item moment = make_moment(arriving, ids, size, t, current_idx, -1, RUNNING);
                moments[t - 1] = moment;
                if (needs_schedule == 0) {
                    interesting_moments[t - 1] = 0;
                    continue;
                } else {
                    interesting_moments[t - 1] = 1;

                    waiting[current_idx] = 1;
                    current_idx = scheduled_idx(periods, waiting, left_c, left_p, size, algorithm);
                    needs_schedule = 0;
                    waiting[current_idx] = 0;
                    //TODO MAKE SIMULATION ENTRY
                }
            }
        } else {
            left_c[current_idx] = computes[current_idx];
            if (left_p[current_idx] == 0) {
                waiting[current_idx] = 1;
                left_p[current_idx] = periods[current_idx];
                arriving[current_idx] = 1;
            }

            int all_done = 1;

            for (int i = 0; i < size; i++) {
                if (waiting[i] == 1) {
                    all_done = 0;
                    break;
                }
            }

            if (all_done == 1) {
                scheduler_result_item moment = make_moment(arriving, ids, size, t, current_idx, -1, FINISHED);
                moments[t - 1] = moment;
                interesting_moments[t - 1] = 1;
//                scheduler_temp_result result = {.interest_times = interesting_moments, .simulation = moments, .simulation_length = steps};
                scheduler_result result = {.simulation = moments, .simulation_length = steps, .tasks = set, .is_schedulable = is_sched, .task_size = size};
                return result;
            }

            if ((t + 1) == steps) {
                int all_finished = 1;
                for (int i = 0; i < size; i++) {
                    if (left_p[i] != periods[i]) {
                        all_finished = 0;
                        break;
                    }
                }
                if (all_finished == 0) {
                    //SOMETHING WRONG HAPPENED
                } else {
                    //FINISHED SUCCESSFULLY
                    //TODO MAKE SIMULATION ENTRY
                    scheduler_result_item moment = make_moment(arriving, ids, size, t, current_idx, -1, FINISHED);
                    moments[t - 1] = moment;
                    interesting_moments[t - 1] = 1;
//                    scheduler_temp_result result = {.interest_times = interesting_moments, .simulation = moments, .simulation_length = steps};
                    scheduler_result result = {.simulation = moments, .simulation_length = steps, .tasks = set, .is_schedulable = is_sched, .task_size = size};
                    return result;
                }
            }
            scheduler_result_item moment = make_moment(arriving, ids, size, t, current_idx, -1, RUNNING);
            moments[t - 1] = moment;
            interesting_moments[t - 1] = 1;

            current_idx = scheduled_idx(periods, waiting, left_c, left_p, size, algorithm);
            needs_schedule = 0;
            waiting[current_idx] = 0;
            //TODO MAKE SIMULATION ENTRY
        }
    }
//    scheduler_temp_result result = {.interest_times = interesting_moments, .simulation = moments, .simulation_length = steps};
    scheduler_result result = {.simulation = moments, .simulation_length = steps, .tasks = set, .is_schedulable = is_sched, .task_size = size};
    return result;
}

int scheduled_idx(int periods[], int waiting[], int left_c[], int left_p[], int size, Algorithm algorithm) {
    switch (algorithm) {
        case RM:
            return scheduled_idx_rm(periods, waiting, size);
        case EDF:
            return scheduled_idx_edf(left_p, waiting, size);
        case LLF:
            return scheduled_idx_llf(left_c, left_p, waiting, size);
    }
    return -1;
}

int scheduled_idx_rm(int periods[], int waiting[], int size) {
    int min = -1;
    int idx = 0;
    for (int i = 0; i < size; i++) {
        if (waiting[i] == 1) {
            if (min == -1 || periods[i] < min) {
                min = periods[i];
                idx = i;
            }
        }
    }
    return idx;
}

int scheduled_idx_edf(int left_p[], int waiting[], int size) {
    int min = -1;
    int idx = 0;
    for (int i = 0; i < size; i++) {
        if (waiting[i] == 1) {
            if (min == -1 || left_p[i] < min) {
                min = left_p[i];
                idx = i;
            }
        }
    }
    return idx;
}

int scheduled_idx_llf(int left_c[], int left_p[], int waiting[], int size) {
    int min = -1;
    int idx = 0;
    for (int i = 0; i < size; i++) {
        if (waiting[i] == 1) {
            int lax = left_p[i] - left_c[i];
            if (min == -1 || lax < min) {
                min = lax;
                idx = i;
            }
        }
    }
    return idx;
}

scheduler_result_item
make_moment(int arrivals[], int ids[], int size, int time, int current_idx, int crashed_idx, Status status) {
    int crash_id = -1;
    if (crashed_idx >= 0) {
        crash_id = ids[crashed_idx];
    }
    int positives = 0;
    for (int i = 0; i < size; i++) {
        if (arrivals[i] == 1) {
            positives++;
        }
    }

    if (positives == 0) {
        scheduler_result_item moment = {.time = time, .running_task_id = ids[current_idx], .crashed_task_id = crash_id, .status = status, .arriving_task_size = 0};
        return moment;
    }

    int copy[positives];
    int copy_idx = 0;

    for (int i = 0; i < size; i++) {
        if (arrivals[i] == 1) {
            copy[copy_idx] = ids[i];
            copy_idx++;
        }
    }

    int *arrivings = copy;

    scheduler_result_item moment = {.time = time, .running_task_id = ids[current_idx], .crashed_task_id = crash_id, .status = status, .arriving_task_size = positives, .arriving_tasks = arrivings};
    return moment;

}

int is_schedulable(task_set *set, Algorithm algorithm) {
    switch (algorithm) {
        case RM:
            return test_rm(set);
        case EDF:
            return test_edf(set);
        case LLF:
            return test_bini(set);
    }
    return -1;
}


