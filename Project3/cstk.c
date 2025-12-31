#include "cstk.h"
#include <stdlib.h>
#include <stdio.h>

Stack *stk_create(int capacity) {
    Stack *s = malloc(sizeof(Stack));
    s->data = malloc(sizeof(int) * capacity);
    s->top = s->data;
    s->capacity = capacity;
    return s;
}

int stk_empty(Stack *s){
    return s->top == s->data;
}

int stk_full(Stack *s){
    return s->top == s->data + s->capacity;
}

void stk_push(Stack *s, int value){
    if (!stk_full(s)) {
        *(s->top) = value;
        s->top++;
    }
}

int stk_peek(Stack *s){
    if (!stk_empty(s)) {
        return *(s->top - 1);
    }
    return 0;
}

int stk_pop(Stack *s){
    if (!stk_empty(s)) {
        s->top--;
        return *(s->top);
    }
    return 0;
}

void stk_display(Stack *s, int reverse){
    if (reverse == 1) {
        for (int *ptr = s->data; ptr < s->top; ptr++) {
            printf("%d ", *ptr);
        }
    } else {
        for (int *ptr = s->top - 1; ptr >= s->data; ptr--) {
            printf("%d ", *ptr);
        }
    }
    printf("\n");
}

void stk_destroy(Stack *s){
    free(s->data);
    free(s);
}

Stack *stk_copy(Stack *s){
    Stack *new_stk = stk_create(s->capacity);
    for (int *ptr = s->data; ptr < s->top; ptr++) {
        stk_push(new_stk, *ptr);
    }
    return new_stk;
}