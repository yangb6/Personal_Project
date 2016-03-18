#include <unordered_map>
#include "cell.h"
using namespace std;
class Honeycomb
{
public:
	~Honeycomb(){this->free_memory();}
	//Use hash map to store "location" of each character, so that we can easily find each charcter
	unordered_map<char, vector<Cell*> > honeycombMap;
	//Use vector to store the whole data
	vector< vector<Cell*> > layerData;
	Honeycomb(ifstream &in_str_1)
	{
		storeInputData(in_str_1);
		generateHoneycomb();
		generateMap();
	}
	unordered_map<char, vector<Cell*> > getHoneycombMap()
	{
		return honeycombMap;
	}
	vector< vector<Cell*> >  getLayerData() 
	{
		return layerData;
	}
	void setLayerData(vector< vector<Cell*> > new_layerData)
	{
		this->layerData = new_layerData;
	}
private:
	//Cut the honeycomb into different layer and set the each layer value
	vector<Cell*> generateEachLayer(string line_input,int layer)
	{
		vector<Cell*> ans;
		for(int i=0;i<line_input.size();i++)
		{
			Cell * new_cell = new Cell(line_input[i],layer);
			ans.push_back(new_cell);
		}
		return ans;
	}
	void storeInputData(ifstream &in_str_1)
	{
		string layer_number;
		in_str_1>>layer_number;
		int total_layer = stoi(layer_number);
		for(int i = 0 ;i<total_layer;i++)
		{
			string line_input;
			in_str_1>>line_input;
			if(line_input.size() > 0)
			{
				if((line_input.size() == i * 6 && i != 0)||(line_input.size() == 1&& i==0))
				{
					layerData.push_back(generateEachLayer(line_input,i));
				}
				else
				{
					cerr<<"Incorrect number of characters for layer: "<<i<<endl;
				}
			}
		}
	}
	//Set neighbors which was at the same layer of current cell
	void addSameLayerNeighbours(vector<Cell*> &currentLayerCells)
	{
		if(currentLayerCells.size()>1)
		{
			for(int i = 0;i<currentLayerCells.size();i++)
			{
				if(i == 0)
				{
					currentLayerCells[0]->add_one_Neigh(currentLayerCells[i+1]);
					currentLayerCells[0]->add_one_Neigh(currentLayerCells[currentLayerCells.size()-1]);
				}
				else if(i == currentLayerCells.size()-1)
				{
					currentLayerCells[i]->add_one_Neigh(currentLayerCells[0]);
					currentLayerCells[i]->add_one_Neigh(currentLayerCells[i-1]);
				}
				else
				{
					currentLayerCells[i]->add_one_Neigh(currentLayerCells[i+1]);
					currentLayerCells[i]->add_one_Neigh(currentLayerCells[i-1]);
				}

			}
		}
	}

	//Set neighbors which was lower than current cell
	void lowLayerNeighbours(int currentLayer, int lowerLayer)
	{
		int lowerIndex = 0;
		for(int i = 0; i < layerData[currentLayer].size(); i++)
		{
			layerData[currentLayer][i]->add_one_Neigh(layerData[lowerLayer][lowerIndex]);
			if((i  % currentLayer !=0) && (i != 0))
			{
				if (i == layerData[currentLayer].size() - 1) 
				{
                    layerData[currentLayer][i]->add_one_Neigh(layerData[lowerLayer][0]);
                    continue;
                }
                lowerIndex++;
                layerData[currentLayer][i]->add_one_Neigh(layerData[lowerLayer][lowerIndex]);
			}
		}
	}
	//Set neighbors which was upper than current cell
	void upLayerNeighs(int currentLayer,int upperlayer)
	{
		int upperIndex = 0;
		for(int i = 0; i < layerData[currentLayer].size();i++)
		{
			if(i == 0)
			{
				layerData[currentLayer][i]->add_one_Neigh(layerData[upperlayer][layerData[upperlayer].size()-1]);
			}
			if(currentLayer == 1)
			{
				layerData[currentLayer][i]->add_one_Neigh(layerData[upperlayer][upperIndex++]);
				if(i != 0)
				{
					layerData[currentLayer][i]->add_one_Neigh(layerData[upperlayer][upperIndex++]);
				}
				layerData[currentLayer][i]->add_one_Neigh(layerData[upperlayer][upperIndex]);
				continue;
			}
			layerData[currentLayer][i]->add_one_Neigh(layerData[upperlayer][upperIndex++]);
			layerData[currentLayer][i]->add_one_Neigh(layerData[upperlayer][upperIndex]);
			if(currentLayer != 0 && i % currentLayer == 0 && i != 0 )
			{
				upperIndex = upperIndex + 1;
				layerData[currentLayer][i]->add_one_Neigh(layerData[upperlayer][upperIndex]);
			}
		}
	}


	//Updata each cell about its neighbours
	void generateHoneycomb()
	{
		int total_layer_number = layerData.size();
		for(int i = 0; i<total_layer_number;i++)
		{
			addSameLayerNeighbours(layerData[i]);
			if(i == 0)
			{
				if(total_layer_number > 1)
				{
					layerData[i][0]->addNeighs(layerData[1]);
				}
				continue;
			}
			else if(i == 1)
			{
				for(int j = 0; j<layerData[i].size();j++)
				{
					layerData[i][j]->add_one_Neigh(layerData[0][0]);
				}
			}
			if(i < layerData.size()-1)
			{
				upLayerNeighs(i , i + 1);
			}
			if(i > 1)
			{
				lowLayerNeighbours(i, i-1);
			}

		}
	}

	void generateMap()
	{
		for(int i = 0; i< layerData.size();i++)
		{
			for(int j = 0 ;j < layerData[i].size();j++)
			{
				char current_char = layerData[i][j]->getValue();
				honeycombMap[current_char].push_back(layerData[i][j]);
			}
		}
	}

	//Free the memory 
	void free_memory()
	{
		for(int i = 0 ;i<layerData.size();i++)
		{
			for(int j=0;j<layerData[i].size();j++)
			{
				delete(layerData[i][j]);
			}
		}
	}


};