/**
 * Creating a generic linked list class using C.
 * 
 * Svita Kiran
 * 10/30/2025
 * CS333
*/

#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>

LinkedList *ll_create() {
    LinkedList *l = malloc(sizeof(LinkedList));
    l->head = NULL;
    l->size = 0;
    return l;
}

void ll_push(LinkedList *l, void *data) {
    Node *new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = l->head;
    l->head = new_node;
    l->size++;
}

void *ll_pop(LinkedList *l) {
    if (l->head == NULL) {
        return NULL;
    }
    Node *temp = l->head;
    void *data = temp->data;
    l->head = l->head->next;
    free(temp);
    l->size--;
    return data;
}

void ll_append(LinkedList *l, void *data) {
    Node *new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    if (l->head == NULL) {
        l->head = new_node;
    } else {
        Node *current = l->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    l->size++;
}

void *ll_remove(LinkedList *l, void *target, int (*compfunc)(void *, void *)) {
    Node *current = l->head;
    Node *previous = NULL;
    while (current != NULL) {
        if (compfunc(current->data, target) == 0) {
            if (previous == NULL) {
                l->head = current->next;
            } else {
                previous->next = current->next;
            }
            void *data = current->data;
            free(current);
            l->size--;
            return data;
        }
        previous = current;
        current = current->next;
    }
    return NULL;
}

void *ll_find(LinkedList *l, void *target, int (*compfunc)(void *, void *)) {
    Node *current = l->head;
    while (current != NULL) {
        if (compfunc(current->data, target) == 0) {
            return current->data;
        }
        current = current->next;
    }
    return NULL;
}

int ll_size(LinkedList *l) {
    return l->size;
}

void ll_clear(LinkedList *l, void (*freefunc)(void *)) {
    Node *current = l->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        if (freefunc != NULL) {
            freefunc(temp->data);
        }
        free(temp);
    }
    l->head = NULL;
    l->size = 0;
}

void ll_map(LinkedList *l, void (*mapfunc)(void *)) {
    Node *current = l->head;
    while (current != NULL) {
        mapfunc(current->data);
        current = current->next;
    }
}