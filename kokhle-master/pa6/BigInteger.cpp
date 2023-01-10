/********************************************************************************* 
* Konan Le, kokhle 
* 2022 Spring CSE101 PA6
* BigInteger.cpp 
* Source code for BigInteger ADT
*********************************************************************************/
#include "BigInteger.h"
#include "List.h"
#include <cmath>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

int power = 9;
long base = pow(10.0, power);

// Constructor functions -----------

// BigInteger zero constructor
BigInteger::BigInteger() {
  signum = 0;
  // No need to do anything with digits here, already allocated memory via class
}

// BigInteger constructor
BigInteger::BigInteger(std::string s) {
  // To parse string, use substring?
  // keep a counter for each section of the scrubber
  // substring starting from length to pow, incrementing each time
  // first check for sign
  // No need to make copy of string, s is already a copy
  if (s.length() == 0) {
    throw std::invalid_argument("BigInteger: constructor, nothing in string s");
  }
  // Checking for sign, if none then set it to positive
  signum = 1;
  if (s[0] == '-') {
    signum = -1;
    s.erase(s.begin()); // erase the sign
  } else if (s[0] == '+') {
    s.erase(s.begin());
  }

  // Check if a 0
  s.erase(0, s.find_first_not_of('0'));
  if (s.length() != 0) {
    digits.moveFront();
    // If passed conditional, means its a non-zero
    // Now construct accordingly, dividing it into pow length digits
    // append rightmost,
    // Should pass a string of 00000 as 0

    // start building digits
    int scrub = s.length(); // cursor for adding digits
    while (scrub > 0) {     // had an equals =
      scrub -= power;
      if (scrub < 0) {
        // if end of the string, (beginning) add on remaining digits
        scrub += power;
        std::string digit =
            s.substr(s.find_first_not_of("0"),
                     scrub); // add remaining digits, strips leading 0s
        // add to the list
        // list should be built like this:
        // 123456789
        //(123),(456),(789)

        ListElement digitl = stol(digit);
        digits.insertAfter(digitl);
        break;
      }
      std::string digit = s.substr(scrub, power);
      // add to list
      ListElement digitl = stol(digit);
      digits.insertAfter(digitl);
    }
  } else {
    // if failed, means all 0s
    // so, return 0 state bigint
    signum = 0;
    digits.clear(); // unecessary? because already empty?
  }
}

// Copy Constructor
BigInteger::BigInteger(const BigInteger &N) {
  signum = N.signum;
  this->digits = N.digits;
}

// Accessor functions ----------

// Sign() returns -1, 1, or 0 for positive, negative, or 0 value.
int BigInteger::sign() const { return signum; }

// Compare() returns -1, 1, or 0 depending on if this BigInteger is < N, > N, or
// == N respectively.
int BigInteger::compare(const BigInteger &N) const {
  List selfdigits = this->digits;
  List Ndigits = N.digits;
  // Sign comparisons
  if (signum == 0 && N.signum == 0) {
    return 0;
  }
  int signchk = 0;
  if (signum > N.signum) {
    return 1;
  } else if (signum < N.signum) {
    return -1;
  } else {
    // Signs are equal, need to compare
    signchk = signum;
  }
  // Should be okay to manipulate this-> cursor right? I can just reset if need
  // be

  // Check if same number of digits; bigger number of digits
  if ((selfdigits.length() > Ndigits.length() && signchk == -1) ||
      (selfdigits.length() < Ndigits.length() && signchk == 1)) {
    // if this is smaller
    return -1;
  } else if ((selfdigits.length() < Ndigits.length() && signchk == -1) ||
             (selfdigits.length() > Ndigits.length() && signchk == 1)) {
    // if this is larger
    return 1;
  } else {
    // time to compare each digit starting from the left
    selfdigits.moveFront();
    Ndigits.moveFront();
    for (int i = 0; i < selfdigits.length(); i++) {
      ListElement digitval = selfdigits.moveNext();
      ListElement Ndigitval = Ndigits.moveNext();
      if (digitval > Ndigitval) {
        return (1 * signchk);
      } else if (digitval < Ndigitval) {
        return (-1 * signchk);
      }
    }
    // Everything is the same, it's equal
    return 0;
  }
}

// Manipulation functions ----------
// makeZero() resets this bigInteger to zero state
void BigInteger::makeZero() {
  digits.clear();
  // Clear() clears memory of digits list, so need to allocate new
  List digits2;
  digits = digits2;
  signum = 0;
}

// negate() reverses sign of BigInteger if it is positive or negative
void BigInteger::negate() {
  if (signum != 0) {
    signum *= -1;
  }
}

// Arithmetic functions ------------

