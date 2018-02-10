#ifndef MWT_HPP
#define MWT_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include "MWTNode.hpp"
using namespace std;

class MWT {

public: 

  MWTNode * root;

  MWT(const vector<string> words) {
    root = new MWTNode();
    build(words);
  }

  ~MWT() {
    delete root;
  }

  bool find(string word) {
    MWTNode* curr = root;
    for(unsigned int i = 0; i < word.length(); i++) {
      string letter = "" + word[i];
      //if character key doesn't exist
      if(curr->table.find(letter) == curr->table.end()) {
        return false;
      }
      curr = curr->table[letter];
    }
    return curr->isWord;
  }

private:

  //create the MWT given a vector of strings
  void build(const vector<string> words) {

    for(string s : words) {
      //start at root for each string
      MWTNode* curr = root;
      for(unsigned int i = 0; i < s.length(); i++) {

        string letter = "" + s[i];
        //if key doesn't exist yet
        if(curr->table.find(letter) == curr->table.end()) {
          //insert key and create new MWTNode
          curr->table[letter] = new MWTNode();
          //set the new child's parent as curr
          curr->table[letter]->parent = curr;
        }
        //go to next MWTNode
        curr = curr->table[letter];
      }
      //set next node as a word node and update count
      curr->isWord = true;
      curr->count++;
    }
  }

};

#endif //MWT_HPP
