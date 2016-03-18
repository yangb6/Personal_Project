#include <set>
#include "honeycomb.h"
#include "dictionary.h"
using namespace std;
//If we find current character, go to next character and then search in the current character's neighbours
void serch_oneByone(Cell * cell, string validWord, string left_word,set<string> &results)
	{
		if(cell->getValue() == left_word[0])
		{
			cell->setState(1);
			left_word = left_word.substr(1,left_word.size()-1);
			if(left_word.size() == 0)
			{
				results.insert(validWord);
				return;
			}
			vector<Cell*> all_neighbours = cell->getNeigh();
			for(int i = 0;i < all_neighbours.size();i++)
			{
				if(all_neighbours[i]->getState() == 0)
				{
					serch_oneByone(all_neighbours[i],validWord,left_word,results);
				}
			}
		}
		else
		{
			return;
		}
	}

//Search the same character in the honeycombMap
void find_word(vector<Cell*> & startingCells,string each_word, vector<vector<Cell*> >&layerData,set<string> &results)
	{
		if(startingCells.size()>0)
		{
			for(int i = 0;i < startingCells.size(); i++)
			{
				int initial_results_size = results.size();
				serch_oneByone(startingCells[i],each_word,each_word,results);
				for(int l = 0;l<layerData.size();l++)
				{
					for(int m = 0 ;m < layerData[l].size();m++)
					{
						layerData[l][m]->setState(0);
					}
				}
				int after_results_size = results.size();
				if(initial_results_size < after_results_size)
				{
					break;
				}

			}
		}
	}


//Function to find the if the word in the honeycomb or not
set<string> getFinalResults( Honeycomb &honeycomb, Dictionary &dictionary,set<string> &results)
{
	unordered_set<string> dic = dictionary.getDic();
	unordered_set<string>::iterator word = dic.begin();
	unordered_map<char, vector<Cell*> > final_map = honeycomb.getHoneycombMap();
	vector<vector<Cell*> > every_layer_data = honeycomb.getLayerData();
	while(word != dic.end())
	{
		string each_word = *word;
		find_word(final_map[each_word[0]],each_word,every_layer_data,results);
		word++;
	}
	return results;
}

int main(int argc, char * argv[])
{
    if(argc != 3)
    {
        cerr<<"Usage:"<<argv[0]<<"inputFileName outputFileName object\n";
        return 1;
    }
    ifstream in_str_1(argv[1]);
    if(!in_str_1)
    {
        cerr<<"Could not open "<<argv[1]<<"to read\n";
        return 1;
    }
    ifstream in_str_2(argv[2]);
    if(!in_str_2)
    {
    	cerr<<"Could not open "<<argv[1]<<"to read\n";
        return 1;
    }
    Dictionary *dictionary =new Dictionary(in_str_2);
    Honeycomb *new_honey = new Honeycomb(in_str_1);
    set<string> final_resutls;
    getFinalResults(*new_honey,*dictionary,final_resutls);
    set<string>::iterator itr = final_resutls.begin();
    while(itr != final_resutls.end())
    {
    	cout<<*itr<<endl;
    	itr++;
    }
    delete(dictionary);
    delete(new_honey);
    return 0;
}