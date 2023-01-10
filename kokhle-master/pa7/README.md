# CSE 101, Spring Quarter 2022

## Konan Le - kokhle

## Programming Assignment 7

#### Order.cpp
<p> Main file for PA7, exercising Dictionary ADT. Order.cpp takes in an input file with a varying number of lines, each containing a word. The code will create a dictionary with each line as a key, and the corresponding line numbers as their values. Order.cpp will then print out each key : pair value in alphabetical order, then print out each key in a pre-order walk of the Dictionary BST.</p>

#### Dictionary.cpp
<p> Source code for Dictionary ADT, containing all code for functions. </p>

#### Dictionary.h
<p> Header file for use in testing files and Order.cpp. Contains function prototypes, class specifications for use in Dictionary ADT and other user files. Modified to allow for transplant function. </p>

#### DictionaryTest.cpp
<p> Personalized testing harness which calls the various functions defined in Dictionary.cpp and checks for errors. </p>

#### Makefile
<p> Allows the user to perform various tasks related to compiling, such as: cleaning binaries, testing for memory leaks, and of course compiling the binaries for program execution. </p>

#### README.md
<p> A table of contents for PA7. Lists each file, their purpose, and a general description. </p>

#### Notes:
<p> Header file modified to add a transplant helper function. </p>
