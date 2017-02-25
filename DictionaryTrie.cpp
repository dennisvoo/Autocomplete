#include "util.h"
#include "DictionaryTrie.h"
#include <set>
#include <queue>

/* Author: Dennis Vo
 * Date: 2/9/17
 * Assignment: PA2
 * Description: Implementation of a Dictionary using a Ternary Search Tree.
 */

/** Ctor for node class, initializing values of node. */
Node::Node() {
  isWord = false;
  left = 0; mid = 0; right = 0;
  text = " ";
  finalText = " ";
  freq = 0;
}

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie() {
  root = new Node();
}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq) {
  if (word == " ") {
    return false;
  }
 
  if (find(word)) {
    insertHelper(root, word, 0, freq);
    // calling help method to update freq if word in there
    return false;
  } else {
    insertHelper(root, word, 0, freq);
    return true;
  }
}

/** Helper method for insert returns a node pointer and takes in a node ptr,
 *  a string, an index, and a freq. It uses the node ptr to traverse down
 *  the trie and insert letters of the word. It iterates through the letters
 *  using the ind parameter. Freq is included to update a frequency at the
 *  word node.
 */
Node* DictionaryTrie::insertHelper(Node* node, std::string word, int ind, 
unsigned int freq) {
  if (!node) {
    node = new Node();
    node->text = word[ind];
    // insert char at index if current node is empty
  }

  /* If node exists, we traverse down trie, following rules of a ternary search
   * trie, and finds children for current node.
   */
  if (node->text[0] > word[ind]) {
    node->left = insertHelper(node->left, word, ind, freq);
  }
  else if (node->text[0] < word[ind]) {
    node->right = insertHelper(node->right, word, ind, freq);
  }
  else if (ind < (int) word.size() - 1) {
    // checking if we have reached end of word we are trying to insert
    node->mid = insertHelper(node->mid, word, ind + 1, freq);
  } else {
    node->isWord = true;
    node->finalText = word;
    node->freq = freq;
    // update isWord and freq if we have reached word node
  }

  return node;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const {
  Node* search = findHelper(root, word, 0);
  // use helper method to traverse down tree, iterating through letters
 
  return search&&search->isWord;
  // returns true if we find a word node at the end
}

/** Helper method that returns a node ptr, traversing down trie. It takes in
  * a node ptr to traverse down tree along with a word and index used to
  * iterate through the letters.
  */
Node* DictionaryTrie::findHelper(Node* node, std::string word, int ind) const {
  if (!node) {
    return 0;
  }

  if (node->text[0] > word[ind]) {
    return findHelper(node->left, word, ind);
  }
  if (node->text[0] < word[ind]) {
    return findHelper(node->right, word, ind);
  }
  if (ind < (int) word.size() - 1) {
    return findHelper(node->mid, word, ind + 1);
  }

  return node;
  
  /* recursive method of findHelper should return nodes containing the word
   * in reverse order and first node returned should return true (word node)*/
}

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
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions) {
  std::vector<std::string> words;

  std::set<std::pair<Node*, unsigned int>> set;

  Node* curr = findHelper(root, prefix, 0); //grab ptr to node at end of prefix

  if (!curr) {
    return words;
  }

  if (curr->isWord) {
    std::pair<Node*, unsigned int> pairs;
    pairs.first = curr; pairs.second = curr->freq;
    set.insert(pairs);
  }

  // queue for BFS
  std::queue<Node*> q; 
  q.push(findHelper(root,prefix,0)->mid);
  // push prefix's node onto queue

  // Perform the BFS on the nodes of the trie

  while (!q.empty()) {
    if (q.front()->isWord) {
      std::pair<Node*, unsigned int> pairs;
      pairs.first = q.front(); pairs.second = q.front()->freq;
      set.insert(pairs);
    }

    if (q.front()->left) {
      q.push(q.front()->left);
    }
    if (q.front()->mid) {
      q.push(q.front()->mid);
    }
    if (q.front()->right) {
      q.push(q.front()->right);
    }
    q.pop();
  }
  
  // We make another copy of a vector to store all total completions
  // Then we will choose the first num_completions of the vector later
  std::vector<std::string> wordCopy;
  int totalWords = set.size();

  for (int i = 0; i < totalWords; i++) {
    auto it = set.begin();
    auto end = set.end();
    std::pair<Node*, unsigned int> temp;
    temp = *it;

    while (it != end) {
      ++it;

      if (it == end) {
        break;
      }

      if ((*it).second >= temp.second) {
        temp = *it;
      }
    }

    wordCopy.push_back(temp.first->finalText);
    set.erase(temp);
  }

  for (int i = 0; i < (int) num_completions; i++) {
    // iterate through finalSet to insert into final vector
    std::string finalWord = wordCopy[i];
    words.push_back(finalWord);
  }

  return words;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie() {
  deleteAll(root);
}

/** Helper static method recursively traverses down tree, deleting nodes. */
void DictionaryTrie::deleteAll(Node* n) {
  if (!n) {
    return;
  }
  deleteAll(n->left);
  deleteAll(n->mid);
  deleteAll(n->right);
  delete(n);
  return;
}
