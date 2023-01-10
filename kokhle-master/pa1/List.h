/*********************************************************************************
 * Konan Le, kokhle
 * 2022 Spring CSE101 PA1
 * List.h
 * Header file for List ADT
 *********************************************************************************/
#pragma once

#include <stdbool.h>
#include <stdio.h>
// Exported types ----------
typedef struct ListObj *List;
typedef int ListElement;

// Constructors and Destructors ----------
List newList(void);
void freeList(List *pL);

// Access functions ----------
int length(List L); // returns num of elements in L
int index(List L);  // returns index of cursor element if defined, -1 otherwise
int get(List L);    // returns cursor element
int front(List L);  // returns front element of L
int back(List L);   // returns back element of L
bool equals(List A, List B); // Checks if A and B are in same state

// Manipulation procedures ----------
void clear(List L);      // Reset L to original empty state
void set(List L, int x); // overwrite cursor element's data with X
void moveFront(List L);  // If L is not-empty, sets cursor under front element.
                         // Otherwise, does nothing
void moveBack(List L);   // If L is non-empty, sets cursor under back element.
                         // Otherwise, does nothing.
void movePrev(
    List L); // If cursor is defined and not at front, move cursor one step
             // toward the front of L. If cursor is defined and at the front,
             // cursor becomes undefined. If cursor is undefined, do nothing.

void moveNext(List L); // If cursor is defined and not at back, move cursor one
                       // step toward back.
                       // If cursor is defined and at back, cursor becomes
                       // undefined. If cursor is undefined, do nothing

void prepend(List L, int x); // Insert new element into L. If L is non-empty,
                             // insertion takes place before front element.
void append(List L,
            int x); // Insert new element into L. If L is non-empty, insertion
                    // takes place after back element.
void insertBefore(List L, int x); // Inserts a new element before cursor
                                  // Pre: length() > 0, index() >= 0.
void insertAfter(List L, int x);  // Insert new element after cursor.
                                  // pre: length() > 0 , index() >= 0.
void deleteFront(List L);         // delete front element. Pre: Length() > 0.
void deleteBack(List L);          // Delete back element. Pre: Length() > 0
void delete (List L); // delete cursor element, making cursor undefined. Pre:
                      // length() > 0, index() >= 0.

// Other operations -----------

// Prints to a file pointed to be out variable, a string representation of L
// consisting of: sequence of integers, with front on the left hand side.
void printList(FILE *out, List L);

// returns new list with same integer sequence as L.
// Cursor is undefined, regardless of cursor state in L. State of L is
// unchanged.
List copyList(List L);

// returns a new list which is the concatenatino of A and B.
// Cursor is undefined, regardless of cursor states in A and B.
// A and B remain unchanged.
// List concatList(List A, List B);
