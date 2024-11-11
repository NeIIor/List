#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define INVALID_VALUE -1
#define SIZE_LIST 9
#define POISON -666
#define PHANTOM_NEXT 0

typedef struct {
    int data; // TODO typedef
    int next;
    int prev;
} node_t;

typedef struct {
    node_t* Arr;
    int free;
} list_t;


void         initList     (list_t* List);
void         freeList     (list_t* List);
bool      addElemList     (list_t* List, int value, int index);
bool      delElemList     (list_t* List, int index);
bool listFullnessList     (list_t* List);
#endif // LIST_H