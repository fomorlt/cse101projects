/*********************************************************************************
 * Konan Le, kokhle
 * 2022 Spring CSE101 PA5
 * Shuffle.cpp
 * Main program file for testing List ADT, finds number of perfect shuffles to
 * return list to original state
 *********************************************************************************/

#include "List.h"
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;
#define MAX_LEN 300

// Shuffle performs one perfect shuffle on List D
void shuffle(List &D) {
  // Split lists
  List L1;
  List L2;
  // Sort arrays
  D.moveFront();
  for (int i = 0; i < floor(D.length() / 2); i++) {
    // use moveNext to pass in value and move in same instruction
    // move through D - cursor will be preserved, so we can use in
    // the next loop
    L1.insertBefore(D.moveNext());
  }
  // Add other half of D to L2
  for (int j = 0; j < (D.length() - floor(D.length() / 2)); j++) {
    L2.insertBefore(D.moveNext());
  }

  // Now build list accordingly
  // Can't clear due to error
  D.moveFront();
  L1.moveFront();
  L2.moveFront();
  for (int k = 0; k < (floor(D.length() / 2)); k++) {
    D.setAfter(L2.moveNext());
    D.moveNext();
    D.setAfter(L1.moveNext());
    D.moveNext();
    // End of list check
    // If N is odd, extra card is in the right half - L2 will be bigger. add it
    // at the end of D - can't move next.
    if ((L2.length() > L1.length()) && (k == (floor(D.length() / 2) - 1))) {
      D.setAfter(L2.moveNext());
    }
  }
}
// Main function!
int main(int argc, char *argv[]) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
    return (EXIT_FAILURE);
  }
  // Establish how large to make list
  int listsize = stoi(argv[1]);
  // shuff to hold shuffled list, unshuff to hold unaltered list comparison
  List shuff;
  List unshuff;
  int numshuff = 0; // initialize number of shuffles to 0
  // Populate list, perform perfect shuffle operation for each size until
  // listsize is reached print top of table
  cout << left << setw(16) << "deck size"
       << "shuffle count" << endl;
  cout << "------------------------------" << endl;
  for (int i = 0; i < listsize; i++) {
    shuff.moveBack(); // reset cursor
    unshuff.moveBack();
    shuff.insertBefore(i + 1);
    unshuff.insertBefore(i + 1);
    // first shuffle to overcome conditional
    numshuff = 1;
    shuffle(shuff);
    while (!(unshuff == shuff)) {
      // printf("stuck in while loop?\n");
      // Could do a do-while loop here?
      shuffle(shuff);
      numshuff++;
    }
    // print to output
    cout << " " << left << setw(16) << (i + 1) << left << setw(14) << numshuff
         << endl;
  }

  return (EXIT_SUCCESS);
}
