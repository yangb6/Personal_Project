#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <cstring>
#include <cstdlib>
#include <map>
#include <iomanip>
using namespace std;

//Using cell class to represent each cell in honeycomb
//Cell has different variables to represent its status
class Cell
{
public:
	Cell();
	Cell(char value, int levelNumber)
	{
		this->value = value;
		state = 0;
		level =levelNumber;
	}
	int getState(){ return state;}
	void setState(int state) {this->state = state;}
	int getLevel(){return level;}
	void setLevel(int level) { this->level = level;}
	vector<Cell*> getNeigh(){return neighbours;}
	void setNeigh(vector<Cell*> neighbours){this->neighbours = neighbours;}
	char getValue(){return value;}
	void setValue(char value){this->value = value;}
	void addNeighs(vector<Cell*> neighbours)
	{
		for(int i = 0;i<neighbours.size();i++)
		{
			this->neighbours.push_back(neighbours[i]);
		}
	}
	void add_one_Neigh(Cell* one_neigh)
	{
		this->neighbours.push_back(one_neigh);
	}

private:
	char value;
	int level;
	int state;
	vector<Cell*> neighbours;

	
};