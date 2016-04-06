// CSCI 1200 Data Structures
// Homework 5: Multi-Linked Lists


// NOTE: You should not need to make any changes to this file, except
// to add your own test cases at the bottom of the file where
// indicated.


#include <iostream>
#include <cmath>
#include <string>
#include <list>
#include <vector>
#include <cassert>
#include <cstdlib>

#include "multi_linked_list.h"
using namespace std;
void ProvidedTests();
void StudentTests();


// ================================================================================
// A simple function to test if two STL lists contain the "same" elements
// returns true if it contains the same number of elements in the same order
// otherwise returns false
template <class T> bool same(const std::list<T> &a, const std::list<T> &b) {
  if (a.size() != b.size()) return false;
  typename std::list<T>::const_iterator a_itr = a.begin();
  typename std::list<T>::const_iterator b_itr = b.begin();
  while (a_itr != a.end()) {
    if (*a_itr != *b_itr) return false;
    a_itr++;
    b_itr++;
  }
  return true;
}



// ================================================================================
// This program stress tests the templated MultiLL container class


int main() {
  ProvidedTests();
  StudentTests();
}


// ================================================================================
// ================================================================================

void ProvidedTests() {

  std::cout << "Begin ProvidedTests..." << std::endl;

  // The test data (stored in STL lists)
  std::list<std::string> songs;
  songs.push_back("hound dog");
  songs.push_back("poker face");
  songs.push_back("brown eyed girl");
  songs.push_back("let it be");
  songs.push_back("walk like an egyptian");
  songs.push_back("man in the mirror");
  songs.push_back("stairway to heaven");
  songs.push_back("dancing in the street");
  songs.push_back("every breath you take");
  songs.push_back("hotel california");
  // the same data, sorted!
  std::list<std::string> sorted_songs(songs);
  sorted_songs.sort();


  // create an empty multi-linked list and fill it with the test data
  MultiLL<std::string> my_list;
  for (std::list<std::string>::iterator itr = songs.begin(); itr != songs.end(); itr++) {
    my_list.add(*itr);
  }
  assert (songs.size() == my_list.size());



  // -------------------
  // iterator tests

  // test the chronological iterator (forwards)
  std::cout << "chronological order" << std::endl;
  std::list<std::string> chrono_order;
  MultiLL<std::string>::iterator itr = my_list.begin_chronological();
  while (itr != my_list.end_chronological()) {
    std::cout << "  " << *itr << std::endl;
    chrono_order.push_back(*itr);
    itr++;
  }
  std::cout << std::endl;
  assert (same(songs,chrono_order));


  // test the sorted order iterator (forwards)
  std::cout << "sorted order" << std::endl;
  std::list<std::string> sorted_order;
  itr = my_list.begin_sorted();
  while (itr != my_list.end_sorted()) {
    std::cout << "  " << *itr << std::endl;
    sorted_order.push_back(*itr);
    itr++;
  }
  std::cout << std::endl;
  assert (same(sorted_songs,sorted_order));


  // test the random order iterator
  std::cout << "random order" << std::endl;
  std::list<std::string> random_order;
  itr = my_list.begin_random();
  for (unsigned int i = 0; i < my_list.size(); i++,itr++) {
    std::cout << "  " << *itr << std::endl;
    random_order.push_back(*itr);
  }
  std::cout << std::endl;
  // loop through the elements a second time (the order should be the same!)
  std::list<std::string>::iterator itr2 = random_order.begin();
  for (unsigned int i = 0; i < my_list.size(); i++,itr++,itr2++) {
    // verify that the elements repeat the order
    assert (*itr == *itr2);
  }
  std::list<std::string> random_order_check(random_order);
  random_order_check.sort();
  // verify that all of the elements appeared in the initial loop
  assert (same(sorted_songs,random_order_check));



  // test the re-randomization by creating a new random iterator
  std::cout << "random order 2" << std::endl;
  std::list<std::string> random_order2;
  itr = my_list.begin_random();
  for (unsigned int i = 0; i < my_list.size(); i++,itr++) {
    std::cout << "  " << *itr << std::endl;
    random_order2.push_back(*itr);
  }
  std::cout << std::endl;
  // with over 3 million different possible permutations of 10
  // elements, it is highly unlikely they will be the same!
  assert (!same(random_order,random_order2));


  
  // -------------------
  // erase tests

  // erase the first element inserted
  itr = my_list.begin_chronological();
  assert (*itr == "hound dog");
  itr = my_list.erase(itr);
  assert (*itr == "poker face");
  assert (my_list.size() == 9);
  std::cout << "erased: hound dog" << std::endl;

 // erase the second to last element in sorted order
  itr = my_list.begin_sorted();
  for (int i = 0; i < 7; i++) { itr++; }
  assert (*itr == "stairway to heaven");
  itr = my_list.erase(itr);
  assert (*itr == "walk like an egyptian");
  assert (my_list.size() == 8);  
  std::cout << "erased: stairway to heaven" << std::endl;

  // erase the third element in the random order
  itr = my_list.begin_random();
  itr++;
  itr++;
  std::string tmp = *itr;
  // note that the return value of erase with a random iterator is undefined
  my_list.erase(itr);
  std::cout << "erased: " << tmp << std::endl;
  assert (my_list.size() == 7);
  assert (!my_list.empty());

  my_list.clear();
  assert (my_list.empty());
  assert (my_list.size() == 0);
  std::cout << "cleared the whole list!" << std::endl << std::endl;

  std::cout << "Finished ProvidedTests." << std::endl;
}

