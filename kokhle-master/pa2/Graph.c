/*********************************************************************************
 * Konan Le, kokhle
 * 2022 Spring CSE101 PA2
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

// constant macros - infinity and NIL
#define INF -100
#define NIL -200

// Graph definition
typedef struct GraphObj *Graph;

// neighbors, color, parent, distance must be pointer b/c array of ints and
// Lists
typedef struct GraphObj {
  int source;
  int size;
  int *parent;
  int *distance;
  int order;
  List *neighbors;
  int *color;
} GraphObj;

// Constructors and Destructors -----------

// newGraph() allocates memory and initializes values for a GraphObj
Graph newGraph(int n) {
  Graph G = malloc(sizeof(GraphObj));
  // if (G) {
  // source is NIL if BFS hasn't been called
  G->source = NIL;
  // edges and vertices
  G->size = 0;
  G->order = n;
  G->parent = (int *)malloc(sizeof(int) * (G->order + 1));
  G->distance = (int *)malloc(sizeof(int) * (G->order + 1));
  G->neighbors = (List *)malloc(sizeof(List) * (G->order + 1));
  G->color = (int *)malloc(sizeof(int) * (G->order + 1));
  for (int i = 1; i < (G->order + 1); i++) {
    G->parent[i] = NIL;
    // inf distance if no path or if BFS not called
    G->distance[i] = INF;
    // each list contains neighbors of i
    G->neighbors[i] = newList();
    G->color[i] = 0;
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
    free((*pG)->distance);
    (*pG)->distance = NULL;
    free((*pG)->neighbors);
    (*pG)->neighbors = NULL;
    free((*pG)->color);
    (*pG)->color = NULL;
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

// getSource() returns the most recent source vertex of BFS
int getSource(Graph G) {
  if (G == NULL) {
    fprintf(stderr, "Error in Graph ADT: getSource(), L is NULL.");
    exit(EXIT_FAILURE);
  }
  return G->source;
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

// getDist() returns distance from most recent BFS to vertex u.
// vertex u must exist within bounds or else error will occur
int getDist(Graph G, int u) {
  if (G == NULL) {
    fprintf(stderr, "Error in Graph ADT: getDist(), L is NULL.");
    exit(EXIT_FAILURE);
  }
  if ((u > (G->order + 1)) || (u < 1)) {
    fprintf(stderr,
            "Error in Graph ADT: getDist(), given vertex %d is not valid.", u);
    exit(EXIT_FAILURE);
  }
  return G->distance[u];
}

// getPath() appends to list L the vertices of the shortest path from source to
// vertex u. appends NIL if no path exists. precondition: getSource(G) != NIL
void getPath(List L, Graph G, int u) {
  if (G == NULL) {
    fprintf(stderr, "Error in Graph ADT: getPath(), L is NULL.");
    exit(EXIT_FAILURE);
  }
  if (u > G->order || u < 1) {
    fprintf(stderr, "Error in Graph ADT: getPath(), vertex u is out of bounds");
    exit(EXIT_FAILURE);
  }
  if (getSource(G) == u) {
    // If source is the same as input vertex
    append(L, u);
  } else if (G->parent[u] == NIL) {
    append(L, NIL);
  } else {
    getPath(L, G, G->parent[u]);
    append(L, u);
  }
}

// Manipulator Functions -----------

// makeNull() resets G to original no edge state.
void makeNull(Graph G) {
  if (G == NULL) {
    fprintf(stderr, "Error in Graph ADT: makeNull(), graph is NULL.");
    exit(EXIT_FAILURE);
  }
  // reset size (edges) to 0
  G->size = 0;
  G->source = NIL;
  // deleting arrays
  for (int i = 1; i < (G->order + 1); i++) {
    G->parent[i] = NIL;
    G->distance[i] = INF;
    // deleting array of lists
    clear(G->neighbors[i]);
    G->color[i] = 0; // potential problem here? set to NIL?
  }
}
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
      if (v < get(G->neighbors[u])) {
        movePrev(G->neighbors[u]);
        /*
        if (index(G->neighbors[u]) == -1) {
          // means that v is going to the very front
          break;
        }
        */
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
  G->size--; //-- to account for 2 size increases from 2 addArc()
}

// BFS() performs breadth first search starting at vertex s (source)
// Based on Graph Algorithms Handout & PA2 Assignment Doc
// Colors: 0 = white, 1 = grey, 2 = black
void BFS(Graph G, int s) {
  if (G == NULL) {
    fprintf(stderr, "Error in Graph ADT: BFS(), G is NULL");
    exit(EXIT_FAILURE);
  }
  if (s > (G->order + 1) || s < 1) {
    fprintf(stderr, "Error in Graph ADT: BFS(), s is out of bounds");
    exit(EXIT_FAILURE);
  }
  // Resetting BFS just in case
  for (int i = 1; i < (G->order + 1); i++) {
    G->parent[i] = NIL;
    G->distance[i] = INF;
    G->color[i] = 0;
  }
  G->source = s;
  G->color[s] = 1;
  G->distance[s] = 0;
  G->parent[s] = NIL;
  // new empty queue
  List Q = newList();
  append(Q, s);
  int top = 0;
  while (length(Q) != 0) { // Queue, so FIFO
    // Exploring neighbors
    top = front(Q);
    // Adjacent vertices to front of Q
    List adj = G->neighbors[top];
    moveFront(adj);
    for (int i = 0; i < length(adj); i++) {
      if (G->color[get(adj)] == 0) { // if y is undiscovered (white)
        G->color[get(adj)] = 1;      // discover y, set to gray
        G->distance[get(adj)] = G->distance[top] + 1;
        // travelling down the list
        G->parent[get(adj)] = top;
        append(Q, get(adj));
      }
      moveNext(adj);
    }
    G->color[top] = 2; // finish x, set to black
    deleteFront(Q);    // move onto next layer of BFS
  }
  // cleanup
  freeList(&Q);
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
