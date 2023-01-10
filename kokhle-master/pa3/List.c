/*********************************************************************************
 * Konan Le, kokhle
 * 2022 Spring CSE101 PA3
 * List.c
 * Contains functions for use in List ADT
 *********************************************************************************/
#include "List.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Node ADT (inspired by Prof. Tantalo Code)----------
typedef struct NodeObj *Node;
typedef struct NodeObj {
  Node next;
  Node prev;
  ListElement data;
} NodeObj;

Node node_create(int data) {
  Node n = malloc(sizeof(NodeObj));
  if (n) {
    n->next = NULL;
    n->prev = NULL;
    n->data = data;
    return n;
  } else {
    fprintf(stderr, "Not enough heap memory for node!");
    exit(EXIT_FAILURE);
  }
}

// Delete Node function
void node_delete(Node *n) {
  if (n != NULL && *n != NULL) {
    free(*n);
    *n = NULL;
    n = NULL;
  }
}

// List ADT----------
typedef struct ListObj {
  Node front;
  Node back;
  Node cursor;
  int length;
  int index_cursor;
} ListObj;

// Constructor-Destructor----------
List newList(void) {
  List L = malloc(sizeof(ListObj));
  L->index_cursor = -1;
  L->length = 0;
  L->front = L->cursor = L->back = NULL;
  return L;
}
// Frees all memory associated with input list
void freeList(List *pL) {
  // if pointer to list is not NULL and list data itself is not NULL
  if (pL != NULL && *pL != NULL) {
    while (((*pL)->front != NULL) && length(*pL) != 0) {
      deleteFront(*pL);
    }

    /*
   Node curr = (*pL)->front;
   Node aft = NULL;
   while (curr != NULL) {
     aft = curr->next;
     node_delete(&curr);
     curr = aft;
   }
   free(curr);
   curr = NULL;
   free(aft);
   aft = NULL;
   */
    // use star pL to get list itself
    free(*pL);
    *pL = NULL;
    pL = NULL;
  }
}

// Accessor funcs--------------
// Returns length of input list
int length(List L) { return L->length; }
// returns cursor index of list
int index(List L) {
  // No need to check if -1, defined as -1 by default

  return L->index_cursor;
}

// front() returns data of front item in List
// Precondition - length of list L must be greater than 0
int front(List L) {
  if (length(L) > 0) {
    //
    return L->front->data;
  } else {
    fprintf(
        stderr,
        "Error in List ADT: front(), length of list must be greater than 0.");
    exit(EXIT_FAILURE);
  }
}

// back() returns data of back item in list
// Precondition - length of list L must be greater than 0
int back(List L) {
  if (length(L) > 0) {
    return L->back->data;
  } else {
    fprintf(
        stderr,
        "Error in List ADT: back(), length of list must be greater than 0.");
    exit(EXIT_FAILURE);
  }
}

// Get() returns cursor data
// preconditions: length(L) must be greater than 0
int get(List L) {
  if (length(L) <= 0) {

    fprintf(stderr, "Error in List ADT: get(), length of list must be greater "
                    "than or equal to 0.");
    exit(EXIT_FAILURE);
  }
  if (index(L) < 0) {

    fprintf(
        stderr,
        "Error in List ADT: get(), index of cursor must be greater than 0.");
    exit(EXIT_FAILURE);
  }
  return L->cursor->data;
}

// equals() checks if two lists are equal to each other
bool equals(List A, List B) {
  // Iterates through lists, comparing them
  // If A and B exist, have the same length as a minor precondition
  if (((A == NULL) && (B != NULL)) || ((A != NULL) && (B == NULL))) {
    return false;
  } else if (A == NULL && B == NULL) {
    return true;
  }
  // printf("a_length = %d, b_length = %d\n", A->length, B->length);
  if ((A->length == B->length)) {
    Node A_track = A->front;
    Node B_track = B->front;
    for (int i = 0; i < A->length; i++) {
      // printf("A_data = %d, B_data = %d\n", A_track->data, B_track->data);
      if (A_track->data != B_track->data) {
        return false;
      }
      A_track = A_track->next;
      B_track = B_track->next;
    }
    return true;
  } else {
    return false;
  }
}

// Manipulation funcs-------------
void set(List L, int x) {
  if (L && (length(L) > 0) && (index(L) >= 0)) {
    L->cursor->data = x;
  } else {
    fprintf(stderr, "Error in List ADT: set(), L does not exist, length(L) is "
                    "less than 0, or cursor_index is less than or equal to 0.");
    exit(EXIT_FAILURE);
  }
}

