/****************************************************************************************
 *  Konan Le - kokhle
 *  CSE101 Spring 2021
 *  Programming Assignment 1
 *  ListTest.c
 *  A modified ListClient.c
 *  Peronalized Test client for List ADT
 *****************************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"

#define MAX_LEN 300

int main(int argc, char *argv[]) {
  // out = stdout;
  List A = newList();
  List B = newList();
  // List C = NULL;
  if (!A && !B) {
    fprintf(stderr, "A and B haven't been initialized");
    exit(EXIT_FAILURE);
  }
  // Testing printList
  append(A, 0);
  append(A, 7);
  append(A, 5);
  append(A, 9);
  printList(stdout, A);

  // Testing access functions
  if (length(A) != 4) {
    fprintf(stderr, "A does not have length of 4");
    exit(EXIT_FAILURE);
  }
  moveFront(A);
  if (index(A) == -1) {
    fprintf(stderr, "index of cursor wasn't set!");
    exit(EXIT_FAILURE);
  }
  if (front(A) != 0) {
    fprintf(stderr, "front is not set properly");
    exit(EXIT_FAILURE);
  }
  if (back(A) != 9) {
    fprintf(stderr, "back was not set properly");
    exit(EXIT_FAILURE);
  }
  if (get(A) != 0) {
    fprintf(stderr, "get is not working properly");
    exit(EXIT_FAILURE);
  }
  B = copyList(A); // assuming copyList works at this point
  if (!equals(A, B)) {
    fprintf(stderr, "A does not equal B after copyList()");
    exit(EXIT_FAILURE);
  }

  // Should set front to 3
  set(A, 3);
  if (front(A) != 3) {
    fprintf(stderr, "front was not set to 3");
    exit(EXIT_FAILURE);
  }
  moveBack(A);
  if (get(A) != 9) {
    fprintf(stderr, "Cursor was not set to back");
    exit(EXIT_FAILURE);
  }

  movePrev(A);
  if (get(A) != 5) {
    fprintf(stderr, "Cursor was not able to go to prev!");
    exit(EXIT_FAILURE);
  }
  // moveFront semi-tested above already
  moveNext(A);
  if (get(A) != 9) {
    fprintf(stderr, "Cursor was not able to move next!");
    exit(EXIT_FAILURE);
  }
  prepend(A, 8);
  moveFront(A);
  if (get(A) != 8) {
    fprintf(stderr, "Prepend or moveFront did not work!");
    exit(EXIT_FAILURE);
  }

  // append already tested above
  insertAfter(A, 12);
  moveNext(A);
  if (get(A) != 12) {
    fprintf(stderr, "insertAfter or moveNext did not work.");
    exit(EXIT_FAILURE);
  }

  insertBefore(A, 35);
  movePrev(A);
  if (get(A) != 35) {
    fprintf(stderr, "insertBefore or movePrev did not work.");
    exit(EXIT_FAILURE);
  }
  prepend(A, 12);
  prepend(A, 15);
  deleteFront(A);
  moveFront(A);
  if (get(A) != 12) {
    fprintf(stderr, "error in deleteFront");
    exit(EXIT_FAILURE);
  }
  append(A, 42);
  append(A, 53);
  deleteBack(A);
  moveBack(A);
  if (get(A) != 42) {
    fprintf(stderr, "Error in deleteBack");
    exit(EXIT_FAILURE);
  }
  prepend(A, 12);
  prepend(A, 13);
  prepend(A, 14);
  moveFront(A);
  moveNext(A);
  delete (A);
  moveFront(A);
  moveNext(A);
  if (get(A) != 12) {
    fprintf(stderr, "Failed big test");
    exit(EXIT_FAILURE);
  }
  clear(A);
  printf("cleared first set of tests");
  // next tests

  // List C = NULL;
  int i;
  for (i = 1; i <= 10; i++) {
    append(A, i);
    prepend(B, i);
  }
  printList(stdout, A);
  printf("\n");
  printList(stdout, B);
  printf("\n");
  append(A, 1);
  printf("Append A, 1 works\n");
  append(A, 2);
  printf("append A, 2 works\n");
  append(A, 3);
  printf("a, 3 works\n");
  append(A, 5);
  printf("about to start printlist\n");
  if (A == NULL) {
    printf("LIST IS NULL!!!!!!!!!\n");
    exit(EXIT_FAILURE);
  }
  printList(stdout, A);
  printf("printlist worked with no crashes\n");

  append(A, 1);
  deleteBack(A);
  append(A, 2);
  append(A, 3);
  append(A, 5);
  moveFront(A);
  insertAfter(A, 12);
  deleteBack(A);
  append(A, 1);
  append(A, 5);
  append(A, 16);
  append(A, 176);
  append(A, 3214);
  append(A, 123456);
  moveFront(A);
  printf("Moved cursor to front with no errors\n");
  moveNext(A);
  moveNext(A);
  moveNext(A);
  printf("Moved 3 over, index should be 2\n");
  if (index(A) != 3) {
    printf("index_cursor is not equal to 3!\n");
    return 1;
  }

  moveNext(A);

  moveNext(A);

  moveNext(A);
  printf("Successfully moved next 6 times\n");
  clear(A);

  // next tests
  append(A, 1);
  append(A, 5);
  append(A, 7);
  moveBack(A);
  append(A, 45);
  append(A, 51);
  append(A, 3214);
  append(A, 7125987);
  deleteBack(A);
  if (index(A) != 2) {
    printf("wrong index! should be 2\n");
    return 1;
  }

  printf("Moving around, potential double free");
  moveBack(A);
  movePrev(A);
  movePrev(A);
  if (index(A) != 3) {
    printf("wrong index! should be 3\n");
    return 2;
  }

  moveFront(A);
  movePrev(A);
  if (index(A) != -1) {
    return 3;
  }
  printf("final clear\n");
  clear(A);
  // new tests

  // Insert after index test
  /*
  append(A, 5);
  append(A, 6);
  append(A, 4);
  append(A, 33);
  append(A, 2);
  append(A, 1);
  moveBack(A);

  insertAfter(A, 75);
  */
  /*
  moveNext(A);
  if (index(A) != 6)
    return 1;
  insertAfter(A, 345);
  moveBack(A);
  if (index(A) != 7)
    return 2;
    */

  // DleteFront_index
  /*
  prepend(A, 5);
  prepend(A, 65);
  prepend(A, 43);
  prepend(A, 2);
  prepend(A, 8);
  prepend(A, 1);
  moveFront(A);
  deleteFront(A);
  if (index(A) != -1) {
    printf("index_cursor is not undefined!\n");
    return 1;
  }

  moveBack(A);
  printf("movedback\n");
  deleteFront(A);
  printf("deletedfront");
  if (index(A) != 3) {
    printf("index is not 3!\n");
    return 2;
  }
  */

  // Delete length tests
  /*
  append(A, 1);
      append(A, 2);
      printList(out, A);
      moveFront(A);
      printList(out, A);
      printf("About to start the first delete\n");
      delete (A);
      printf("Successfully did first delete\n");
      append(A, 3);
      append(A, 5);
      moveFront(A);
      insertAfter(A, 12);
      delete (A);
  int len = length(A);
  printf("len: %d\n", len);
      if (length(A) != 3) {
        printf("Length is not equal to 3!");
        return 1;
      }
      */
  // Delete Index Tests
  /*
   prepend(A, 5);
   prepend(A, 65);
   prepend(A, 43);
   moveBack(A);
   delete (A);
   if (index(A) != -1) {
     printf("index is not -1!\n");
     return 1;
   }
   prepend(A, 2);
   prepend(A, 8);
   prepend(A, 1);
   moveBack(A);
   printf("Delete_index test 4 about to commence \n");
   if (index(A) != 4) {
     printf("Index is not 4!\n");
     return 2;
   }
   delete (A);
   moveBack(A);
   if (index(A) != 3) {
     printf("index is not 3");
     return 3;
   }
   moveFront(A);
   printf("about to delete a for test 4\n");
   delete (A);
   moveFront(A);
   if (index(A) != 0) {
     printf("Index should be 0");
     return 4;
   }
   printf("about to delete A for test 5\n");
   int cur = get(A);
     int ind = index(A);
     printf("ind: %d\n", ind);
   printf("cur: %d\n", cur);
   delete (A);
   printf("deleted A\n");
   if (index(A) != -1) {
     printf("index should be undefined\n");
     return 5;
   }
 */

  // insertbefore equals test
  /*
  prepend(A, 1);
  prepend(B, 1);
  prepend(A, 2);
  moveFront(B);
  printf("about to call insertbefore\n");
  insertBefore(B, 2);
  printf("successfully called insertbefore\n");
  if (!equals(A, B)) {
    printf("A, B not equal to each other\n");
  return 1;
  }
  prepend(B, 3);
  moveFront(A);
  insertBefore(A, 3);
  if (!equals(A, B)) {
    printf("A and B are not equal\n");
    return 2;
  }
  printf("sucessfully completed all tests");
  */

  // Non-empty front
  /*
  prepend(A, 5);
  append(A, 7);
  prepend(A, 2);
  printf("List after prepend 5, append 7, prepend 2\n");
  printList(out, A);
  moveFront(A);
  int cur = get(A);
  printf("cur data: %d\n", cur);
  insertBefore(A, 43);
  deleteFront(A);
  printf("\n");
  printList(out, A);
  cur = get(A);
  printf("cur data after deleteFront: %d\n", cur);
  delete (A);
  printf("\n");
  printList(out, A);
  printf("cur data after delete(): %d\n", cur);
  if (front(A) != 5) {
    printf("Front data is not equal to 5!\n");
    return 1;
  }
  */

  // empty copylist
  /*
  List C = copyList(A);
    bool res = (!equals(A, C) || A == C);
    freeList(&C);
    if (res) {
      return 1;
    }
    */

  /*
    // nonempty copylist'
    append(A, 2);
    prepend(A, 1);
    moveFront(A);
    List C = copyList(A);
    bool res = (index(A) != 0 || !equals(A, C) || A == C);
    printf("index: %d\n", index(A));
    printf("boolean: %d\n", !equals(A, C));
    printf("boolean2: %d\n", A == C);
    freeList(&C);
    if (res)
      return 1;
    freeList(&A);
    */

  // cleanup
  printf("double free at the end? probably error in the way I formatted my "
         "files\n");
  freeList(&A);
  printf("freed A\n");
  freeList(&B);
  printf("freed B\n");
  return 0;
}
