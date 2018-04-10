#ifndef CUSTOMTREE_HPP
#define CUSTOMTREE_HPP

#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include "CustomNode.hpp"

using namespace std;

class CustomTree {
public:

  CustomNode* root;
  unordered_map<string, CustomNode*> directory;
  //keep track of sizes to test
  int numUniqueWords;
  int numWords;

  CustomTree() : numUniqueWords(0), numWords(0) {
    //set root as period
    root = new CustomNode(".");
    directory["."] = root;
  }

  CustomTree(vector<string> words) : numUniqueWords(0), numWords(0) {
    root = new CustomNode(".");
    directory["."] = root;
    build(words);
  }

  ~CustomTree() {
    //iterate through directory and delete all the nodes there
    auto it = directory.begin();
    auto en = directory.end();
    for(; it != en; it++) {
      delete (*it).second;
    }
  }

  void build(vector<string> words) {

    //keep track of previous word
    CustomNode* prev = root;

    for(string s : words) {
      auto it = directory.find(s);
      auto en = directory.end();
      //if given string doesn't have a node created for it
      if(it == en) {
        numUniqueWords++;
        directory[s] = new CustomNode(s);
      }
      //add that new word as a "next-word" of the previous
      //or increment it (handled in addNextWord())
      prev->addNextWord(directory[s]);
      numWords++;
      prev = prev->map[s].first;
    }
  }

  //find used for testing existence of nodes
  bool find(string word) {
    auto it = directory.find(word);
    auto en = directory.end();
    if(it == en) {
      return false;
    }
    return true;
  }

private:


};

#endif //CUSTOMTREE_HPP