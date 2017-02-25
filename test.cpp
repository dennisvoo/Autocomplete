#include<iostream>
#include<string>
#include<algorithm>
#include<set>
#include<cstdlib>
#include<fstream>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#define LETTERS 26
using namespace std;

/* Author: Dennis Vo
 * Date: 2/9/17
 * Assignment: PA2
 * Description: Handles all the testing for the Dictionary files.
 */

int main(int argc, char** argv)
{

  //Initialize words
  vector<std::string> words;
  vector<string>::iterator wit;
  vector<string>::iterator wen;
  //initialize nonwords
  set<string> nope;
  set<string>::iterator nit;
  set<string>::iterator nen;

  //Initialize data structures
  DictionaryBST d_bst;
  DictionaryHashtable d_ht;
  DictionaryTrie dt;
  int t_bst, t_ht, tt;

  words.push_back("harry");
  words.push_back("sriram");
  words.push_back("cse");
  words.push_back("crucio");
  words.push_back("autocomplete");
  
  
  cout << "Inserting into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 1);
      //cout << t_bst << " " << t_ht << " "<< tt << "... ";
      if(!t_bst)
	{
	  cout << "failed for DictionaryBST... ";
	}
      if(!t_ht)
	{
	  cout << "failed for DictionaryHashset... ";
	}
      if(!tt)
	{
	  cout << "failed for DictionaryTrie... ";
	}
      if(t_bst && t_ht && tt)
	{
	  cout << "PASSED! :D ";
	}
      cout << endl;
    }

  cout << endl << "Re-inserting elements that were just inserted into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 0);
      if(t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(!t_bst && !t_ht && !tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }

  cout << endl;

  
/*You are supposed to add more test cases in this file */

  /* Testing to see if predictCompletions returns correct vector given
   * specific frequencies on 4 entries
   */
  DictionaryTrie dict;
  dict.insert("ab", 5);
  dict.insert("abb", 10);
  dict.insert("abc", 25);
  dict.insert("abcd", 20);

  if (!dict.find("ab")) {
    cout << "dict fails" << endl;
  }
  if (!dict.find("abc")) {
    cout << "dict fails" << endl;
  }
  if (!dict.find("abcd")) {
    cout << "dict fails" << endl;
  }
 
  cout << "First Trie" << endl;
  vector<string> completions;
  completions = dict.predictCompletions("ab",4);
  cout << completions[0] << endl;
  cout << completions[1] << endl;
  cout << completions[2] << endl;
  cout << completions[3] << endl;
 
  cout << "Next Trie" << endl;
  DictionaryTrie dict1;
  dict1.insert("ab", 5);
  dict1.insert("abb", 10);
  dict1.insert("abc", 25);
  dict1.insert("abcd", 20);
  dict1.insert("abacus", 15);
  dict1.insert("abby", 30);
  dict1.insert("abcde", 1);
  dict1.insert("abcdef", 2);
  dict1.insert("abab", 3);
  dict1.insert("abbef", 12);
  dict1.insert("abcs", 13);
  dict1.insert("abcdy", 9);

  vector<string> completions1;
  completions1 = dict1.predictCompletions("ab",10);
  cout << completions1[0] << endl;
  cout << completions1[1] << endl;
  cout << completions1[2] << endl;
  cout << completions1[3] << endl;
  cout << completions1[4] << endl;
  cout << completions1[5] << endl;
  cout << completions1[6] << endl;
  cout << completions1[7] << endl;
  cout << completions1[8] << endl;
  cout << completions1[9] << endl;


  DictionaryTrie gradedTrie;
  ifstream shuffledFile ("shuffled_unique_freq_dict.txt");
  Utils::load_dict(gradedTrie, shuffledFile);

  vector<string> testPrefixes;
  testPrefixes.push_back("be");
  testPrefixes.push_back("the");
  testPrefixes.push_back("do");
  testPrefixes.push_back("co");
  testPrefixes.push_back("yo");

  vector<int> testSizes;
  testSizes.push_back(10);
  testSizes.push_back(20);
  testSizes.push_back(50);

  for (auto prefix : testPrefixes) {
    for (auto size : testSizes) {
      cout << "Using prefix: " << prefix << " And size: " << size << endl;
      auto testVector = gradedTrie.predictCompletions(prefix,size);
      cout << "Vector Returned Has Size: " << testVector.size() << endl;
      for (auto iterator : testVector) {
        cout << iterator << ", ";
      }
      cout << endl << endl;
    }
    
  }

  return 0;
}