// Sets cursor to front of list
void moveFront(List L) {
  if (L == NULL) {
    fprintf(stderr, "Error in List ADT: moveFront(), L is NULL!");
    exit(EXIT_FAILURE);
  }
  if (length(L) <= 0) {
    // Do nothing
    return;
  }
  // moving cursor attributes accordingly
  L->cursor = L->front;
  L->index_cursor = 0;
}

// Sets cursor to back of list
void moveBack(List L) {
  if (L && (L->length > 0)) {
    L->cursor = L->back;
    L->index_cursor = L->length - 1; //-1 to account for 0 indexing
  } else {
    // Do nothing
    return;
  }
}

void movePrev(List L) {
  if (L == NULL) {
    fprintf(stderr, "Error in List ADT: movePrev(), L is null.");
    exit(EXIT_FAILURE);
  }
  if (index(L) == -1) {
    // Do nothing
    return;
  }
  if (L->cursor == L->front) {

    L->index_cursor = -1;
    L->cursor = NULL;
    return;
  }
  if ((L->cursor != NULL) && (L->cursor != L->front)) {
    L->cursor = L->cursor->prev;
    L->index_cursor--;
  }
}

void moveNext(List L) {
  if (L == NULL) {
    fprintf(stderr, "Error in List ADT: moveNext(), L is null.");
    exit(EXIT_FAILURE);
  }
  if (index(L) == -1) {
    // Do nothing
    return;
  }
  if (L->cursor == L->back) {
    L->index_cursor = -1;
    L->cursor = NULL;
    return;
  }
  if ((L->cursor != NULL) && (L->cursor != L->back)) {
    L->cursor = L->cursor->next;
    L->index_cursor++;
  }
}

// Adds node into front of list - leftmost. becomes new front.
void prepend(List L, int x) {
  if (L != NULL) {
    Node new = node_create(x);
    if (length(L) > 0) {
      L->front->prev = new;
      new->next = L->front;
    } else if (length(L) == 0) {
      L->front = L->back = new;
    } else {
      fprintf(stderr,
              "Error in List ADT: prepend(), length of L is less than 0");
      exit(EXIT_FAILURE);
    }
    L->front = new;
    L->length++;
    // need to check if cursor is at the end or not
    if (L->index_cursor != -1) {
      L->index_cursor++;
    }
  } else {
    fprintf(stderr, "Error in List ADT: prepend(), L is NULL.");
    exit(EXIT_FAILURE);
  }
}

void append(List L, int x) {
  if (L != NULL) {
    Node new = node_create(x);
    if (length(L) > 0) {
      L->back->next = new;
      new->prev = L->back;
    } else if (length(L) == 0) {
      L->front = L->back = new;
    } else {
      fprintf(stderr,
              "Error in List ADT: append(), Length of L is less than 0.");
      exit(EXIT_FAILURE);
    }
    L->back = new;
    L->length++;

    // printf("successfully incremented length and index_cursor\n");
  } else {
    fprintf(stderr, "Error in List ADT: append(), L is NULL.");
    exit(EXIT_FAILURE);
  }
}

void insertBefore(List L, int x) {
  if (L == NULL) {
    fprintf(stderr, "Error in List ADT: insertBefore(), L is NULL.");
    exit(EXIT_FAILURE);
  }
  if (length(L) <= 0) {
    fprintf(stderr,
            "Error in List ADT: insertBefore(), L must be greater than 0");
    exit(EXIT_FAILURE);
  }
  if (index(L) < 0) {
    fprintf(stderr, "Error in List ADT: insertBefore(), index of L is "
                    "undefined or less than 0");
    exit(EXIT_FAILURE);
  }
  if (L->cursor == L->front) {
    prepend(L, x);
  } else { // If not at the front, insert as usual
    // Creating nodes to work with - new node to insert, node being shifted
    Node new = node_create(x);
    // copies node pointer of L->cursor->prev into old
    Node old = L->cursor->prev;

    L->cursor->prev = new; // overwrites prev with
    new->next = L->cursor;
    // preserving pointer to node being overwritten, rearranging pointers
    // just need to move next pointer of stored, and prev
    // pointer of new
    new->prev = old;
    old->next = new;
    L->length++;
    L->index_cursor++;
  }
}

