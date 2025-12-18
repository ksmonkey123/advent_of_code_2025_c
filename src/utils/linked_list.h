#ifndef AOC_LINKED_LIST_H
#define AOC_LINKED_LIST_H

struct ll_node {
    void* data; // node owns
    struct ll_node* next;
};

struct LinkedList {
    struct ll_node* head;
    struct ll_node* tail;
};

// add data to the end of the list
void ll_append(struct LinkedList* list, void* data);

// destroy the data of the list. the data referenced by the node is destroyed too
void ll_destroy(struct LinkedList* list);

#endif //AOC_LINKED_LIST_H