//
//  main.cpp
//  
//
//  Created by Bing Yang on 11/3/15.
//
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Query.h"
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <map>

using namespace std;
//==================================================================================================================
//Function to read the inputFile.
void readFile(vector<char> &genome,vector<Query> & queries,unsigned int &kmer,string &method)
{
    string temp;
    while(cin>>temp && temp != "quit")
    {
        if(temp == "genome")
        {
            //Read the genome file.
            string fileName;
            cin>>fileName;
            const char *p = fileName.c_str();
            ifstream in_str(p);
            char single_genome;
            while(in_str>>single_genome)
            {
                genome.push_back(single_genome);
            }
        }
        else if(temp == "kmer")
        {
            //Read kmer
            cin>>kmer;
        }
        else if(temp == "query")
        {
            //Read one query
            Query one_query;
            unsigned int mismatches;
            cin>>mismatches;
            one_query.set_mismatch(mismatches);
            string query_string;
            cin>>query_string;
            one_query.set_query(query_string);
            one_query.set_seed( kmer);
            queries.push_back(one_query);
        }
        else
        {
            method = temp;
        }
    }
}
//==================================================================================================================
//This part of code uses the map as the k_mer database.(Just as requirement in the homework.)



//Iterating through the genome sequence to generate the map.
void generate_map(const vector<char> &genome,map<string, vector<unsigned int> >&k_mers,unsigned int kmer)
{
    for(unsigned int i=0;i+kmer-1<genome.size();i++)
    {
        char temp[kmer+1];
        temp[kmer] = '\0';
        for(unsigned int j=0;j<kmer;j++)
        {
            temp[j] = genome[i+j];
        }
        string one_kmers(temp);
        k_mers[one_kmers].push_back(i);
    }
}
//Function to find the difference between two string(two string have the same length.)
bool find_difference(const string &s1, const string&s2,unsigned int mismatches,unsigned int &mismatchNumber,unsigned int kmer)
{
    unsigned int count_difference = 0;
    for(unsigned int i=kmer;i<s1.size();i++)
    {
        if(s1.substr(i,1) != s2.substr(i,1))
        {
            count_difference++;
        }
    }
    if(count_difference>mismatches)
    {
        return false;
    }
    else
    {
        mismatchNumber = count_difference;
        return true;
    }
}
//Function to find the query position in the genome sequence.
void find_position(vector<Query> &queries,const vector<char> &genome, const map<string,vector<unsigned int> >&k_mers,unsigned int kmer)
{
    //Traversal all query in the vector.
    for(unsigned int i = 0;i<queries.size();i++)
    {
        map<string,vector<unsigned int> >::const_iterator it;
        it = k_mers.find(queries[i].get_seed());
        //The seed can be matched.
        if(it != k_mers.end())
        {
            unsigned int count = queries[i].get_query().size();
            char temp[count+1];
            temp[count] = '\0';
            for(unsigned int j =0; j< it->second.size();j++)
            {
                if(it->second[j]+count-1<genome.size())
                {
                    for(unsigned int k=0;k<count;k++)
                    {
                        temp[k] = genome[it->second[j]+k];
                    }
                    string matchQuery(temp);
                    unsigned int mismatchNumber = 0;
                    if(find_difference(matchQuery,queries[i].get_query(),queries[i].get_mismatch(),mismatchNumber,kmer))
                    {
                        queries[i].add_matchPosition(it->second[j]);
                        queries[i].add_mismatchNumber(mismatchNumber);
                        queries[i].add_matchQuery(matchQuery);
                        queries[i].add_matchqueryNumber();
                    }
                }
            }
        }
    }
}
//===================================================================================================================
//This part use vector as the database.

