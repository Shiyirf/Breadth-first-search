//-----------------------------------------------------------------------------
//
// GraphTest.c
// 
// This is a fancy test client that calculates the Radius and Diameter of 
// the graph defined on lines 41-49, along with its Central and Peripheral 
// vertices.  The definitions of these terms at:
// 
//    http://en.wikipedia.org/wiki/Distance_(graph_theory)
// 
// Place this file in a directory with copies of your List.c, List.h, Graph.c, 
// Graph.h and an appropriate Makefile, then compile and run. The output 
// is contained in the file GraphClientOut.
// 
// This program does not exercise all functions in your Graph ADT, but it 
// does a pretty good job of testing BFS().  If your output differs from 
// the above, you have a logical problem in either your Graph or List ADT.
// 
// Remember you are required to submit a file named GraphTest.c with pa4 that
// exercises your Graph functions.  Do not submit this file.
//
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   int n=20;
   Graph G = newGraph(n);
   for(int i=1; i<10; i++){
      if( i%2 ) addEdge(G, i, i+1);
      if( i<=5 ) addEdge(G, i, i+10);
   }
   addEdge(G, 9, 11);
   addEdge(G, 17, 13);
   addEdge(G, 14, 2);
   printf("Order is %d\n", getOrder(G));
   printf("Size is %d\n", getSize(G));
   printGraph(stdout, G);

   // Calculate the eccentricity of each vertex
   List L = newList();
   for(int s=1; s<=n; s++){
      BFS(G, s);
      printf("Source is %d\n", getSource(G));
      for(int a = s; a < s+5 && a <= n; a++){
          printf("The parent of %d is %d\n", a, getParent(G, a));
      }
      if (s < n-5){
          getPath(L,G,s+5);
          printf("The distance from %d to %d is %d\n", s, s+5, getDist(G, s+5));
          printf("Path is :");
          printList(stdout,L);
          clear(L);
      }
   }
    makeNull(G);
    printf("Order is %d\n", getOrder(G));
    printf("Size is %d\n", getSize(G));
   // Free objects
   freeList(&L);
   freeGraph(&G);

   return(0);
}
