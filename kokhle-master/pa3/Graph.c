/*********************************************************************************
 * Konan Le, kokhle
 * 2022 Spring CSE101 PA3
 * Graph.c
 * Contains functions for use in Graph ADT
 *********************************************************************************/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "List.h"

// constant macros
#define UNDEF -100
#define NIL 0

// Graph definition
typedef struct GraphObj *Graph;

// neighbors, color, parent, distance must be pointer b/c array of ints and
// Lists
typedef struct GraphObj {
  int size;
  int *parent;
  int *discover;
  int *finish;
  int order;
  List *neighbors;
  int *color;
  int time;
} GraphObj;

// Constructors and Destructors -----------

// newGraph() allocates memory and initializes values for a GraphObj
Graph newGraph(int n) {
  Graph G = malloc(sizeof(GraphObj));
  // if (G) {
  // edges and vertices
  G->size = 0;
  G->time = 0;
  G->order = n;
  G->parent = (int *)malloc(sizeof(int) * (G->order + 1));
  G->finish = (int *)malloc(sizeof(int) * (G->order + 1));
  G->discover = (int *)malloc(sizeof(int) * (G->order + 1));
  G->neighbors = (List *)malloc(sizeof(List) * (G->order + 1));
  G->color = (int *)malloc(sizeof(int) * (G->order + 1));
  for (int i = 1; i < (G->order + 1); i++) {
    G->parent[i] = NIL;
    // inf distance if no path or if BFS not called
    // each list contains neighbors of i
    G->neighbors[i] = newList();
    G->color[i] = 0;
    G->discover[i] = UNDEF;
    G->finish[i] = UNDEF;
  }
  return G;
  //} else {
  //  fprintf(stderr, "Error in Graph ADT: newGraph(), not enough memory for
  //  G");
  // exit(EXIT_FAILURE);
  //}
}

// freeGraph() deallocates memory from Graph ADT
void freeGraph(Graph *pG) {
  if ((pG != NULL) && (*pG != NULL)) {
    // while loop to delete neighbors
    for (int i = 1; i < ((*pG)->order + 1); i++) {
      freeList(&((*pG)->neighbors[i]));
    }
    free((*pG)->parent);
    (*pG)->parent = NULL;
    free((*pG)->neighbors);
    (*pG)->neighbors = NULL;
    free((*pG)->color);
    (*pG)->color = NULL;
    free((*pG)->discover);
    (*pG)->discover = NULL;
    free((*pG)->finish);
    (*pG)->finish = NULL;
    free((*pG));
    (*pG) = NULL;
    pG = NULL;
  }
}

// Accessor Functions ----------

// getOrder() returns number of vertices in the graph
// 1-indexing so that indices can be identfied with vertex labels
int getOrder(Graph G) {
  if (G == NULL) {
    fprintf(stderr, "Error in Graph ADT: getOrder(), L is null.");
    exit(EXIT_FAILURE);
  }
  return G->order;
}

// getSize() returns number of edges in graph
int getSize(Graph G) {
  if (G == NULL) {
    fprintf(stderr, "Error in Graph ADT: getSize(), L is NULL.");
    exit(EXIT_FAILURE);
  }
  return G->size;
}

// getDiscover() returns discovery time of vertex u
// pre: vertex u must be in bounds of the graph
int getDiscover(Graph G, int u) {
  if (G == NULL) {
    fprintf(stderr, "Error in Graph ADT, getDiscover(), L is NULL.");
    exit(EXIT_FAILURE);
  }
  if ((1 <= u) && (u <= (getOrder(G) + 1))) {
    return G->discover[u];
  } else {
    fprintf(stderr,
            "Error in Graph ADT, getDiscover(). vertex u is out of bounds.");
    exit(EXIT_FAILURE);
  }
}

// getFinish() returns finish time of vertex u
// pre: vertex u must be in bounds of the graph
int getFinish(Graph G, int u) {
  if (G == NULL) {
    fprintf(stderr, "Error in Graph ADT, getDiscover(), L is NULL.");
    exit(EXIT_FAILURE);
  }
  if ((1 <= u) && (u <= (getOrder(G) + 1))) {
    return G->finish[u];
  } else {
    fprintf(stderr,
            "Error in Graph ADT, getDiscover(). vertex u is out of bounds.");
    exit(EXIT_FAILURE);
  }
}

