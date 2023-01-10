/*********************************************************************************
 * Konan Le, kokhle
 * 2022 Spring CSE101 PA4
 * Matrix.c
 * Contains functions for use in Matrix ADT
 *********************************************************************************/
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "Matrix.h"

// private structs
typedef struct EntryObj *Entry;

typedef struct EntryObj {
  int col;
  double val;
} EntryObj;

typedef struct MatrixObj {
  int size;
  List *rows;
} MatrixObj;
// Constructors and Destructors ----------

// newMatrix() - returns new nXn Matrix obj in zero state
Matrix newMatrix(int n) {
  Matrix M = malloc(sizeof(MatrixObj));
  if (M) {
    M->size = n;
    M->rows = (List *)malloc(sizeof(List) * (M->size + 1));
    for (int i = 1; i < (M->size + 1); i++) {
      M->rows[i] = newList();
    }
    return M;
  } else {
    fprintf(stderr,
            "Error in Matrix ADT: newMatrix(), not enough memory for M!\n");
    exit(EXIT_FAILURE);
  }
}

// newEntry() returns a new EntryObj with col and val
Entry newEntry(int column, double value) {
  Entry E = malloc(sizeof(EntryObj));
  E->col = column;
  E->val = value;
  return E;
}

void freeEntry(Entry *pE) {
  if (pE != NULL && *pE != NULL) {
    free(*pE);
    *pE = NULL;
    pE = NULL; // swap the order?
  }
}

// freeMatrix() clears up heap memory allocated to Matrix obj
void freeMatrix(Matrix *pM) {
  if (pM != NULL && *pM != NULL) {
    // free entries
    makeZero(*pM);
    for (int i = 1; i < ((*pM)->size + 1); i++) {
      // Lists are empty, now free allocated memory
      freeList(&((*pM)->rows[i]));
    }
    free((*pM)->rows);
    (*pM)->rows = NULL;
    free(*pM);
    *pM = NULL;
  }
}

// Access Functions ----------

// size() returns number of entries in matrix M
int size(Matrix M) {
  if (M == NULL) {
    fprintf(stderr, "Error in Matrix ADT: size(), M is NULL!\n");
    exit(EXIT_FAILURE);
  }
  // Size of matrix is nXn
  return M->size;
}

// NNZ() returns number of non-zero elements in M.
int NNZ(Matrix M) {
  // simply add all lengths of all lists
  if (M == NULL) {
    fprintf(stderr, "Error in Matrix ADT: NNZ(), M is NULL\n");
    exit(EXIT_FAILURE);
  }
  int nnz = 0;
  for (int i = 1; i < (size(M) + 1); i++) {
    if (length(M->rows[i]) != 0) {
      nnz += length(M->rows[i]);
    }
  }
  return nnz;
}

// equals() returns 1 if matrices A and B are equal, 0 otherwise.
int equals(Matrix A, Matrix B) {
  if (A == NULL && B == NULL) {
    return 1;
  }
  if (A == NULL) {
    fprintf(stderr, "Error in Matrix ADT: equals(), A is NULL\n");
    exit(EXIT_FAILURE);
  }
  if (B == NULL) {
    fprintf(stderr, "Error in matrix ADT: equals(), B is NULL\n");
    exit(EXIT_FAILURE);
  }
  if (size(A) != size(B)) {
    // Not same size, can't be equal.
    return 0;
  }
  Matrix tempM = copy(B);
  for (int i = 1; i < (size(A) + 1); i++) {
    if (length(A->rows[i]) != length(tempM->rows[i])) {
      // entries won't match up
      freeMatrix(&tempM);
      return 0;
    }
    moveFront(A->rows[i]);
    moveFront(tempM->rows[i]);
    while (index(A->rows[i]) != -1) {
      Entry entA = (Entry)get(A->rows[i]);
      Entry entB = (Entry)get(tempM->rows[i]);
      if ((entA->col != entB->col) || (entA->val != entB->val)) {
        // Column doesn't match or value doesn't match, not equal.
        // Each entry should be exactly the same, in same order.
        freeMatrix(&tempM);
        return 0;
      }
      moveNext(A->rows[i]);
      moveNext(tempM->rows[i]);
    }
  }
  freeMatrix(&tempM);
  // Everything seems to be equal - return true
  return 1;
}

