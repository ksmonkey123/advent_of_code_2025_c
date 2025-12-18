#include "linked_list.h"

#include <stdlib.h>

void ll_append(struct LinkedList *list, void *data) {
    struct ll_node *node = malloc(sizeof(struct ll_node));
    node->data = data;
    node->next = NULL;

    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
}

void ll_destroy(struct LinkedList *list) {
    // destroy all nodes
    struct ll_node *node = list->head;
    while (node != NULL) {
        struct ll_node *next = node->next;
        free(node->data);
        free(node);
        node = next;
    }
    // drop now invalid refs
    list->head = NULL;
    list->tail = NULL;
}