// getParent() returns parent of a vertex u
// vertex u must exist within bounds or else error will occur
int getParent(Graph G, int u) {
  if (G == NULL) {
    fprintf(stderr, "Error in Graph ADT: getParent(), L is NULL.");
    exit(EXIT_FAILURE);
  }
  if ((u > (G->order + 1)) || (u < 1)) {
    fprintf(stderr,
            "Error in Graph ADT: getParent(), given vertex %d is not valid.",
            u);
    exit(EXIT_FAILURE);
  }
  // Check if G is out of order
  return G->parent[u];
}

// Manipulator Functions -----------

// addArc() inserts a directed edge to the adjacency list of origin vertex to
// end vertex Sort neighbor list in order of increasing labels pre: 1 < (u, v) <
// getOrder(G)
void addArc(Graph G, int u, int v) {
  if (G == NULL) {
    fprintf(stderr, "Error in Graph ADT: addArc(), G is NULL.");
    exit(EXIT_FAILURE);
  }
  if ((u < 1) || (v < 1) || (u > (getOrder(G) + 1)) ||
      (v > (getOrder(G) + 1))) { // possible error in these conditionals
                                 // printf("u: %d, v: %d\n", u, v);
    fprintf(stderr, "Error in Graph ADT: addArc(), u or v is not greater than "
                    "1, OR u or v is not less than getOrder(G).");
    exit(EXIT_FAILURE);
  }
  // If edge already exists, do nothing
  List adj = G->neighbors[u];
  moveFront(adj);
  for (int k = 0; k < length(adj); k++) {
    if (get(adj) == v) {
      break;
    }
    moveNext(adj);
  }
  // Insertion Sort
  // If new edge, just add the edge. If not, insert while sorting.
  if (length(G->neighbors[u]) == 0) {
    append(G->neighbors[u], v);
    G->size++;
  } else {
    moveBack(G->neighbors[u]);
    // While loop to move cursor
    while (index(G->neighbors[u]) != -1) {
      // if inserted neighbor is less than cursor
      if (v == get(G->neighbors[u])) {
        return;
      } else if (v < get(G->neighbors[u])) {
        movePrev(G->neighbors[u]);
      } else {
        // once cursor element is equal to or greater than vertex v, insert
        break;
      }
    }
    // Outside of while loop to move cursor, now insert the element
    if (index(G->neighbors[u]) == -1) {
      prepend(G->neighbors[u], v);
      G->size++;
    } else {
      // found spot where next is larger or equal, cursor has moved one spot
      // back
      insertAfter(G->neighbors[u], v);
      G->size++;
    }
  }
}

// addEdge() inserts a new edge joining u to v and v to u.
// Sort each list in order of increasing labels
// pre: 1 < (u, v) < getOrder(G)
void addEdge(Graph G, int u, int v) {

  if (G == NULL) {
    fprintf(stderr, "Error in Graph ADT: addEdge(), G is NULL.");
    exit(EXIT_FAILURE);
  }
  if ((u < 1) || (v < 1) || (u > (getOrder(G) + 1)) ||
      (v >= (getOrder(G) + 1))) { // possible error in these conditionals
    printf("u: %d, v: %d\n", u, v);
    fprintf(stderr, "Error in Graph ADT: addEdge(), u or v is not greater than "
                    "1, OR u or v is not less than getOrder(G).");
    exit(EXIT_FAILURE);
  }
  // could just use 2 directed edges - becomes one edge that goes both ways
  addArc(G, u, v);
  addArc(G, v, u);
  G->size -= 1; //-- to account for 2 size increases from 2 addArc()
}

// Visit() is the recursive segment of DFS. It travels down a path, changes
// colors accordingly, and checks time accordingly.
// Code based on DFS pseudocode from Graph Algorithms handout
void Visit(Graph G, List stack, int x) {
  // each int x is a root for dfs to check from
  G->discover[x] =
      ++(G->time); // prefix increment will increase actual value itself
  G->color[x] = 1; // set to grey
  List adj = G->neighbors[x];
  moveFront(adj); // DFS starts from least to greatest
  for (int i = 0; i < length(adj); i++) {
    if (G->color[get(adj)] == 0) {
      G->parent[get(adj)] = x; // parent should be set here????
      Visit(G, stack, get(adj));
    }
    moveNext(adj); // after fully travelling down one path, go to next sibling
  }
  G->color[x] = 2;   // set to black
  prepend(stack, x); // Done with vertex, push to stack
  // going to result in stack holding more values in the front - in order from
  // last finishing time to lowest, as intended
  G->finish[x] = ++(G->time);
}

