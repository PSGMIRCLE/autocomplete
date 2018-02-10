#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include "MWTNode.hpp"
#include "MWT.hpp"
using namespace std;

int main() {
  /*
  MWTNode * node = new MWTNode();
  MWTNode * tester;
  node->table["t"] = new MWTNode();
  tester = node->table["t"];
  tester->count = 5;
  cout << node->table["t"]->count << endl;*/

  vector<string> list = {"category", "cat", "car", "apple"};

  MWT* mwt = new MWT(list);

  //MWTNode* curr = mwt->root;

  string test1, test2, test3, test4, test5;
  if(mwt->find("cat")) {test1 = "true";}
  else {test1 = "false";}

  if(mwt->find("tit")) {test2 = "true";}
  else {test2 = "false";}

  if(mwt->find("category")) {test3 = "true";}
  else {test3 = "false";}

  if(mwt->find("apple")) {test4 = "true";}
  else {test4 = "false";}

  if(mwt->find("cate")) {test5 = "true";}
  else {test5 = "false";}

  cout << test1 << " should be TRUE" << endl;
  cout << test2 << " should be FALSE" << endl;
  cout << test3 << " should be TRUE" << endl;
  cout << test4 << " should be TRUE" << endl;
  cout << test5 << " should be FALSE" << endl;

  return 0;
}
