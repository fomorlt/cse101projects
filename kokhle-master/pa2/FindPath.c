/*********************************************************************************
 * Konan Le, kokhle
 * 2022 Spring CSE101 PA2
 * FindPath.c
 * Code for using Graph ADT to find shortest path between a pair of vertices
 *********************************************************************************/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "List.h"

#define MAX_LEN 300

int main(int argc, char *argv[]) {
  int line_count;
  FILE *in, *out;
  char line[MAX_LEN];

  // Check for 2 arguments
  if (argc != 3) {
    fprintf(stderr, "Usage: <input file> <output file\n");
    exit(EXIT_FAILURE);
  }
  // open files for reading and writing
  in = fopen(argv[1], "r");
  if (in == NULL) {
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }

  out = fopen(argv[2], "w");
  if (out == NULL) {
    printf("Unable to open file %s for writing\n", argv[2]);
    exit(1);
  }

  // read each line of input file, then count and print tokens
  line_count = 0;
  while (fgets(line, MAX_LEN, in) != NULL) {
    line_count++;
  }
  // Rewind in order to get file position ready for data reading
  rewind(in);

  // Reading Data
  // Reading number of vertices
  int numvertices = 0;
  fscanf(in, "%d", (&numvertices));
  Graph G = newGraph(numvertices);
  int vert1;
  int vert2;
  // printf("numvertices: %d\n", numvertices);
  int dummyline = 1;
  for (dummyline = 1; dummyline < line_count; dummyline++) {
    // vertices must be in range 1 to n
    fscanf(in, "%d %d", &vert1, &vert2);
    // printf("about to go into if statement");
    if ((vert1 <= (getOrder(G))) && (vert1 > 0) && (vert2 <= (getOrder(G))) &&
        (vert2 > 0)) {
      // printf("passes if statement\n");
      addEdge(G, vert1, vert2);
    } else if (vert1 == 0 && vert2 == 0) {
      // Dummy line, time for next part
      break;
    }
  }

  // Print adjacency list
  printGraph(out, G);

  // Read source-destination pair
  int srce;
  int dest;
  List L = newList();
  for (int next = dummyline; next < line_count; next++) {
    // printf("inside second for loop\n");
    fscanf(in, "%d %d", &srce, &dest);
    if ((srce <= (getOrder(G) + 1)) && (srce > 0) &&
        (dest <= (getOrder(G) + 1)) && (dest > 0)) {
      // printf("passinng second if statement\n");
      // making sure in range 1 to n
      BFS(G, srce);
      fprintf(out, "\n");
      getPath(L, G, dest);
      if (getDist(G, dest) == INF) {
        fprintf(out, "The distance from %d to %d is infinity\n", srce, dest);
        fprintf(out, "No %d-%d path exists\n", srce, dest);
      } else {
        fprintf(out, "The distance from %d to %d is %d\n", srce, dest,
                getDist(G, dest));
        fprintf(out, "A shortest %d-%d path is: ", srce, dest);
        printList(out, L);
        fprintf(out, "\n");
      }
      clear(L);
      // Now loop around for next source-destination pair
    }
    if ((srce == 0) && (dest == 0)) {
      // Dummy line - reading is over
      break;
    }
  }

  // Cleanup
  // Close files
  fclose(in);
  fclose(out);

  // Free memory
  freeList(&L);
  freeGraph(&G);
  return 0;
}
