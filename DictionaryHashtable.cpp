#include "util.h"
#include "DictionaryHashtable.h"

/* Author: Dennis Vo
 * Date: 2/9/17
 * Assignment: PA2
 * Description: Implementation of a Dictionary using a HashTable.
 */

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){
  // implementing using ordered_set from cpp
  std::unordered_set<std::string> table;
}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word) {
  return table.insert(word).second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const {
  if (table.find(word) != table.end()) {
    return true;
  } else {
    return false;
  }
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable() {
  std::unordered_set<std::string>();
}
