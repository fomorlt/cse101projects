/*********************************************************************************
 * Konan Le, kokhle
 * 2022 Spring CSE101 PA4
 * Matrix.h
 * Header file for Matrix ADT
 *********************************************************************************/
#pragma once

#ifndef MATRIX_H_INCLUDE_
#define MATRIX_H_INCLUDE_
#include <stdbool.h>
#include <stdio.h>

#include "List.h"

// Exported types ----------
// typedef MatrixObj* Matrix;
typedef struct MatrixObj *Matrix;

// newMatrix() returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n);

// freeMatrix() frees heap memory associiated with *pM, and sets *pM to NULL.
void freeMatrix(Matrix *pM);

// Access functions ----------

// size() returns the size of square matrix M.
int size(Matrix M);

// NNZ() returns number of non-zero elements in M
int NNZ(Matrix M);

// equals() returns true (1) if matrices A and B are equal, false (0) if
// otherwise. Not boolean
int equals(Matrix A, Matrix B);

// Manipulation procedures ----------

// makeZero() resets matrix M to zero matrix state
void makeZero(Matrix M);

// changeEntry() changes ith row, jth column of M to value x.
// Precondition: 1 <= i, i <= size(M). 1<=j, j <= size(M).
// Time complexity worst case: O(a)
void changeEntry(Matrix M, int i, int j, double x);

// Matrix Arithmetic

// copy() returns reference to a NEW matrix object, with the same entries as A.
// Time complexity worst case:  O(n+a).
Matrix copy(Matrix A);

// transpose() returns reference to new Matrix object which represents transpose
// of A. TC worst case: O(n+a)
Matrix transpose(Matrix A);

// scalarMult() returns reference to new Matrix object representing x times A.
// Time complexity worst case: O(n+a)
Matrix scalarMult(double x, Matrix A);

// sum() returns reference to new Matrix object, representing A + B.
// pre: size(A) == size(B)
// TC worst case: O(n+a+b)
Matrix sum(Matrix A, Matrix B);

// diff() returns reference to new Matrix object representing A - B.
// pre: size(A) == size(B)
// TC worst case: O(n+a+b)
Matrix diff(Matrix A, Matrix B);

// product() returns a reference to new Matrix object representing AB.
// pre: size(A) == size(B)
// TC worst case: O(n^2+a+b)
Matrix product(Matrix A, Matrix B);

// Other functions ----------
// printMatrix() prints a string representation o Matrix M to out. No zero rows
// are printed (sparse matrix). Every non-zero row is one line - row number,
// colon, space, spaced list of pairs "(col, val)" for each non-zero value in
// the row. Double val will be rounded to 1 decimal point.
void printMatrix(FILE *out, Matrix M);

#endif
