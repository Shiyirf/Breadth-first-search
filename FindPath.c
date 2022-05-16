#include "List.h"
#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    FILE *in, *out;
    int n;

    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    fscanf(in, "%d", &n);
    Graph G = newGraph(n);

    int u, v;
    while(fscanf(in, "%d %d\n", &u, &v) && u!=0)
        addEdge(G, u, v);

    printGraph(out, G);

    List L = newList();
    while(fscanf(in, "%d %d\n", &u, &v) && u!=0){
        BFS(G, u);
        getPath(L, G, v);
        if (getDist(G, v)>=0){
            fprintf(out, "The distance from %d to %d is %d\n"
                         "A shortest %d-%d path is: ", u, v, getDist(G, v), u, v);
            printList(out, L);
        }
        else{
            fprintf(out, "The distance from %d to %d is infinity\n"
                         "No %d-%d path exists\n\n",u,v, u, v);

        }
        clear(L);
    }
    fclose(in);
    fclose(out);
    freeList(&L);
    freeGraph(&G);
        return 0;
}
