# CSE 101, Spring Quarter 2022

## Konan Le - kokhle

## Programming Assignment 8

#### WordFrequency.cpp
<p> Main file for PA8, exercising the RBT Dictionary ADT. WordFrequency.cpp takes in an input file containing text of any kind - be it a story, paragraph, etc. It will parse each individual word in the file, then add it to a Dictionary object. Then, it will print out the dictionary to the desired output file.</p>

#### Order.cpp
<p> Second main file for PA8, exercising RBT Dictionary ADT. Order.cpp takes in an input file with a varying number of lines, each containing a word. The code will create a dictionary with each line as a key, and the corresponding line numbers as their values. Order.cpp will then print out each key : pair value in alphabetical order, then print out each key in a pre-order walk of the Dictionary BST.</p>

#### Dictionary.cpp
<p> Source code for Dictionary ADT, containing all code for functions. Now modified to work as a Red-Black Binary Tree.</p>

#### Dictionary.h
<p> Header file for use in testing files and Order.cpp. Contains function prototypes, class specifications for use in Dictionary ADT and other user files.</p>

#### DictionaryTest.cpp
<p> Personalized testing harness which calls the various functions defined in Dictionary.cpp and checks for errors. </p>

#### Makefile
<p> Allows the user to perform various tasks related to compiling, such as: cleaning binaries, testing for memory leaks, and of course compiling the binaries for program execution. </p>

#### README.md
<p> A table of contents for PA8. Lists each file, their purpose, and a general description. </p>

#### Notes:
<p> N/A </p>
