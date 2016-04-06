//
//  Battleship_puzzles.cpp
//  
//
//  Created by Bing Yang on 10/26/15.
//
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include "Ship.h"
#include "Board.h"
#include <sstream>
#include <algorithm>

using namespace std;
//Function for read file.
void read_file(ifstream & in_str,Board & board, vector<Ship> & ships,vector<string> &constraint)
{
    string temp;
    in_str>>temp;
    int row;
    in_str>>row;
    board.set_row(row);
    int column;
    in_str>>column;
    board.set_column(column);
    string rows;
    in_str>>rows;
    for(int i = 0 ;i<board.get_row();i++)
    {
        string each_row;
        in_str>>each_row;
        if(each_row != "?")
        {
            int a = atoi(each_row.c_str());
            board.row_count.push_back(a);
        }
        else
        {
            int a = -1;
            board.row_count.push_back(a);
        }
    }
    string cols;
    in_str>>cols;
    for(int i = 0; i<board.get_column();i++)
    {
        string each_col;
        in_str>>each_col;
        int a = 0;
        if(each_col != "?")
        {
            a = atoi(each_col.c_str());
            board.column_count.push_back(a);
        }
        else
        {
            a = -1;
            board.column_count.push_back(-1);
        }
    }
    while (in_str>>temp)
    {
        if(temp == "constraint")
        {
            for(int i = 0; i<3;i++)
            {
                string limit;
                in_str>>limit;
                constraint.push_back(limit);
            }
        }
        else
        {
            Ship one_ship;
            one_ship.set_type(temp);
            ships.push_back(one_ship);
        }
    }
}

void print_board(Board&board)
{
    for(int i = 0 ;i< board.get_row();i++)
    {
        for(int j = 0;j<board.get_column();j++)
        {
            if(board.elements[i][j])
            {
                cout<<"*";
            }
            else
            {
                cout<<"_";
            }
            
        }
        cout<<endl;
    }
    cout<<endl;
}

