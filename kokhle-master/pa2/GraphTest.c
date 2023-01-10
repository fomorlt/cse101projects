/*********************************************************************************
 * Konan Le, kokhle
 * 2022 Spring CSE101 PA2
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
  Graph A = newGraph(13);
  Graph B = newGraph(50);
  List Path = newList();

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

  // Testing cleanup
  freeList(&Path);
  freeGraph(&A);
  freeGraph(&B);
  printf("\n");
  printf("----------\n");
  printf("Successfully completed all tests!\n");
  return EXIT_SUCCESS;
}
