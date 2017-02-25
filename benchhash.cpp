#include "util.h"


/* Author: Dennis Vo
 * Date: 2/10/17
 * Assignment: PA2
 * Description: benchhash analyzing two hash functions
 */

/* Hash Function 1 */
int hash1 (std::string word, int size) {
  int sum = 0;
  for (int k = 0; k < (int) word.length(); k++) {
    sum = sum + int(word[k]);
  }
  return  sum % size; 
}

/* Hash Function 2 */
int hash2 (std::string word, int size) {
  int seed = 131; 
  unsigned long hash = 0;
  for(int i = 0; i < (int) word.length(); i++) {
    hash = (hash * seed) + word[i];
  }
  return hash % size;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << "Wrong # of Arguments" << std::endl;
    return -1;
  }

  std::string dictfile = argv[1];
  int num_words = std::stoi(argv[2]);



}
