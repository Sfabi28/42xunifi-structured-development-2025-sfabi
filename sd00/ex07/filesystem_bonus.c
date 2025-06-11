#include "filesystem.h"

int compute_total_size(FSNode *node)
{
    if (node == NULL) {
        return 0;
    }

    int total_size = node->size;

    FSNode *child = get_children(node);
    while (child != NULL) {
        total_size += compute_total_size(child);
        child = get_sibling(child);
    }

    return total_size;
}

void free_filesystem(FSNode *node)
{
    if (node == NULL) {
        return;
    }

    FSNode *child = get_children(node);
    while (child != NULL) {
        FSNode *temp = get_sibling(child);
        free_filesystem(child);
        child = temp;
    }

    free(node->name);
    free(node);
}

void print_structure(const FSNode *node, int indent)
{
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < indent; i++) {
        printf("  ");
    }

    if (node->size == 0) {
        printf("[Folder] %s\n", node->name);
    } else {
        printf("[File] %s (%d bytes)\n", node->name, node->size);
    }

    FSNode *child = get_children(node);
    while (child != NULL) {
        print_structure(child, indent + 1);
        child = get_sibling(child);
    }
}

