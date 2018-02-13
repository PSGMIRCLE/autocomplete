/**
 *  CSE 100 PA2 C++ Autocomplete
 *  Author: Jonathan Margoliash
 *  Modified from code authored by: Jor-el Briones, Christine Alvarado
 */

#ifndef AUTOCOMPLETE_HPP
#define AUTOCOMPLETE_HPP

#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include "MWT.hpp"
#include "MWTNode.hpp"
using namespace std;

/**
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie.
 */
class Autocomplete
{

public:

  MWT * mwt;

  /* 
  Create an Autocomplete object.
  This object should be trained on the words vector
  That is - the predictCompletions() function below should pull autocomplete
  suggestions from this vector

  Input: words. Must be all lowercase, with most  non-word characters removed (e.g. ',' ';' '%' etc.)
  In addition to alphabetic characters, words may contain digits, single apostrophes, dashes etc.
  */
  Autocomplete(const vector<string> words) {
    mwt = new MWT(words);
  }

  /* Return up to 10 of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than 10 legal completions, this
   * function returns a vector with as many completions as possible.
   * Otherwise, 10 completions should be returned.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the 10 most frequent completions
   * of the prefix)
   * If you need to choose between two or more completions which have the same frequency,
   * choose the one that comes first in alphabetical order.
   *
   * Inputs: prefix. The prefix to be completed. Must be of length >= 1.
   * Return: the vector of completions
   */
  vector<string> predictCompletions(const string prefix) {

    vector<string> completions;

    //check if prefix is at least length 1
    if(prefix.empty()) {
      return completions;
    }
    //check if a node for prefix exists in MWT
    if(mwt->getNode(prefix) == nullptr) {
      //if not, return empty 
      return completions;
    }
    //iterate to the prefix, must return an existing node
    MWTNode* curr = mwt->getNode(prefix);

    queue<MWTNode*> queue;

    vector<MWTNode*> list;

    //push the prefix node to start
    queue.push(curr);

    //add possible completions to queue
    while(!queue.empty()) {
      curr = queue.front();
      //if the node is a word node, add it to the list of words
      if(curr->isWord) {
        list.push_back(curr);
      }
      //pop the node so we don't run it again
      queue.pop();

      //declare iterators to iterate through the hash map
      auto it = curr->table.begin();
      auto en = curr->table.end();

      //push all possible pointers to next letters to queue
      for(; it != en; it++) {
        //push the MWTNode pointer to queue
        queue.push((*it).second);
      }
    }

    
    //sort the list of pairs by frequency and then by string
    sort(list.begin(), list.end(), 
      [] (MWTNode* const &x, MWTNode* const &y) {
        //if frequencies are same
        if(x->count == y->count) {
          //sort by string alphabetically backwards
          //since we return the new array in reverse
          return x->word > y->word;
        }
        //else just sort by frequencies
        return x->count < y->count;
      });

      /*
    sort(list.begin(), list.end(), 
      [] (MWTNode* const &x, MWTNode* const &y) {
        //else just sort by frequencies
        return x->count < y->count;
      });*/

    //only want 10 completions max
    int iterations = 0;
    for(int i = list.size() - 1; i >= 0; i--) {
      if(iterations >= 10) {
        return completions;
      }
      //add to list of completions
      completions.push_back(list[i]->word);
      iterations++;
    }

    return completions;
  }

  /* Destructor */
  ~Autocomplete() {
    delete mwt;
  }

  //You may add your own code here

private:

  //you may add your own code here

};

#endif // AUTOCOMPLETE_HPP
