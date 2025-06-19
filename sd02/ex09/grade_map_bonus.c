#include "grade_map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GradeNode *compute_distribution(const char **mapped_grades, int size)
{
    GradeNode *head = NULL;
    for (int i = 0; i < size; i++) {
        GradeNode *curr = head;
        while (curr) {
            if (strcmp(curr->grade, mapped_grades[i]) == 0) {
                curr->count++;
                break;
            }
            curr = curr->next;
        }
        if (!curr) {
            GradeNode *new_node = malloc(sizeof(GradeNode));
            new_node->grade = malloc(strlen(mapped_grades[i]) + 1); // ALLOCAZIONE
            strcpy(new_node->grade, mapped_grades[i]);
            new_node->count = 1;
            new_node->next = head;
            head = new_node;
        }
    }
    return head;
}

void print_distribution(GradeNode *head)
{
    GradeNode *curr = head;
    printf("Grade distribution:\n");
    while (curr) {
        printf("Grade %s: %d\n", curr->grade, curr->count);
        curr = curr->next;
    }
}

void free_distribution(GradeNode *head)
{
    while (head) {
        GradeNode *tmp = head;
        head = head->next;
        free(tmp->grade);
        free(tmp);
    }
}