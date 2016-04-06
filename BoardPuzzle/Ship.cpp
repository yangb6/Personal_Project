//
//  Ship.cpp
//  
//
//  Created by Bing Yang on 10/29/15.
//
//

#include <stdio.h>
#include "Ship.h"

void Ship::set_length()
{
    if(type == "submarine")
        length = 1;
    if(type == "destroyer")
        length = 2;
    if(type == "cruiser")
        length = 3;
    if(type == "battleship")
        length = 4;
    if(type == "carrier")
        length = 5;
    if(type == "cargo")
        length = 6;
    if(type == "tanker")
        length = 7;
};
bool is_bigger(const Ship & ship1,const Ship &ship2)
{
    return(ship1.get_length()>ship2.get_length());
}
