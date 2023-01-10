/*********************************************************************************
 * Konan Le, kokhle
 * 2022 Spring CSE101 PA3
 * FindComponents.c
 * Code for using Graph ADT to find all strongly connected components in
 * topological order
 *********************************************************************************/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "List.h"

#define MAX_LEN 300
#define UNDEF -100
#define NIL 0

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
  int dummyline = 1;
  for (dummyline = 1; dummyline < line_count; dummyline++) {
    // vertices must be in range 1 to n
    fscanf(in, "%d %d", &vert1, &vert2);
    // printf("about to go into if statement");
    if ((vert1 <= (getOrder(G))) && (vert1 > 0) && (vert2 <= (getOrder(G))) &&
        (vert2 > 0)) {
      // printf("passes if statement\n");
      addArc(G, vert1, vert2);
    } else if (vert1 == 0 && vert2 == 0) {
      // Dummy line, all done reading the thing
      break;
    }
  }

  // Print adjacency list
  fprintf(out, "Adjacency list representation of G:\n");
  printGraph(out, G);
  fprintf(out, "\n");

  // Initialize stack from 1 to n number of vertices
  List stack = newList();
  for (int i = 1; i < (getOrder(G) + 1); i++) {
    append(stack, i);
  }
  // Run DFS on graph from smallest vertex to largest
  DFS(G, stack);

  // Create transpose graph
  Graph transgrph = transpose(G);

  // DFS on transpose graph to get new Stack
  DFS(transgrph, stack);

  // Component counting time
  int scccount = 0;
  // Need an array of Lists to contain each SCC
  List *scc = (List *)malloc(sizeof(List) * (getOrder(G) + 1));
  // Read stack and compose
  moveBack(stack);
  scc[scccount] = newList();
  for (int j = 0; j < length(stack); j++) {
    if (getParent(transgrph, get(stack)) != NIL) {
      append(scc[scccount], get(stack));
    }
    if (getParent(transgrph, get(stack)) == NIL) {
      // if parent is null, means end of component.
      // include last vertex as part of component
      append(scc[scccount], get(stack));
      scccount++;
      scc[(scccount)] = newList();
    }
    movePrev(stack);
  }

  // Printing SCCs
  fprintf(out, "G contains %d strongly connected components: \n", scccount);
  for (int i = 0; i < scccount; i++) {
    moveBack(scc[i]);
    fprintf(out, "Component %d:", (i + 1));
    for (int k = 0; k < length(scc[i]); k++) {
      fprintf(out, " %d", get(scc[i]));
      movePrev(scc[i]);
    }
    fprintf(out, "\n");
  }

  // Cleanup
  // Close files
  fclose(in);
  fclose(out);

  // Free memory
  for (int l = 0; l < (getOrder(G) + 1); l++) {
    freeList(&(scc[l]));
  }
  free(scc);
  scc = NULL;
  freeList(&stack);
  freeGraph(&G);
  return 0;
}