// DFS() performs a depth-first search from lowest to greatest vertex, builds a
// stack for use in FindComponents.c colors: 0 = white, 1 = grey, 2 = black Works
// off of one single stack - appends vertices to current stack, works up until
// the old stack has been fully deleted
// List S should start with a pre-initialized stack from 1 to n amount of
// vertices
void DFS(Graph G, List S) {
  // Preconditions
  if (G == NULL) {
    printf("Now it reaches G== NULL!");
    fprintf(stderr, "Error in Graph ADT: DFS(), G is NULL!");
    exit(EXIT_FAILURE);
  }
  if (S == NULL) {
    fprintf(stderr, "Error in Graph ADT: DFS(), S is NULL!");
  }
  if (length(S) != getOrder(G)) {
    fprintf(stderr, "Error in Graph ADT: DFS(), length of stack must be same "
                    "as order of the graph");
    exit(EXIT_FAILURE);
  }
  // initialize values for DFS
  for (int i = 1; i < (G->order + 1); i++) {
    G->parent[i] = NIL;
    G->color[i] = 0;
    G->discover[i] = UNDEF;
    G->finish[i] = UNDEF;
  }
  G->time = 0;
  // Goes through vertices specified in stack list
  int oldStacklen = length(S);
  // holds the current length in oldStack - shouldn't be changing or anything
  // like that as length of the stack increases
  moveFront(S);
  for (int i = 0; i < oldStacklen; i++) { // Goes up the original stack amount
    if (G->color[get(S)] == 0) {
      Visit(G, S, get(S));
    }
    moveNext(S);
  }
  for (int j = 0; j < oldStacklen; j++) {
    moveBack(S); // Should leave only newly created stack in List S
    delete (S);
  }
}

// Other Operations ----------
// printGraph() prints adjacency list (graph G) to desired output
void printGraph(FILE *out, Graph G) {
  if (G == NULL) {
    fprintf(stderr, "Error in Graph ADT: printGraph(), G is NULL");
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i < (G->order + 1); i++) {
    fprintf(out, "%d: ", i);
    printList(out, G->neighbors[i]);
    fprintf(out, "\n");
  }
}

// transpose() flips all edge directions in a graph
Graph transpose(Graph G) {
  if (G == NULL) {
    fprintf(stderr, "Error in Graph ADT: transpose(), G is NULL!");
    exit(EXIT_FAILURE);
  }
  // Go through each vertex's edges (adj neighbors), add an arc from each
  // neighbor to parent
  Graph transposeGraph = newGraph(getOrder(G));
  List adj = newList();
  int dest = 0;
  for (int i = 1; i < (getOrder(G) + 1); i++) {
    // adjacency list of each vertex, then flip the edges
    adj = G->neighbors[i];
    moveFront(adj);
    for (int j = 0; j < length(adj); j++) {
      dest = get(adj);
      addArc(transposeGraph, dest, i);
      moveNext(adj);
    }
  }
  return transposeGraph;
}

// copyGraph() should return a copy of Graph G
// Should the the same as transpose, but just without reversing the edges
Graph copyGraph(Graph G) {
  if (G == NULL) {
    fprintf(stderr, "Error in Graph ADT: copyGraph(), G is NULL");
    exit(EXIT_FAILURE);
  }
  Graph copyGraph = newGraph(getOrder(G));
  List adj = newList();
  int dest = 0;
  for (int i = 1; i < (getOrder(G) + 1); i++) {
    // adjacency list of each vertex, then flip the edges
    adj = G->neighbors[i];
    moveFront(adj);
    for (int j = 0; j < length(adj); j++) {
      dest = get(adj);
      addArc(copyGraph, i, dest);
      moveNext(adj);
    }
  }
  return copyGraph;
}