void generate_vector(const vector<char> &genome,vector<string>&k_mers,vector<vector<unsigned int> >&k_mers_positions,unsigned int kmer)
{
    for(unsigned int i =0;i+kmer-1<genome.size();i++)
    {
        char temp[kmer+1];
        temp[kmer] = '\0';
        for(unsigned int j=0;j<kmer;j++)
        {
            temp[j] = genome[i+j];
        }
        string one_kmers(temp);
        //Use a bool variable to see if this k_mer existed or not.
        bool is_existed =false;
        unsigned int k=0;
        while (k<k_mers.size()&&!is_existed)
        {
            if(k_mers[k] == one_kmers)
            {
                k_mers_positions[k].push_back(i);
                is_existed = true;
            }
            else
            {
                k++;
            }
        }
        //if this k_mer do not existed before, add it to the k_mers vector.
        if(!is_existed)
        {
            k_mers.push_back(one_kmers);
            vector<unsigned int> new_position;
            new_position.push_back(i);
            k_mers_positions.push_back(new_position);
        }
    }
}

void find_position(vector<Query> &queries,const vector<char> &genome, vector<string>&k_mers,vector<vector<unsigned int> >&k_mers_positions ,unsigned int kmer)
{
    for(unsigned int i = 0;i<queries.size();i++)
    {
        //Traversal the k_mers vector to find if any k_mer match the seed.
        bool has_found = false;
        unsigned int k=0;
        while(k<k_mers.size()&&!has_found)
        {
            if(k_mers[k] == queries[i].get_seed())
            {
                has_found = true;
                unsigned int count = queries[i].get_query().size();
                char temp[count+1];
                temp[count] = '\0';
                for(unsigned int j=0; j<k_mers_positions[k].size();j++)
                {
                    if(k_mers_positions[k][j]+count-1<genome.size())
                    {
                        for(unsigned int l=0;l<count;l++)
                        {
                            temp[l] = genome[k_mers_positions[k][j] + l];
                        }
                        string matchQuery(temp);
                        unsigned int mismatchNumber = 0;
                        if(find_difference(matchQuery,queries[i].get_query(),queries[i].get_mismatch(),mismatchNumber,kmer))
                        {
                            queries[i].add_matchPosition(k_mers_positions[k][j]);
                            queries[i].add_mismatchNumber(mismatchNumber);
                            queries[i].add_matchQuery(matchQuery);
                            queries[i].add_matchqueryNumber();
                        }
                    }
                }
            }
            else
            {
                k++;
            }
        }
    }
}

//==================================================================================================================
//Function to print the match queries.
void print_queries(const vector<Query> & queries)
{
    for(unsigned int i=0;i<queries.size();i++)
    {
        if(queries[i].get_matchqueryNumber() != 0)
        {
            cout<<"Query: "<<queries[i].get_query()<<endl;
            for(unsigned int j = 0; j<queries[i].get_matchqueryNumber();j++)
            {
                cout<<queries[i].get_matchPositions()[j]<<" ";
                cout<<queries[i].get_mismatchNumber()[j]<<" ";
                cout<<queries[i].get_matchQueries()[j]<<endl;
            }
        }
        else
        {
            cout<<"Query: "<<queries[i].get_query()<<endl;
            cout<<"No Match"<<endl;
        }
    }
}
//==================================================================================================================
int main(int argc,char* argv[])
{
    string method ;
    vector<char> genome;
    vector<Query> queries;
    unsigned int kmer = 0;
    //read the input file and get the data.
    readFile(genome,queries,kmer,method);
    if(method == "")
    {
        map<string,vector<unsigned int> > k_mers;
        //Generate map
        generate_map(genome,k_mers,kmer);
        //Find the query position and upgrade the information of queries.
        find_position(queries,genome,k_mers,kmer);
        //output the queries.
        print_queries(queries);
    }
    else if(method == "new_method")
    {
        vector<string> k_mers;
        vector <vector<unsigned int> > k_mers_positions;
        generate_vector(genome,k_mers,k_mers_positions,kmer);
        find_position(queries,genome,k_mers,k_mers_positions,kmer);
        print_queries(queries);
    }
}
