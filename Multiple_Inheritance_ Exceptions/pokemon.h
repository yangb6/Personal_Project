//
//  Pokemon.h
//  
//
//  Created by Bing Yang on 12/11/15.
//
//


#ifndef Pokemon_h
#define Pokemon_h

#include <vector>
#include <map>
#include <string>
using namespace std;

class Pokemon
{
public:
    //Constructors to create the object.
    Pokemon(const map<string,vector<string> >&facts);
    string getLabel(){return label; }
    bool SharesEggGroup(Pokemon* a);
    virtual ~Pokemon(){}

//Member variables
protected:
    string id;
    string label;
    string species;
    vector<string> types;
    vector<string> abilities;
    string genderThreshold;
    string catchRate;
    vector<string> eggGroups;
    string hatchCounter;
    string height;
    string weight;
    string baseExpYield;
    string baseFriendship;
    string expGroup;
    vector<string> evYield;
    string bodyStyle;
    string color;
    vector<string> baseStats;
    
};
//Five EggGroup Class
class Water1:virtual public Pokemon
{
public:
    Water1(const map<string,vector<string> >&facts);
};
    
    
class Grass:virtual public Pokemon
{
public:
    Grass(const map<string,vector<string> >&facts);
};

class Monster:virtual public Pokemon
{
public:
    Monster(const map<string,vector<string> >&facts);
};

class Field:virtual public Pokemon
{
public:
    Field(const map<string,vector<string> >&facts);
};
    
class Flying:public Pokemon
{
public:
    Flying(const map<string,vector<string> >&facts);
};


//10 specificf class
class Lotad:public Water1,public Grass
{
public:
    Lotad(const map<string,vector<string> >&facts);
};

class Lombre:public Lotad
{
public:
    Lombre(const map<string,vector<string> >&facts);
};

class Ludicolo:public Lombre
{
public:
    Ludicolo(const map<string,vector<string> >&facts);
};
    
    
class Cranidos:public Monster
{
public:
    Cranidos(const map<string,vector<string> >&facts);
};

class Rampardos:public Cranidos
{
public:
    Rampardos(const map<string,vector<string> >&facts);
};

class Mareep: public Monster, public Field
{
public:
    Mareep(const map<string,vector<string> >&facts);
};

class Flaaffy:public Mareep
{
public:
    Flaaffy(const map<string,vector<string> >&facts);
};

class Ampharos:public Flaaffy
{
public:
    Ampharos(const map<string,vector<string> >&facts);
};

class Vullaby:public Flying
{
public:
    Vullaby(const map<string,vector<string> >&facts);
};
    
class Mandibuzz:public Vullaby
{
public:
    Mandibuzz(const map<string,vector<string> >&facts);
};
    
    
//Empty class
class Amorphous
{
    
};
    
class Bug
{
    
};
    
class Dragon
{
   
};
    
class Fairy
{
   
};
        
class HumanLike
{
   
};
        
class Mineral
{
    
};
            
class Water2
{
    
};
            
class Water3
{
    
};
                
class Ditto
{
    
};
                
class Undiscovered
{
    
};
                    
    

#endif /* Pokemon_h */