//Function for find solutions.
void find_all_solutions(Board &board, vector<Ship> &ships, vector< vector<Ship> > & solutions,int count_ship)
{
        //judge if the last ship has been placed on the board.
        if(count_ship == ships.size())
        {
            if(board.is_finished())
            {
                solutions.push_back(ships);
            }
        }
        else
        {
            //Traversal each row to place the board.
            for(int i=0;i < board.get_row();i++)
            {
                //Judge if it is possible to place the ship.
                if(ships[count_ship].get_length() <= board.row_count[i] && ships[count_ship].get_length()<= board.each_row_left[i])
                {
                    //From the first position of the row to try every possible position
                    for(int j=0; j<board.get_column();j++)
                    {
                        //The ship shouldn't beyond the board.
                        if(j+ships[count_ship].get_length()<= board.get_column())
                        {
                            //Use a bool variable to see if a series of the cell is null or not.
                            bool is_enough=false;
                            for(int k=j;k<j+ships[count_ship].get_length();k++)
                            {
                                if(board.elements[i][k])
                                {
                                    is_enough = true;
                                }
                            }
                            if(!is_enough)
                            {
                                //place the ship
                                
                                //Use a vector to record_change of each step.
                                vector<bool> record_change;
                                record_change.resize(2*ships[count_ship].get_length() + 6);
                                int count_change = 0;
                                for(int i=0;i<record_change.size();i++)
                                {
                                    record_change[i] = false;
                                }
                                ships[count_ship].set_start_row(i);
                                ships[count_ship].set_start_column(j);
                                ships[count_ship].set_direction("horizontal");
                                //upgrade the board
                                for(int m = j ;m < j+ships[count_ship].get_length();m++)
                                {
                                    board.elements[i][m] = true;
                                    board.each_row_left[i] = board.each_row_left[i] - 1;
                                    board.each_column_left[m] = board.each_column_left[m] -1;
                                }
                                //The row before the current row
                                if(i-1>=0)
                                {
                                    for(int m = j;m<j+ships[count_ship].get_length();m++)
                                    {
                                        if(!board.elements[i-1][m])
                                        {
                                            board.elements[i-1][m] = true;
                                            record_change[count_change] = true;
                                            board.each_row_left[i-1] = board.each_row_left[i-1] - 1;
                                            board.each_column_left[m] = board.each_column_left[m] -1;
                                        }
                                        count_change = count_change +1;
                                    }
                                    
                                    if(j-1>=0)
                                    {
                                        if(!board.elements[i-1][j-1])
                                        {
                                            board.elements[i-1][j-1] = true;
                                            record_change[count_change] = true;
                                            board.each_row_left[i-1] = board.each_row_left[i-1] - 1;
                                            board.each_column_left[j-1] = board.each_column_left[j-1] -1;
                                        }
                                        
                                        count_change = count_change + 1;
                                    }
                                    if(j+ships[count_ship].get_length() <board.get_column())
                                    {
                                        if(!board.elements[i-1][j+ships[count_ship].get_length()])
                                        {
                                            board.elements[i-1][j+ships[count_ship].get_length()] = true;
                                            record_change[count_change] = true;
                                            board.each_row_left[i-1] = board.each_row_left[i-1] - 1;
                                            board.each_column_left[j+ships[count_ship].get_length()] = board.each_column_left[j+ships[count_ship].get_length()] -1;
                                        }
                                        count_change = count_change + 1;
                                    }
                                }
                                //The row after the current row
                                if(i+1<board.get_row())
                                {
                                    for(int m = j;m<j+ships[count_ship].get_length();m++)
                                    {
                                        if(!board.elements[i+1][m])
                                        {
                                            board.elements[i+1][m] = true;
                                            record_change[count_change] = true;
                                            board.each_row_left[i+1] = board.each_row_left[i+1] - 1;
                                            board.each_column_left[m] = board.each_column_left[m] -1;
                                        }
                                        count_change = count_change + 1;
                                    }
                                    
                                    if(j-1>=0)
                                    {
                                        if(!board.elements[i+1][j-1])
                                        {
                                            board.elements[i+1][j-1] = true;
                                            record_change[count_change] = true;
                                            board.each_row_left[i+1] = board.each_row_left[i+1] - 1;
                                            board.each_column_left[j-1] = board.each_column_left[j-1] -1;
                                        }
                                        count_change = count_change + 1;
                                    }
                                    if(j+ships[count_ship].get_length() <board.get_column())
                                    {
                                        if(!board.elements[i+1][j+ships[count_ship].get_length()])
                                        {
                                            board.elements[i+1][j+ships[count_ship].get_length()] = true;
                                            record_change[count_change] = true;
                                            board.each_row_left[i+1] = board.each_row_left[i+1] - 1;
                                            board.each_column_left[j+ships[count_ship].get_length()] = board.each_column_left[j+ships[count_ship].get_length()] -1;
                                        }
                                        count_change = count_change + 1;
                                    }
                                }
                                if(j-1>=0)
                                {
                                    if(!board.elements[i][j-1])
                                    {
                                        board.elements[i][j-1] = true;
                                        record_change[count_change] = true;
                                        board.each_row_left[i] = board.each_row_left[i] - 1;
                                        board.each_column_left[j-1] = board.each_column_left[j-1] -1;
                                    }
                                    count_change= count_change+1;
                                }
                                if(j+ships[count_ship].get_length()<board.get_column())
                                {
                                    if(!board.elements[i][j+ships[count_ship].get_length()])
                                    {
                                        board.elements[i][j+ships[count_ship].get_length()] = true;
                                        record_change[count_change] = true;
                                        board.each_row_left[i] = board.each_row_left[i] - 1;
                                        board.each_column_left[j+ships[count_ship].get_length()] = board.each_column_left[j+ships[count_ship].get_length()] -1;
                                    }
                                    count_change = count_change + 1;
                                }
                                
                                board.row_count[i] = board.row_count[i]- ships[count_ship].get_length();
                                for(int m = j;m<j+ships[count_ship].get_length();m++)
                                {
                                    board.column_count[m] = board.column_count[m] - 1;
                                }
                                count_ship = count_ship + 1;
                                //recusion for next ship.
                                find_all_solutions(board, ships, solutions,count_ship);
                                
                                count_ship = count_ship - 1;
                                count_change = 0;
                                for(int m = j; m < j+ships[count_ship].get_length();m++)
                                {
                                    board.elements[i][m] = false;
                                    board.each_row_left[i] = board.each_row_left[i] + 1;
                                    board.each_column_left[m] = board.each_column_left[m] +1;
                                }
                                //We have to reset the board, since we have make some changes before, we have to clean these changes.
                                if(i-1>=0)
                                {
                                    for(int m = j;m<j+ships[count_ship].get_length();m++)
                                    {
                                        if(record_change[count_change])
                                        {
                                            board.elements[i-1][m] = false;
                                            board.each_row_left[i-1] = board.each_row_left[i-1] + 1;
                                            board.each_column_left[m] = board.each_column_left[m] +1;
                                            
                                        }
                                        count_change = count_change + 1;
                                        
                                    }
                                    
                                    if(j-1>=0)
                                    {
                                        if(record_change[count_change])
                                        {
                                            board.elements[i-1][j-1] = false;
                                            board.each_row_left[i-1] = board.each_row_left[i-1] + 1;
                                            board.each_column_left[j-1] = board.each_column_left[j-1] +1;
                                        }
                                        count_change = count_change + 1;
                                        
                                    }
                                    if(j+ships[count_ship].get_length() <board.get_column())
                                    {
                                        if(record_change[count_change])
                                        {
                                            board.elements[i-1][j+ships[count_ship].get_length()] =false;
                                            board.each_row_left[i-1] = board.each_row_left[i-1] + 1;
                                            board.each_column_left[j+ships[count_ship].get_length()] = board.each_column_left[j+ships[count_ship].get_length()] +1;
                                        }
                                        count_change = count_change + 1;
                                    }
                                }
                                if(i+1<board.get_row())
                                {
                                    for(int m = j;m<j+ships[count_ship].get_length();m++)
                                    {
                                        if(record_change[count_change])
                                        {
                                            board.elements[i+1][m] = false;
                                            board.each_row_left[i+1] = board.each_row_left[i+1] +1;
                                            board.each_column_left[m] = board.each_column_left[m] +1;
                                        }
                                        count_change = count_change + 1;
                                    }
                                    if(j-1>=0)
                                    {
                                        if(record_change[count_change])
                                        {
                                            board.elements[i+1][j-1] = false;
                                            board.each_row_left[i+1] = board.each_row_left[i+1] + 1;
                                            board.each_column_left[j-1] = board.each_column_left[j-1] +1;
                                        }
                                        count_change = count_change + 1;
                                    }
                                    if(j+ships[count_ship].get_length() <board.get_column())
                                    {
                                        if(record_change[count_change])
                                        {
                                            board.elements[i+1][j+ships[count_ship].get_length()] = false;
                                            board.each_row_left[i+1] = board.each_row_left[i+1] + 1;
                                            board.each_column_left[j+ships[count_ship].get_length()] = board.each_column_left[j+ships[count_ship].get_length()] +1;
                                        }
                                        count_change = count_change +1;
                                    }
                                }
                                if(j-1>=0)
                                {
                                    if(record_change[count_change])
                                    {
                                        board.elements[i][j-1] = false;
                                        board.each_row_left[i] = board.each_row_left[i] + 1;
                                        board.each_column_left[j-1] = board.each_column_left[j-1] +1;
                                    }
                                    count_change = count_change + 1;
                                }
                                if(j+ships[count_ship].get_length()<board.get_column())
                                {
                                    if(record_change[count_change])
                                    {
                                        board.elements[i][j+ships[count_ship].get_length()] = false;
                                        board.each_row_left[i] = board.each_row_left[i] +1;
                                        board.each_column_left[j+ships[count_ship].get_length()] = board.each_column_left[j+ships[count_ship].get_length()] +1;
                                    }
                                }
                                board.row_count[i] = board.row_count[i] + ships[count_ship].get_length();
                                for(int m = j;m<j+ships[count_ship].get_length();m++)
                                {
                                    board.column_count[m] = board.column_count[m] + 1;
                                }
                            }
                        }
                    }
                }
            }
            
            //Traversal for each column, the logic is the same as traversaling for row.
            for(int i=0;i <board.get_column();i++)
            {
                if(ships[count_ship].get_length() <= board.column_count[i] )
                {
                    for(int j=0; j<board.get_row();j++)
                    {
                        if(j+ships[count_ship].get_length()<= board.get_row())
                        {
                            bool is_enough=false;
                            for(int k=j;k<j+ships[count_ship].get_length();k++)
                            {
                                if(board.elements[k][i])
                                {
                                    is_enough = true;
                                }
                            }
                            if(!is_enough)
                            {
                                vector<bool> record_change;
                                record_change.resize(2*ships[count_ship].get_length() + 6);
                                for(int i=0;i<record_change.size();i++)
                                {
                                    record_change[i] = false;
                                }
                                int count_change = 0;
                                ships[count_ship].set_start_row(j);
                                ships[count_ship].set_start_column(i);
                                ships[count_ship].set_direction ("vertical");
                                for(int m = j;m<j+ships[count_ship].get_length();m++)
                                {
                                    board.elements[m][i] = true;
                                    board.each_column_left[i] = board.each_column_left[i] - 1;
                                    board.each_row_left[m] =board.each_row_left[m]-1;
                                }
                                if(i-1>=0)
                                {
                                    for(int m = j;m<j+ships[count_ship].get_length();m++)
                                    {
                                        if(!board.elements[m][i-1])
                                        {
                                            board.elements[m][i-1] = true;
                                            record_change[count_change] = true;
                                            board.each_column_left[i-1] = board.each_column_left[i-1] - 1;
                                            board.each_row_left[m] =board.each_row_left[m]-1;
                                        }
                                        count_change = count_change + 1;
                                    }
                                    if(j-1>=0)
                                    {
                                        if(!board.elements[j-1][i-1])
                                        {
                                            board.elements[j-1][i-1] = true;
                                            record_change[count_change] = true;
                                            board.each_row_left[j-1] = board.each_row_left[j-1] -1;
                                            board.each_column_left[i-1] = board.each_column_left[i-1]-1;
                                        }
                                        count_change = count_change + 1;
                                    }
                                    if(j+ships[count_ship].get_length() < board.get_row())
                                    {
                                        if(!board.elements[j+ships[count_ship].get_length()][i-1])
                                        {
                                            board.elements[j+ships[count_ship].get_length()][i-1] = true;
                                            record_change[count_change] = true;
                                            board.each_row_left[j+ships[count_ship].get_length()] = board.each_row_left[j+ships[count_ship].get_length()] -1;
                                            board.each_column_left[i-1] = board.each_column_left[i-1]-1;
                                        }
                                        count_change = count_change + 1;
                                    }
                                }
                                if(i+1<board.get_column())
                                {
                                    for(int m = j;m<j+ships[count_ship].get_length();m++)
                                    {
                                        if(!board.elements[m][i+1])
                                        {
                                            board.elements[m][i+1] = true;
                                            record_change[count_change] = true;
                                            board.each_column_left[i+1] = board.each_column_left[i+1] - 1;
                                            board.each_row_left[m] = board.each_row_left[m] -1;
                                        }
                                        count_change = count_change + 1;
                                    }
                                    if(j-1>=0)
                                    {
                                        if(!board.elements[j-1][i+1])
                                        {
                                            board.elements[j-1][i+1] =true;
                                            record_change[count_change] = true;
                                            board.each_row_left[j-1]=board.each_row_left[j-1]-1;
                                            board.each_column_left[i+1] = board.each_column_left[i+1] -1;
                                        }
                                        count_change = count_change + 1;
                                    }
                                    if(j+ships[count_ship].get_length() < board.get_row())
                                    {
                                        if(!board.elements[j+ships[count_ship].get_length()][i+1])
                                        {
                                            board.elements[j+ships[count_ship].get_length()][i+1] = true;
                                            record_change[count_change] = true;
                                            board.each_row_left[j+ships[count_ship].get_length()] = board.each_row_left[j+ships[count_ship].get_length()] -1;
                                            board.each_column_left[i+1] = board.each_column_left[i-1]-1;
                                        }
                                        count_change = count_change +1;
                                    }
                                }
                                if(j-1>=0)
                                {
                                    if(!board.elements[j-1][i])
                                    {
                                        board.elements[j-1][i] = true;
                                        record_change[count_change] = true;
                                        board.each_row_left[j-1] = board.each_row_left[j-1]-1;
                                        board.each_column_left[i] =  board.each_column_left[i] -1;
                                    }
                                    count_change = count_change+1;
                                }
                                if(j+ships[count_ship].get_length()<board.get_row())
                                {
                                    if(!board.elements[j+ships[count_ship].get_length()][i])
                                    {
                                        board.elements[j+ships[count_ship].get_length()][i] = true;
                                        record_change[count_change] = true;
                                        board.each_row_left[j+ships[count_ship].get_length()] = board.each_row_left[j+ships[count_ship].get_length()] -1;
                                        board.each_column_left[i] =  board.each_column_left[i] -1;
                                    }
                                    count_change = count_change +1;
                                }
                                board.column_count[i] = board.column_count[i] - ships[count_ship].get_length();
                                for(int m = j;m<j+ships[count_ship].get_length();m++)
                                {
                                    board.row_count[m] = board.row_count[m]-1;
                                }
                                count_ship = count_ship + 1;
                                
                                
                                find_all_solutions(board, ships, solutions,count_ship);
                                
                                count_change = 0;
                                count_ship = count_ship -1;
                                for(int m = j;m<j+ships[count_ship].get_length();m++)
                                {
                                    board.elements[m][i] = false;
                                    board.each_column_left[i] = board.each_column_left[i] +1;
                                    board.each_row_left[m] =board.each_row_left[m]+1;
                                }
                                if(i-1>=0)
                                {
                                    for(int m = j;m<j+ships[count_ship].get_length();m++)
                                    {
                                        if(record_change[count_change])
                                        {
                                            board.elements[m][i-1] = false;
                                            board.each_row_left[m] =board.each_row_left[m]+1;
                                            board.each_column_left[i-1] = board.each_column_left[i-1] + 1;
                                        }
                                        count_change = count_change +1;
                                    }
                                    if(j-1>=0)
                                    {
                                        if(record_change[count_change])
                                        {
                                            board.elements[j-1][i-1] = false;
                                            board.each_row_left[j-1] = board.each_row_left[j-1] +1;
                                            board.each_column_left[i-1] = board.each_column_left[i-1]+1;
                                        }
                                        count_change = count_change + 1;
                                    }
                                    if(j+ships[count_ship].get_length() < board.get_row())
                                    {
                                        if(record_change[count_change])
                                        {
                                            board.elements[j+ships[count_ship].get_length()][i-1] = false;
                                            board.each_row_left[j+ships[count_ship].get_length()] = board.each_row_left[j+ships[count_ship].get_length()] +1;
                                            board.each_column_left[i-1] = board.each_column_left[i-1]+1;
                                        }
                                        count_change = count_change + 1;
                                    }
                                }
                                if(i+1<board.get_column())
                                {
                                    for(int m = j;m<j+ships[count_ship].get_length();m++)
                                    {
                                        if(record_change[count_change])
                                        {
                                            board.elements[m][i+1] = false;
                                            board.each_column_left[i+1] = board.each_column_left[i+1] +1;
                                            board.each_row_left[m] = board.each_row_left[m] +1;
                                            
                                        }
                                        count_change = count_change + 1;
                                    }
                                    if(j-1>=0)
                                    {
                                        if(record_change[count_change])
                                        {
                                            board.elements[j-1][i+1] =false;
                                            board.each_row_left[j-1]=board.each_row_left[j-1]+1;
                                            board.each_column_left[i+1] = board.each_column_left[i+1] +1;
                                        }
                                        count_change = count_change + 1;
                                    }
                                    if(j+ships[count_ship].get_length() < board.get_row())
                                    {
                                        if(record_change[count_change])
                                        {
                                            board.elements[j+ships[count_ship].get_length()][i+1] = false;
                                            board.each_row_left[j+ships[count_ship].get_length()] = board.each_row_left[j+ships[count_ship].get_length()] +1;
                                            board.each_column_left[i+1] = board.each_column_left[i-1]+1;
                                        }
                                        count_change = count_change +1;
                                    }
                                }
                                if(j-1>=0)
                                {
                                    if(record_change[count_change])
                                    {
                                        board.elements[j-1][i] = false;
                                        board.each_row_left[j-1] = board.each_row_left[j-1]+1;
                                        board.each_column_left[i] =  board.each_column_left[i] +1;
                                    }
                                    count_change = count_change +1;
                                }
                                if(j+ships[count_ship].get_length()<board.get_row())
                                {
                                    if(record_change[count_change])
                                    {
                                        board.elements[j+ships[count_ship].get_length()][i] = false;
                                        board.each_row_left[j+ships[count_ship].get_length()] = board.each_row_left[j+ships[count_ship].get_length()] +1;
                                        board.each_column_left[i] =  board.each_column_left[i] +1;
                                    }
                                    count_change = count_change + 1;
                                }
                                board.column_count[i] = board.column_count[i] + ships[count_ship].get_length();
                                for(int m = j;m<j+ships[count_ship].get_length();m++)
                                {
                                    board.row_count[m] = board.row_count[m]+1;
                                }
                            }
                        }
                    }
                }
                
            }
        }
}
void print_new_board(vector<Ship> &ships,vector<vector<string> > &new_board,int row,int column)
{
    new_board.resize(row);
    //Initialize the board.
    for(int i = 0; i< new_board.size();i++)
    {
        new_board[i].resize(column);
    }
    for(int i=0; i<new_board.size();i++)
    {
        for(int j=0;j<new_board[i].size();j++)
        {
            new_board[i][j] = " ";
        }
    }
    for(int i = 0; i<ships.size();i++)
    {
        if(ships[i].get_type() == "submarine")
        {
            new_board[ships[i].get_start_row()][ships[i].get_start_column()] ="o";
        }
        else if(ships[i].get_type() == "destroyer")
        {
            if(ships[i].get_direction() == "horizontal")
            {
                new_board[ships[i].get_start_row()][ships[i].get_start_column()] ="<";
                new_board[ships[i].get_start_row()][ships[i].get_start_column()+1] =">";
            }
            else
            {
                new_board[ships[i].get_start_row()][ships[i].get_start_column()] ="^";
                new_board[ships[i].get_start_row()+1][ships[i].get_start_column()] ="V";
            }
        }
        else
        {
            if(ships[i].get_direction() == "horizontal")
            {
                new_board[ships[i].get_start_row()][ships[i].get_start_column()] ="<";
                new_board[ships[i].get_start_row()][ships[i].get_start_column()+ships[i].get_length()-1] =">";
                for(int j=0;j<ships[i].get_length()-2;j++)
                {
                    new_board[ships[i].get_start_row()][ships[i].get_start_column()+j+1] ="X";
                }
            }
            else
            {
                new_board[ships[i].get_start_row()][ships[i].get_start_column()] ="^";
                new_board[ships[i].get_start_row()+ships[i].get_length() - 1][ships[i].get_start_column()] ="V";
                for(int j=0;j<ships[i].get_length()-2;j++)
                {
                    new_board[ships[i].get_start_row()+1+j][ships[i].get_start_column()] ="X";
                }
            }
        }
        
    }

}

