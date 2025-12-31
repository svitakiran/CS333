#include "cstk2.h"
#include <stdlib.h>
#include <stdio.h>

Stack *stk_create(int capacity){
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (void **)malloc(sizeof(void *) * capacity);
    s->top = s->data;
    s->capacity = capacity;
    return s;
}

void stk_destroy(Stack *stack){
    free(stack->data);
    free(stack);
}

int stk_size(Stack *stack){
    return stack->top - stack->data;
}

void stk_push(Stack *stack, void *item){
    if (stack->top - stack->data < stack->capacity) {
        *(stack->top) = item;
        stack->top++;
    }
}

void *stk_peek(Stack *stack){
    if (stack->top != stack->data) {
        return *(stack->top - 1);
    }
    return NULL;
}

void *stk_pop(Stack *stack){
    if (stack->top != stack->data) {
        stack->top--;
        return *(stack->top);
    }
    return NULL;
}

char *stk_toString(Stack *stack, char *(*toString)(void *)){
    int size = stk_size(stack);
    if (size == 0) {
        char *result = (char *)malloc(3 * sizeof(char));
        result[0] = '[';
        result[1] = ']';
        result[2] = '\0';
        return result;
    }

    char **elements = (char **)malloc(size * sizeof(char *));
    int totalLength = 2; // for '[' and ']'

    for (int i = 0; i < size; i++) {
        elements[i] = toString(stack->data[i]);
        totalLength += strlen(elements[i]) + 2; // for element and ", "
    }
    totalLength -= 2; // remove last ", "

    char *result = (char *)malloc(totalLength * sizeof(char));
    result[0] = '[';
    int pos = 1;

    for (int i = 0; i < size; i++) {
        int len = strlen(elements[i]);
        strcpy(result + pos, elements[i]);
        pos += len;
        if (i < size - 1) {
            result[pos++] = ',';
            result[pos++] = ' ';
        }
        free(elements[i]);
    }
    result[pos++] = ']';
    result[pos] = '\0';

    free(elements);
    return result;
}