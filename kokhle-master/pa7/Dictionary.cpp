/*********************************************************************************
 * Konan Le, kokhle
 * 2022 Spring CSE101 PA7
 * Dictionary.cpp
 * Source code for Dictionary ADT functions
 *********************************************************************************/
#include <cmath>
#include <string>

#include "Dictionary.h"

// Constructors ----------
// Private node constructor
Dictionary::Node::Node(keyType k, valType v) {
  parent = nullptr;
  right = nullptr;
  left = nullptr;
  key = k;
  val = v;
}

// Empty dictionary constructor
Dictionary::Dictionary() {
  nil = new Node("nil", 0);
  nil->parent = nil;
  nil->right = nil;
  nil->left = nil;
  root = nil;
  current = nil;
  num_pairs = 0;
}

// preOrderCopy() is a helper function that recursively inserts a deep copy of
// the subtree rooted at R into this Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node *R, Node *N) {
  // if ((R != nullptr) && (R->left != nullptr) && (R->right != nullptr)) {
  if (R->key != "nil") {
    // Makes sure not to take any nil
    // std::cout << "Rkey: " << R->key << " Rval: " << R->val << std::endl;
    setValue(R->key, R->val);
    preOrderCopy(R->left, N->left);
    preOrderCopy(R->right, N->right);
  }
}

// Copy constructor
Dictionary::Dictionary(const Dictionary &D) {
  nil = new Node("nil", 0);
  nil->parent = nil;
  nil->right = nil;
  nil->left = nil;
  root = nil;
  current = nil;
  num_pairs = 0;
  preOrderCopy(D.root, root);
  num_pairs = D.num_pairs;
}

// Destructor
Dictionary::~Dictionary() {
  postOrderDelete(root);
  delete nil;
  // garbage collection will take care of pointers
}

// Accessor functions -----------

// size() returns size of this Dictionary
int Dictionary::size() const { return num_pairs; }

// search() is a helper function that looks for a subtree rooted at R
// inspired by pseudocode
Dictionary::Node *Dictionary::search(Node *R, keyType k) const {
  if (R == nil || k == R->key) {
    return R;
  } else if (k < R->key) {
    return search(R->left, k);
  } else { // potential error
    return search(R->right, k);
  }
}

// contains() returns true if there exists a pair such that key == k, false
// otherwise
bool Dictionary::contains(keyType k) const {
  Node *result = search(root, k); // starts search from root, all of dictionary
  // code either returns nil or a matching root
  if (result == nil) {
    return false;
  } else {
    return true;
  }
}

// getValue() returns reference to value of key k
// pre: contains(k)
valType &Dictionary::getValue(keyType k) const {
  if (contains(k)) {
    Node *knode = search(root, k);
    return knode->val;
  } else {
    throw std::length_error("Dictionary ADT: getValue(), no key k found!");
  }
}

// hasCurrent() returns true if current iterator is defined, returns false
// otherwise.
bool Dictionary::hasCurrent() const {
  // current node will either have something or be nil
  if (current != nil) {
    return true;
  } else {
    return false;
  }
}

// currentKey() returns the current key.
// precondition: hasCurrent()
keyType Dictionary::currentKey() const {
  if (hasCurrent()) {
    return current->key;
  } else {
    throw std::length_error(
        "Dictionary ADT: currentKey(), current is not defined!");
  }
}

// currentVal() returns a reference to the current value
// precondition: hasCurrent()
valType &Dictionary::currentVal() const {
  if (hasCurrent()) {
    return current->val;
  } else {
    throw std::logic_error(
        "Dictionary ADT: currentVal(), current is not defined!");
  }
}

// Manipulation functions --------------

// postOrderDelete() recursively deletes all nodes in the subtree rooted at R,
// sets R to nil.
void Dictionary::postOrderDelete(Node *R) {
  if (R != nil) {
    postOrderDelete(R->left);
    postOrderDelete(R->right);
    num_pairs--;
    delete R;
  }
  R = nil;
}
// clear() resets dictionary to 0 state with no pairs
void Dictionary::clear() {
  postOrderDelete(root);
  num_pairs = 0;
  current = nil;
  root = nil;
}

