//
//  Board.h
//  
//
//  Created by Bing Yang on 10/27/15.
//
//

#ifndef Board_h
#define Board_h

#include <stdio.h>
#include <vector>
#include "Ship.h"
using namespace std;
class Board
{
public:
    int get_row() const{return row;}
    int get_column() const{return column;}
    void set_row(int a) {row = a;}
    void set_column(int b){column = b;}
    //record how many elements in each row and column.
    vector <int> row_count;
    vector <int> column_count;
    vector <vector <bool> > elements;
    //record how many empty space left for next ship.
    vector <int> each_row_left;
    vector <int> each_column_left;
    //Function to create a board for one solution.
    void create_board(const vector<Ship> &ships );
    void initialize();
    //This function can judge if each row and column are filled with the right number of element.
    bool is_finished();
    bool operator ==(Board & board);
private:
    int row ;
    int column ;
};
#endif /* Board_h */