// ================================================================================
// ================================================================================

void StudentTests() {

  std::cout << "Begin StudentTests..." << std::endl;

  // ---------------------------
  // ADD YOUR OWN TEST CASES BELOW
  
  // be sure to test:
  //   copy constructor
  //   assignment operator
  //   destructor
  //   all corner cases of erase
  //   decrement operator for the chronological & sorted iterators
  //   pre vs. post increment & decrement operations for iterators
  //   MultiLL containing types other than std::string
  //   anything else that is necessary
//------------------------------------------------------------
//copy constructor
    cout<<endl;
    cout<<"Test for copy constructor:"<<endl;
    std::list<std::string> songs;
    songs.push_back("hound dog");
    songs.push_back("poker face");
    songs.push_back("brown eyed girl");
    songs.push_back("let it be");
    songs.push_back("walk like an egyptian");
    songs.push_back("man in the mirror");
    songs.push_back("stairway to heaven");
    songs.push_back("dancing in the street");
    songs.push_back("every breath you take");
    songs.push_back("hotel california");
    
    MultiLL<std::string> my_list;
    for (std::list<std::string>::iterator itr = songs.begin(); itr != songs.end(); itr++) {
        my_list.add(*itr);
    }
    cout<<"Copy my_list to my_second_list."<<endl;
    MultiLL<std::string> my_second_list(my_list);
    std::cout << "Songs in my_second_list" << std::endl;
    std::list<std::string> chrono_order;
    MultiLL<std::string>::iterator itr = my_second_list.begin_chronological();
    while (itr != my_second_list.end_chronological()) {
        std::cout << "  " << *itr << std::endl;
        chrono_order.push_back(*itr);
        itr++;
    }
    std::cout << std::endl;
    assert (same(songs,chrono_order));
    
//-------------------------------------------------------------
//assignment operator
    cout<<"Test for assignment operator, two iterators are:"<<endl;
    cout<<"ite_chrono_1 = my_list.begin_chronological();"<<endl;
    cout<<"ite_sort_1 = my_list.begin_sorted()"<<endl;
    MultiLL<string>:: iterator ite_chrono_1 = my_list.begin_chronological();
    MultiLL<string>:: iterator ite_sort_1 = my_list.begin_sorted();
    if(ite_chrono_1 != ite_sort_1)
    {
        cout<<"After use != operator,we know that "<<"ite_chrono_1 is different with ite_sort_1."<<endl;
    }
    ite_sort_1 = ite_chrono_1;
    if(ite_sort_1 == ite_chrono_1)
    {
        cout<<"After operation "<<"=,"<<"ite_sort_1 is equal to ite_chrono_1."<<endl;
    }
    
    //assignment operator for MultiLL;
    MultiLL<std::string> my_third_list;
    my_third_list = my_list;
    cout<<"Using = for my_third_list to copy my_list"<<endl;
    cout<<"Node in my_third_list:"<<endl;
    MultiLL<std::string>::iterator ite_third_list = my_third_list.begin_chronological();
    while(ite_third_list != my_third_list.end_chronological())
    {
        cout<<*ite_third_list<<endl;
        ite_third_list++;
    }
    cout<<endl;
//-------------------------------------------------------------
//Destructor
    cout<<"Test for destructor: use clear function to clear a list."<<endl;
    cout<<"Originally, the size of my_second_list: "<<my_second_list.size()<<endl;
    my_second_list.clear();
    cout<<"After using clear function, the size of my_second_list: "<<my_second_list.size()<<endl;
    cout<<"Using an iterator ite_chrono_2 to see if there was any node in the list:"<<endl;
    MultiLL<string>::iterator ite_chrono_2 = my_second_list.begin_chronological();
    if(ite_chrono_2 == my_second_list.end_chronological())
    {
        cout<<"The ite_chrono_2 is NULL"<<endl;
    }
    cout<<endl;
//-------------------------------------------------------------
//all corner cases of erase
    cout<<"Test for corner cases of erase."<<endl;
    //1.We use an iterator which type is not random,chrono and sorted.
    cout<<"--1.Wrong type iterator.--"<<endl;
    MultiLL<string>::iterator test_ite;
    my_list.erase(test_ite);
    
    cout<<"--2.The list is NULL.--"<<endl;
    MultiLL<std::string> one_node_list;
    MultiLL<string>::iterator one_node_ite;
    one_node_ite = one_node_list.begin_chronological();
    one_node_list.erase(one_node_ite);
    
    cout<<"--3.The list have only one Node.--"<<endl;
    one_node_list.add("I have one node.");
    one_node_ite = one_node_list.begin_chronological();
    cout<<"size of one_node_list: "<<one_node_list.size()<<"   Node value:"<<*one_node_ite<<endl;
    cout<<"Erase this node. "<<endl;
    one_node_list.erase(one_node_ite);
    cout<<"size of one_node_list: "<<one_node_list.size()<<endl;
    if(one_node_ite == one_node_list.end_chronological() && one_node_ite == one_node_list.end_sorted())
    {
        cout<<"The node has been erased."<<endl;
    }
    
    cout<<endl;
//-------------------------------------------------------------
//decrement operator for the chronological & sorted iterators
    cout<<"Test for decrement operator for the chronological & sorted iterators"<<endl;
    cout<<"Using increment to find the 4th Node in the sorted list and chronological:"<<endl;
    MultiLL<string>:: iterator decre_ite_chrono = my_list.begin_chronological();
    MultiLL<string>:: iterator decre_ite_sort = my_list.begin_sorted();
    cout<<"--At first:--"<<endl;
    cout<<"decre_ite_chrono value: "<<*decre_ite_chrono<<",  decre_ite_sort value: "<<*decre_ite_sort<<endl;
    cout<<endl;
    cout<<"--First time increment.--"<<endl;
    decre_ite_chrono++;decre_ite_sort++;
    cout<<"decre_ite_chrono value: "<<*decre_ite_chrono<<",  decre_ite_sort value: "<<*decre_ite_sort<<endl;
    cout<<endl;
    cout<<"--Second time increment.--"<<endl;
    decre_ite_chrono++;decre_ite_sort++;
    cout<<"decre_ite_chrono value: "<<*decre_ite_chrono<<",  decre_ite_sort value: "<<*decre_ite_sort<<endl;
    cout<<endl;
    cout<<"--Third time increment.--"<<endl;
    decre_ite_chrono++;decre_ite_sort++;
    cout<<"decre_ite_chrono value: "<<*decre_ite_chrono<<",  decre_ite_sort value: "<<*decre_ite_sort<<endl;
    cout<<endl;
    cout<<"--First time decrement.--"<<endl;
    decre_ite_chrono--;decre_ite_sort--;
    cout<<"decre_ite_chrono value: "<<*decre_ite_chrono<<",  decre_ite_sort value: "<<*decre_ite_sort<<endl;
    cout<<endl;
    cout<<"--Second time decrement.--"<<endl;
    decre_ite_chrono--;decre_ite_sort--;
    cout<<"decre_ite_chrono value: "<<*decre_ite_chrono<<",  decre_ite_sort value: "<<*decre_ite_sort<<endl;
    cout<<endl;
    cout<<"--Third time decrement.--"<<endl;
    decre_ite_chrono--;decre_ite_sort--;
    cout<<"decre_ite_chrono value: "<<*decre_ite_chrono<<",  decre_ite_sort value: "<<*decre_ite_sort<<endl;
    cout<<endl;
    
//-------------------------------------------------------------
//   pre vs. post increment & decrement operations for iterators
    cout<<"Test for pre vs. post increment & decrement operations for iterators."<<endl;
    cout<<"Using two iterator: incre_ite_1,incre_ite_2 to see the difference."<<endl;
    MultiLL<string>::iterator incre_ite_1 = my_list.begin_chronological();
    MultiLL<string>::iterator incre_ite_2 = my_list.begin_chronological();
    cout<<"--At first--:"<<endl;
    cout<<"iterator incre_ite_1 value: "<<*incre_ite_1<<", iterator incre_ite_2: "<<*incre_ite_2<<endl;
    cout<<"--After the first time operation.--"<<endl;
    incre_ite_1 = incre_ite_2++;
    cout<<"iterator incre_ite_1 value: "<<*incre_ite_1<<", iterator incre_ite_2: "<<*incre_ite_2<<endl;
    cout<<"--After second time operation.--"<<endl;
    incre_ite_1 = ++incre_ite_2;
    cout<<"iterator incre_ite_1 value: "<<*incre_ite_1<<", iterator incre_ite_2: "<<*incre_ite_2<<endl;
    cout<<endl;
    
    
    
//-------------------------------------------------------------
//MultiLL containing types other than std::string
    cout<<"Test for another type of data:"<<endl;
    list<int> number_list;
    for(int i = 0 ; i<10;i++)
    {
        number_list.push_back(i);
    }
    MultiLL<int> my_int_list;
    for(list<int>::iterator itr = number_list.begin();itr!=number_list.end();itr++)
    {
        my_int_list.add(*itr);
    }
    MultiLL<int>::iterator ite_int = my_int_list.begin_chronological();
    while(ite_int != my_int_list.end_chronological())
    {
        cout<<" "<<*ite_int<<endl;
        ite_int++;
    }
    cout<<endl;
//-------------------------------------------------------------




  std::cout << "Finished StudentTests." << std::endl;
}

// ================================================================================
