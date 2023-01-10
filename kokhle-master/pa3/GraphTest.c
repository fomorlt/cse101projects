/*********************************************************************************
 * Konan Le, kokhle
 * 2022 Spring CSE101 PA3
 * GraphTest.c
 * Personalized test client for Graph ADT
 *********************************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "List.h"

#define MAX_LEN 300

int main(int argc, char *argv[]) {
  // FILE *in, *out;
  // int line_count = 0;
  // char line[MAX_LEN];

  // New Graphs
  Graph G = newGraph(8);
  Graph transg = NULL;
  Graph copyg = NULL;
  List stack = newList();

  // Checking initialization
  // Checking getOrder
  if (getOrder(G) != 8) {
    fprintf(stderr, "order did not initialize properly!");
    exit(EXIT_FAILURE);
  }

  // Testing time initializations - discover and finish
  for (int i = 1; i <= 8; i++) {
    if (getDiscover(G, i) != UNDEF) {
      fprintf(stderr, "Discover times did not initialize properly!");
      exit(EXIT_FAILURE);
    }
    if (getFinish(G, i) != UNDEF) {
      fprintf(stderr, "Finish times did not initialize properly!");
      exit(EXIT_FAILURE);
    }
  }

  // Checking addArc
  // Testing with graph example given in lecture
  addArc(G, 1, 2);
  addArc(G, 2, 3);
  addArc(G, 2, 5);
  addArc(G, 2, 6);
  addArc(G, 3, 4);
  addArc(G, 3, 7);
  addArc(G, 4, 3);
  addArc(G, 4, 8);
  addArc(G, 5, 1);
  addArc(G, 5, 6);
  addArc(G, 6, 7);
  addArc(G, 7, 6);
  addArc(G, 7, 8);
  addArc(G, 8, 8);

  if (getSize(G) != 14) {
    fprintf(stderr, "Error in size functionality!\n");
    exit(EXIT_FAILURE);
  }
  printf("Testing Graph!\n");
  printGraph(stdout, G);

  // Preparing stack
  for (int i = 1; i <= 8; i++) {
    append(stack, i);
  }

  // Testing if DFS works
  DFS(G, stack);
  printList(stdout, stack);

  if (getParent(G, 6) != 7) {
    fprintf(stdout, "parent: %d\n", getParent(G, 6));
    fprintf(stdout, "parents not forming properly\n");
    exit(EXIT_FAILURE);
  }
  if (getParent(G, 4) != 3) {
    fprintf(stdout, "parents not forming properly\n");
    exit(EXIT_FAILURE);
  }
  if (getDiscover(G, 2) != 2) {
    fprintf(stdout, "discover time not applying properly\n");
    exit(EXIT_FAILURE);
  }
  if (getDiscover(G, 8) != 5) {
    fprintf(stdout, "discover time not applying properly\n");
    exit(EXIT_FAILURE);
  }
  if (getDiscover(G, 7) != 8) {

    fprintf(stdout, "discover time not applying properly\n");
    exit(EXIT_FAILURE);
  }
  if (getFinish(G, 8) != 6) {
    fprintf(stdout, "finish time not applying properly!\n");
    exit(EXIT_FAILURE);
  }
  if (getFinish(G, 4) != 7) {

    fprintf(stdout, "finish time not applying properly!\n");
    exit(EXIT_FAILURE);
  }

  // Testing transpose and copy
  // Transpose test should result in swapping of edges
  transg = transpose(G);
  printGraph(stdout, transg);
  transg = transpose(transg);
  printGraph(stdout, transg);

  // Copy test should result in the same graphs coming out
  copyg = copyGraph(transg);
  printGraph(stdout, copyg);
  copyg = copyGraph(G);
  printGraph(stdout, copyg);
  copyg = copyGraph(copyg);
  printGraph(stdout, copyg);

  /*
 // Checking initialization
 if (getSource(A) != NIL) {
   fprintf(stderr, "source did not initialize to NIL");
   exit(EXIT_FAILURE);
 }
 if (getSize(A) != 0) {
   fprintf(stderr, "size not initialized to 0");
   exit(EXIT_FAILURE);
 }
 if (getOrder(A) != 13) {
   fprintf(stderr, "order did not initialize properly!");
   exit(EXIT_FAILURE);
 }
 // Testing getDist on Graph B
 for (int i = 1; i <= 50; i++) {
   if (getDist(B, i) != INF) {
     fprintf(stderr, "Distances did not initialize properly!");
     exit(EXIT_FAILURE);
   }
 }
 // Add Edge uses add Arc, so it tests both
 // Testing out my own custom graph
 addEdge(A, 1, 2);
 addEdge(A, 1, 3);
 addEdge(A, 1, 4);
 addEdge(A, 1, 5);
 addEdge(A, 2, 7);
 addEdge(A, 2, 6);
 addEdge(A, 3, 8);
 addEdge(A, 4, 9);
 addEdge(A, 9, 10);
 addEdge(A, 9, 13);
 addEdge(A, 9, 11);
 addEdge(A, 10, 12);
 if (getSize(A) != 12) {
   fprintf(stderr, "Size not working properly?");
   exit(EXIT_FAILURE);
 }

 // Print graph A, tests printGraph() and sees if addEdge works
 printf("Graph A:\n");
 printGraph(stdout, A);

 // Limit testing if calling BFS multiple times will break it
 BFS(A, 1);
 BFS(A, 10);
 BFS(A, 13);
 if (getSource(A) != 13) {
   fprintf(stderr, "Error in setting source for BFS?");
   exit(EXIT_FAILURE);
 }
 BFS(A, 5);
 BFS(A, 3);
 BFS(A, 4);
 if (getSource(A) != 4) {
   fprintf(stderr, "Error in setting source for BFS?");
   exit(EXIT_FAILURE);
 }
 if (getDist(A, 7) != 3) {
   fprintf(stderr, "Error in distance calculation?");
   exit(EXIT_FAILURE);
 }
 if (getDist(A, 12) != 3) {
   fprintf(stderr, "Error in distance calculation?");
   exit(EXIT_FAILURE);
 }
 if (getParent(A, 3) != 1) {
   fprintf(stderr, "Error in parent calculation?");
   exit(EXIT_FAILURE);
 }
 clear(Path);
 printf("Check shortest path with printed graph above:\n");
 getPath(Path, A, 6);
 printList(stdout, Path);
 clear(Path);

 makeNull(A);
 if (getSize(A) != 0) {
   fprintf(stderr, "Error in makeNull()");
   exit(EXIT_FAILURE);
 }
 */

  // Testing cleanup
  freeList(&stack);
  freeGraph(&G);
  freeGraph(&transg);
  freeGraph(&copyg);

  printf("\n");
  printf("----------\n");
  printf(
      "Successfully completed all tests! Be sure to manually check graphs\n");
  return EXIT_SUCCESS;
}