// I use a function to delete the "wrong" solutions and find the solution which meet the constraints.
bool fliter_wrong_solutions(vector<Ship> &ships,int row ,int column,vector<string> &constraints,vector<vector<string> > &new_board)
{
    //place ship on the board and to see if it meet all requirement.If it does, then it is wright, or it is wrong.
    print_new_board(ships,new_board,row,column);
    for(int i = 0; i< constraints.size();i=i+3)
    {
        int row_number = atoi(constraints[i].c_str());
        int col_number = atoi(constraints[i+1].c_str());
        if(constraints[i+2] == "_")
        {
            if(new_board[row_number][col_number] != " ")
            {
                return false;
            }
        }
        else
        {
            if(new_board[row_number][col_number] != constraints[i+2])
            {
                return false;
            }
        }
    }
    return true;

    
}

//Function to delete same solutions.
void delete_same_solutions(vector< vector<Ship> >  &solutions,int row, int column,vector<Board> &  boards)
{
    vector< vector<Ship> >::iterator it;
    it = solutions.begin();
    while (it!=solutions.end())
    {
        Board new_board;
        new_board.set_row(row);
        new_board.set_column(column);
        new_board.create_board(*it);
        vector<Board>::iterator it_boards;
        it_boards = boards.begin();
        bool is_existed =false;
        while (it_boards != boards.end() && !is_existed)
        {
            if(*it_boards == new_board)
            {
                is_existed = true;
                it = solutions.erase(it);
            }
            else
            {
                it_boards++;
            }
        }
        if(!is_existed)
        {
            boards.push_back(new_board);
            it++;
        }
    }
}

