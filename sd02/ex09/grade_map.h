#ifndef GRADE_MAP_H
#define GRADE_MAP_H

typedef const char *(*GradeMapper)(int score);

typedef struct GradeNode {
    char *grade;
    int count;
    struct GradeNode *next;
} GradeNode;

void map_scores(const int *scores, int size, GradeMapper mapper, const char **mapped_grades);
GradeNode *compute_distribution(const char **mapped_grades, int size);
void print_distribution(GradeNode *head);
void free_distribution(GradeNode *head);
const char* standard_mapper(int score);
const char* passfail_mapper(int score);
const char* plusminus_mapper(int score);

#endif