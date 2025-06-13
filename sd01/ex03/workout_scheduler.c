#include "workout_scheduler.h"

struct WorkoutPlan *create_workout_schedule(char *username)
{
    struct Userdata *user_data = get_user_data(username);
    if (!user_data)
        return NULL;

    struct WorkoutPlan *plan = build_base_plan(user_data);
    if (!plan) {
        free_user_data(user_data);
        return NULL;
    }

    plan = refine_plan(plan, user_data);
    if (!plan) {
        free_user_data(user_data);
        return NULL;
    }

    int days = determine_duration(plan);
    if (days <= 0) {
        free_workout_plan(plan);
        free_user_data(user_data);
        return NULL;
    }

    for (int day = 1; day <= days; ++day) {
        assign_daily_exercises(plan, day);
        assign_daily_tips(plan, day);
    }

    free_user_data(user_data);
    return plan;
}