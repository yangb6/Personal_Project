//
//  pokeman.cpp
//  
//
//  Created by Bing Yang on 12/11/15.
//
//

#include <stdio.h>
#include "pokemon.h"
using namespace std;
Pokemon::Pokemon(const map<string,vector<string> >&facts)
{
    map<string, vector<string> >::const_iterator itr;
    itr = facts.find("id");
    if(itr != facts.end())
    {
        id = itr->second[0];
    }
    itr = facts.find("label");
    if(itr != facts.end())
    {
        label = itr->second[0];
    }
    itr = facts.find("species");
    if(itr != facts.end())
    {
        species = itr->second[0];
    }
    itr = facts.find("types");
    if(itr != facts.end())
    {
        types = itr->second;
    }
    itr = facts.find("abilities");
    if(itr != facts.end())
    {
        abilities = itr->second;
    }
    itr = facts.find("genderThreshold");
    if(itr != facts.end())
    {
        genderThreshold = itr->second[0];
    }
    itr = facts.find("catchRate");
    if(itr != facts.end())
    {
        catchRate =itr->second[0];
    }
    itr = facts.find("eggGroups");
    if(itr != facts.end())
    {
        eggGroups = itr->second;
    }
    itr = facts.find("hatchCounter");
    if(itr!= facts.end())
    {
        hatchCounter = itr->second[0];
    }
    itr = facts.find("height");
    if(itr != facts.end())
    {
        height = itr->second[0];
    }
    itr = facts.find("weight");
    if(itr != facts.end())
    {
        weight = itr->second[0];
    }
    itr = facts.find("baseExpYield");
    if(itr != facts.end())
    {
        baseExpYield = itr->second[0];
    }
    itr = facts.find("baseFriendship");
    if(itr != facts.end())
    {
        baseFriendship = itr->second[0];
    }
    itr = facts.find("expGroup");
    if(itr != facts.end())
    {
        expGroup = itr->second[0];
    }
    itr = facts.find("evYield");
    if(itr != facts.end())
    {
        evYield = itr->second;
    }
    itr = facts.find("bodyStyle");
    if(itr != facts.end())
    {
        bodyStyle = itr->second[0];
    }
    itr = facts.find("color");
    if(itr != facts.end())
    {
        color = itr->second[0];
    }
    itr = facts.find("baseStats");
    if(itr != facts.end())
    {
        baseStats = itr->second;
    }
    
}

//Constructor for EggGroup
//===================================================================================================

Water1::Water1(const map<string,vector<string> >&facts):Pokemon(facts)
    {
        map<string,vector<string> >::const_iterator itr = facts.find("eggGroups");
        bool has_find = false;
        for(int i = 0; i < itr->second.size(); i++)
        {
            if(itr->second[i] == "Water1")
            {
                has_find = true;
            }
        }
        if(!has_find)
            throw 0;
    }




Grass::Grass(const map<string,vector<string> >&facts):Pokemon(facts)
    {
        map<string,vector<string> >::const_iterator itr = facts.find("eggGroups");
        bool has_find = false;
        for(int i = 0; i < itr->second.size(); i++)
        {
            if(itr->second[i] == "Grass")
            {
                has_find = true;
            }
        }
        if(!has_find)
            throw 0;
    }



Monster::Monster(const map<string,vector<string> >&facts):Pokemon(facts)
    {
        map<string,vector<string> >::const_iterator itr = facts.find("eggGroups");
        bool has_find = false;
        for(int i = 0; i < itr->second.size(); i++)
        {
            if(itr->second[i] == "Monster")
            {
                has_find = true;
            }
        }
        if(!has_find)
            throw 0;
    }



Field::Field(const map<string,vector<string> >&facts):Pokemon(facts)
    {
        map<string,vector<string> >::const_iterator itr = facts.find("eggGroups");
        bool has_find = false;
        for(int i = 0; i < itr->second.size(); i++)
        {
            if(itr->second[i] == "Field")
            {
                has_find = true;
            }
        }
        if(!has_find)
            throw 0;
    }



Flying::Flying(const map<string,vector<string> >&facts):Pokemon(facts)
    {
        map<string,vector<string> >::const_iterator itr = facts.find("eggGroups");
        bool has_find = false;
        for(int i = 0; i < itr->second.size(); i++)
        {
            if(itr->second[i] == "Flying")
            {
                has_find = true;
            }
        }
        if(!has_find)
            throw 0;
    }


