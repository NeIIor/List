#include "list.h"
#include "dump.h"

void initList (list_t* List) {
    List->Arr = (node_t*) calloc (SIZE_LIST, sizeof(node_t));
    List->free = 1;


    List->Arr[0].data = POISON;
    List->Arr[0].next = PHANTOM_NEXT;
    List->Arr[0].prev = INVALID_VALUE;

    for (size_t i = 1; i < SIZE_LIST; i++) {
        List->Arr[i].data = POISON;
        List->Arr[i].next = i + 1;
        List->Arr[i].prev = INVALID_VALUE;
    }
    List->Arr[SIZE_LIST - 1].next = 0;
}

void freeList (list_t* List) {
    free (List->Arr);
}

bool listFullness (list_t* List) {
    if (List->free == 0) {
        fprintf(stderr,"List is full\n");
        return false;
    }
    else {
        return true;
    }
}

bool addElemList (list_t* List, int value, int index) {
    if (!listFullness (List)) {
        fprintf(stderr, "Can't add elem in full list. Delete some elems to add one");
        return false;
    }
    int old_free = List->free;
    int old_next = List->Arr[index     ].next;

    List->free = List->Arr[old_free].next;

    List->Arr[old_free].data = value;
    List->Arr[old_free].next = old_next;
    List->Arr[old_free].prev = index;

    List->Arr[index   ].next = old_free;
    List->Arr[old_next].prev = old_free;

    dumpList (List);
    return true;
}

bool delElemList (list_t* List, int index) {

    if (List->Arr[0].next == 0) {
        printf("Can't delete elem from empty list");
        return false;
    }

    int old_next = List->Arr[index].next;
    int old_prev = List->Arr[index].prev;

    List->Arr[old_prev].next = old_next;
    List->Arr[old_next].prev = old_prev;

    List->Arr[index].data = POISON;
    List->Arr[index].prev = INVALID_VALUE;

    List->Arr[index].next = List->free;
                            List->free = index;
    dumpList (List);
    return true;
}

