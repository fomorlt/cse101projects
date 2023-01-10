# CSE 101, Spring Quarter 2021

## Konan Le - kokhle

## Programming Assignment 3

#### Graph.c
<p> Source code for Graph ADT. Contains links to List ADT. </p>

#### Graph.h
<p> Header file for use in testing files and FindComponents.c. Contains functions prototypes, declarations and macros for use
in Graph ADT and other user files. </p>

#### List.c
<p> Source code for List ADT. Contains a private Node ADT for use in creating Lists. </p>

#### List.h
<p> Header file for use in testing files, Graph ADT and FindComponents.c. Contains function prototypes, declarations and
macros for use in List ADT and other user files. </p>

#### FindComponents.c
<p> Main file for PA3, exercising the Graph ADT. FindComponents.c takes in a text file with information about a directed graph
(vertices, directed edges), performs a Depth First Search (DFS) as it compiles a stack. Then, it performs another DFS on the
transpose of the graph using the new stack as the order for source vertices. The NIL parents of the resulting stack of the
second DFS will mark a complete strongly connected component. FindComponents.c will then print out the adjacency list and the
strongly connected components of the graph.
</p>

#### Makefile
<p> Allows the user to perform various tasks related to compiling, such as: cleaning binaries, formatting code, testing
for memory leaks, and of course compiling the binaries themselves for program execution. </p>

#### README.md
<p> A table of contents for PA3. Lists each file, their purpose, and a general description. </p>

### Comments
<p>Much of the work was based on my code for PA2. I implemented the time counter as a part of the Graph ADT pointers,
which allowed me to increment time as I needed for that particular graph's DFS.</p>
