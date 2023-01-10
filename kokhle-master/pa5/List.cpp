/*********************************************************************************
 * Konan Le, kokhle
 * 2022 Spring CSE101 PA5
 * List.cpp
 * Source code for List ADT
 *********************************************************************************/
#include "List.h"
#include <iostream>
#include <stdexcept>
#include <string>

// Code inspired by Queue.cpp example provided
// Private constructors ----------

// Node constructor
List::Node::Node(ListElement x) {
  next = nullptr;
  prev = nullptr;
  data = x;
}

// Class Constructor & Destructor ----------

// Empty List constructor
List::List() {
  frontDummy = new Node(1);
  backDummy = new Node(10);
  frontDummy->next = backDummy;
  backDummy->prev = frontDummy;
  beforeCursor = frontDummy;
  afterCursor = backDummy;
  pos_cursor = 0;
  num_elements = 0;
}

// Copy constructor
List::List(const List &L) {
  // Initialize empty list
  frontDummy = new Node(1);
  backDummy = new Node(10);
  frontDummy->next = backDummy;
  backDummy->prev = frontDummy;
  beforeCursor = frontDummy;
  afterCursor = backDummy;
  pos_cursor = 0;
  num_elements = 0;
  // Populate new list with elements of L
  Node *newN = L.backDummy->prev; // next? most likely yeah
  for (int i = 0; i < L.num_elements; i++) {
    this->insertAfter(newN->data);
    newN = newN->prev;
  }
}

// Destructor
List::~List() {
  Node *delN = frontDummy;
  Node *tempN = frontDummy;
  // Delete every node
  while (delN != nullptr) {
    tempN = delN->next;
    delete delN;
    delN = tempN;
    // when reaches back, delN->next becomes null pointer
  }
}

// Access Functions ----------

// Length() returns length of list
int List::length() const { return (num_elements); }

// front() returns front element of the list
// precondition: length > 0
ListElement List::front() const {
  if (length() == 0) {
    throw std::length_error("List: front(): empty List");
  }
  Node *front = frontDummy->next;
  return (front->data);
}

// back() returns back element of the list
// precondition: length > 0
ListElement List::back() const {
  if (length() == 0) {
    throw std::length_error("List: back(): empty List");
  }
  Node *back = backDummy->prev;
  return (back->data);
}

// position() returns position of cursor in the list
int List::position() const {
  if (0 <= pos_cursor || pos_cursor <= length()) {
    return (pos_cursor);
  } else {
    throw std::length_error("List: position(): cursor out of bounds!");
  }
}

// peekNext() returns element after the cursor
// precondition: position < length
ListElement List::peekNext() const {
  if (position() >= length()) {
    throw std::range_error("List: peekNext(): no way to peek next!");
  }
  return (afterCursor->data);
}

// peekPrev() returns element before the cursor
// precondition: position > 0
ListElement List::peekPrev() const {
  if (position() <= 0) {
    throw std::range_error("List: peekPrev(): no way to peek previous.");
  }
  return (beforeCursor->data);
}

// clear() deletes all elements in List and sets it to empty state
void List::clear() {
  moveFront();
  while (length() > 0) {
    eraseAfter();
    // should stop before freeing dummy nodes
  }
  // Reinitializing list
  frontDummy->next = backDummy;
  backDummy->prev = frontDummy;
  beforeCursor = frontDummy;
  afterCursor = backDummy;
  num_elements = 0;
  pos_cursor = 0;
}

// moveFront() moves cursor to position 0 in the List
void List::moveFront() {
  beforeCursor = frontDummy;
  afterCursor = frontDummy->next;
  pos_cursor = 0;
}

// moveBack() moves cursor to position length() in the list
void List::moveBack() {
  beforeCursor = backDummy->prev;
  afterCursor = backDummy;
  pos_cursor = length();
}

// moveNext() moves cursor position up, and returns List element that was passed
// over
// precondition: position() < length()
ListElement List::moveNext() {
  if (position() >= length()) {
    throw std::range_error("List: moveNext(): no way to move to next.");
  }
  beforeCursor = afterCursor;
  afterCursor = afterCursor->next;
  pos_cursor++;
  return (beforeCursor->data);
}

// movePrev() moves cursor position down, and returns List element that was
// passed over
// precondition: position > 0
ListElement List::movePrev() {
  if (position() <= 0) {
    throw std::range_error("List: movePrev(): no way to move to previous.");
  }
  beforeCursor = beforeCursor->prev;
  afterCursor = beforeCursor->next;
  pos_cursor--;
  return (afterCursor->data);
}

// insertAfter() inserts value x after the cursor.
void List::insertAfter(ListElement x) {
  Node *newN = new Node(x);
  newN->prev = beforeCursor;
  newN->next = afterCursor;
  beforeCursor->next = newN;
  afterCursor->prev = newN;
  afterCursor = newN;
  num_elements++;
}

// insertBefore() inserts x before the cursor.
void List::insertBefore(ListElement x) {
  Node *newN = new Node(x);
  newN->next = afterCursor;
  newN->prev = beforeCursor;
  beforeCursor->next = newN;
  afterCursor->prev = newN;
  beforeCursor = newN;
  num_elements++;
  pos_cursor++;
}

// setAfter() rewrites afterCursor element with x
// precondition: position() < length()
void List::setAfter(ListElement x) {
  if (position() >= length()) {
    throw std::range_error(
        "List: setAfter(): position is greater than or equal to length!");
  }
  afterCursor->data = x;
}

