/*********************************************************************************
 * Konan Le, kokhle
 * 2022 Spring CSE101 PA4
 * MatrixTest.c
 * Personalized test client for Matrix ADT
 *********************************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "Matrix.h"

int main() {
  int n = 3;
  Matrix A = newMatrix(n);
  Matrix B = newMatrix(n);
  // Matrix C = newMatrix(n);
  Matrix C, D, E, F, G, H, I, J, K;

  // Checking initialization
  if (size(A) != 3) {
    fprintf(stderr, "size of A is not properly initialized!");
    exit(EXIT_FAILURE);
  }
  if (size(B) != 3) {
    fprintf(stderr, "size of B is not properly initialized!");
    exit(EXIT_FAILURE);
  }
  printf("About to start adding things\n");
  changeEntry(A, 1, 1, 1);
  printf("Added first item\n");
  changeEntry(A, 1, 2, 1);
  printf("Added second item\n");
  changeEntry(A, 1, 3, 1);
  changeEntry(A, 2, 1, 5);
  changeEntry(A, 2, 2, 5);
  changeEntry(A, 2, 3, 5);
  printf("Working so far\n");
  changeEntry(A, 3, 1, 9);
  printf("Is it this one?\n");
  changeEntry(A, 3, 2, 9);
  printf("Or is it this one?\n");
  changeEntry(A, 3, 3, 9);
  printf("Finished adding things!\n");
  B = copy(A);

  printf("Matrix B: should be copyy\n");
  printMatrix(stdout, B);
  printf("Matrix A:\n");
  printMatrix(stdout, A);

  printf("Finished copying!\n");
  // Testing NNZ
  printf("NNZ of A (should be 9) : %d\n", NNZ(A));
  if (NNZ(A) != 9) {
    fprintf(stderr, "Error, NNZ not returning correct number!\n");
    exit(EXIT_FAILURE);
  }
  makeZero(A);
  changeEntry(A, 1, 1, 1);
  changeEntry(A, 1, 2, 1);
  changeEntry(A, 1, 3, 0);
  changeEntry(A, 2, 1, 5);
  changeEntry(A, 2, 2, 0);
  if (NNZ(A) != 3) {
    fprintf(stderr, "Error, NNZ not returning correct number!\n");
    exit(EXIT_FAILURE);
  }

  // Testing Add
  printf("Going to test sum()\n");
  printf("Matrix A: \n");
  printMatrix(stdout, A);
  printf("Matrix B: \n");
  printMatrix(stdout, B);
  C = sum(A, B);
  printf("Matrix C: sum of A and B\n");
  printMatrix(stdout, C);

  printf("Matrix A: should only have 3 entries\n");
  printMatrix(stdout, A);

  // Testing empty new matrices
  F = newMatrix(10);
  G = newMatrix(10);
  if (equals(F, G) != 1) {
    fprintf(stderr, "Error: empty matrices of same size are not equal.\n");
    exit(EXIT_FAILURE);
  }

  printf("Matrix A transpose:\n");
  I = transpose(A);
  printMatrix(stdout, I);
  printf("Finished transpose!\n");
  // C = sum(A, B);
  D = diff(A, B);
  E = product(A, B);

  printf("Matrix D: A - B\n");
  printMatrix(stdout, D);

  printf("Matrix E: A * B\n");
  printMatrix(stdout, E);

  J = newMatrix(100);
  H = newMatrix(100);
  changeEntry(J, 58, 69, 50.0);
  changeEntry(J, 43, 55, 60.0);
  printf("Matrix J (should have 2 entries)\n");
  printMatrix(stdout, J);
  if (NNZ(J) != 2) {
    fprintf(stderr, "Error, NNZ of matrix not working.\n");
    exit(EXIT_FAILURE);
  }
  // Multiplying by 0 matrix should result in another 0 matrix
  K = product(H, J);
  printf("Matrix K, should have 0 entries\n");
  printMatrix(stdout, K);
  if (NNZ(K) != 0) {
    fprintf(stderr, "Error, NNZ of matrix not passing!\n");
    exit(EXIT_FAILURE);
  }

  // Cleanup
  freeMatrix(&A);
  printf("freed matrix successfully\n");
  freeMatrix(&B);
  freeMatrix(&C);
  freeMatrix(&D);
  freeMatrix(&E);
  freeMatrix(&F);
  freeMatrix(&G);
  freeMatrix(&J);
  freeMatrix(&K);
  /* Expected Outputs:

  Matrix B: Copy:
  1: (1, 1.0) (2, 1.0) (3, 1.0)
  2: (1, 5.0) (2, 5.0) (3, 5.0)
  3: (1, 9.0) (2, 9.0) (3, 9.0)

  Matrix A:
  1: (1, 1.0) (2, 1.0) (3, 1.0)
  2: (1, 5.0) (2, 5.0) (3, 5.0)
  3: (1, 9.0) (2, 9.0) (3, 9.0)

  Matrix C: Sum of a new A (diff from above) and B

  1: (1, 2.0) (2, 2.0) (3, 1.0)
  2: (1, 10.0) (2, 5.0) (3, 5.0)
  3: (1, 9.0) (2, 9.0) (3, 9.0)

  Matrix A transposed should have:
  1: (1, 1.0) (2, 5.0)
  2: (1, 1.0)

  Matrix D should have: A - B
  1: (3, -1.0)
  2: (2, -5.0) (3, -5.0)
  3: (1, -9.0) (2, -9.0) (3, -9.0)

  Matrix E should have A * B:
  1: (1, 6.0) (2, 6.0) (3, 6.0)
  2: (1, 5.0) (2, 5.0) (3, 5.0)

  Matrix J should have 2 entries, and matrix H should be empty
  Matrix J:
  43: (55, 60.0)
  58: (69, 50.0)

  Matrix K, J * H, shouldn't print anything.
  Empty matrix multiplication should empty the matrix.

  */

  printf("Passed all tests!\n");
  return EXIT_SUCCESS;
}
/*
changeEntry(A, 1,1,1); changeEntry(B, 1,1,1);
changeEntry(A, 1,2,2); changeEntry(B, 1,2,0);
changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
changeEntry(A, 2,2,5); changeEntry(B, 2,2,1);
changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
changeEntry(A, 3,3,9); changeEntry(B, 3,3,1);

printf("%d\n", NNZ(A));
printMatrix(stdout, A);
printf("\n");

printf("%d\n", NNZ(B));
printMatrix(stdout, B);
printf("\n");

C = scalarMult(1.5, A);
printf("%d\n", NNZ(C));
printMatrix(stdout, C);
printf("\n");

D = sum(A, B);
printf("%d\n", NNZ(D));
printMatrix(stdout, D);
printf("\n");

E = diff(A, A);
printf("%d\n", NNZ(E));
printMatrix(stdout, E);
printf("\n");

F = transpose(B);
printf("%d\n", NNZ(F));
printMatrix(stdout, F);
printf("\n");

G = product(B, B);
printf("%d\n", NNZ(G));
printMatrix(stdout, G);
printf("\n");

H = copy(A);
printf("%d\n", NNZ(H));
printMatrix(stdout, H);
printf("\n");

printf("%s\n", equals(A, H)?"true":"false" );
printf("%s\n", equals(A, B)?"true":"false" );
printf("%s\n", equals(A, A)?"true":"false" );

makeZero(A);
printf("%d\n", NNZ(A));
printMatrix(stdout, A);

freeMatrix(&A);
freeMatrix(&B);
freeMatrix(&C);
freeMatrix(&D);
freeMatrix(&E);
freeMatrix(&F);
freeMatrix(&G);
freeMatrix(&H);

return EXIT_SUCCESS;
}
*/

/*
Output of this program:
9
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

6
1: (1, 1.0) (3, 1.0)
2: (2, 1.0)
3: (1, 1.0) (2, 1.0) (3, 1.0)

9
1: (1, 1.5) (2, 3.0) (3, 4.5)
2: (1, 6.0) (2, 7.5) (3, 9.0)
3: (1, 10.5) (2, 12.0) (3, 13.5)

9
1: (1, 2.0) (2, 2.0) (3, 4.0)
2: (1, 4.0) (2, 6.0) (3, 6.0)
3: (1, 8.0) (2, 9.0) (3, 10.0)

0

6
1: (1, 1.0) (3, 1.0)
2: (2, 1.0) (3, 1.0)
3: (1, 1.0) (3, 1.0)

7
1: (1, 2.0) (2, 1.0) (3, 2.0)
2: (2, 1.0)
3: (1, 2.0) (2, 2.0) (3, 2.0)

9
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

true
false
true
0
*/
