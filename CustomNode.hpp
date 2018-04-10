#ifndef CUSTOMNODE_HPP
#define CUSTOMNODE_HPP

#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

using namespace std;

class CustomNode {
public:

  unordered_map<string, pair<CustomNode*, int>> map;
  string word;

  CustomNode(string s) {
    word = s;
  }

  void addNextWord(CustomNode* node) {
    auto it = map.find(node->word);
    auto en = map.end();
    //if node for given string doesn't exist in map
    if(it == en) {
      //make the new pair with frequency 1
      map[node->word] = make_pair(node, 1);
    }
    else {
      //else just update its frequency
      map[node->word].second++;
    }
  }


};

#endif //CUSTOMNODE_HPP