// setBefore() rewrites beforeCursor element with x
void List::setBefore(ListElement x) {
  if (position() <= 0) {
    throw std::range_error("List: setBefore(): unable to set anything before; "
                           "position is less than or equal to 0!");
  }
  beforeCursor->data = x;
}

// eraseAfter() deletes the afterCursor element
// precondition: position < length
void List::eraseAfter() {
  if (position() >= length()) {
    throw std::range_error("List: eraseAfter(): nothing after cursor!");
  }
  Node *delNode = afterCursor;
  beforeCursor->next = afterCursor->next;
  afterCursor->next->prev = beforeCursor;
  afterCursor = afterCursor->next;
  num_elements--;
  delete delNode;
}

// eraseBefore() deletes the beforeCursor element
// precondition: position > 0
void List::eraseBefore() {
  if (position() <= 0) {
    throw std::range_error("List: eraseBefore(): nothing before cursor!");
  }
  Node *delNode = beforeCursor;
  afterCursor->prev = beforeCursor->prev;
  beforeCursor->prev->next = afterCursor;
  beforeCursor = beforeCursor->prev;
  delete delNode;
  num_elements--;
  pos_cursor--;
}

// findNext() performs a linear search starting from current position (front to
// back) to find the first element of x. If found, moves cursor over the
// element, places after then returns final cursor position. Takes advantage of
// fact that moveNext returns element passed over
int List::findNext(ListElement x) {
  while (position() < length()) {
    if (moveNext() == x) {
      // std::cout << "found x, should return position! Position: " <<
      // position() << std::endl; call function, it returns the element before -
      // perfect for findNext
      return (position());
    }
  }
  // Haven't found x, move cursor to position length() and return -1
  // Cursor already at position length()
  moveBack();
  return (-1);
}

// findPrev starts from current cursor position, performs linear search (back to
// front). if x is found, place cursor before the element and return cursor
// position. if x is not found, place cursor at position 0, return -1 takes
// advantage of movePrev returning value of element passed over

int List::findPrev(ListElement x) {
  while (position() > 0) {
    if (movePrev() == x) {
      return (position());
    }
  }
  // if got to this point, cursor is at position 0
  return (-1);
}

// cleanup() goes through the list, and removes any repeats. order of cleaned
// list is kept with the order of the first appearance. cursor is preserved
void List::cleanup() {
  // Preserve element before cleanup
  int savedcur = position();
  // Keep track of starting point for each element to be cleaned
  // Start at 1 to let moving of cleancur work properly for first loop
  int cleancur = 1;
  int cleanel = 0;
  while (cleancur < length()) {
    moveFront();
    // Move to cleaning element
    for (int i = 0; i < cleancur; i++) {
      // Anything right before right before cleancur ends
      // is to be cleaned. Now, eraseBefore().
      cleanel = moveNext();
    }
    // Loop until findNext returns -1, means no clones left in list
    // Move actual pos_cursor to accomodate if moved around
    while (findNext(cleanel) != -1) {
      if (position() <= savedcur) {
        savedcur--;
      }
      eraseBefore();
    }
    // Element cleaned, move on to next element
    cleancur++;
  }
  // Done cleaning, restore cursor to in between
  moveFront();
  while (position() < savedcur) {
    moveNext();
  }
}

// concat() returns a new List with the elements of current List followed by
// elements of list L. Cursor of returned list will be at pos 0.
List List::concat(const List &L) const {

  List newL;
  // newL.moveFront(); //unecessary? cursor is default at the front
  Node *tempN = L.backDummy->prev;
  for (int i = 0; i < L.length(); i++) {
    newL.insertAfter(tempN->data);
    tempN = tempN->prev;
  }

  // start adding current list
  tempN = backDummy->prev;
  for (int i = 0; i < length(); i++) {
    newL.insertAfter(tempN->data);
    tempN = tempN->prev;
  }
  // Done constructing list
  return (newL);
}

// to_string() returns a string representation of the List to a comma separated
// sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
  Node *N = nullptr;
  std::string s = "";

  N = frontDummy->next;
  for (int i = 0; i < length(); i++) {
    s += std::to_string(N->data) + " ";
    N = N->next;
  }
  return s;
}

// equals() returns true if and only if this list is the same integer sequence
// as list R. Cursors should remain unchanged
bool List::equals(const List &R) const {
  bool eq = false;
  Node *M = nullptr;
  Node *N = nullptr;
  eq = (this->length() == R.length());
  N = frontDummy->next;
  M = R.frontDummy->next;
  while (eq && N != backDummy->prev) {
    eq = (N->data == M->data);
    N = N->next;
    M = M->next;
  }
  return eq;
}

// Overriden Operators ---------

// operator<<()
// inserts string representation of Q, defined by member function to_string()
// into stream
std::ostream &operator<<(std::ostream &stream, const List &L) {
  return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if List A == List B, as defined by member
// function equals()
bool operator==(const List &A, const List &B) { return A.List::equals(B); }

// operator=()
// Overwrites state of this List with state of list L.
List &List::operator=(const List &L) {
  if (this != &L) {      // ensuring not self assignment
    List temp = List(L); // copy L

    // swap copy's fields with fields of this
    std::swap(frontDummy, temp.frontDummy);
    std::swap(backDummy, temp.backDummy);
    std::swap(afterCursor, temp.afterCursor);
    std::swap(beforeCursor, temp.beforeCursor);
    std::swap(num_elements, temp.num_elements);
    std::swap(pos_cursor, temp.pos_cursor);
    // PROBLEM HERE, swapping pointers to L's front dummy somehow, thus making
    // returned List just an alias of the copied list?
  }

  return *this;
  // copy is deleted upon return
}
