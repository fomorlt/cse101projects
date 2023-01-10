//-----------------------------------------------------------------------------
// Konan Le, kokhle
// Spring 2022 CSE 101, PA6
// ListTest.cpp
// Custom test client for List ADT
//-----------------------------------------------------------------------------
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;
#include "List.h"

int main() {
  // int i, n=10;

  List A, B, C, D, E, F;
  // Testing insertAfter
  A.insertAfter(3);
  // Inserting before at beginning of list?
  A.insertBefore(5);
  A.insertBefore(7);
  A.insertAfter(8);
  // List at this point should be 5, 7, 8, 3
  // Position is at 2, between 7 and 8
  if (A.length() != 4) {
    throw std::length_error("Incorrect length calculated!");
    return (EXIT_FAILURE);
  }
  cout << "Front of List A: " << A.front() << endl;

  cout << "Back of List A: " << A.back() << endl;

  if (A.front() != 5) {
    throw std::length_error("Incorrect front!");
    return (EXIT_FAILURE);
  }
  if (A.back() != 3) {
    throw std::length_error("Incorrect back!");
    return (EXIT_FAILURE);
  }

  cout << "Position of cursor: " << A.position() << endl;
  if (A.position() != 2) {
    throw std::length_error("Position did not initialize properly!");
    return (EXIT_FAILURE);
  }

  if (A.peekNext() != 8) {
    throw std::length_error("pointers to next not working!");
    return (EXIT_FAILURE);
  }

  if (A.peekPrev() != 7) {
    throw std::length_error("pointers to prev not working!");
    return (EXIT_FAILURE);
  }

  // Testing moveFront
  A.moveFront();
  if (A.peekNext() != 5) {
    throw std::length_error("moveFront not working!");
    return (EXIT_FAILURE);
  }

  // Testing moveNext
  A.moveNext();

  if (A.peekPrev() != 5) {
    throw std::length_error("moveNext not working!");
    return (EXIT_FAILURE);
  }
  if (A.peekNext() != 7) {
    throw std::length_error("moveNext not working!");
  }
  A.moveNext();
  A.moveNext();
  // testing movePrev
  A.movePrev();
  if (A.peekPrev() != 7) {
    throw std::length_error("movePrev not working!");
  }
  if (A.peekNext() != 8) {
    throw std::length_error("movePrev not working!");
  }
  // Testing set After, set Prev
  A.setAfter(9);
  A.setBefore(4);
  // List should now be 5, 4, 9, 3
  // Going to check back and front of the nodes
  if (A.peekPrev() != 4) {
    throw std::length_error("movePrev not working!");
  }
  if (A.peekNext() != 9) {
    throw std::length_error("movePrev not working!");
  }
  A.movePrev();
  if (A.peekPrev() != 5) {
    throw std::length_error("movePrev not working!");
  }
  if (A.peekNext() != 4) {
    throw std::length_error("movePrev not working!");
  }
  A.moveNext();
  A.moveNext();
  if (A.peekPrev() != 9) {
    throw std::length_error("movePrev not working!");
  }
  if (A.peekNext() != 3) {
    throw std::length_error("movePrev not working!");
  }
  // Testing eraseBefore()
  A.movePrev();
  A.eraseBefore();
  // List should now be 5, 9, 3
  if (A.peekPrev() != 5) {
    throw std::length_error("movePrev not working!");
  }
  if (A.peekNext() != 9) {
    throw std::length_error("movePrev not working!");
  }
  // Testing pointer from the back
  A.movePrev();
  if (A.peekNext() != 5) {
    throw std::length_error("movePrev not working!");
  }
  // Repopulating List
  A.insertAfter(4);
  A.insertAfter(6);
  A.insertAfter(14);
  A.insertAfter(7);
  // New list: 7, 14, 6, 4, 5, 9, 3
  // Testing eraseAfter
  A.moveNext();
  A.eraseAfter();
  if (A.peekNext() != 6) {
    throw std::length_error("eraseAfter not working!");
  }
  // Curveball test, random check to see if indices are correct
  if (A.position() != 1) {
    throw std::length_error("Position incorrect!");
  }
  if (A.length() != 6) {
    throw std::length_error("Number of elements incorrect!");
  }

  // Testing other functions
  A.clear();
  // Populating newList
  // A.moveBack();
  A.insertAfter(5);
  A.insertAfter(4);
  A.insertAfter(4);
  A.insertAfter(3);
  A.insertAfter(2);
  A.insertAfter(1);
  printf("position: %d\n", A.position());
  // List should be 1, 2, 3, 4, 4, 5
  if (A.findNext(4) != 4) {
    throw std::length_error("findNext incorrect!");
  }
  cout << "-------------------------------------" << endl;
  A.moveFront();
  int temp = A.findNext(5);
  cout << "blargh: output of findNext is: " << temp << endl;
  A.moveFront();
  if (A.findNext(5) != 6) {
    cout << "Error: Position of A after findNext: " << A.position() << endl;
    throw std::length_error("findNext incorrect test 2!");
  }

  A.moveBack();

  if (A.findPrev(2) != 1) {
    cout << "Error: Position of findPrev: " << A.position() << endl;
    throw std::length_error("findPrev incorrect!");
  }
  A.moveFront();

  A.insertAfter(3);
  A.insertAfter(2);
  A.insertAfter(4);
  A.insertAfter(5);
  // New list is 5, 4, 2, 3, 1, 2, 3, 4, 4, 5
  A.cleanup();
  if (A.length() != 5) {
    throw std::length_error("cleanup() not working!");
  }
  // list after cleanup should be 5, 4, 2, 3, 1
  A.moveFront();
  A.moveNext();
  A.moveNext();
  if (A.peekPrev() != 4) {
    throw std::length_error("error in cleanup! test 1");
  }
  if (A.peekNext() != 2) {
    throw std::length_error("error in cleanup! test 2");
  }
  B.insertAfter(9);
  B.insertAfter(8);
  B.insertAfter(7);
  B.insertAfter(6);
  A.concat(B);

  // Testing equals
  C.insertAfter(1);
  C.insertAfter(5);
  C.insertAfter(7);
  C.insertAfter(8);
  C.insertAfter(4);
  C.insertAfter(9);

  D.insertAfter(1);
  D.insertAfter(5);
  D.insertAfter(7);
  D.insertAfter(8);
  D.insertAfter(4);
  D.insertAfter(9);
  if (C.equals(D) != true) {
    throw std::length_error("problem with equals!");
  }

  F.insertBefore(1);
  F.insertBefore(2);
  F.insertBefore(3);
  F.insertBefore(5);
  F.insertBefore(12);
  // List should be: 1, 2, 3, 5, 12
  F.movePrev();
  /*
  if (E.peekNext() != 12) {
      throw std::length_error("movePrev or peekNext not working: list E");
  }
  if (E.peekPrev() != 5) {
      throw std::length_error("List E test failing: peekPrev()");
  }
  if (E.length() != 5) {
      throw std::length_error("List E test failing: length");
  }
  */
  F.eraseAfter();
  // list should now be 1, 2, 3, 5
  printf("F length after erasing 1st time: %d\n", F.length());
  /*
  if (E.peekPrev() != 5) {
      throw std::length_error("List E test failling: eraseAfter");
  }
  */
  if (F.length() != 4) {
    printf("Test F length: %d\n", F.length());
    throw std::length_error("List F test failing: length");
  }
  F.findPrev(2);
  printf("F position after findprev: %d\n", F.position());
  F.eraseAfter();

  printf("F length after erasing 2nd time: %d\n", F.length());
  if (F.length() != 3) {
    printf("Position F: %d\n", F.position());
    throw std::length_error("List E test failing: eraseAfter after findPrev");
  }
  printf("Testing equals operator override\n");
  A.clear();
  B.clear();
  A.insertAfter(2);
  A.insertAfter(1);
  A.insertAfter(5);
  A.insertAfter(8);
  A.insertAfter(8);
  cout << A << endl;
  B = A;
  if (!A.equals(B)) {
    cout << A << endl;
    cout << B << endl;
    throw std::length_error("List A and B are not equal!");
  }

  // Testing concat

  C.clear();
  D.clear();
  E.clear();
  C.insertAfter(2);
  C.insertAfter(1);
  C.insertAfter(5);
  C.insertAfter(8);
  C.insertAfter(8);
  // C should be 8, 8, 5, 1, 2
  cout << "List C: " << C << endl;
  D.insertAfter(4);
  D.insertAfter(16);
  D.insertAfter(87);
  D.insertAfter(14);
  // D should be 14, 87, 16, 4
  cout << "List D: " << D << endl;
  E = C.concat(D);
  // E should be 8, 8, 5, 1, 2, 14, 87, 16, 4
  cout << "List E: " << E << endl;
  cout << "---------------------------" << endl;

  C.clear();
  D.clear();
  E.clear();
  A.clear();
  B.clear();

  A.insertAfter(1);
  A.insertAfter(2);
  A.insertAfter(3);
  // A: 1, 2, 3
  B.insertAfter(4);
  B.insertAfter(5);
  B.insertAfter(6);
  // C: 4, 5, 6

  E = A;
  cout << "E should be A! 3 2 1: " << E << endl;

  C = A.concat(B);
  // C.moveFront();
  // printf("position of C after moveFront: %d\n", C.position());

  printf("position C.position : %d\n", C.position());

  printf("position A.concatb.position: %d\n", A.concat(B).position());

  /*
  cout << "List C before moveNext insert 9: " << C << endl;
  C.moveNext();
  C.insertAfter(9);
  cout << "List C after moveNext insert 9: " << C << endl;
  */

  if (C.position() != 0) {
    cout << "Position of C.pos: " << C.position() << endl;
    throw std::length_error("position is wrong!");
  }

 // E.clear();
  //cout << "A should still be 3 2 1: " << A << endl;

  A.clear();
  cout << "What about E?: " << E << endl;

  std::cout << "Successfully passed all tests!" << endl;
  return (EXIT_SUCCESS);
}