//Function to output the solutions.
void print_solutions(vector<Ship> &ships,int row,int column,vector<int> &each_row,vector<int>&each_col,vector<vector<string> > & one_board)
{
    row = row+2;
    column = column +2;
    for(int i =0; i<ships.size();i++)
    {
        cout<<setw(15)<<left<<ships[i].get_type();
        cout<<setw(3)<<left<<ships[i].get_start_row();
        cout<<setw(3)<<left<<ships[i].get_start_column();
        if(ships[i].get_type() != "submarine")
        {
            cout<<setw(10)<<left<<ships[i].get_direction();
        }
        cout<<endl;
        //place the ship on the diagram.
    }
    
    for(int i =0; i<row;i++)
    {
        for(int j=0;j<column;j++)
        {
            if(i == 0 || i == row-1)
            {
                cout<<"+";
            }
            else if(j == 0 || j == column-1)
            {
                cout<<"|";
                if(j == column - 1)
                {
                    cout<<each_row[i-1];
                }
            }
            else
            {
                cout<<one_board[i-1][j-1];
            }
        }
        cout<<endl;
        
    }
    cout<<" ";
    for(int i=0;i<each_col.size();i++)
    {
        cout<<each_col[i];
    }
    cout<<endl;
}

int main(int argc, char*argv[])
{
    ifstream in_str(argv[1]);
    Board board;
    vector <Ship> ships;
    vector <string> constraint;
    read_file(in_str,board,ships,constraint);
    int row = board.get_row();
    int column = board.get_column();
    for(int i = 0 ;i<ships.size();i++)
    {
        ships[i].set_length();
    }
    //Sort the ship, so the largest ship is in the front.
    sort(ships.begin(),ships.end(),is_bigger);
    board.initialize();
    //Record the initial data.
    vector<int> each_row = board.row_count;
    vector<int> each_col = board.column_count;
    vector< vector<Ship> >  solutions;
    int count_ship = 0;
    find_all_solutions(board, ships, solutions,count_ship);
    vector <Board> boards;
    //delete same solutions.
     delete_same_solutions(solutions,board.get_row(),board.get_column(),boards);
    //Fliter the wrong solutions and find the solution meet the constraints.
    vector< vector<vector<string> > > all_boards;
    vector< vector<Ship> >::iterator it_solution;
    it_solution = solutions.begin();
    while(it_solution != solutions.end() )
    {
        vector<vector <string> > one_board;
        if(!fliter_wrong_solutions(*it_solution,row,column,constraint,one_board))
        {
            it_solution = solutions.erase(it_solution);
        }
        else
        {
            all_boards.push_back(one_board);
            it_solution++;
        }
    }
    
    //Print all solutions
    if(argc == 3)
    {
        if(solutions.size()==0)
        {
            cout<<"No solutions"<<endl;
        }
        else
        {
            for(int i=0;i<solutions.size();i++)
            {
                cout<<"Solution:"<<endl;
                print_solutions(solutions[i],row,column,each_row,each_col,all_boards[i]);
                cout<<endl;
            }
            cout<<"Found  "<<solutions.size()<<"  solution(s)"<<endl;
        }
    }
    //Pring one solution.
    else if(argc ==2)
    {
        if(solutions.size()==0)
        {
            cout<<"No solutions"<<endl;
        }
        else
        {
            cout<<"Solution:"<<endl;
            print_solutions(solutions[0],row,column,each_row,each_col,all_boards[0]);
        }
    }
    else
    {
        cout<<"Wrong Input!"<<endl;
    }
    
    return 0;
}