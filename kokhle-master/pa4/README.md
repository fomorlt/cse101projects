# CSE 101, Spring Quarter 2022

## Konan Le - kokhle

## Programming Assignment 4

#### Sparse.c
<p> Main file for PA4, exercising Matrix ADT. Sparse.c takes in a text file detailing 2 sparce matrices, then uses functions provided in Matrix.c to perform various mathematical functions on the matrices. For example, transposing a matrix, adding the two matrices, subtracting them, multiplying them, et cetera. Sparse.c will then write to an output file the results of these various functions. </p>

#### Matrix.c
<p> Source code for Matrix ADT. Relies on List ADT. </p>

#### Matrix.h
<p> Header file for use in testing files and Sparse.c. Contains function prototypes and declarations for use in Matrix ADT and other user files. </p>

#### MatrixTest.c
<p> Personalized testing file which calls the various functions defined in Matrix.c and checks for errors. </p>

#### List.c
<p> Source code for List ADT. Modified from earlier PAs to use void pointers instead of integers. </p>

#### List.h
<p> Header file for use in testing files, Matrix.c and Sparse.c. Contains function prototypes and declarations for use in List ADT, Matrix ADT, and other user files. </p>

#### ListTest.c
<p> Personalized testing file which calls the variosu functions defined in List.c and checks for errors. </p>

#### Makefile
<p> Allows the user to perform various tasks related to compiling, such as: cleaning binaries, formatting code, testing for memory leaks, and of course compiling the binaries for program execution. </p>

#### README.md
<p> A table of contents for PA4. Lists each file, their purpose, and a general description. </p>
