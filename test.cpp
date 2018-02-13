#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include "MWTNode.hpp"
#include "MWT.hpp"
#include "Autocomplete.hpp"
#include "AutocompleteUtils.hpp"
using namespace std;

int main() {

  vector<string> list = {"", "category", "cat", "cat", "car", "apple", "Portable charger", "pup", "pup", "pup"};

  MWT* mwt = new MWT(list);

  cout << endl << "STARTING TESTS" << endl << "--------------" << endl;

  string test1, test2, test3, test4, test5, test6, test7, test8, test9, test10;
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

  if(mwt->find("c")) {test6 = "true";}
  else {test6 = "false";}

  if(mwt->find("")) {test7 = "true";}
  else {test7 = "false";}

  if(mwt->find("Portable charger")) {test8 = "true";}
  else {test8 = "false";}

  if(mwt->find("Portable charge")) {test9 = "true";}
  else {test9 = "false";}

  if(mwt->find("29284")) {test10 = "true";}
  else {test10 = "false";}

  cout << test1 << " should be TRUE" << endl;
  cout << test2 << " should be FALSE" << endl;
  cout << test3 << " should be TRUE" << endl;
  cout << test4 << " should be TRUE" << endl;
  cout << test5 << " should be FALSE" << endl;
  cout << test6 << " should be FALSE" << endl;
  cout << test7 << " should be TRUE" << endl;
  cout << test8 << " should be TRUE" << endl;
  cout << test9 << " should be FALSE" << endl;
  cout << test10 << " should be FALSE" << endl;

  cout << "\tALL EXISTENCE TESTS PASSED" << endl << endl;

  string test11, test12, test13, test14, test15;

  if(mwt->count("cat") == 2) {test11 = "true";}
  else {test11 = "false";}

  if(mwt->count("pup") == 3) {test12 = "true";}
  else {test11 = "false";}

  if(mwt->count("category") == 1) {test13 = "true";}
  else {test11 = "false";}

  if(mwt->count("not in tree") == 0) {test14 = "true";}
  else {test11 = "false";}

  if(mwt->count("Portable charger") == 1) {test15 = "true";}
  else {test11 = "false";}

  cout << test11 << " should be TRUE" << endl;
  cout << test12 << " should be TRUE" << endl;
  cout << test13 << " should be TRUE" << endl;
  cout << test14 << " should be TRUE" << endl;
  cout << test15 << " should be TRUE" << endl;

  cout << "\tALL COUNT TESTS PASSED" << endl << endl;


  vector<string> awords = {"a", "an", "an", "zzz", "and", "and", "and",
    "apple", "azzzNOTINLIST", "aza", "autocomplete", "dfd", "autocomplete",
    "autocomplete", "autocomplete", "fjsdlkfj", "dfjldkf", "aaaaaaaaaaaj",
    "auto", "amplify", "astringent"};

  vector<string> bwords = {"bus", "bus", "bus", "busy", "buster",
    "busted", "Busted", "buszzz", "busted", "buuuuuuuu", "baaaaaaa",
    "buuuuuuuu", "b1231213131", "b1231213131", "b(*2jd&]", "b(*2jd&]",
    "b(*2jd&]"};
  Autocomplete* tester = new Autocomplete(bwords);

  vector<string> completions = tester->predictCompletions("b");

  auto it = completions.begin();
  auto en = completions.end();

  for(; it != en; it++) {
    cout << *it << endl;
  }

  cout << "\t" << completions.size() << " completions found" << endl;

  cout << "\tSIMPLE PREDICT COMPLETION TESTS PASSED" << endl << endl;

  string empty = "TestCases/EmptyCorpus.txt";
  string small = "TestCases/SingleCorpus.txt";
  string medium = "TestCases/ModerateCorpus.txt";
  string large = "TestCases/LargeCorpus.txt";

  //CHANGE FILE NAME AND PREFIX HERE
  string sample = large;
  string prefix = "poss";

  cout << "TESTING SAMPLE FILE..." << endl;
  cout << "Looking for completions for prefix: \"" << prefix << "\"" << endl;
  cout << "In file: \"" << sample << "\"..." << endl;

  Autocomplete* tester2 = new Autocomplete(AutocompleteUtils::getWords(sample));

  vector<string> completions2 = tester2->predictCompletions(prefix);

  auto it2 = completions2.begin();
  auto en2 = completions2.end();

  for(; it2 != en2; it2++) {
    cout << *it2 << endl;
  }

  cout << "\t" << completions2.size() << " completions found" << endl << endl;

  return 0;
}
