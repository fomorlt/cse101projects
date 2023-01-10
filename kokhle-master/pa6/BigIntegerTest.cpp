/*********************************************************************************
 * Konan Le, kokhle
 * 2022 Spring CSE101 PA6
 * BigIntegerTest.c
 * Personalized testing harness for BigInteger ADT
 *********************************************************************************/
#include "BigInteger.h"
#include "List.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int main() {

  string bigboitest = "13000000000000000000000000000000000000000";
  BigInteger bigboitestbi = BigInteger(bigboitest);
  cout << "bigboitestbi printed: " << bigboitestbi << endl;

  string s1 = "52389403";
  string s2 = "45352662";
  string s3 = "-123456789101112";
  string s4 = "+123456";
  string s5 = "-123456";
  string s6 = "-1234567891";
  string s7 = "-12345678";
  string s8 = "-123456789";
  string s9 = "61078260312512683145";
  string s10 = "12369581726359917257";
  string s11 = "73447842038872600402";
  string s12 = "+123456";
  string zero1 = "0000000000000";
  string zero2 = "+0";
  string zero3 = "-0";

  // Testing initialization
  cout << "About to start initialization tests!" << endl;

  BigInteger A = BigInteger(s1);
  BigInteger B = BigInteger(s2);
  cout << "made A and B" << endl;
  BigInteger C = BigInteger(s3);
  BigInteger D = BigInteger(s4);
  cout << "Made A, b, c, d, e" << endl;
  BigInteger E = BigInteger(s5);
  BigInteger F = BigInteger(s6);
  BigInteger G = BigInteger(s7);
  cout << "Made EFG" << endl;
  BigInteger H = BigInteger(s8);
  BigInteger I = BigInteger(s9);
  BigInteger J = BigInteger(s10);
  BigInteger K = BigInteger(s11);
  BigInteger L = BigInteger(s12);

  cout << "Successfully created BigIntegers" << endl;

  if (A.sign() != 1) {
    throw length_error("Sign error in A, not positive!");
  }

  if (C.sign() != -1) {
    printf("B sign: %d\n", B.sign());
    throw length_error("Sign error in C, not negative!");
  }

  if (D.sign() != 1) {
    throw length_error("Sign error in D, not positive!");
  }

  // Testing to_string and << override
  cout << "A: " << A << endl;
  cout << "B: " << B << endl;
  cout << "C: " << C << endl;
  BigInteger justzero = BigInteger(zero1);
  BigInteger poszero = BigInteger(zero2);
  BigInteger negzero = BigInteger(zero3);
  cout << "Just zero: " << justzero << endl;
  cout << "positive zero: " << poszero << endl;
  cout << "negative zero: " << negzero << endl;

  // Checking compare
  cout << "About to start comparing tests!" << endl;

  // basic comparison, bigger number vs smaller
  if (A.compare(B) != 1) {
    throw length_error("Error in compare! Bigger number should return 1");
  }
  // Comparing positive and negative, negative has more digits
  if (C.compare(D) != -1) {
    throw length_error(
        "Error in compare! Negative should be smaller, return -1");
  }
  // Comparing smaller to bigger same sign
  if (D.compare(A) != -1) {
    throw length_error("Error in compare!");
  }
  // Comparing negative to negative
  if (E.compare(C) != 1) {
    throw length_error("Error in compare, same negative sign!");
  }
  if (C.compare(E) != -1) {
    throw length_error(
        "Error in compare, same negative sign, bigger should be smaller!");
  }
  if (L.compare(D) != 0) {
    throw length_error(
        "Error in compare, same sign and number should return 0");
  }

  // Testing addition
  cout << "About to start addition tests" << endl;
  BigInteger add1 = I.add(J);
  // Basic Addition
  if (add1.compare(K) != 0) {
    throw length_error("Error in addition!");
  }
  // Adding negative to a positive

  // Simple one

  // Complicated one
  string add2 = "456789012310589259018205";
  string add3 = "-925801298501298310294";
  string add4 = "455863211012087960707911";
  BigInteger addtest1 = BigInteger(add2);       // A
  BigInteger addtest2 = BigInteger(add3);       // B
  BigInteger addtest3 = BigInteger(add4);       // A + -B
  BigInteger addtest4 = addtest1.add(addtest2); // Calculating
  if (addtest3.compare(addtest4) != 0) {
    throw length_error("Error in adding negative to positive!");
  }
  string add5 = "-9129587129857192857129857125905018257987123";
  string add6 = "12950801259801298098095812059849482848";
  string add7 = "-9129574179055933055831759030092958408504275";
  BigInteger addtest5 = BigInteger(add5);           // A
  BigInteger addtest6 = BigInteger(add6);           // B
  BigInteger addtest7 = BigInteger(add7);           // A + B
  BigInteger addtest56res = addtest5.add(addtest6); // Calculating
  if (addtest7.compare(addtest56res) != 0) {
    throw length_error("Error in adding positive to negative");
  }

  // Adding extra big numbers
  string addkonan1 = "9876545439000000000000000200001234567896543654365346534";
  string addkonan2 = "9876545439009128734667000204389234563462889273552583012";
  string resultkonan =
      "19753090878009128734667000404390469131359432927917929546";
  BigInteger addkonan1bi = BigInteger(addkonan1);
  BigInteger addkonan2bi = BigInteger(addkonan2);
  BigInteger resultkonanbi = BigInteger(resultkonan);
  BigInteger sumkonanbi = addkonan1bi.add(addkonan2bi);
  if (sumkonanbi.compare(resultkonanbi) != 0) {
    throw length_error("adding extra big numbers weird");
  }

  // trying b-a
  string subwhy1 =
      "-98765454390000000000000002000000000000065436543653465341"; // B
  string addwhat1 =
      "9876545439009128734667000204389234563462889273552583012"; // A
  string resulthow1 =
      "-88888908950990871265333001795610765436602547270100882329";
  BigInteger addbi1 = BigInteger(addwhat1); // a
  BigInteger subbi1 = BigInteger(subwhy1);  // b
  BigInteger resultbi1 = BigInteger(resulthow1);
  BigInteger sumbi1 = addbi1.add(subbi1); //
  cout << "resulthow1 string: " << resulthow1 << endl;
  cout << "resultbi1 (BigInt of resulthow1): " << resultbi1 << endl;
  cout << "sumbi1 (result of adding): " << sumbi1 << endl;
  if (sumbi1.compare(resultbi1) != 0) {
    throw length_error("add big number and negative weird 1");
  }

  cout << "testing adding of negative number to positive number" << endl;
  string addkonan11 =
      "87629586912561975639576137658713653817658136513876518356";
  string addkonan21 =
      "-87629586912561975509576137658713653817658136513876518356";
  string resultkonan1 = "130000000000000000000000000000000000000";
  BigInteger addkonan1bi1 = BigInteger(addkonan11);
  BigInteger addkonan2bi1 = BigInteger(addkonan21);
  BigInteger resultkonanbi1 = BigInteger(resultkonan1);
  BigInteger sumkonanbi1 = addkonan1bi1.add(addkonan2bi1);

  cout << "-----Extra Big Numbers: Weird Test X" << endl;
  cout << "resultkonan1 string: " << resultkonan1 << endl;
  cout << "resultkonanbi1 (BigInt of resultkonan1): " << resultkonanbi1 << endl;
  cout << "sumkonanbi1 (result of adding): " << sumkonanbi1 << endl;

  if (sumkonanbi1.compare(resultkonanbi1) != 0) {
    printf("result of the thing: %d\n", sumkonanbi1.compare(resultkonanbi1));
    throw length_error("adding extra big numbers weird test x");
  }

  // Tough tests!
  string addwhat2 = "9876545439123456789000000200001234567896543654365346534";
  string subwhy2 =
      "-9876545439459128734667000204389234563462889273552583012"; // B
  string resulthow2 = "-335671945667000004387999995566345619187236478";
  BigInteger addbi2 = BigInteger(addwhat2); // a
  BigInteger subbi2 = BigInteger(subwhy2);  // b
  BigInteger resultbi2 = BigInteger(resulthow2);
  BigInteger sumbi2 = addbi2.add(subbi2);
  if (sumbi2.compare(resultbi2) != 0) {
    throw length_error("add big number and negative weird 2");
  }

  string addwhat = "9876545439000000000000000200000000000006543654365346534";
  string subwhy =
      "-9876545439009128734667000204389234563462889273552583012"; // B
  string resulthow = "-9128734667000004389234563456345619187236478";
  BigInteger addbi = BigInteger(addwhat); // a
  BigInteger subbi = BigInteger(subwhy);  // b
  BigInteger resultbi = BigInteger(resulthow);
  BigInteger sumbi = addbi.add(subbi);
  if (sumbi.compare(resultbi) != 0) {
    throw length_error("add big number and negative weird final");
  }

  // Testing subtraction

  string posbi = "192487129789";
  string posbi2 = "112341244";
  string negbi = "-623142879";
  string resbi = "193110272668";
  string resbi2 = "192374788545";
  BigInteger posbibi = BigInteger(posbi);
  BigInteger posbibi2 = BigInteger(posbi2);
  BigInteger negbibi = BigInteger(negbi);
  BigInteger resbibi = BigInteger(resbi);
  BigInteger calcbibi = posbibi.sub(negbi);
  BigInteger resbibi2 = BigInteger(resbi2);
  BigInteger calcbibi2 = posbibi.sub(posbibi2);
  // Checking basic subtraction - bigger minus smaller
  if (resbibi2.compare(calcbibi2) != 0) {
    throw length_error("Error in subtraction, basic");
  }
  // subtracting negative check, should be adding
  if (resbibi.compare(calcbibi) != 0) {
    throw length_error("Error in subtraction");
  }

  // Testing multiplication
  cout << "---------- Testing multiplication! -----------" << endl;
  string multposlarge = "12387129847129847129874";
  string multpossmall = "7694791284729184";
  string multneglarge = "-9876387658374384756837456";
  string multnegsmall = "-53681374687364768459";

  string largesmallprod = "95316378790503497001656401667766042816";
  string neglargesmallprod = "530178066446860496161524703464700960538600304";
  string neglargepossmallprod = "-75996741678266089294059383208063267515904";
  // basic positive times positive
  cout << "basic positive times positive" << endl;
  BigInteger multposlargebi = BigInteger(multposlarge);
  BigInteger multpossmallbi = BigInteger(multpossmall);
  BigInteger largesmallprodbi = BigInteger(largesmallprod); // should be result
  // result
  BigInteger prod1 = multposlargebi.mult(multpossmallbi); // result calculated
  if (prod1.compare(largesmallprodbi) != 0) {
    cout << "should be result: " << largesmallprodbi << endl;
    cout << "calculated: " << prod1 << endl;
    throw length_error("Error in product, positive with positive!");
  }

  // small pos times negative large
  BigInteger multneglargebi = BigInteger(multneglarge);
  cout << "multneglargebi sign should be -1: " << multneglargebi.sign() << endl;
  BigInteger negposprodbi = BigInteger(neglargepossmallprod);
  BigInteger prod2 =
      multpossmallbi.mult(multneglargebi); // multneglarge would be N
  if (prod2.compare(negposprodbi) != 0) {
    cout << "negposprodbi: " << negposprodbi << endl;
    cout << "prod2: " << prod2 << endl;
    throw length_error("product error, small pos * neg large");
  }

  // From ModelListTest
  BigInteger A1 = BigInteger("+111122223333");
  BigInteger B1 = BigInteger("+222211110000");

  // pos + pos = pos
  BigInteger D1 = BigInteger("+333333333333");
  BigInteger C1 = A1 + B1;
  if (!(C1 == D1)) {
    throw length_error("Error in pospos");
  }

  // add a positive and a negative integer
  //-> pos + neg = 0
  B1 = BigInteger("-111122223333");
  C1 = A1 + B1;
  if (C1.sign() != 0) {
    cout << "C (A + B, should be 0): " << C1 << endl;
    cout << "C sign: " << C1.sign() << endl;
    throw length_error("Error adding pos to neg");
  }

  // Mult Assign Tests
  BigInteger A2 = BigInteger("-111122223333");
  BigInteger B2 = BigInteger("111122223333");
  BigInteger D2 = BigInteger("-12348148518469129628889");

  // neg * pos = neg
  A2 *= B2;
  if (A2.sign() != -1) {
    cout << "A sign after neg * pos: " << A2.sign() << endl;
    throw length_error("neg * pos sign error");
  }
  if (!(A2 == D2)) {
    return 2;
  }

  A2.makeZero();
  B2.makeZero();
  cout << "A2 (should be empty) : " << A2 << endl;
  cout << "B2 (should be empty) : " << B2 << endl;
  if (A2.sign() != 0 || B2.sign() != 0) {
    throw length_error("Error in makeZero sign!");
  }
  // Testing override operators, negate, etc
  string op1 = "901287461289746";   // positive
  string op2 = "-5937592835747";    // negative
  BigInteger op3 = BigInteger(op1); // A
  BigInteger op4 = BigInteger(op2); // B
  BigInteger op5 = (op3 + op4);
  string op5result = "895349868453999";
  BigInteger op6 = BigInteger(op5result);
  if (!(op5 == op6)) {
    throw length_error("operator add override being weird");
  }
  BigInteger op7 = (op3 - op4);
  string op7result = "907225054125493";
  BigInteger op8 = BigInteger(op7result);
  if (!(op7 == op8)) {
    throw length_error("operator sub override being funky");
  }

  BigInteger op9 = (op3 * op4);
  string op9result = "-5351477973102597442153350262";
  BigInteger op10 = BigInteger(op9result);
  if (!(op9 == op10)) {
    throw length_error("operator mult override being strange");
  }
  string oppa = "925879182579";
  BigInteger oppabig = BigInteger(oppa);
  string oppa2 = "-233428578467528457";
  BigInteger oppa2big = BigInteger(oppa2);
  string oppa3 = "-216126661422093208261581150603";
  BigInteger oppa3big = BigInteger(oppa3);
  oppabig *= oppa2big;
  if (!(oppabig == oppa3big)) {
    throw length_error("operator *= being odd");
  }

  oppabig = BigInteger(oppa);
  oppabig += oppa2big;
  string oppa4 = "-233427652588345878";
  BigInteger oppa4big = BigInteger(oppa4);
  if (!(oppabig == oppa4big)) {
    throw length_error("operator += being crazy");
  }

  oppabig = BigInteger(oppa);
  oppabig -= oppa2big;
  string oppa5 = "233429504346711036";
  BigInteger oppa5big = BigInteger(oppa5);
  if (!(oppabig == oppa5big)) {
    throw length_error("operator -= being woah");
  }

  // Testing comparison
  if (!((oppabig > oppa2big) && (oppabig >= oppa2big))) {
    throw length_error("op>, negative should be less than positive");
  }
  if (!((oppa3big < oppa2big) && (oppa3big <= oppa2big))) {
    throw length_error(
        "op<, bigger negative should be less than smaller negative");
  }
  if (!(oppa2big <= oppa2big)) {
    throw length_error("op<=, should pass equal");
  }
  if (!(oppabig >= oppabig)) {
    throw length_error("op>=, should pass equal");
  }
  cout << "Successfully passed all tests!" << endl;
  return EXIT_SUCCESS;
}
