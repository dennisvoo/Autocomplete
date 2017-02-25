#include "util.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#include "DictionaryTrie.h"
#include <fstream>
#include <string>

/* Author: Dennis Vo
 * Date: 2/10/17
 * Assignment: PA2
 * Description: benchdict benchmarks all 3 dictionary types and gives average
 *              runtime for all 3
 */


int main(int argc, char *argv[]) {
  if (argc != 5) {
    std::cout << "Wrong # of arguments" << std::endl;
    return -1;
  }

  int min_size = std::stoi(argv[1]);
  int step_size = std::stoi(argv[2]);
  int num_iterations = std::stoi(argv[3]);
  std::string dictfile = argv[4];

  std::cout<< "Benchmarking DictionaryBST" << std::endl;
  for (int i = 0; i < num_iterations; i++) {
    DictionaryBST* bst = new DictionaryBST();
    std::ifstream input;
    input.open(dictfile, std::ifstream::in);
    Utils::load_dict(*bst, input, min_size + i * step_size);
    
    // load next 100 words into a vector
    std::vector<std::string> strings;
    Utils::load_vector(strings, input, 100);

    // initialize time
    long long time = 0;
    
    // find time it takes to find 100 words
    // do it 5 times to get a good average runtime
    for (int i = 0; i < 5; i++) {
      Timer T;    
      T.begin_timer();

      for (int j = 0; j < 100; j++) {
        (*bst).find(strings[j]);
      }

      time += T.end_timer();
    }
    time = time/5;

    std::cout << min_size + i * step_size << "\t" << time << std::endl;

    // close file and delete dict obj
    input.close();
    delete(bst);
  }

  /* identical to BST benchmark */
  std::cout<< "Benchmarking DictionaryHashtable" << std::endl;
  for (int i = 0; i < num_iterations; i++) {
    DictionaryHashtable* hasht = new DictionaryHashtable();
    std::ifstream input2;
    input2.open(dictfile, std::ifstream::in);
    Utils::load_dict(*hasht, input2, min_size + i * step_size);

    std::vector<std::string> strings2;
    Utils::load_vector(strings2, input2, 100);

    long long time = 0;
    for (int i = 0; i < 5; i++) {
      Timer T;    
      T.begin_timer();

      for (int i = 0; i < 100; i++) {
        (*hasht).find(strings2[i]);
      }

      time += T.end_timer();
    }

    time = time/5;

    std::cout << min_size + i * step_size << "\t" << time << std::endl;

    input2.close();
    delete(hasht);
  }

  /* identical to BST benchmark */
  std::cout<< "Benchmarking DictionaryTrie" << std::endl;
  for (int i = 0; i < num_iterations; i++) {
    DictionaryTrie* trie = new DictionaryTrie();
    std::ifstream input3;
    input3.open(dictfile, std::ifstream::in);
    Utils::load_dict(*trie, input3, min_size + i * step_size);

    std::vector<std::string> strings3;
    Utils::load_vector(strings3, input3, 100);

    long long time = 0;
    for (int i = 0; i < 5; i++) {
      Timer T;    
      T.begin_timer();

      for (int i = 0; i < 100; i++) {
        (*trie).find(strings3[i]);
      }

      time += T.end_timer();
    }
    
    time = time/5;

    std::cout << min_size + i * step_size << "\t" << time << std::endl;

    input3.close();
    delete(trie);
  }

  return 0;
}