//===================================================================================================
//===================================================================================================
//MY specific class constructor

Lotad::Lotad(const map<string,vector<string> >&facts):
    Pokemon(facts),Water1(facts),Grass(facts)
{
    map<string,vector<string> >::const_iterator itr = facts.find("baseStats");
    bool has_find = false;
    if (itr->second[0] == "40" ||itr->second[0] == "60"|| itr->second[0] == "80" )
    {
        has_find = true;
    }
    if(!has_find)
        throw 0;
    
}



Lombre::Lombre(const map<string,vector<string> >&facts):
    Pokemon(facts),Lotad(facts)
{
    map<string,vector<string> >::const_iterator itr = facts.find("baseStats");
    bool has_find = false;
    if (itr->second[0] == "60" ||itr->second[0] == "80" )
    {
        has_find = true;
    }
    if(!has_find)
        throw 0;
}



Ludicolo::Ludicolo(const map<string,vector<string> >&facts):
    Pokemon(facts),Lombre(facts)
{
    map<string,vector<string> >::const_iterator itr = facts.find("baseStats");
    bool has_find = false;
    if (itr->second[0] == "80" )
    {
        has_find = true;
    }
    if(!has_find)
        throw 0;
}





Cranidos::Cranidos(const map<string,vector<string> >&facts):
    Pokemon(facts),Monster(facts)
{
    map<string,vector<string> >::const_iterator itr = facts.find("baseStats");
    bool has_find = false;
    if (itr->second[0] == "67" || itr->second[0] == "97" )
    {
        has_find = true;
    }
    if(!has_find)
        throw 0;
}



Rampardos::Rampardos(const map<string,vector<string> >&facts):
    Pokemon(facts),Cranidos(facts)
{
    map<string,vector<string> >::const_iterator itr = facts.find("baseStats");
    bool has_find = false;
    if (itr->second[0] == "97" )
    {
        has_find = true;
    }
    if(!has_find)
        throw 0;
}



Mareep::Mareep(const map<string,vector<string> >&facts):
    Pokemon(facts),Monster(facts),Field(facts)
{
    map<string,vector<string> >::const_iterator itr = facts.find("baseStats");
    bool has_find = false;
    if (itr->second[0] == "55"  || (itr->second[0] == "70" && itr->second[1] == "55" && itr->second[2] == "55")
        || itr->second[0] == "90")
    {
        has_find = true;
    }
    if(!has_find)
        throw 0;
}



Flaaffy::Flaaffy(const map<string,vector<string> >&facts):
    Pokemon(facts),Mareep(facts)
{
    map<string,vector<string> >::const_iterator itr = facts.find("baseStats");
    bool has_find = false;
    if ((itr->second[0] == "70" && itr->second[1] == "55" && itr->second[2] == "55") || itr->second[0] == "90")
    {
        has_find =true;
    }
    if(!has_find)
        throw 0;
}



Ampharos::Ampharos(const map<string,vector<string> >&facts):
    Pokemon(facts),Flaaffy(facts)
{
    map<string,vector<string> >::const_iterator itr = facts.find("baseStats");
    bool has_find = false;
    if (itr->second[0] == "90" )
    {
        has_find = true;
    }
    if(!has_find)
        throw 0;
}



Vullaby::Vullaby(const map<string,vector<string> >&facts):
    Flying(facts)
{
    map<string,vector<string> >::const_iterator itr = facts.find("baseStats");
    bool has_find = false;
    if ((itr->second[0] == "70" && itr->second[1] == "55" && itr->second[2] == "75")
        || itr->second[0] == "110")
    {
        has_find = true;
    }
    if(!has_find)
        throw 0;
}



Mandibuzz::Mandibuzz(const map<string,vector<string> >&facts):
    Vullaby(facts)
{
    map<string,vector<string> >::const_iterator itr = facts.find("baseStats");
    bool has_find = false;
    if (itr->second[0] == "110" )
    {
        has_find = true;
    }
    if(!has_find)
        throw 0;
}
//===================================================================================================





bool Pokemon::SharesEggGroup(Pokemon * a)
{
    bool has_find = false;
    for(int i = 0; i<eggGroups.size();i++)
    {
        for(int j =0; j<a->eggGroups.size();j++)
        {
            if(eggGroups[i] == a->eggGroups[j])
            {
                has_find = true;
            }
        }
    }
    return has_find;
}
;
