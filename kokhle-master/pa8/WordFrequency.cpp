/*********************************************************************************
 * Konan Le, kokhle
 * 2022 Spring CSE101 PA8
 * WordFrequency.cpp
 * Main program file for PA8 Dictionary ADT operations; reads in any text file,
 * parses individual words without strings counted by delimiter, then adds it to 
 * a dictionary and prints it to an outfile.
 *********************************************************************************/

#include <algorithm>
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
  string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
  int line_count;
  ifstream in;
  ofstream out;
  string line;
  string tokenBuffer;
  string token;
  size_t begin, end, len;
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
    len = line.length();
    begin = min(line.find_first_not_of(delim, 0), len);
    end = min(line.find_first_of(delim, begin), len);
    token = line.substr(begin, end - begin);
    while (token != "") {
      transform(token.begin(), token.end(), token.begin(), ::tolower);
      if (D.contains(token)) {
        int &count = D.getValue(token);
        count++;
      } else {
        D.setValue(token, 1);
      }
      begin = min(line.find_first_not_of(delim, end + 1), len);
      end = min(line.find_first_of(delim, begin), len);
      token = line.substr(begin, end - begin);
    }
  }
  out << D;

  return (EXIT_SUCCESS);
}
