/*********************************************************************************
 * Konan Le, kokhle
 * 2022 Spring CSE101 PA4
 * List.h
 * Header file for List ADT
 *********************************************************************************/
#pragma once
#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_

#include <stdbool.h>
#include <stdio.h>
// Exported types ----------
typedef struct ListObj *List;
typedef void *ListElement;

// Constructors and Destructors ----------
List newList(void);
void freeList(List *pL);

// Access functions ----------
int length(List L);  // returns num of elements in L
int index(List L);   // returns index of cursor element if defined, -1 otherwise
void *get(List L);   // returns cursor element
void *front(List L); // returns front element of L
void *back(List L);  // returns back element of L

// Manipulation procedures ----------
void clear(List L);        // Reset L to original empty state
void set(List L, void *x); // overwrite cursor element's data with X
void moveFront(List L); // If L is not-empty, sets cursor under front element.
                        // Otherwise, does nothing
void moveBack(List L);  // If L is non-empty, sets cursor under back element.
                        // Otherwise, does nothing.
void movePrev(
    List L); // If cursor is defined and not at front, move cursor one step
             // toward the front of L. If cursor is defined and at the front,
             // cursor becomes undefined. If cursor is undefined, do nothing.

void moveNext(List L); // If cursor is defined and not at back, move cursor one
                       // step toward back.
                       // If cursor is defined and at back, cursor becomes
                       // undefined. If cursor is undefined, do nothing

void prepend(List L, void *x); // Insert new element into L. If L is non-empty,
                               // insertion takes place before front element.
void append(List L, void *x);  // Insert new element into L. If L is non-empty,
                               // insertion takes place after back element.
void insertBefore(List L, void *x); // Inserts a new element before cursor
                                    // Pre: length() > 0, index() >= 0.
void insertAfter(List L, void *x);  // Insert new element after cursor.
                                    // pre: length() > 0 , index() >= 0.
void deleteFront(List L);           // delete front element. Pre: Length() > 0.
void deleteBack(List L);            // Delete back element. Pre: Length() > 0
void delete (List L); // delete cursor element, making cursor undefined. Pre:
                      // length() > 0, index() >= 0.

// Other operations -----------

// Prints to a file pointed to be out variable, a string representation of L
// consisting of: sequence of integers, with front on the left hand side.
// void printList(FILE *out, List L);

#endif
