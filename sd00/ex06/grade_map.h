#ifndef GRADE_MAP_H
#define GRADE_MAP_H

typedef const char *(*GradeMapper)(int score);

void map_scores(const int *scores, int size, GradeMapper mapper, const char **mapped_grades);

#endif