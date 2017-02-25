/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 */

#ifndef DICTIONARY_TRIE_H
#define DICTIONARY_TRIE_H

#include <vector>
#include <string>

/* Author: Dennis Vo
 * Date: 2/9/17
 * Assignment: PA2
 * Description: Header file for Dictionary implementation using a ternary
 *              search tree.
 */


/* Separate node class for implementing the trie. */
class Node {
public:
  // ctor for ternary search tree node
  bool isWord;
  Node* left; Node* mid; Node* right;
  std::string text;
  std::string finalText; // contains entire word for a word node
  unsigned int freq; // node class initialization used from discussion

  Node();
};

/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class DictionaryTrie {
public:

  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

  /* Return up to num_completions of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than num_completions legal completions, this
   * function returns a vector with as many completions as possible.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the num_completions most frequent completions
   * of the prefix)
   */
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);

  /* Destructor */
  ~DictionaryTrie();

private:
  /* Pointer to root of trie */
  Node* root;

  /* Helper method to insert nodes onto trie */
  Node* insertHelper(Node* node, std::string word, int ind, unsigned int freq);

  /* Helper method to traverse down trie and find a word */
  Node* findHelper(Node* node, std::string word, int ind) const;

  /* Helper method that traverses down trie and deletes nodes. */
  static void deleteAll(Node* n);
};


#endif // DICTIONARY_TRIE_H
