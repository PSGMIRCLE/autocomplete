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
    //build the backing data structure MWT
    root = new MWTNode();
    build(words);
  }

  ~MWT() {
    deleteAll(root);
  }

  void deleteAll(MWTNode* node) {
    //recursively call delete for each child node
    for(pair<char, MWTNode*> x : *(node->table)) {
      deleteAll(x.second);
    }
    delete node;
  }

  //gets an existing word
  MWTNode* getWord(const string word) {
    //if word doesn't exist, return nullptr
    if(!find(word)) {
      return nullptr;
    }
    //iterate to word
    MWTNode* curr = root;
    for(unsigned int i = 0; i < word.length(); i++) {
      char letter = word[i];
      curr = (*(curr->table))[letter];
    }
    return curr;
  }

  //gets any node within the MWT regardless of if it exists
  MWTNode* getNode(const string word) {
    MWTNode* curr = root;
    for(unsigned int i = 0; i < word.length(); i++) {
      char letter = word[i];
      //if node doesn't exist
      if(curr->table->find(letter) == curr->table->end()) {
        return nullptr;
      }
      curr = (*(curr->table))[letter];
    }
    return curr;
  }

  bool find(const string word) {
    MWTNode* curr = root;
    for(unsigned int i = 0; i < word.length(); i++) {
      char letter = word[i];
      //if character key doesn't exist
      if(curr->table->find(letter) == curr->table->end()) {
        return false;
      }
      curr = (*(curr->table))[letter];
    }
    //return whether or not that word exists
    return curr->isWord;
  }

  int count(const string word) {
    //if word doesn't exist in MWT
    if(!find(word)) {
      return 0;
    }
    MWTNode* curr = root;
    //iterate to last node
    for(unsigned int i = 0; i < word.length(); i++) {
      char letter = word[i];
      curr = (*(curr->table))[letter];
    }
    return curr->count;
  }

private:

  //create the MWT given a vector of strings
  void build(const vector<string> words) {

    for(string s : words) {
      //start at root for each string
      MWTNode* curr = root;
      for(unsigned int i = 0; i < s.length(); i++) {

        char letter = s[i];
        //if key doesn't exist yet
        if(curr->table->find(letter) == curr->table->end()) {
          //insert key and create new MWTNode
          (*(curr->table))[letter] = new MWTNode();
        }
        //go to next MWTNode
        curr = (*(curr->table))[letter];
      }
      //set next node as a word node and update count
      curr->isWord = true;
      curr->count++;
      curr->word = s;
    }
  }

};

#endif //MWT_HPP
