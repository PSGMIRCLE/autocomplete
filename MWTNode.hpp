#ifndef MWTNODE_HPP
#define MWTNODE_HPP

#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class MWTNode {

public: 

  unordered_map<string, MWTNode*> table;
  bool isWord;
  int count;
  MWTNode * parent;

  MWTNode() : isWord(false), count(0), parent(0) {}

  ~MWTNode() {
    table.clear();
  }

};

#endif //MWTNODE_HPP
