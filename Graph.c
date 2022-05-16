#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"


#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct GraphObj{
	List * adj;
	int * color;
	int * parent;
	int * distance;
    int size;
	int order;
	int source;
}GraphObj;

Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    G->adj = malloc((n+1)*sizeof (List));
    for(int i = 1; i<=n; i++){
        G->adj[i] = newList();
    }
    G->color = malloc((n+1)*sizeof (int));
    G->parent = malloc((n+1)*sizeof (int));
    G->distance = malloc((n+1)*sizeof (int));
    G->size = 0;
    G->order = n;
    G->source = 0;
    return G;
}
void freeGraph(Graph* pG){
    if (pG == NULL || *pG == NULL) {
        fprintf(stderr, "Error in freeGraph()! The node does not exist!\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 1; i <= getOrder(*pG); i++){
        freeList(&(*pG)->adj[i]);
    }
    free((*pG)->adj);
    free((*pG)->color);
    free((*pG)->parent);
    free((*pG)->distance);
    free(*pG);
    *pG = NULL;
}

int getOrder(Graph G){
    return G->order;
}
int getSize(Graph G){
    return G->size;
}
int getSource(Graph G){
    return G->source ?  G->source: NIL;
}
int getParent(Graph G, int u){
    if (u < 1 || G->order < u){
        fprintf(stderr, "Error in getParent()!");
        exit(EXIT_FAILURE);
    }
    if(G->source)   return G->parent[u];
    return NIL;
}
int getDist(Graph G, int u){
    if (u < 1 || G->order < u){
        fprintf(stderr, "Error in getDist()!");
        exit(EXIT_FAILURE);
    }
	if(G->source)
		return G->distance[u];
return INF;
    //return G->source ? G->parent[u] : NIL;
}

void getPath(List L, Graph G, int u){
    if (G == NULL){
        printf("Error in getPath()!");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || G->order < u){
        printf("Error in getPath()!");
        exit(EXIT_FAILURE);
    }
    if (u == G->source){
        append(L,u);
    }
    else if (G->parent[u] == NIL){
        append(L, NIL);
    }
    else {
        getPath(L, G, G->parent[u]);
        append(L, u);
    }
}
void makeNull(Graph G){
    G->size = 0;
    for (int i = 1; i <= getOrder(G); i++) {
        clear(G->adj[i]);
    }
}
void addEdge(Graph G, int u, int v){
    if (u < 1 || G->order < u || v < 1 || G->order < v){
        fprintf(stderr, "Error in addEdge()!");
        exit(EXIT_FAILURE);
    }
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
}
void addArc(Graph G, int u, int v){
    if (u < 1 || G->order < u || v < 1 || G->order < v){
        fprintf(stderr, "Error in addArc()!");
        exit(EXIT_FAILURE);
    }
    if(length(G->adj[u]) == 0){
        append(G->adj[u], v);
        G->size++;
    }
    else{
	G->size++;
        int l = length(G->adj[u]);
        for (int i = 1; i <= l; i++) {
 //           printf("jinbuqu\n");
            int zeroIndex = 0;
            moveBack(G->adj[u]);
            for (int j = length(G->adj[u]) - 1; j >= 0; j--) {
                if (v < get(G->adj[u])) {
                    if (j == 0)
                        zeroIndex = 1;
                    else
                        movePrev(G->adj[u]);
                }
                if (v == get(G->adj[u])) return;
            }
            if (zeroIndex == 1)
                insertBefore(G->adj[u], v);
            else
                insertAfter(G->adj[u], v);
        }
    }

}

void BFS(Graph G, int s) {
	if (s < 1 || G->order < s){
		fprintf(stderr, "Error in BFS()!");
		exit(EXIT_FAILURE);
	}
	for (int i = 1; i <= G->order; i++){
		G->color[i] = WHITE;
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	G->color[s] = GRAY;
	G->distance[s] = 0;
    G->parent[s] = NIL;

	G->source = s;
	List Q = newList();
	append(Q, s);
	while (length(Q) != 0){
		int x = front(Q);
		deleteFront(Q);
		
		moveFront(G->adj[x]);
		while (index(G->adj[x]) != -1){
			int y = get(G->adj[x]);
			if ((G->color[y]) == WHITE){
				G->color[y] = GRAY;
				G->distance[y] = G->distance[x] + 1;
				G->parent[y] = x;
				append(Q, y);
			}
			moveNext(G->adj[x]);
		}
		G->color[x] = BLACK;
	}
	freeList(&Q);
}

void printGraph(FILE* out, Graph G){
    for (int i = 1; i <= getOrder(G) ; ++i) {
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
        //fprintf(out, "\n");
    }
}

