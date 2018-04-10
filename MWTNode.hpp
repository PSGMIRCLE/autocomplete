#ifndef MWTNODE_HPP
#define MWTNODE_HPP

#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class MWTNode {

public: 

  //backing hash table to store children
  unordered_map<char, MWTNode*>* table;
  bool isWord;
  string word = "";
  int count;

  MWTNode() : isWord(false), count(0) {
    //initialize table
    table = new unordered_map<char, MWTNode*>();
  }

  ~MWTNode() {
    delete table;
  }

};

#endif //MWTNODE_HPP
