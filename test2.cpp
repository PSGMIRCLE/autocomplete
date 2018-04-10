#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <utility>
#include "DocumentGenerator.hpp"
#include "CustomTree.hpp"
#include "CustomNode.hpp"
using namespace std;

int main() {

  DocumentGenerator* gen = new DocumentGenerator("PresidentialSpeeches/Obama");

  vector<string> list = gen->getWords("MyTests/testtext.txt");

  for(string s : list) {
    cout << s << endl;
  }

  CustomTree* tree = new CustomTree(list);

  //testing node existence with CustomTree build
  if(false) {
    cout << "TESTING NODE EXISTENCE..." << endl;

    if(tree->find("cat")) {
      cout << "FOUND cat" << endl;
    }
    if(tree->find("box")) {
      cout << "SHOULDN'T HAVE FOUND box" << endl;
    }
    if(tree->find("bed")) {
      cout << "FOUND bed" << endl;
    }
    if(tree->find("brit")) {
      cout << "FOUND brit" << endl;
    }
    if(tree->find(".")) {
      cout << "FOUND ." << endl;
    }
    if(tree->find(",")) {
      cout << "FOUND ," << endl;
    }
    if(tree->find("dfeg")) {
      cout << "FOUND dfeg" << endl;
    }
    if(tree->find("bin")) {
      cout << "FOUND bin" << endl;
    }
    if(tree->find("poop")) {
      cout << "FOUND poop" << endl;
    }
  }

  //get the node for string cat
  CustomNode* curr = tree->directory["cat"];

  auto it = curr->map.find("bed");
  auto en = curr->map.end();

  cout << "TESTING EACH NODES' NEXT WORDS" << endl;
  if(it != en) {
    cout << "FOUND bed" << endl;
  }
  it = curr->map.find("brit");
  if(it != en) {
    cout << "INCORRECTLY FOUND brit" << endl;
  }
  it = curr->map.find("brain");
  if(it != en) {
    cout << "FOUND brain" << endl;
  }

  cout << endl;

  cout << "TESTING FREQUENCIES..." << endl;
  cout << tree->directory["cat"]->map["bed"].second << " should be 1" << endl;
  cout << tree->directory["cat"]->map["brain"].second << " should be 3" << endl;
  cout << tree->directory["brain"]->map["cat"].second << " should be 2" << endl;
  cout << tree->directory["brain"]->map["."].second << " should be 1" << endl;
  //cout << tree->directory[""]->map["cat"].second << " should be 1" << endl;
  cout << endl;

  vector<string> list2 = gen->getWords("MyTests/testtext2.txt");
  tree->build(list2);

  cout << "TESTING FREQUENCIES WITH SECOND BUILD..." << endl;
  cout << tree->directory["cat"]->map["bed"].second << " should be 3" << endl;
  cout << tree->directory["poop"]->map["dfeg"].second << " should be 2" << endl;
  //cout << tree->directory[""]->map["cat"].second << " should be 2" << endl;
  cout << endl;

  cout << "TESTING DOCUMENTGENERATOR CONSTRUCTOR..." << endl;
  cout << "Number of unique words: " << gen->tree->numUniqueWords << endl;
  cout << "Number of total words: " << gen->tree->numWords << endl;
  cout << endl;

  DocumentGenerator* gen2 = new DocumentGenerator("MyTests");

  cout << gen2->generateNextWord("cat") << " could be bed or brain" << endl;
  cout << gen2->generateNextWord("dfeg") << " could be cat" << endl;

  cout << endl;

  cout << gen->generateNextWord("the") << " could be anything" << endl;

  cout << endl;

  cout << gen->tree->directory["."]->word << " is size: " << gen->tree->directory["."]->word.size() << endl;

  cout << gen->generateDocument(1000);

  return 0;
}
