#include "grade_map.h"

#include <stdio.h>
#include <stdlib.h>

static const char* standard_mapper(int score)
{
    if (score >= 90)
        return "A";
    if (score >= 80)
        return "B";
    if (score >= 70)
        return "C";
    if (score >= 60)
        return "D";
    return "F";
}

static const char* passfail_mapper(int score)
{
    if (score >= 60)
        return "P";
    return "F";
}

static const char* plusminus_mapper(int score)
{
    if (score >= 97)
        return "A+";
    if (score >= 93)
        return "A";
    if (score >= 90)
        return "A-";
    if (score >= 87)
        return "B+";
    if (score >= 83)
        return "B";
    if (score >= 80)
        return "B-";
    if (score >= 77)
        return "C+";
    if (score >= 73)
        return "C";
    if (score >= 70)
        return "C-";
    if (score >= 67)
        return "D+";
    if (score >= 63)
        return "D";
    if (score >= 60)
        return "D-";
    return "F";
}

void map_scores(const int *scores, int size, GradeMapper mapper, const char **mapped_grades)
{
    for (int i = 0; i < size; i++) {
        mapped_grades[i] = mapper(scores[i]);
    }
}

int main() {
    // Example usage
    int scores[] = {99, 85, 75, 65, 55};
    const int size = sizeof(scores) / sizeof(scores[0]);
    const char *mapped_grades[size];

    // Using standard mapper
    map_scores(scores, size, plusminus_mapper, mapped_grades);
    for (int i = 0; i < size; i++) {
        printf("Score: %d, Grade: %s\n", scores[i], mapped_grades[i]);
    }

    return 0;
}