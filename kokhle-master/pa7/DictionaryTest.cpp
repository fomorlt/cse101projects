/*********************************************************************************
 * Konan Le, kokhle
 * 2022 Spring CSE101 PA7
 * DictionaryTest.cpp
 * Personalized testing client for Dictionary ADT
 *********************************************************************************/
#include "Dictionary.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int main() {

  cout << "Trying to create dictionaries" << endl;
  Dictionary A = Dictionary();
  Dictionary B = Dictionary();

  cout << "Testing size()" << endl;
  if (A.size() != 0 || B.size() != 0) {
    throw length_error("num_pairs not initialized to 0!");
  }
  cout << "Testing current, if current set to nil properly then root also works"
       << endl;
  if (A.hasCurrent() != false || B.hasCurrent() != false) {
    throw length_error("hasCurrent not initialized to nil!");
  }

  cout << "Testing manipulation functions" << endl;
  A.setValue("test1", 10);
  B.begin(); // should be nil
  A.begin(); // should be test1, 10
  if (A.currentVal() != 10) {
    throw length_error("currentVal not working!");
  }
  if (A.currentKey() != "test1") {
    throw length_error("currentKey not working!");
  }
  if (A.size() != 1) {
    throw length_error("size not incrementing!");
  }
  cout << "Testing currentVal on empty dict" << endl;
  try {
    B.currentVal();
  } catch (logic_error const &) {
  }
  B.end();
  try {
    B.currentVal();
  } catch (logic_error const &) {
  }
  try {
    B.currentKey();
  } catch (logic_error const &) {
  }

  cout << "Testing next()" << endl;
  A.setValue("test2", 150);
  A.setValue("test3", 1000);
  A.setValue("test4", 200); // test1, 2, 3, 4 have values 10, 150, 1000, 200
  A.begin();                // test1
  cout << "moving next 1st time" << endl;
  A.next();
  cout << "moving next 2nd time" << endl;
  A.next();
  if (A.currentKey() != "test3" || A.currentVal() != 1000) {
    throw length_error("next() not working!");
  }
  cout << "move to final position" << endl;
  A.next(); // test4 here
  A.prev();

  if (A.currentKey() != "test3" || A.currentVal() != 1000) {
    throw length_error("prev() not working!");
  }
  cout << A.currentKey() << " " << A.currentVal() << endl;
  if (A.hasCurrent() != true) {
    throw length_error("value should not be nil here!");
  }
  A.next(); // moves past final pos, should set current to nil

  cout << "Testing remove" << endl;
  A.setValue("d", 20);
  A.setValue("b", 46);
  A.setValue("a", 87);
  A.setValue("c", 765);
  A.setValue("f", 42);
  A.setValue("e", 64);
  A.setValue("g", 128);
  A.begin();
  A.remove("a");
  if (A.hasCurrent()) {
    throw length_error(
        "current should be undefined, removed the current cursor");
  }
  cout << "Testing copy!" << endl;
  Dictionary C = Dictionary(A);
  cout << "successfully used copy constructor" << endl;
  if (!(C.equals(A))) {
    throw length_error("C is not equal A!");
  }
  if (!(A.equals(C))) {
    throw length_error("A is not equal to C!");
  }
  cout << "A: " << A << endl;
  cout << "A copy (C): " << C << endl;
  A.begin();
  C.begin();
  if ((A.currentVal() != C.currentVal()) ||
      (A.currentKey() != C.currentKey())) {
    throw length_error("built wrong begin?");
  }
  A.end();
  C.end();
  if ((A.currentVal() != C.currentVal()) ||
      (A.currentKey() != C.currentKey())) {
    throw length_error("built wrong end?");
  }

  cout << "---------------------" << endl;

  Dictionary D;
  cout << "made empty D" << endl;
  D = A;
  cout << "successfully used op=" << endl;

  cout << "testing outputs" << endl;
  cout << "A: " << A << endl;
  cout << "A copy (C)" << C << endl;
  cout << "A op= (D)" << D << endl;
  cout << "Testing prestring" << endl;
  string prestring = A.pre_string();
  cout << prestring << endl;

  if (!(A.contains("g"))) {
    throw length_error("Error with A.contains!");
  }
  if (A.getValue("d") != 20) {
    throw length_error("Error with getValue!");
  }

  A.clear();
  if (A.size() != 0) {
    throw length_error("Error with A.clear()");
  }

  cout << endl;
  cout << "------------------------------" << endl;
  cout << "Successfully passed all tests!" << endl;
  return (EXIT_SUCCESS);
}