// add() adds this BigInteger and BigInteger N.
BigInteger BigInteger::add(const BigInteger &N) const {
  // Check if 0 integer
  if (N.signum == 0) {
    BigInteger output(*this);
    return output;
  } else if (signum == 0) {
    BigInteger output(N);
    return output;
  }
  // setup vectors for addition
  List Ndigits = N.digits;        // B
  List selfdigits = this->digits; // A
  BigInteger output;
  output.signum = 1;
  selfdigits.moveBack();
  Ndigits.moveBack();
  output.digits.moveFront();
  // initialize bounds to 0 in case same number of digits
  int up = 0;
  int low = 0;
  // Set range of shared digits
  if (selfdigits.length() < Ndigits.length()) {
    low = selfdigits.length();
  } else {
    low = Ndigits.length();
  }

  // set range of non-shared digits
  if (selfdigits.length() > Ndigits.length()) {
    up = selfdigits.length();
  } else {
    up = Ndigits.length();
  }

  // Add up shared digits
  // dig1 is number from digits
  // dig2 is number from N.digits
  for (int i = 0; i < low; i++) {
    // convert digits to correct sign
    ListElement dig1 = selfdigits.movePrev() * signum;
    ListElement dig2 = Ndigits.movePrev() * N.signum;
    output.digits.insertAfter(dig1 + dig2);
    // ListElemnt digres = dig1 + dig2;
    // Build up list from leftmost bit to rightmost
  }
  for (int j = 0; j < (up - low); j++) {
    // Leftover digits are either in N or in this, so find out where it belongs
    // Only comes here if leftover digits, length not equal
    if (selfdigits.length() > Ndigits.length()) {
      // this has leftover digits, add it to the result
      output.digits.insertAfter(selfdigits.movePrev() * signum);
    } else {
      // else would be if digits is less than N digits
      output.digits.insertAfter(Ndigits.movePrev() * N.signum);
    }
  }
  // Normalize output of digits, a mix of negative and positive numbers
  // output.signum = normalizeList(output.digits, output.signum);
  int carry = 0;
  do {
    output.digits.moveBack();
    // First moveBack is 0
    carry = 0;
    for (int i = 0; i < output.digits.length(); i++) {
      ListElement newnum = (output.digits.movePrev() * output.signum) + carry;
      // Reducing number to within base value
      // Set carry to use in next digit
      carry = 0;
      if (newnum >= base) {
        carry = 1;
        newnum -= base;
      } else if (newnum < 0) {
        carry = -1;
        newnum += base;
      }
      // Reached the end of the list,
      if (i == (output.digits.length() - 1) && carry == -1) {
        output.digits.setAfter(newnum -= base);
        break;
      }
      // Still have digits left
      output.digits.setAfter(newnum);
    }
    if (carry == 1) {
      // increase digits with 1
      output.digits.insertAfter(carry);
    } else if (carry == -1) {
      output.signum *= -1;
    }
  } while (carry == -1);
  // Strip leading 0 digits
  // Because add will fill up to the base amount
  output.digits.moveFront();
  for (int k = 0; k < output.digits.length(); k++) {
    // start reading from front to back so we can catch beginning 0s
    ListElement compare = output.digits.moveNext();
    if (compare == 0) {
      output.digits.eraseBefore();
      if (k == (output.digits.length() - 1)) {
        output.signum = 0;
      }
    } else {
      // No more leading 0s, found first digit with something in it
      break;
    }
  }

  // All done!
  return output;
}

// For sub, A-B. If B > A, then B-A * -1.
// sub() returns BigInteger representing this - N.
BigInteger BigInteger::sub(const BigInteger &N) const {
  BigInteger Ncopy = N;
  BigInteger thiscopy = *this;
  BigInteger output;
  // If the same, then A-A should return 0
  if (thiscopy.compare(Ncopy) == 0) {
    output.makeZero(); // necessary? should already be zero
    return output;
  } else if (thiscopy.compare(Ncopy) == -1) {
    // if A is smaller than B, B greater
    thiscopy.negate();
    output = Ncopy.add(thiscopy); // B + (-A) * -1
    output.negate();
    return output;
  } else {
    // A is bigger, simply add
    Ncopy.negate();
    output = thiscopy.add(Ncopy); // A + (-B)
    return output;
  }
}

// scalarMultList multiplies L by M. Used in mult()
void scalarMultList(List &L, ListElement m) {
  L.moveBack();
  ListElement operand;
  for (int i = 0; i < L.length(); i++) {
    operand = L.movePrev();
    L.setAfter(m * operand);
  }
}

// shiftList appends p zero digits to L, multiplying L by base ^ p. Used by
// mult().
void shiftList(List &L, int p) {
  std::string shiftstring = std::string(power, '0');
  ListElement shift = stol(shiftstring);
  for (int i = 0; i < p; i++) {
    L.moveBack();
    L.insertAfter(shift);
  }
}

