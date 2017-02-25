#include "util.h"
#include "DictionaryBST.h"

/* Author: Dennis Vo
 * Date: 2/9/17
 * Assignment: PA2
 * Description: Implementation of a dictionary using BST data structure.
 */

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST() {
  // uses set class from cpp
  std::set<std::string> tree;
}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word) {
  return tree.insert(word).second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const {
  if (tree.find(word) != tree.end()) {
    return true;
  } else {
    return false;
  }
}

/* Destructor */
DictionaryBST::~DictionaryBST() {
  std::set<std::string>();
}

