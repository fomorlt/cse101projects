/*********************************************************************************
 * Konan Le, kokhle
 * 2022 Spring CSE101 PA1
 * Lex.c
 * Main file for PA1 lexicographical ordering
 *********************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"

#define MAX_LEN 300

// Based on FILEIO.c example provided
int main(int argc, char *argv[]) {
  int line_count = 0;
  FILE *in, *out;
  char line[MAX_LEN];

  // checks for 2 arguments
  if (argc != 3) {
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }

  // open files for reading and writing
  in = fopen(argv[1], "r");
  if (in == NULL) {
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }
  out = fopen(argv[2], "w");
  if (out == NULL) {
    printf("Unable to open file %s for writing\n", argv[2]);
    exit(1);
  }

  // counting number of lines n in the input file.
  while (fgets(line, MAX_LEN, in) != NULL) {
    line_count++;
  }

  // Need to rewind in orer to set file position back at top for reading actual
  // data
  rewind(in);

  // string array for reading, needs to read multiple words so needs a double
  // pointer. Code inspired by stackoverflow and discord
  // Most errors have been traced to this block of code
  char **sarray = (char **)calloc(line_count, sizeof(char *));
  for (int i = 0; i < line_count; i++) {
    // use fgets to store into 'line', then takes from line
    // and puts it into string array
    fgets(line, MAX_LEN, in);
    sarray[i] = (char *)calloc(strlen(line), sizeof(char));
    strcpy(sarray[i], line);
  }
  // Now that we have data, time to make a ListObj out of it
  // Initialization and sorting of List
  // make list, set cursor to front
  // Elements are indices of the array as described in pa1.pdf
  // Sort as entering
  // Using Insertion Sort code based on CLRS, Github pseudocode from tutor
  // Sebastian, and Geeks4Geeks
  List L = newList();
  append(L, 0);
  for (int i = 1; i < line_count; i++) {
    moveBack(L);
    int compare = get(L);
    while ((index(L) != -1) && (strcmp(sarray[compare], sarray[i]) > 0)) {
      movePrev(L);
      if (index(L) == -1) {
        break;
      }
      compare = get(L);
    }
    if (index(L) == -1) { // at front of list, movePrev's into index_cursor =
                          // -1.
      prepend(L, i);

    } else {
      insertAfter(L, i);
    }
  }

  // printing to output file
  // print the corresponding index's value in sarray
  moveFront(L);
  int ind = 0;
  for (int i = 0; i < line_count; i++) {
    ind = get(L);
    fprintf(out, "%s", sarray[ind]);
    moveNext(L);
  }

  // cleanup time

  // free sarray data, then sarray itself
  for (int i = 0; i < line_count; i++) {
    free(sarray[i]);
  }
  free(sarray);
  // free list
  freeList(&L);
  // close files
  fclose(in);
  fclose(out);
  // end of main function
  return (EXIT_SUCCESS);
}
