#include "task_scheduler.h"

static int initialize_scheduler(struct TaskList *tasks, struct TaskProfile **profile, struct PriorityMap **priorities, int *core_count, int *error)
{
    *profile = profile_tasks(tasks);
    if (!*profile) {
        *error = 1;
        return 0;
    }

    *priorities = compute_priorities_mock(*profile);
    if (!*priorities) {
        *error = 1;
        return 0;
    }

    *core_count = get_available_core_count();
    if (*core_count <= 0) {
        *error = 1;
        return 0;
    }

    return 1;
}

static struct ScheduleResult *assign_tasks(struct TaskProfile *profile, int core_count, int *error)
{
    struct ScheduleResult *result = create_schedule_result(core_count);
    if (!result) {
        *error = 1;
        return NULL;
    }

    int core = 0;
    while (!*error && core < core_count) {
        int task_id = select_best_task(profile);
        if (task_id == -1) {
            *error = 1;
        } else {
            update_schedule_entry(result, core, task_id);
        }
        core++;
    }
    return result;
}

struct ScheduleResult *schedule_tasks(struct TaskList *tasks)
{
    struct TaskProfile *profile = NULL;
    struct PriorityMap *priorities = NULL;
    struct ScheduleResult *result = NULL;
    int core_count = 0;
    int error = 0;

    if (initialize_scheduler(tasks, &profile, &priorities, &core_count, &error))
        result = assign_tasks(profile, core_count, &error);

    if (priorities)
        free_priority_map(priorities);
    if (profile)
        free_task_profile(profile);

    if (error) {
        if (result)
            free_schedule_result(result);
        result = NULL;
    }

    return result;
}