//
//  Query.cpp
//  
//
//  Created by Bing Yang on 11/3/15.
//
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include "Query.h"
using namespace std;

void Query::set_seed(unsigned int kmer)
{
    seed = query_string.substr(0,kmer);
}

void Query::add_matchPosition(unsigned int a)
{
    match_positions.push_back(a);
}

void Query::add_mismatchNumber(unsigned int a)
{
    mismatch_number.push_back(a);
}

void Query::add_matchQuery(const string&s1)
{
    match_queries.push_back(s1);
}
void Query::add_matchqueryNumber()
{
    match_queriesNumber = match_queriesNumber +1;
};