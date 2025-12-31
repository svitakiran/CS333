/**
 * Header file with all functions for linked list implementation in yourLinkedList.c
 * 
 * Svita Kiran
 * CS333
 * 10/30/2025
*/

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node *head;
    int size;
} LinkedList;


LinkedList *ll_create();

void ll_push(LinkedList *l, void *data);

void *ll_pop(LinkedList *l);

void ll_append(LinkedList *l, void *data);

void *ll_remove(LinkedList *l, void *target, int (*compfunc)(void *, void *));

void *ll_find(LinkedList *l, void *target, int (*compfunc)(void *, void *));

int ll_size(LinkedList *l);

void ll_clear(LinkedList *l, void (*freefunc)(void *));

void ll_map(LinkedList *l, void (*mapfunc)(void *));