// mult() multiplies BigInteger by product of this and N.
BigInteger BigInteger::mult(const BigInteger &N) const {
  // Setup
  BigInteger Ncopy = N; // for anything that needs OG N
  BigInteger Ncopy2;    // for scalar mult
  BigInteger thiscopy = *this;
  BigInteger output;
  Ncopy.signum = 1;
  thiscopy.signum = 1; // So it doesn't interfere with add section of mult
  thiscopy.digits.moveBack();
  Ncopy.digits.moveBack();
  BigInteger addlayer = BigInteger(); // start with 0
  // multiplication
  // scalar mult, add, then normalize until all done
  // outer loop controls iteration over each digit of this as it multiplies each
  // element with each element of N (scalar mult) For each element of scalar
  // mult output, normalize it

  for (int i = 0; i < thiscopy.digits.length(); i++) {
    // setup
    Ncopy2 = N; // reset Ncopy2 to original biginteger for scalar mult
    ListElement carry = 0;
    // math
    ListElement scalar = thiscopy.digits.movePrev();
    shiftList(Ncopy2.digits, i); // append 0s accordingly
    scalarMultList(Ncopy2.digits, scalar);
    addlayer = Ncopy2.add(addlayer);
    addlayer.digits.moveBack();
    carry = 0;
    // Go through each element, normalize it
    for (int j = 0; j < addlayer.digits.length(); j++) {
      // Normalize
      ListElement nextlayernum = (addlayer.digits.movePrev() + carry);
      carry = (ListElement)floor(nextlayernum / base);
      nextlayernum -= carry * base;
      addlayer.digits.setAfter(nextlayernum);
    }
    if (carry >= 0) {
      // At the end of list, add any carry left
      addlayer.digits.insertAfter(carry);
    }
    // End of loop, move to next digit of this and scalar mult, repeat
  }

  for (int k = 0; k < addlayer.digits.length(); k++) {
    // start reading from front to back so we can catch beginning 0s
    ListElement compare = addlayer.digits.moveNext();
    if (compare == 0) {
      addlayer.digits.eraseBefore();
    } else {
      // No more leading 0s, found first digit with something in it
      break;
    }
  }
  addlayer.signum = N.sign() * this->sign();

  return addlayer;
}

// Other Functions ------------

// to_string returns string representation of this BigInteger.
std::string BigInteger::to_string() {
  // Need to modify to padd 0 digits with full base 0s
  if (this->signum == 0) {
    return "0";
  }
  std::string output;
  ListElement digit;
  List thisdigits = this->digits;
  thisdigits.moveFront();
  for (int i = 0; i < thisdigits.length(); i++) {
    digit = thisdigits.moveNext();
    if (digit == 0) {
      std::string out = std::to_string(digit);
      // expand 0 digits to proper digit length
      while ((int)out.length() != power) {
        out.insert(0, "0");
      }
      output += out;
      continue;
    }
    std::string out = std::to_string(digit);
    // expand 0 digits to proper digit length
    // do this for every digit except the final one
    while ((int)out.length() != power) {
      out.insert(0, "0");
    }
    output += out;
  }
 std::string output2 = output.substr(output.find_first_not_of("0")); // add remaining digits, strips leading 0s



  if (this->signum == -1) {
    output2.insert(0, "-");
  }
  return output2;
}

// Overriden Operators -----------

// operator<<() inserts string representation of N into the stream
// added friend, hopefully not going to affect?
std::ostream &operator<<(std::ostream &stream, BigInteger N) {
  return stream << N.to_string();
}

// operator==() returns true if and only if A equals B
bool operator==(const BigInteger &A, const BigInteger &B) {
  return A.compare(B) == 0;
}

bool operator<(const BigInteger &A, const BigInteger &B) {
  return A.compare(B) == -1;
}

bool operator<=(const BigInteger &A, const BigInteger &B) {
  return (A.compare(B) == -1 || A.compare(B) == 0);
}

bool operator>(const BigInteger &A, const BigInteger &B) {
  return A.compare(B) == 1;
}

bool operator>=(const BigInteger &A, const BigInteger &B) {
  return (A.compare(B) == 1 || A.compare(B) == 0);
}

BigInteger operator+(const BigInteger &A, const BigInteger &B) {
  BigInteger output = A.add(B);
  return output;
}

BigInteger operator+=(BigInteger &A, const BigInteger &B) {
  A = A.add(B);
  return A;
}

BigInteger operator-(const BigInteger &A, const BigInteger &B) {
  BigInteger output = A.sub(B);
  return output;
}

BigInteger operator-=(BigInteger &A, const BigInteger &B) {
  A = A.sub(B);
  return A;
}

BigInteger operator*(const BigInteger &A, const BigInteger &B) {
  BigInteger output = A.mult(B);
  return output;
}

BigInteger operator*=(BigInteger &A, const BigInteger &B) {
  A = A.mult(B);
  return A;
}
