//
//  Ship.h
//  
//
//  Created by Bing Yang on 10/27/15.
//
//

#ifndef Ship_h
#define Ship_h

#include <stdio.h>
#include <string>
using namespace std;
class Ship
{
public:
    int get_length() const{return length;}
    int get_start_row() const {return start_row;}
    int get_start_column() const {return start_column;}
    string get_direction() const {return direction;}
    string get_type() const{return type;}
    void set_start_row(int a){start_row = a;}
    void set_start_column(int a ){start_column = a;}
    void set_direction(const string & b){ direction = b;}
    void set_type(const string & b){type = b;}
    void set_length();
private:
    //Position of the ship
    int start_row;
    int start_column;
    //status of the ship
    string direction;
    //different types of ship.
    string type;
    int length;
};

bool is_bigger(const Ship & ship1,const Ship &ship2);
#endif /* Ship_h */