// makeZero() resets matrix M to zero matrix state
void makeZero(Matrix M) {
  if (M == NULL) {
    fprintf(stderr, "Error in Matrix ADT: makeZero(), M is NULL!\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i < (size(M) + 1); i++) {
    moveFront(M->rows[i]);
    while (index(M->rows[i]) != -1) {
      Entry delEnt = (Entry)get(M->rows[i]);
      moveNext(M->rows[i]);
      freeEntry(&delEnt);
    }
    clear(M->rows[i]);
  }
  // delete Entries here?
}

// changeEntry() changes ith row, jth column of M to value x.
// Preconditions: 1 <= i, i <= size(M). 1 <= j, j <= size(M).
void changeEntry(Matrix M, int i, int j, double x) {
  if (M == NULL) {
    fprintf(stderr, "Error in Matrix ADT: changeEntry(), M is NULL!\n");
    exit(EXIT_FAILURE);
  }
  if ((1 > i) || (i > size(M))) {
    fprintf(stderr,
            "Error in Matrix ADT: changeEntry(), i (row) is out of bounds.\n");
    exit(EXIT_FAILURE);
  }
  if (j > size(M) || 1 > j) {
    fprintf(stderr,
            "Error in Matrix ADT: changeEntry(), j (col) is out of bounds!\n");
    exit(EXIT_FAILURE);
  }
  // Row i == List, column J = entryobj data but not quite
  // Need to check if point is already there - if so, do nothing?
  // If List is empty, simply add it
  // Entry E = newEntry(j, x);
  if (length(M->rows[i]) == 0 && x != 0) {
    // Don't add any 0 values
    Entry E = newEntry(j, x);
    append(M->rows[i], E);
  } else if (length(M->rows[i]) > 0) {
    // Insertion sort
    moveBack(M->rows[i]);
    // while loop to move cursor
    while (index(M->rows[i]) != -1) {
      Entry Ecomp = (Entry)get(M->rows[i]); // need to free this?
      if (j == Ecomp->col) {
        // If column space already exists, overwrite the data and exit
        if (x == 0) {
          // If changing value to 0, need to clear it
          delete (M->rows[i]);
          freeEntry(&Ecomp);
          return;
        }
        Ecomp->val = x;
        return;
      } else if (j < Ecomp->col) {
        // If inserted entry column is less than the current column
        movePrev(M->rows[i]);
      } else {
        // If inserted entry column is greater than current column
        break;
      }
    }
    // Outside of while loop to move cursor along row, now insert the Entry into
    // the list
    if (index(M->rows[i]) == -1) {
      Entry E = newEntry(j, x);
      prepend(M->rows[i], E);
      return;

    } else if (x == 0) {
      // trying to add a 0, don't do anything
      // add this check earlier to make it more efficient?
      return;
    } else {
      // Prev is larger, so insert after.
      Entry E = newEntry(j, x);
      insertAfter(M->rows[i], E);
      return;
    }
  }
}

// copy() returns matrix obj with same entries as matrix A
Matrix copy(Matrix A) {
  if (A == NULL) {
    fprintf(stderr, "Error in matrix ADT: copy(), M is NULL\n");
    exit(EXIT_FAILURE);
  }
  Matrix newM = newMatrix(A->size);
  for (int i = 1; i < (newM->size + 1); i++) {
    moveFront(A->rows[i]);
    while (index(A->rows[i]) != -1) {
      Entry E = (Entry)get(A->rows[i]);
      changeEntry(newM, i, E->col, E->val);
      moveNext(A->rows[i]);
    }
  }
  return newM;
}

// transpose() returns a matrix with swapped columns and edges in Matrix A
Matrix transpose(Matrix A) {
  // Swap columns and rows
  if (A == NULL) {
    fprintf(stderr, "Error in Matrix ADT; transpose(), A is NULL\n");
    exit(EXIT_FAILURE);
  }
  // swap column and rows - read each columns rows and columns, make new entries
  // for that, put it in new matrix seems inefficient to store it in variables
  // first - could I just do it directly?
  Matrix newM = newMatrix(A->size);
  for (int i = 1; i < (newM->size + 1); i++) {
    moveFront(A->rows[i]);
    while (index(A->rows[i]) != -1) {
      Entry tempEn = (Entry)get(A->rows[i]);
      changeEntry(newM, tempEn->col, i, tempEn->val);
      moveNext(A->rows[i]);
    }
  }
  // freeEntry(&tempEn);
  return newM;
}

// scalarMult() multiplies every entry in a matrix by x, and outputs the
// multiplied matrix
Matrix scalarMult(double x, Matrix A) {
  if (A == NULL) {
    fprintf(stderr, "Error in Matrix ADT: scalarMult(), A is NULL!\n");
    exit(EXIT_FAILURE);
  }
  Matrix newM = newMatrix(A->size);
  if (x == 0) {
    return newM;
  }
  for (int i = 1; i < (newM->size + 1); i++) {
    moveFront(A->rows[i]);
    while (index(A->rows[i]) != -1) {
      Entry tempEn = (Entry)get(A->rows[i]);
      double mult = x * tempEn->val;
      // Change entry could maybe be done faster
      // if bottlenecking, just do modified insertion sort
      changeEntry(newM, i, tempEn->col, mult);
      moveNext(A->rows[i]);
    }
  }
  // freeEntry(&tempEn);
  return newM;
}

// sum() returns new matrix with matrix A and B added together.
Matrix sum(Matrix A, Matrix B) {
  if (A == NULL || B == NULL) {
    fprintf(stderr, "Error in Matrix ADT: sum(), A or B is NULL\n");
    exit(EXIT_FAILURE);
  }
  if (size(A) != size(B)) {
    fprintf(
        stderr,
        "Error in Matrix ADT: sum(), A and B do not have matching sizes!\n");
    exit(EXIT_FAILURE);
  }
  Matrix tempM = copy(B);
  Matrix newM = newMatrix(A->size);
  double newSum = 0.0; // setting up new sum to add to Matrix C
  // drag and lead!
  for (int i = 1; i < (A->size + 1); i++) {
    // go through each matrix row, add as needed
    moveFront(A->rows[i]);
    moveFront(tempM->rows[i]);
    if (length(A->rows[i]) == 0 && length(tempM->rows[i]) != 0) {
      // just add all of B
      while (index(tempM->rows[i]) != -1) {
        Entry tempEnB = (Entry)get(tempM->rows[i]);
        changeEntry(newM, i, tempEnB->col, tempEnB->val);
        moveNext(tempM->rows[i]);
      }
    }

    if (length(tempM->rows[i]) == 0 && length(A->rows[i]) != 0) {
      // just add all of A
      while (index(A->rows[i]) != -1) {
        Entry tempEnA = (Entry)get(A->rows[i]);
        changeEntry(newM, i, tempEnA->col, tempEnA->val);
        moveNext(A->rows[i]);
      }
    }

    while (index(A->rows[i]) != -1 || index(tempM->rows[i]) != -1) {
      // Going through each column
      if (index(A->rows[i]) != -1 && index(tempM->rows[i]) != -1) {
        Entry tempEnA = (Entry)get(A->rows[i]);
        Entry tempEnB = (Entry)get(tempM->rows[i]);
        if (tempEnA->col == tempEnB->col) {
          // same row, same column, add the values
          newSum = tempEnA->val + tempEnB->val;
          if (newSum != 0) {
            changeEntry(newM, i, tempEnA->col, newSum);
          }
          moveNext(A->rows[i]);
          moveNext(tempM->rows[i]);
        } else if (tempEnA->col < tempEnB->col) {
          //
          changeEntry(newM, i, tempEnA->col, tempEnA->val);
          moveNext(A->rows[i]);
        } else {
          changeEntry(newM, i, tempEnB->col, tempEnB->val);
          moveNext(tempM->rows[i]);
        }
      } else if (index(A->rows[i]) != -1) {
        // push a
        Entry tempEnA = (Entry)get(A->rows[i]);
        changeEntry(newM, i, tempEnA->col, tempEnA->val);
        moveNext(A->rows[i]);
      } else {
        // push b
        Entry tempEnB = (Entry)get(tempM->rows[i]);
        changeEntry(newM, i, tempEnB->col, tempEnB->val);
        moveNext(tempM->rows[i]);
      }
    }
  }
  freeMatrix(&tempM);
  return newM;
}

// diff() returns a new matrix that represents matrix B minus matrix A.
Matrix diff(Matrix A, Matrix B) {
  if (A == NULL || B == NULL) {
    fprintf(stderr, "Error in Matrix ADT: sum(), A or B is NULL\n");
    exit(EXIT_FAILURE);
  }
  if (size(A) != size(B)) {
    fprintf(
        stderr,
        "Error in Matrix ADT: sum(), A and B do not have matching sizes!\n");
    exit(EXIT_FAILURE);
  }
  Matrix tempM = copy(B);
  Matrix newM = newMatrix(A->size);
  double newSum = 0.0; // setting up new sum to add to Matrix C
  // drag and lead!
  for (int i = 1; i < (A->size + 1); i++) {
    // go through each matrix row, add as needed
    moveFront(A->rows[i]);
    moveFront(tempM->rows[i]);
    if (length(A->rows[i]) == 0 && length(tempM->rows[i]) != 0) {
      // just add all of B
      while (index(tempM->rows[i]) != -1) {
        Entry tempEnB = (Entry)get(tempM->rows[i]);
        changeEntry(newM, i, tempEnB->col, (tempEnB->val * -1));
        moveNext(tempM->rows[i]);
      }
    }

    if (length(tempM->rows[i]) == 0 && length(A->rows[i]) != 0) {
      // just add all of A
      while (index(A->rows[i]) != -1) {
        Entry tempEnA = (Entry)get(A->rows[i]);
        changeEntry(newM, i, tempEnA->col, tempEnA->val);
        moveNext(A->rows[i]);
      }
    }

    while (index(A->rows[i]) != -1 || index(tempM->rows[i]) != -1) {
      // Going through each column
      if (index(A->rows[i]) != -1 && index(tempM->rows[i]) != -1) {
        Entry tempEnA = (Entry)get(A->rows[i]);
        Entry tempEnB = (Entry)get(tempM->rows[i]);
        if (tempEnA->col == tempEnB->col) {
          // same row, same column, add the values
          newSum = tempEnA->val - tempEnB->val;
          if (newSum != 0) {
            changeEntry(newM, i, tempEnA->col, newSum);
          }
          moveNext(A->rows[i]);
          moveNext(tempM->rows[i]);
        } else if (tempEnA->col < tempEnB->col) {
          //
          changeEntry(newM, i, tempEnA->col, tempEnA->val);
          moveNext(A->rows[i]);
        } else {
          changeEntry(newM, i, tempEnB->col, (tempEnB->val * -1));
          moveNext(tempM->rows[i]);
        }
      } else if (index(A->rows[i]) != -1) {
        // push a
        Entry tempEnA = (Entry)get(A->rows[i]);
        changeEntry(newM, i, tempEnA->col, tempEnA->val);
        moveNext(A->rows[i]);
      } else {
        // push b
        Entry tempEnB = (Entry)get(tempM->rows[i]);
        changeEntry(newM, i, tempEnB->col, (tempEnB->val * -1));
        moveNext(tempM->rows[i]);
      }
    }
  }
  freeMatrix(&tempM);
  return newM;
}

// vectorDot() multiplies matching entries in a list and adds them together
// 1st member with 1st member, 2nd with 2nd, and so on.
double vectorDot(List P, List Q) {
  // precondition, should probably check if the lengths are the same...
  // but maybe preconditions are uneeded since it's private func

  moveFront(P);
  moveFront(Q);
  double total = 0.0;
  if (length(P) == 0 || length(Q) == 0) {
    return total;
  }
  while (index(P) != -1 && index(Q) != -1) {
    // Going through each column
    Entry tempEnA = (Entry)get(P);
    Entry tempEnB = (Entry)get(Q);
    if (tempEnA->col == tempEnB->col) {
      // same row, same column, multiply and add the values
      total += (tempEnA->val * tempEnB->val);
      moveNext(P);
      moveNext(Q);
    } else if (tempEnA->col < tempEnB->col) {
      // A times 0 is 0, so add nothing to total
      moveNext(P);
    } else {
      // B times 0 is 0, so add nothing to total
      moveNext(Q);
    }
  }

  // Gone through both lists, multiplied. return total.
  return total;
}

// product() returns a new matrix that represents matrix A times matrix B.
Matrix product(Matrix A, Matrix B) {
  if (A == NULL || B == NULL) {
    fprintf(stderr, "Error in Matrix ADT: product(), A or B is NULL!\n");
    exit(EXIT_FAILURE);
  }
  if (size(A) != size(B)) {
    //
    fprintf(stderr,
            "Error in Matrix ADT: product(), A and B do not match sizes!\n");
    exit(EXIT_FAILURE);
  }
  Matrix newM = newMatrix(size(A));
  Matrix tempM = transpose(B);
  for (int i = 1; i < (size(A) + 1); i++) {
    // go through each row, multiply it
    for (int j = 1; j < (size(tempM) + 1); j++) {
      double prod = vectorDot(A->rows[i], tempM->rows[j]);
      if (prod != 0) {
        changeEntry(newM, i, j, prod);
      }
    }
  }

  freeMatrix(&tempM);
  return newM;
}

// Helper function to be used in printMatrix
void printEntry(FILE *out, Entry E) {
  fprintf(out, "(%d, %.1lf) ", E->col, E->val);
}

// printMatrix() prints out lists of every non-zero entry in Matrix M
void printMatrix(FILE *out, Matrix M) {
  if (M == NULL) {
    fprintf(stderr, "Error in Matrix ADT: printMatrix, M is NULL!\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i < (size(M) + 1); i++) {
    if (length(M->rows[i]) != 0) {
      moveFront(M->rows[i]);
      fprintf(out, "%d: ", i);
      while (index(M->rows[i]) != -1) {
        Entry tempEn = (Entry)get(M->rows[i]);
        printEntry(out, tempEn);
        moveNext(M->rows[i]);
      }
      fprintf(out, "\n");
    }
  }
}
