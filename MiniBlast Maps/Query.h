//
//  Query.h
//  
//
//  Created by Bing Yang on 11/3/15.
//
//
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#ifndef Query_h
#define Query_h
using namespace std;
//use a class to record the information about one query.
class Query
{
public:
    Query():match_queriesNumber(0){}
    //Realted functions to set or get the private variables.
    void set_mismatch(unsigned int a){mismatches = a;}
    unsigned int get_mismatch() const {return mismatches;}
    void set_seed(unsigned int kmer);
    const string &get_seed() const {return seed;}
    void set_query(const string & s1){query_string = s1;}
    const string &get_query() const {return query_string;}
    void add_matchPosition(unsigned int a);
    vector<unsigned int> get_matchPositions() const{return match_positions;}
    void add_mismatchNumber(unsigned int a);
    vector<unsigned int> get_mismatchNumber() const {return mismatch_number;}
    void add_matchQuery(const string &s1);
    vector<string> get_matchQueries() const {return match_queries;}
    void add_matchqueryNumber();
    unsigned int get_matchqueryNumber() const {return match_queriesNumber;}
    
private:
    unsigned int mismatches;
    //Record the query position
    vector <unsigned int> match_positions;
    //Record the mismatch_number
    vector <unsigned int> mismatch_number;
    //Record the suitable match_queries
    vector <string> match_queries;
    unsigned int match_queriesNumber;
    string seed;
    string query_string;
};

#endif /* Query_h */
