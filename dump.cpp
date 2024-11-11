#include "list.h"
#include "dump.h"

void dumpList (list_t* List) {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    long      seconds = tv.tv_sec;
    long microseconds = tv.tv_usec; // make global counter
    
    char filename[100] = {0};
    snprintf (filename, sizeof(filename), "file_%ld_%06ld.dot", seconds, microseconds);
    FILE*    file_html = fopen ("dump.html", "a+");
    FILE*    file_dump = fopen (filename,    "a+");
    fprintf (file_dump, "\n");
    fprintf (file_dump,"digraph structs {\n");
    fprintf (file_dump,"charset = \"UTF-8\";\n");
    fprintf (file_dump,"rankdir=TB;\n");
    fprintf (file_dump,"label = \"List\";\n");
    fprintf (file_dump,"bgcolor = \"#0000aa\";\n");
    fprintf (file_dump,"fontcolor = black;\n");
    fprintf (file_dump,"fontsize = 18;\n");
    fprintf (file_dump,"style = \"rounded\";\n");   
    fprintf (file_dump,"margin = 0.3;\n"); 
    fprintf (file_dump,"splines = ortho;\n");
    fprintf (file_dump,"ranksep = 1.0;\n"); 
    fprintf (file_dump,"nodesep = 0.9;\n");
    fprintf (file_dump,"bgcolor = \"#78FFDB\";\n");
    fprintf (file_dump,"edge [color=\"#FF69B4\"]\n;");

    for (int i = 0; i < SIZE_LIST; i++) {
        fprintf (file_dump,"node%d [shape=record,label=\"{ip: %d|<f1> data: %d | <f2> next: %d | <f3> prev: %d}\"];\n", i, i,
        List->Arr[i].data, 
        List->Arr[i].next, List->Arr[i].prev);
    }

    fprintf (file_dump, "\n");

    for (int i = 0; i < SIZE_LIST - 1; i++) {
        fprintf (file_dump, "node%d:<f2> -> node%d:<f1>;\n", i, List->Arr[i].next);
    }

    fprintf (file_dump,"free -> node%d\n", List->free);
    fprintf (file_dump,"head -> node%d\n", List->Arr[0].next);
    fprintf (file_dump,"tail -> node%d\n", List->Arr[0].prev);
    fprintf (file_dump,"{ rank = same; "); 
    for (int i = 0; i < SIZE_LIST; i++) {
        fprintf(file_dump, "node%d; ", i);
    }
    fprintf (file_dump, "}\n}\n");
    fclose  (file_dump);
    
    char command[CMD_SIZE] = {};
    snprintf (command, sizeof(command), "dot -Tpng %s -o %.22s.png", filename, filename);
    system   (command);
    snprintf (filename, sizeof(filename), "file_%ld_%06ld.png",  seconds, microseconds);
    fprintf (file_html,       "<img src=\"%s\"/>\n", filename);
    fclose  (file_html);
}