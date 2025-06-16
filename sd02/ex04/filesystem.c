#include "filesystem.h"

FSNode *create_file(const char *name, int size)
{
    FSNode *file = (FSNode *)malloc(sizeof(FSNode));
    if (!file) {
        return NULL;
    }
    file->name = strdup(name);
    if (!file->name) {
        free(file);
        return NULL;
    }
    file->size = size;
    file->parent = NULL;
    file->first_children = NULL;
    file->next_sibling = NULL;
    return file;
}

FSNode *create_folder(const char *name)
{
    FSNode *folder = (FSNode *)malloc(sizeof(FSNode));
    if (!folder) {
        return NULL;
    }
    folder->name = strdup(name);
    if (!folder->name) {
        free(folder);
        return NULL;
    }
    folder->size = 0;
    folder->parent = NULL;
    folder->first_children = NULL;
    folder->next_sibling = NULL;
    return folder;
}

void add_child(FSNode *parent, FSNode *child)
{
    if (!parent || !child) {
        return;
    }

    child->parent = parent;
    child->next_sibling = parent->first_children;
    parent->first_children = child;
}

FSNode *get_children(const FSNode *parent)
{
    if (!parent) {
        return NULL;
    }
    return parent->first_children;
}

FSNode *get_sibling(const FSNode *node)
{
    if (!node || !node->next_sibling) {
        return NULL;
    }
    return node->next_sibling;
}

