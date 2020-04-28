#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "sanitize.hpp"

using namespace std;

class TextGen {
private:
    map<string, vector<string>> markov_chain; //map usage is mandatory!

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
