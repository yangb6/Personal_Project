//
//  Board.cpp
//  
//
//  Created by Bing Yang on 10/28/15.
//
//

#include <stdio.h>
#include <vector>
#include "Board.h"
#include <string>
#include <iostream>
#include "Ship.h"
using namespace std;
void Board::initialize()
{
    for(int i = 0; i< row;i++)
    {
        vector<bool> temp;
        for(int j=0 ; j<column;j++)
        {
            temp.push_back(false);
        }
        elements.push_back(temp);
    }
    each_row_left.resize(row);
    for(int i = 0; i< row;i++)
    {
        each_row_left[i] = column;
    }
    each_column_left.resize(column);
    for(int j=0 ; j<column;j++ )
    {
        each_column_left[j] = row;
    }
}
//In order to delete same solutions, we place the ship on the board and to see if two boards are the same. If it is same, then
//the solution is the same.
void Board::create_board(const vector<Ship> &ships)
{
    this->initialize();
    for(int i = 0; i<ships.size();i++)
    {
        if(ships[i].get_direction() == "horizontal")
        {
            for(int j=0;j<ships[i].get_length();j++)
            {
                elements[ships[i].get_start_row()][ships[i].get_start_column()+j] = true;
            }
        }
        if(ships[i].get_direction() == "vertical")
        {
            for(int j=0;j<ships[i].get_length();j++)
            {
                elements[ships[i].get_start_row()+j][ships[i].get_start_column()] = true;
            }
        }
    }
}

//Function to see if two board are same.
bool Board::operator==(Board &board)
{
    if(this->elements == board.elements)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Board::is_finished()
{
    for( int i = 0 ;i< row;i++)
    {
        if(row_count[i] != 0)
        {
            return false;
        }
    }
    for(int j= 0;j<column;j++)
    {
        if(column_count[j] != 0)
        {
            return false;
        }
    }
    return true;
};

