/*********************************************************************************
 * Konan Le, kokhle
 * 2022 Spring CSE101 PA2
 * Graph.h
 * Header file for Graph ADT
 *********************************************************************************/
#pragma once

#include <stdbool.h>
#include <stdio.h>

#include "List.h"

// Predefined constants
#define INF -100
#define NIL -200
// Exported types -----------
typedef struct GraphObj *Graph;

// Constructors and Destructors ----------
Graph newGraph(int n);
void freeGraph(Graph *pG);

// Accessor functions ----------
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

// Manipulator functions ----------
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

// Other Operations ----------
void printGraph(FILE *out, Graph G);
