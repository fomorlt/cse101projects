/*********************************************************************************
 * Konan Le, kokhle
 * 2022 Spring CSE101 PA7
 * Order.cpp
 * Main program file for PA7 Dictionary ADT operations; performs various
 * walks and tests of BSTs
 *********************************************************************************/

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "Dictionary.h"
using namespace std;
#define MAX_LEN 300

// Main function!
int main(int argc, char *argv[]) {

  int line_count;
  ifstream in;
  ofstream out;
  string line;
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
    return (EXIT_FAILURE);
  }

  // open file for reading and writing
  in.open(argv[1]);
  if (!in.is_open()) {
    cerr << "Unable to open file " << argv[1] << " for reading" << endl;
    return (EXIT_FAILURE);
  }

  out.open(argv[2]);
  if (!out.is_open()) {
    cerr << "Unable to open file " << argv[2] << " for writing" << endl;
    return (EXIT_FAILURE);
  }

  // Creating Dictionaries
  Dictionary D;

  // Reading lines
  // Only need to reed 3 lines - 1 digit, blank line, another digit
  line_count = 0;
  while (getline(in, line)) {
    line_count++;
    D.setValue(line, line_count);
  }
  out << D << endl;
  string prestring = D.pre_string();
  out << prestring;

  return (EXIT_SUCCESS);
}
