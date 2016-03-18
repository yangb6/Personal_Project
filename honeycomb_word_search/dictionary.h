#include <unordered_set>
#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <cstring>
#include <cstdlib>
#include <iomanip>

//Use a class to store the word we want to find
//Use the hash set to store data so that we can delete same word directly
using namespace std;
class Dictionary
{
public:
	Dictionary(ifstream &in_str_2)
	{
		readDictionary(in_str_2);
	}
	unordered_set<string> getDic()
	{
		return dictionary;
	}
	void setDic(unordered_set<string> dic)
	{
		dictionary = dic;
	}

private:
	unordered_set<string> dictionary;
	void readDictionary(ifstream &in_str_2)
	{
		while(in_str_2)
		{
			string word;
			in_str_2>>word;
			dictionary.insert(word);
		}
	}
};






