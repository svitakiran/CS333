/*
        Bruce Maxwell
        Fall 2012
        CS 333

        Linked list test function

        modified by Svita Kiran
        10/30/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedList.h"

// function that prints an integer
void printInt(void *i) {
    int *a = (int *)i;

    printf("value: %d\n", *a);
}

// function that squares an integer
void squareInt(void *i) {
    int *a = (int *)i;

    *a = *a * *a;
}

// function that compares two integers and returns 1 if they are equal
int compInt(void *i, void *j) {
    int *a = (int *)i;
    int *b = (int *)j;

    return (*a == *b);
}

// function that prints a string
void printString(void *s) {
    char *str = (char *)s;
    printf("value: %s\n", str);
}

// function that compares two strings and returns 1 if they are equal
int compString(void *s1, void *s2) {
    char *str1 = (char *)s1;
    char *str2 = (char *)s2;

    return (strcmp(str1, str2) == 0);
}


// test function for the various linked list functions
int main(int argc, char *argv[]) {
    LinkedList *l;
    int *a;
    int *target;
    int i;

    // // create a list
    // l = ll_create();

    // // push data on the list
    // for (i = 0; i < 20; i += 2) {
    //     a = malloc(sizeof(int));
    //     *a = i;

    //     ll_push(l, a);
    // }

    // // printing the list and testing map
    // printf("After initialization\n");
    // ll_map(l, printInt);

    // ll_map(l, squareInt);

    // printf("\nAfter squaring\n");
    // ll_map(l, printInt);

    // // testing removing data
    // target = malloc(sizeof(int));

    // *target = 16;
    // a = ll_remove(l, target, compInt);
    // if (a != NULL)
    //     printf("\nremoved: %d\n", *a);
    // else
    //     printf("\nNo instance of %d\n", *target);

    // *target = 11;
    // a = ll_find(l, target, compInt);
    // if (a != NULL)
    //     printf("\nFound: %d\n", *a);
    // else
    //     printf("\nNo instance of %d\n", *target);
    // a = ll_remove(l, target, compInt);
    // if (a != NULL)
    //     printf("\nremoved: %d\n", *a);
    // else
    //     printf("\nNo instance of %d\n", *target);

    // printf("\nAfter removals\n");
    // ll_map(l, printInt);

    // // testing appending data
    // ll_append(l, target);

    // printf("\nAfter append\n");
    // ll_map(l, printInt);

    // // test clearing
    // ll_clear(l, free);

    // printf("\nAfter clear\n");
    // ll_map(l, printInt);

    // // rebuild and test append and pop
    // for (i = 0; i < 5; i++) {
    //     a = malloc(sizeof(int));
    //     *a = i;
    //     ll_append(l, a);
    // }

    // printf("\nAfter appending\n");
    // ll_map(l, printInt);

    // a = ll_pop(l);
    // printf("\npopped: %d\n", *a);
    // free(a);

    // a = ll_pop(l);
    // printf("popped: %d\n", *a);
    // free(a);

    // printf("\nAfter popping\n");
    // ll_map(l, printInt);

    // printf("\nList size: %d\n", ll_size(l));



    // second data type: strings
    // new list for strings
    LinkedList *strList = ll_create();
    char *words[] = {"apple", "banana", "cherry", "date"};
    char *targetStr;

    // append strings to list
    for (int i = 0; i < 4; i++) {
        ll_append(strList, words[i]);
    }
    printf("string list after append:\n");
    ll_map(strList, printString);

    // find a string
    targetStr = "banana";
    char *foundStr = ll_find(strList, targetStr, compString);
    if (foundStr != NULL) {
        printf("\nfound: %s\n", foundStr);
    } else {
        printf("\nnot found: %s\n", targetStr);
    }
    
    // remove a string
    targetStr = "cherry";
    char *removedStr = ll_remove(strList, targetStr, compString);
    if (removedStr != NULL) {
        printf("\nremoved: %s\n", removedStr);
    } else {
        printf("\nnot found: %s\n", targetStr);
    }

    printf("\nstring list after removal:\n");
    ll_map(strList, printString);
    // clear string list
    ll_clear(strList, NULL);
    
    return (0);
}