/*********************************************************************************
 * Konan Le, kokhle
 * 2022 Spring CSE101 PA4
 * ListTest.c
 * Personalized testing client for List ADT
 *********************************************************************************/
#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  List A = newList();
  int X[] = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
             11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

  // Checking initialization
  if (!A) {
    fprintf(stderr, "A has not been initialized!\n");
    exit(EXIT_FAILURE);
  }
  if (index(A) != -1) {
    fprintf(stderr, "index is not -1!\n");
    exit(EXIT_FAILURE);
  }
  if (length(A) != 0) {
    fprintf(stderr, "length is not 0!\n");
  }

  // Testing append and other A
  append(A, &X[3]); // append 3
  append(A, &X[5]); // append 5
  append(A, &X[8]); // append 8
  moveFront(A);
  if (index(A) != 0) {
    fprintf(stderr, "moveFront doesn't set index to 0");
    exit(EXIT_FAILURE);
  }
  // Testing moveNext
  moveNext(A);
  if (index(A) != 1 || *(int *)get(A) != 5) {
    fprintf(stderr, "moveNext doesn't work!");
    exit(EXIT_FAILURE);
  }
  deleteFront(A);
  // List should be 5, 8
  // Should have deleted Front
  if (length(A) != 2) {
    fprintf(stderr, "Error in deleteFront length\n");
    exit(EXIT_FAILURE);
  }
  moveFront(A);
  if (*(int *)get(A) != 5) {
    fprintf(stderr, "Error in deleteFront!\n");
    exit(EXIT_FAILURE);
  }

  // Testing append and moveFront
  append(A, &X[11]);
  moveBack(A);
  // List should be 5, 8, 11
  if (*(int *)get(A) != 11) {
    fprintf(stderr, "Error in append or moveBack\n");
    exit(EXIT_FAILURE);
  }
  // Testing prepend and moveBack
  // List should be 20, 5, 8, 11
  prepend(A, &X[20]);
  moveFront(A);
  if (*(int *)get(A) != 20) {
    fprintf(stderr, "Error in prepend or moveFront\n");
    exit(EXIT_FAILURE);
  }

  // Testing delete
  // Trying to delete 2nd element (5)
  moveNext(A);
  delete (A);
  if (index(A) != -1) {
    fprintf(stderr, "Error in delete: cursor should be undefined\n");
    exit(EXIT_FAILURE);
  }
  // List at this point should be: 20, 8, 11
  // After deleting cur element, value after front should be 5
  moveFront(A);
  moveNext(A);
  if (*(int *)get(A) != 8) {
    fprintf(stdout, "Cursor value: %d\n", *(int *)get(A));
    fprintf(stderr, "Error in delete: should have deleted 3\n");
    exit(EXIT_FAILURE);
  }
  // Testing deleteFront, deleteBack, insertAfter, insertBefore
  // A real limit test
  // At this point, list should be: 20, 8, 11
  deleteFront(A);
  deleteBack(A);
  moveFront(A);
  insertBefore(A, &X[12]);
  insertBefore(A, &X[11]);
  insertAfter(A, &X[15]);
  insertAfter(A, &X[19]);
  // List at this point should be 12, 11, 8, 19, 15
  moveBack(A);
  movePrev(A);
  insertAfter(A, &X[14]);
  // 12, 11, 8, 19, 14, 15, cur is on 19
  moveNext(A);
  movePrev(A);
  movePrev(A);
  moveNext(A);
  moveNext(A);
  if (*(int *)get(A) != 14) {
    fprintf(stderr, "Failed limit test!\n");
    exit(EXIT_FAILURE);
  }
  // Testing Set:
  moveFront(A);
  moveNext(A);
  set(A, &X[18]);
  // 12, 18, 8, 19, 14, 15
  // Going to try shifting around, trying to throw off index and cursor
  // and whatnot
  moveBack(A);
  movePrev(A);
  movePrev(A);
  moveNext(A);
  moveFront(A);
  moveNext(A);
  if (*(int *)get(A) != 18 || index(A) != 1) {
    fprintf(stderr, "Error with set or move functions!\n");
    exit(EXIT_FAILURE);
  }

  // Testing front and back
  if (*(int *)front(A) != 12) {
    fprintf(stderr, "error in front!\n");
    exit(EXIT_FAILURE);
  }
  if (*(int *)back(A) != 15) {
    fprintf(stderr, "error in back!\n");
    exit(EXIT_FAILURE);
  }

  // Testing clear
  clear(A);
  if (length(A) != 0 || index(A) != -1) {
    fprintf(stderr, "clear doesn't work.\n");
    exit(EXIT_FAILURE);
  }

  freeList(&A);
  printf("Passed all tests!\n");
  return (0);
}
