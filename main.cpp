#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "dump.h"
#include "html.h"

int main () {
    list_t List = {0, 0};
    initList    (&List);
    addElemList (&List, 10, 0);
    addElemList (&List, 20, 1);
    addElemList (&List, 30, 2);
    addElemList (&List, 40, 3);
    addElemList (&List, 50, 4);
    addElemList (&List, 60, 5);
    addElemList (&List, 70, 6);
    addElemList (&List, 80, 7);
    if (!addElemList (&List, 90, 8)) {
        return 1;
    }
    
    atexit(fillEndHtml); 
    freeList    (&List);

    return 0;
}

