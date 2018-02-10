#ifndef MWT_HPP
#define MWT_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include "MWTNode.hpp"
using namespace std;

class MWT {

protected:

  MWTNode * root;

public: 

  MWT(const vector<string> words) : root(0) {
    root = new MWTNode();
    build(words);
  }

  ~MWT() {
    delete root;
  }

private:

  //create the MWT given a vector of strings
  void build(const vector<string> words) {

    for(string s : words) {
      //start at root for each string
      MWTNode* curr = root;
      for(unsigned int i = 0; i < s.length(); i++) {

        //if key doesn't exist yet
        if(curr->table.find(s[i]) == curr->table.end()) {
          //insert key and create new MWTNode
          curr->table[s[i]] = new MWTNode();
          //set the new child's parent as curr
          curr->table[s[i]]->parent = curr;
        }
        //go to next MWTNode
        curr = curr->table[s[i]];

        //if last character of string
        if(i == s.length() - 1) {
          //set next node as a word node (exclusive) and update count
          curr->isWord = true;
          curr->count++;
        }
      }
    }
  }
};

#endif //MWT_HPP
