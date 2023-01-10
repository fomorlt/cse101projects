/*********************************************************************************
 * Konan Le, kokhle
 * 2022 Spring CSE101 PA3
 * Graph.h
 * Header file for Graph ADT
 *********************************************************************************/
#pragma once

#include <stdbool.h>
#include <stdio.h>

#include "List.h"

// Predefined constants
#define UNDEF -100
#define NIL 0
// Exported types -----------
typedef struct GraphObj *Graph;

// Constructors and Destructors ----------
Graph newGraph(int n);
void freeGraph(Graph *pG);

// Accessor functions ----------
int getOrder(Graph G);
int getSize(Graph G);
int getDiscover(Graph G, int u); // Pre: 1 <= u <= n = getOrder(G)
int getParent(Graph G, int u);
int getFinish(Graph G, int u); // Pre: 1 <= u <= n = getOrder(G)
void getPath(List L, Graph G, int u);

// Manipulator functions ----------
void addEdge(Graph G, int u, int v); // pre: 1 <= u <= n = getOrder(G)
void addArc(Graph G, int u, int v);  // pre: 1 <= u, v <= n
void DFS(Graph G, List S);           // Pre: length(S) == getOrder(G)

// Other Operations ----------
void printGraph(FILE *out, Graph G);
Graph transpose(Graph G);
Graph copyGraph(Graph G);
