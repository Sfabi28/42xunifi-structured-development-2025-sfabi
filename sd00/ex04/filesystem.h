#ifndef FILESYSTEM_H
# define FILESYSTEM_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

struct FSNode {
    char *name;
    int size;
    struct FSNode *parent;
    struct FSNode *children;
    struct FSNode *next_sibling;
} FSNode;


FSNode *create_file(const char *name, int size);
FSNode *create_folder(const char *name);
void add_child(FSNode *parent, FSNode *child);
FSNode *get_children(const FSNode *parent);
FSNode *get_sibling(const FSNode *node);