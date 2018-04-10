/**
 * CSE 100 PA2 SpeechBuilder
 * Author: Jonathan Margoliash
 */

#ifndef DOCUMENT_GENERATOR_HPP
#define DOCUMENT_GENERATOR_HPP

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <utility>
#include "dirent.h"
#include "CustomTree.hpp"
#include "CustomNode.hpp"

using namespace std;

class DocumentGenerator
{
public:

  CustomTree* tree;
  
 /**
 * Builds a document generator from the documents in the given directory
 * This should open all files in the directory, reads them in, tokenize them into words,
 * and build the datastructure from that stream of words.
 *
 * To tokenize a document:
 * * remove all UNWANTED_CHARACTERS from the document
 * * split it into different tokens based on whitespace (treat all whitespace breaks equally)
 * * additionally split each PUNCTUATION character into its own token (so a single period is a 'word')
 * * from here on, we'll use the word "word" to refer to both strings like "hello" and punctuation strings like "." or ","
 *
 * So, for instance, the short sentence
 * "I like trains. Sally ju^mped over the moon, I think? I. I think."
 * Would be tokenized into ["I", "like", "trains", ".", "Sally",
 *   "jumped", "over", "the", "moon", ",", "I", "think", "?", "I", ".", "I" "think", "."]
 * and the frequencies of the words after "I" would be;
 *  like - 1
 *  think - 2
 *  . - 1
 *
 * You may use the utilities in AutocompleteUtils to help you with this
 * and you may rely on them working.
 * Note however that they do not deal with unwanted characters or split punctuation appropriately.
 * 
 * A few notes:
 * 1) you must treat words with different capitalizatoins differently
 * * (so "foo" and "Foo" are different words, and the frequencies of the words that follow (or precede)
 * * "foo" will be different than the frequencies of the words that follow (or precede) "Foo" )
 * 2) pretend that the first word in the document is preceeded by a periood (That way, it is considered when starting any new sentence)
 */
  DocumentGenerator(const string documentsDirectory) {

    tree = new CustomTree();

    DIR* dir;
    struct dirent *ent;
    //read through each file in the given directory
    if((dir = opendir(documentsDirectory.c_str()))) {
      while((ent = readdir(dir))) {
        //convert cstring (char[]*) to string
        string dirName(ent->d_name);
        //tokenize each document into a vector of formatted strings
        vector<string> strings = getWords(documentsDirectory + "/" + dirName);
        //build the tree with each vector
        tree->build(strings);
      }
      closedir(dir);
    }
  }

  /**
 * Suppose you're in the middle of generating a document and that you've just added the word prevWord
 * to the document. generateNextWord(prevWord) should generate the next word at random for the document,
 * according to the frequencies of all the words that followed prevWord in the input documents
 *
 * So, for instance, if in all the input documents the word "foo" was followed by the word "bar" twice and "baz" 8 times,
 * then 80% of the time generateNextWord("foo") should return "baz" and 20% of the time you should return "bar".
 * 
 * This method should return punctuation words like "." and "," as if they were any other word.
 * Likewise, it should be able to take punctuation words as input (generateNextWord(","))
 * 
 * You can assume that prevWord is always a word that's present in one of the documents you've read in.
 */
  string generateNextWord(const string prevWord) {
    //check if passed in string exists in the tree
    if(tree->find(prevWord)) {
      //get the node for given string
      CustomNode* word = tree->directory[prevWord];
      vector<pair<CustomNode*, int>> possibleNextWords;
      auto it = word->map.begin();
      auto en = word->map.end();
      //keep track of total frequencies as denominator for probability
      int total = 0;
      //iterate through possible next-words and add them to a vector
      for(; it != en; it++) {
        possibleNextWords.push_back((*it).second);
        //increment total with each frequency
        total += (*it).second.second;
      }
      //generate a random number between 0 (inclusive) and total (exclusive)
      int x = rand() % total;
      int numerator = 0;

      for(unsigned int i = 0; i < possibleNextWords.size(); i++) {
        //increment the newest frequency to numerator
        numerator += possibleNextWords[i].second;
        //if the random number is less than the numerator
        if(x < numerator) {
          //we select that string
          return possibleNextWords[i].first->word;
        }
      }
    }
    return "I SHOULD NEVER BE RETURNED";
  }