void insertAfter(List L, int x) {
  if (L == NULL) {
    fprintf(stderr, "Error in List ADT: List is NULL");
    exit(EXIT_FAILURE);
  }
  if (length(L) <= 0) {
    fprintf(stderr,
            "Error in List ADT: Length of list is less than or equal to 0");
    exit(EXIT_FAILURE);
  }
  if (index(L) < 0) {
    fprintf(stderr, "Error in List ADT: index_cursor of list is less than 0 "
                    "(probably -1 aka undefined)");
    exit(EXIT_FAILURE);
  }
  if (L->back == L->cursor) {
    append(L, x);
  } else {
    Node new = node_create(x);
    Node old = L->cursor->next;
    L->cursor->next = new;
    new->prev = L->cursor;
    new->next = old;
    old->prev = new;
    L->length++;
  }
  // no need to increment cursor index
}

void deleteFront(List L) {
  if ((length(L) > 0)) {
    Node delnode = L->front;
    if (L->front == L->cursor) {
      L->index_cursor = -1;
    } else {
      L->index_cursor--;
    }
    if (length(L) > 1) {
      L->front = L->front->next;
    } else {
      L->front = L->back = NULL;
    }

    L->length--;
    node_delete(&delnode);
  } else {
    fprintf(stderr, "Error in List ADT: deleteFront, L has length less than or "
                    "equal to 0.");
    exit(EXIT_FAILURE);
  }
}

// Delete back element of list
void deleteBack(List L) {
  if (length(L) > 0) { // last potential problem here
    // Setup back node for deletion
    Node delnode = L->back;
    // If cursor is in the back, tell the cursor to be undefined
    if (L->back == L->cursor) {
      L->index_cursor = -1;
    }
    if (length(L) > 1) {
      L->back = L->back->prev;
    } else {
      L->back = L->front = NULL;
    }
    L->length--;
    node_delete(&delnode);
  } else {
    fprintf(stderr,
            "Error in List ADT: deleteBack, L is less than or equal to 0.");
    exit(EXIT_FAILURE);
  }
}

// delete() deletes cursor element
void delete (List L) {
  if (L == NULL) {
    fprintf(stderr, "Error in List ADT: delete(), L is NULL");
    exit(EXIT_FAILURE);
  }
  if (length(L) <= 0) {
    fprintf(stderr,
            "Error in List ADT: delete(), length is less than or equal to 0");
    exit(EXIT_FAILURE);
  }
  if (index(L) < 0) {
    fprintf(stderr, "Error in List ADT: delete(), index is less than 0 "
                    "(probably -1, undefined)");
    exit(EXIT_FAILURE);
  }
  if (L->cursor == NULL) {
    fprintf(stderr, "Error in List ADT: delete(), Cursor node is null!");
    exit(EXIT_FAILURE);
  }
  // if cursor is at back
  if (L->cursor == L->back) {
    // L->cursor->next->prev = L->cursor->prev;
    deleteBack(L);
  } else if (L->cursor == L->front) {
    // L->cursor->prev->next = L->cursor->next;
    deleteFront(L);
  } else {
    Node curr = L->cursor;
    L->cursor->next->prev = L->cursor->prev;
    L->cursor->prev->next = L->cursor->next;
    L->index_cursor = -1;
    L->length--;
    node_delete(&curr);
  }
}

// clear() resets L to original empty state
void clear(List L) {
  if (L != NULL) {
    while (L->back != NULL) {
      deleteBack(L);
    }
    L->length = 0;
    L->index_cursor = -1;
  } else {
    fprintf(stderr, "Error in List ADT: clear(), L is NULL.");
    exit(EXIT_FAILURE);
  }
}

void printList(FILE *out, List L) {
  if (L != NULL) {
    Node curr = L->front;
    for (int i = 0; i < length(L); i++) {
      fprintf(out, "%d ", curr->data);
      // fprintf(stdout, " %d", curr->data);
      curr = curr->next;
    }
  } else {
    fprintf(stderr, "Error in List ADT: printList(), L appears to be NULL");
    exit(EXIT_FAILURE);
  }
}

List copyList(List L) {
  if (L != NULL) {
    List newL = newList();
    Node curr = L->front;
    for (int i = 0; i < length(L); i++) {
      append(newL, curr->data);
      curr = curr->next;
    }
    return newL;
  } else {
    return NULL;
  }
}