// setValue() inserts node with key k and value v into this Dictionary. If key
// already exists, overwrite the value. Otherwise, insert the new node.
void Dictionary::setValue(keyType k, valType v) {
  // TreeInsert() from pseudocode
  Node *insertN = new Node(
      k, v); // making new node, can do this later to save time complexity
  insertN->left = nil;
  insertN->right = nil;
  Node *y = nil;
  Node *x = root;
  while (x != nil) {
    y = x;
    if (k < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  insertN->parent = y;
  if (y == nil) {
    root = insertN; // the tree is empty
  } else if (k < y->key) {
    y->left = insertN;
  } else if (k > y->key) {
    y->right = insertN;
  } else {
    y->val = v;
    delete insertN;
    num_pairs--;
  }
  num_pairs++;
}

// transplant() is a helper function that adds a node to the BST and adjusts
// pointers
void Dictionary::transplant(Node *u, Node *v) {
  if (u->parent == nil) {
    root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  if (v != nil) {
    v->parent = u->parent;
  }
}

// findMin() returns a pointer to the leftmost Node in the subtree at root R. If
// subtree is empty, return nil.
Dictionary::Node *Dictionary::findMin(Node *R) {
  if (R == nil) {
    return R;
  }
  Node *search = R;
  while (search->left != nil) {
    search = search->left;
  }
  return search;
}

// findMax() returns a pointer to the rightmost Node in the subtree at root R.
// If subtree is empty, return nil.
Dictionary::Node *Dictionary::findMax(Node *R) {
  if (R == nil) {
    return nil;
  }
  Node *search = R;
  while (search->right != nil) {
    search = search->right;
  }
  return search;
}

// findNext() returns pointer to node sucessor N in an in-order tree walk.
Dictionary::Node *Dictionary::findNext(Node *R) {
  /*
  if (R == nil) {
      return nil;
  }
  */
  Node *search = R;
  if (search->right != nil) {
    return findMin(search->right);
  }
  Node *y = search->parent; // case 2, no right
  while (y != nil && search == y->right) {
    search = y;
    y = y->parent;
  }
  return y;
}

// findPrev() returns pointer to node predecessor of N
Dictionary::Node *Dictionary::findPrev(Node *R) {
  if (R == nil) {
    return nil;
  }

  Node *search = R;
  if (search->left != nil) {
    return findMax(search->left);
  }
  Node *y = search->parent; // case 2, no left
  while (y != nil && search == y->left) {
    search = y;
    y = y->parent;
  }
  return y;
}

// remove() deletes any pair with key == k. If pair is current, then current
// becomes undefined. pre contains(k)
void Dictionary::remove(keyType k) {
  if (contains(k)) {
    // z = removeN
    Node *removeN = search(root, k);
    if (removeN == current) {
      current = nil;
    }
    if (removeN->left == nil) {
      transplant(removeN, removeN->right);
    } else if (removeN->right == nil) {
      transplant(removeN, removeN->left);
    } else {
      // y = min
      Node *min = findMin(removeN->right);
      if (min->parent != removeN) {
        transplant(min, min->right);
        min->right = removeN->right;
        min->right->parent = min;
      }
      transplant(removeN, min);
      min->left = removeN->left;
      min->left->parent = min;
    }
    delete removeN;
    num_pairs--;
  } else {
    throw std::length_error(
        "Dictionary ADT, remove(): key k not found in dictionary!");
  }
}

// begin() places current iterator at first key value pair. otherwise, does
// nothing. based on < operator on keys
void Dictionary::begin() { current = findMin(root); }

// end() places current iterator at last key value pair.
void Dictionary::end() { current = findMax(root); }

// next() advances current iterator to the next pair if it is not at the last
// pair. if current isat the last iterator, make current undefined. pre:
// hasCurrent()
void Dictionary::next() {
  if (hasCurrent()) {
    if (current == findMax(root)) {
      current = nil;
      return;
    }
    current = findNext(current);
  } else {
    throw std::length_error("Dictionary ADT: next(), current is nil!");
  }
}

void Dictionary::prev() {
  if (hasCurrent()) {
    if (current == findMin(root)) {
      current = nil;
      return;
    }
    current = findPrev(current);
  } else {
    throw std::length_error("Dictionary ADT: prev(), current is nil!");
  }
}

// Other Functions ------------

// inOrderString() is a helper function to append a string representation of
// itself
void Dictionary::inOrderString(std::string &s, Node *R) const {
  if (R != nil) {
    inOrderString(s, R->left);
    // if this doesn't work, make a new string to hold the value, then
    // s += that value
    std::string entry = (R->key + " : " + std::to_string(R->val) + "\n");
    s += entry;
    inOrderString(s, R->right);
  }
}

// preOrderString() is a helper function to append a string representation of
// itself
void Dictionary::preOrderString(std::string &s, Node *R) const {
  if (R != nil) {
    s += (R->key + "\n");
    preOrderString(s, R->left);
    preOrderString(s, R->right);
  }
}

// to_string() returns string representation of this Dictionary. Consecutive key
// value pairs
std::string Dictionary::to_string() const {
  std::string s = ""; // initialization
  inOrderString(s, root);
  return s;
}

// pre_string() returns consisting of all keys in the dictionary.
std::string Dictionary::pre_string() const {
  std::string s = ""; // initialization
  preOrderString(s, root);
  return s;
}

// equals() returns true if and only if this dictionary contains the same key
// value pairs as Dictionary D.
bool Dictionary::equals(const Dictionary &D) const {
  // Dictionary Dcopy = D;
  std::string thisstring = to_string();
  std::string Dstring = D.to_string();
  return (thisstring == Dstring);
}

// Overloaded operators --------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// to_string
std::ostream &operator<<(std::ostream &stream, Dictionary &D) {
  return stream << D.to_string();
}

// operator ==() returns true if and only if Dict A == Dict B, as defined by
// equals().
bool operator==(const Dictionary &A, const Dictionary &B) {
  return A.equals(B);
}

// operator=()
// Overwrites state of Dictionary with state of D
Dictionary &Dictionary::operator=(const Dictionary &D) {
  if (this != &D) {
    Dictionary tempD = D;
    std::swap(nil, tempD.nil);
    std::swap(root, tempD.root);
    std::swap(current, tempD.current);
    std::swap(num_pairs, tempD.num_pairs);
  }
  return (*this);
}