  /**
 * Generate a document with numWords words in it.
 *
 * See the docs on generateNextWord for a description of what it means to generate a word.
 * After generating all the words - concatenate them all into a single string representing the entire document, and return that string.
 *
 * Notes:
 * The first word you generate should be as if the previous word was '.'
 * Your document should not contain whitespace except for spaces.
 * Your should insert a single space in front of each word except:
 * * Don't insert spaces in front of punctuation marks
 * * Don't insert a space at the start of the document
 * 
 * The document will likely not end at the end of a sentence. That's okay.
 */
  string generateDocument(const int numWords) {

    //generate psuedo-randomness
    srand(time(NULL));

    //start with first node
    CustomNode* start = tree->root;
    string document = "";
    string buffer;
    const string space = " ";
    bool firstWord = true;

    for(int i = 0; i < numWords; i++) {
      buffer = generateNextWord(start->word);
      //if first word, don't add space before it
      if(firstWord) {
        document += buffer;
        firstWord = false;
      }
      //if next word is single character
      else if(buffer.size() == 1) {
        //if that character is a punctuation mark
        if(PUNCTUATION.find(buffer[0]) != string::npos) {
          document += buffer;
        }
        //if single character string but not punctuation
        else {
          //add space
          document += space;
          document += buffer;
        }
      }
      //if actual word
      else {
        document += space;
        document += buffer;
      }
      start = start->map[buffer].first;
    }
    return document;
  }

  ~DocumentGenerator() {
    delete tree;
  }

  //modified tokenize to handle unwanted chars and punctuation
  vector<string> tokenize(const string line) {
    vector<string> words;
    vector<char> word;
    for (unsigned char c : line) {
      //if we find an unwanted character, skip it
      if(UNWANTED_CHARACTERS.find(c) != string::npos) {
        continue;
      }
      //if letter is punctuation
      if(PUNCTUATION.find(c) != string::npos) {
        //push previous word before punctuation
        if(word.size() > 0) {
          words.push_back(string(word.begin(), word.end()));
        }
        //clear buffer string
        word.clear();
        //add punctuation mark to buffer string
        word.push_back(c);
        //push that punctuation mark too
        words.push_back(string(word.begin(), word.end()));
        word.clear();
        continue;
      }
      //if letter isn't unwanted, punctuation, nor a space
      if (whitespace.find(c) == string::npos) {
        //add it
        word.push_back(c);
      } 
      //if letter is a space
      else if (word.size() > 0) {
        words.push_back(string(word.begin(), word.end()));
        word.clear();
      }
    }
    //if last character is a space for some strange reason
    if (word.size() > 0) {
      //push back the last word if there was one
      words.push_back(string(word.begin(), word.end()));
    }
    return words;
  }

  //same getWords implementation from starter AutocompeteUtils.hpp
  //Piazza post said it was ok to do this
  vector<string> getWords(const string fileLocation) {
    vector<string> words;

    ifstream infile;
    infile.open(fileLocation);

    if (!infile) {
      cerr << "Couldn't open file: " << fileLocation << endl;
      exit(1);
    }

    string line;
    while(getline(infile, line)) {
      vector<string> wordsInLine = tokenize(line);
      words.insert(words.end(), wordsInLine.begin(), wordsInLine.end());
    }

    return words;  
  }
  
  //Feel free to put your own code here

private:
  const string PUNCTUATION = ".!,?";
  const string UNWANTED_CHARACTERS = ";:\"~()[]{}\\/^_<>*=&%@$+|`";
  const string whitespace = " \t\r\n\v\f";


  //Feel free to put your own code here
};

#endif //DOCUMENT_GENERATOR_HPP

