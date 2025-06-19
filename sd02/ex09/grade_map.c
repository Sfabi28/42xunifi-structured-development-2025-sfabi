#include "grade_map.h"

const char* standard_mapper(int score)
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

const char* passfail_mapper(int score)
{
    if (score >= 60)
        return "P";
    return "F";
}

const char* plusminus_mapper(int score)
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