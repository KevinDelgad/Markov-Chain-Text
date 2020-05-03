#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "sanitize.hpp"
#include <deque>
#include <sstream>

using namespace std;

class TextGen {
private:
    map<string, vector<string>> markov_chain; //map usage is mandatory!
    std::vector<string> words;

public:
	TextGen(const unsigned int seed);
	void readIn(const string & filename);
	bool isEndPunctuation(const char character);
	vector<string> getValues(const string & key);
	string generateSentence();
	map<string, vector<string>> get_markovChain();
};

//TextGen's constructor has been created for you
TextGen::TextGen(const unsigned int seed)
{
	srand(seed);//seeds our random number generator
}

//Create the rest of the functions below...
void TextGen::readIn(const string & filename){
  std::ifstream in_file;
  in_file.open(filename.c_str());
  deque<std::string> stringQueue;
  string tempWord;
  string tempKey;
  string tempValue;
  string currentWord;
  string testerStr;
  string heldword;
  char testChar;
  while(in_file >> tempWord)
  {
    sanitize(tempWord);
    stringQueue.push_back(tempWord);
  }

  stringQueue.push_front("^");

  while(!stringQueue.empty())
  {
      tempKey = stringQueue.front();
      stringQueue.pop_front();
      heldword = stringQueue.front();
      stringQueue.pop_front();

      if(heldword.size() > 1)
      {
        testChar = heldword[heldword.size()-1];

          if(isEndPunctuation(testChar))
          {
            stringQueue.push_front(heldword.substr(heldword.size()-1));
            heldword = heldword.substr(0, heldword.size() - 1);
          }
      }

      stringQueue.push_front(heldword);

      if(tempKey == "?" || tempKey == "!"|| tempKey == ".")
      {
        stringQueue.push_front("$");
      }

      if(tempKey == "$" && !stringQueue.empty())
      {
        stringQueue.push_front("^");
      }

      tempValue = stringQueue.front();
      markov_chain[tempKey].push_back(tempValue);

        if(tempValue == "mind,--for")
        {
          std::cout << tempValue << '\n';
        }
  }


}

bool TextGen::isEndPunctuation(const char character){
  if(character == '?' || character == '!' || character == '.')
  {
    return true;
  }

  return false;
}
vector<string> TextGen::getValues(const string & key){
  return markov_chain[key];
}

string TextGen::generateSentence(){
  int random;
  map<string, vector<string>>::iterator it;
  string sentence;
  string curWord;
  string entryString = "^";
  string exitString = "$";
  bool endPunc = false;
  it = markov_chain.find(entryString);
  while(it->first != "$")
  {
    random = rand() % it->second.size();
    curWord = it->second[random];
    it = markov_chain.find(curWord);
    if(curWord != exitString)
    {
      sentence += curWord;

      if(curWord == "." || curWord == "!" || curWord == "?")
      {
        endPunc = true;
      }

      if(!endPunc){
        sentence += " ";
      }

    }
  }


  return sentence;

}

map<string, vector<string>> TextGen::get_markovChain(){

  return markov_chain;

}
