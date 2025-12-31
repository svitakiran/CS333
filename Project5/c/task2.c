/**
 * Impelement a word counter that can count the number of occurences of every word
 * in a text file
 * 
 * Svita Kiran
 * 11/13/2025
 * CS333
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "linkedList.h"
#include "linkedList.c"
#include <ctype.h>

#define MAX_WORD 100

typedef struct {
    char word[100];
    int count;
} Word;

// comparison function for ll_find
int compare_words(void *a, void *b) {
    return strcmp(((Word*)a)->word, ((Word*)b)->word);
}

// convert word to lowercase
void to_lower(char *s) {
    for (int i = 0; s[i]; i++)
        s[i] = tolower((unsigned char)s[i]);
}

// strip punctuation from start/end
void clean_word(char *s) {
    int len = strlen(s);

    int start = 0;
    while (start < len && ispunct((unsigned char)s[start]))
        start++;

    int end = len - 1;
    while (end >= 0 && ispunct((unsigned char)s[end]))
        end--;

    int j = 0;
    for (int i = start; i <= end; i++)
        s[j++] = s[i];
    s[j] = '\0';
}

int main(int argc, char *argv[]) {

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    LinkedList *list = ll_create();
    char buffer[MAX_WORD];

    while (fscanf(fp, "%99s", buffer) == 1) {
        clean_word(buffer);
        to_lower(buffer);

        if (strlen(buffer) == 0)
            continue;

        Word temp;
        strcpy(temp.word, buffer);

        Word *found = ll_find(list, &temp, compare_words);

        if (found) {
            found->count++;
        } else {
            Word *new_word = malloc(sizeof(Word));
            strcpy(new_word->word, buffer);
            new_word->count = 1;
            ll_append(list, new_word);
        }
    }

    fclose(fp);

    // convert list to array to sort
    int n = ll_size(list);
    Word **arr = malloc(sizeof(Word*) * n);

    Node *cur = list->head;
    int i = 0;
    while (cur) {
        arr[i++] = (Word*)cur->data;
        cur = cur->next;
    }

    // bubble sort descending
    for (int a = 0; a < n; a++) {
        for (int b = a + 1; b < n; b++) {
            if (arr[b]->count > arr[a]->count) {
                Word *tmp = arr[a];
                arr[a] = arr[b];
                arr[b] = tmp;
            }
        }
    }

    int limit = (n < 20) ? n : 20;
    for (int k = 0; k < limit; k++)
        printf("%8s\t%d\n", arr[k]->word, arr[k]->count);

    free(arr);

    ll_clear(list, free);
    free(list);

    return 0;
}