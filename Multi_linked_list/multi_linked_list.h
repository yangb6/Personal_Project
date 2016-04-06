//
//  multi_linked_list.hpp
//  
//
//  Created by Bing Yang on 10/12/15.
//
//

#ifndef multi_linked_list_h
#define multi_linked_list_h
#include <stdio.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include "mtrand.h"
#include <ctime>
using namespace std;

MTRand_int32 mtrand_autoseed(time(NULL));

//Node class
template <class T>
class Node
{
public:
    Node():chrono_next(NULL),chrono_prev(NULL),sorted_next(NULL),sorted_prev(NULL),random_next(NULL){}
    Node(const T& s_name):value(s_name),chrono_next(NULL),chrono_prev(NULL),sorted_next(NULL),sorted_prev(NULL),random_next(NULL){}
    T value;
    Node<T> *chrono_next;
    Node<T> *chrono_prev;
    Node<T> *sorted_next;
    Node<T> *sorted_prev;
    Node<T> *random_next;
};


//Iterator class
template <class T> class MultiLL;
template <class T>
class list_iterator
{
public:
    //default constructor, copy constructor, assignment operator, &destructor
    list_iterator():ptr_(NULL) {}
    list_iterator(const list_iterator<T>& old):type(old.type),ptr_(old.ptr_){}
    list_iterator<T> &operator=(const list_iterator<T>& old)
    {
        type = old.type;
        ptr_ = old.ptr_;
        return *this;
    }
    ~list_iterator(){}
    
    //dereferencing operator gives access to the value at the pointer
    T& operator*(){return ptr_->value;}
    //increment & decrement operators
    list_iterator<T> & operator++()//pre-increment
    {
        //We should judge the type of this iterator.
        if(type == "chrono")
        {
            ptr_ = ptr_->chrono_next;
            return *this;
        }
        else if(type == "random")
        {
            ptr_= ptr_->random_next;
            return *this;
        }
        else
        {
            ptr_ = ptr_->sorted_next;
            return *this;
        }
    }
    list_iterator<T> operator++(int)//post-increment
    {
        if(type == "chrono")
        {
            list_iterator<T> temp(*this);
            ptr_ = ptr_->chrono_next;
            return temp;
        }
        else if(type == "random")
        {
            list_iterator<T> temp(*this);
            ptr_ = ptr_->random_next;
            return temp;
        }
        else
        {
            list_iterator<T>temp(*this);
            ptr_ = ptr_->sorted_next;
            return temp;
        }
    }
    list_iterator <T>& operator--()//pre-decrement.
    {
        if(type == "chrono")
        {
            ptr_ = ptr_->chrono_prev;
            return *this;
        }
        else if(type == "sorted")
        {
            ptr_ = ptr_->sorted_prev;
            return *this;
        }
        else
        {
            cout<<"The random type iterator can't do decrement."<<endl;
            return *this;
        }
    }
    list_iterator<T> operator--(int)//post-decrement.
    {
        if(type == "chrono")
        {
            list_iterator<T> temp(*this);
            ptr_ = ptr_->chrono_prev;
            return temp;
        }
        else if(type == "sorted")
        {
            list_iterator<T> temp(*this);
            ptr_ = ptr_->sorted_prev;
            return temp;
        }
        else
        {
            cout<<"The random type iterator can't do decrement."<<endl;
            return *this;
        }

    }
    
    //The MultiLL class needs access to the private ptr_ and type member varibale
    friend class MultiLL<T>;
    
    //Comparions operators
    bool operator==(const list_iterator<T>& r) const
    {
        return (ptr_ == r.ptr_ && type == r.type);
    }
    bool operator!=(const list_iterator<T> & r) const
    {
        return (ptr_ != r.ptr_ || type != r.type);
    }
    
    
private:
    string type;
    Node<T> *ptr_;
};

//MultiLL class decalration

template <class T>
class MultiLL
{
public:
    //default constructor,copy constructor, assignment operator, &destructor
    MultiLL():count(0),chrono_head(NULL),chrono_tail(NULL),sorted_head(NULL),sorted_tail(NULL),random_head(NULL){}
    MultiLL(const MultiLL<T> &old)
    {
        count = 0;
        this->copy_list(old);
    }
    MultiLL &operator= (const MultiLL<T> &old)
    {
        count = 0;
        this->copy_list(old);
        return *this;
    }
    ~MultiLL(){this->destroy_list();}
    
    //simple accessors & modifiers
    unsigned int size() const {return count;}
    bool empty() const{return count==0;}
    void clear() {this->destroy_list();}
    //Functions for iterator
    typedef list_iterator<T> iterator;
    iterator begin_chronological() const
    {
        iterator itr;
        itr.type = "chrono";
        itr.ptr_ = chrono_head;
        return itr;
    }
    iterator begin_sorted() const
    {
        iterator itr;
        itr.type= "sorted";
        itr.ptr_ = sorted_head;
        return itr;
    }
    iterator end_chronological() const
    {
        iterator ite_chrono;
        ite_chrono.type = "chrono";
        ite_chrono.ptr_ = NULL;
        return ite_chrono;
    }
    iterator end_sorted() const
    {
        iterator ite_sorted;
        ite_sorted.type = "sorted";
        ite_sorted.ptr_ = NULL;
        return ite_sorted;
    }
    
    //Add function.
    void add(const T &t)
    {
        //If there is no node in the MultiLL, we just need to adjust some related pointers.
        if(count == 0)
        {
            Node<T> *new_node = new Node<T>;
            new_node->value = t;
            chrono_head = new_node;
            chrono_tail = new_node;
            sorted_head = new_node;
            sorted_tail = new_node;
            count = count+1;
        }
        //If some Node had existed before, we have to devide it into several situation, especially for the sorted list.
        else
        {
            //In the chronological list, we just add the Node to the end of the list.
            Node<T> *new_node = new Node<T>;
            new_node->value = t;
            new_node->chrono_prev = chrono_tail;
            new_node->chrono_next = NULL;
            chrono_tail->chrono_next = new_node;
            chrono_tail = new_node;
            count = count + 1;
            
            //In the sorted list, we have to consider the situation that add the new Node at the begin , middle, end of the sorted list.
            iterator ite_sorted;
            ite_sorted = this->begin_sorted();
            bool has_add = false;
            while(ite_sorted != this->end_sorted() && !has_add)
            {
                if(ite_sorted.ptr_->value > new_node->value)
                {
                    //add the new node to the begin of the sorted list
                    if(ite_sorted.ptr_ == sorted_head)
                    {
                        new_node->sorted_next = sorted_head;
                        new_node->sorted_prev = NULL;
                        sorted_head->sorted_prev = new_node;
                        sorted_head = new_node;
                        has_add = true;
                    }
                    //add the new node to the middle of the sorted list
                    else
                    {
                        ite_sorted.ptr_->sorted_prev ->sorted_next = new_node;
                        new_node->sorted_next = ite_sorted.ptr_;
                        new_node->sorted_prev = ite_sorted.ptr_->sorted_prev;
                        ite_sorted.ptr_->sorted_prev = new_node;
                        has_add = true;
                    }
                }
                ++ite_sorted;
            }
            //add the new node to the end of the sorted list.
            if(!has_add)
            {
                new_node->sorted_prev = sorted_tail;
                new_node->sorted_next = NULL;
                sorted_tail->sorted_next = new_node;
                sorted_tail = new_node;
            }
            
        }
    }


    
    iterator begin_random()
    {
        //Reset the random list,set all random_next pointer NULL.
        random_head = NULL;
        iterator ite_chrono;
        ite_chrono = this->begin_chronological();
        while (ite_chrono != this->end_chronological())
        {
            ite_chrono.ptr_->random_next = NULL;
            ++ite_chrono;
        }
        //There is no element in the MultiLL,we just need to set related pointer NULL.
        if(chrono_head == NULL)
        {
            iterator ite_random;
            ite_random.type = "random";
            ite_random.ptr_ = NULL;
            return ite_random;
        }
        //Some nodes was stored in the list.
        else
        {
            const unsigned int count1 = count;
            bool find_number[count1];
            for(int i = 0; i<count1;i++)
            {
                find_number[i] = false;
            }
            iterator ite;
            ite.type = "random";
            ite.ptr_ = NULL;
            iterator temp;
            //use a new_count to record that how many node had been reset.
            unsigned int new_count;
            //First, we should set the random_head.
            if(random_head == NULL)
            {
                iterator ite_chrono;
                ite_chrono = this->begin_chronological();
                unsigned int randomNumber = mtrand_autoseed() % (count);
                find_number[randomNumber] = true;
                int i = 0;
                while( i != randomNumber)
                {
                    i++;
                    ite_chrono++;
                }
                random_head = ite_chrono.ptr_;
                ite.ptr_ = ite_chrono.ptr_;
                temp = ite;
                new_count = 1;
            }
            //If random_head is not NULL, we can set other Nodes.

            //If the list only has one node, we can return ite directly.
            if(count == 1)
            {
                return ite;
            }
            else
            {
                iterator ite_chrono1;
                while(temp.ptr_->random_next == NULL)
                {
                    ite_chrono1 = this->begin_chronological();
                    //Use a randomNumber to select a Node.
                    unsigned int randomNumber = mtrand_autoseed() % (count);
                    if(!find_number[randomNumber])
                    {
                        unsigned int i = 0;
                        while( i != randomNumber)
                        {
                            i++;
                            ite_chrono1++;
                        }
                        temp.ptr_->random_next = ite_chrono1.ptr_;
                        temp.ptr_ = ite_chrono1.ptr_;
                        new_count = new_count +1;
                        if(new_count == count)
                        {
                            temp.ptr_->random_next = random_head;
                        }
                        find_number[randomNumber] = true;
                    }
                }
                return ite;
            }
        }
    }
    
    //Two erase helper function, just to reset the pointer.
    void erase_chrono(iterator itr)
    {
        if(itr.ptr_ == chrono_head)
        {
            chrono_head->chrono_next->chrono_prev = NULL;
            chrono_head = chrono_head->chrono_next;
        }
        else if(itr.ptr_ == chrono_tail)
        {
            
            chrono_tail->chrono_prev->chrono_next = NULL;
            chrono_tail = chrono_tail->chrono_prev;
        }
        else
        {
            itr.ptr_->chrono_prev->chrono_next = itr.ptr_->chrono_next;
            itr.ptr_->chrono_next->chrono_prev = itr.ptr_->chrono_prev;
        }
    }
    void erase_sorted(iterator itr)
    {
        if(itr.ptr_ == sorted_head)
        {
            sorted_head->sorted_next->sorted_prev = NULL;
            sorted_head = sorted_head->sorted_next;
        }
        else if(itr.ptr_ == sorted_tail)
        {
            sorted_tail->sorted_prev->sorted_next = NULL;
            sorted_tail = sorted_tail->sorted_prev;
        }
        else
        {
            itr.ptr_->sorted_prev->sorted_next = itr.ptr_->sorted_next;
            itr.ptr_->sorted_next->sorted_prev = itr.ptr_->sorted_prev;
        }
    }

    iterator erase(iterator itr)
    {
        if(itr.type == "chrono")
        {
            if(count == 0)
            {
                cout<<"There is no elements in the list, nothing can be erased."<<endl;
                return itr;
            }
            else if(count == 1)
            {
                //First we should judge the itr point to the only element in the list
                if(itr.ptr_ == chrono_head)
                {
                    chrono_head = NULL;
                    chrono_tail = NULL;
                    sorted_head = NULL;
                    sorted_tail = NULL;
                    count = count - 1;
                    delete itr.ptr_;
                    itr.ptr_ = NULL;
                    return itr;
                }
                else
                {
                    cout<<"The element that itr point to is not in the list."<<endl;
                    return itr;
                }
            }
            //The list contain more than 1 elements.
            else
            {
                //First, we should see the Node that itr.ptr_ point to is in the list or not.
                bool is_in = false;
                iterator  ite_chrono;
                ite_chrono = this->begin_chronological();
                while(ite_chrono != this->end_chronological() && !is_in)
                {
                    if(ite_chrono.ptr_ == itr.ptr_)
                    {
                        is_in = true;
                    }
                    else
                    {
                        ++ite_chrono;
                    }
                }
                
                if(is_in)
                {
                //itr point to the fisrt element in the list.
                    if(itr.ptr_ == chrono_head)
                    {
                        //There were also three situation: itr.ptr_ point to the middle of the sorted list,begin of the sorted list and end of the sorted list.
                        //so use the erase_sorted() helper Function.
                    
                        //1.itr.ptr_ point to the begin of the sorted list.
                        chrono_head->chrono_next->chrono_prev = NULL;
                        chrono_head = chrono_head->chrono_next;
                        this->erase_sorted(itr);
                        delete itr.ptr_;
                        itr.ptr_ = chrono_head;
                        count = count - 1;
                        return itr;
                    }
                 //itr point to the last element in the list.
                    else if(itr.ptr_ == chrono_tail)
                    {
                        //There were also three situation: itr.ptr_ point to the middle of the sorted list,begin of the sorted list and end of the sorted list.
                        chrono_tail->chrono_prev->chrono_next = NULL;
                        chrono_tail = chrono_tail->chrono_prev;
                        this->erase_sorted(itr);
                        delete itr.ptr_;
                        itr = this->end_chronological();
                        count = count - 1;
                        return itr;
                    
                    }
                 //itr point to the middle element in the list.
                    else
                    {
                      //There were also three situation: itr.ptr_ point to the middle of the sorted list,begin of the sorted list and end of the sorted list.
                        iterator temp;
                        temp = itr;
                        temp.ptr_ = temp.ptr_->chrono_next;
                        itr.ptr_->chrono_prev->chrono_next = itr.ptr_->chrono_next;
                        itr.ptr_->chrono_next->chrono_prev = itr.ptr_->chrono_prev;
                        this->erase_sorted(itr);
                        delete itr.ptr_;
                        itr.ptr_ = temp.ptr_;
                        count = count - 1;
                        return itr;
                    }
                }
                else
                {
                    cout<<"The Node that itr.ptr_ points to is not in the list."<<endl;
                    return itr;
                }
            }
        }
        else if(itr.type== "sorted")
        {
            //If there is no elements in the list, print out the wrong information.
            if(count == 0)
            {
                cout<<"There is no elements in the list, nothing can be erased."<<endl;
                return itr;
            }
            //If only 1 Node in the list, reset all head and tail pointer.
            else if(count == 1)
            {
                if(itr.ptr_ == sorted_head)
                {
                    chrono_head = NULL;
                    chrono_tail = NULL;
                    sorted_head = NULL;
                    sorted_tail = NULL;
                    delete itr.ptr_;
                    itr.ptr_ = NULL;
                    count = count - 1;
                    return itr;
                }
                else
                {
                    cout<<"The Node that itr.ptr_ points to is not in the list."<<endl;
                    return itr;
                }
            }
            else
            {
                //First, find out if the Node that itr.ptr_ point to is in the list or not.
                bool is_in =false;
                iterator ite_sorted;
                ite_sorted = this->begin_sorted();
                while(ite_sorted != this->end_sorted() && !is_in)
                {
                    if(itr.ptr_ == ite_sorted.ptr_)
                    {
                        is_in = true;
                    }
                    else
                    {
                        ++ite_sorted;
                    }
                }
                if(is_in)
                {
                    if(itr.ptr_ == sorted_head)
                    {
                        //There were also three situation: itr.ptr_ point to the middle of the chronogical list,begin of the chronogical list and end of the chronogical list.
                        sorted_head->sorted_next->sorted_prev = NULL;
                        sorted_head = sorted_head->sorted_next;
                        this->erase_chrono(itr);
                        delete itr.ptr_;
                        itr.ptr_ = sorted_head;
                        count = count - 1;
                        return itr;
                    }
                    else if(itr.ptr_ == sorted_tail)
                    {
                        sorted_tail->sorted_prev->sorted_next = NULL;
                        sorted_tail = sorted_tail->sorted_prev;
                        this->erase_chrono(itr);
                        delete itr.ptr_;
                        itr = this->end_sorted();
                        count = count - 1;
                        return itr;

                    }
                    else
                    {
                        iterator temp;
                        temp = itr;
                        temp.ptr_ = temp.ptr_->sorted_next;
                        itr.ptr_->sorted_prev->sorted_next = itr.ptr_->sorted_next;
                        itr.ptr_->sorted_next->sorted_prev = itr.ptr_->sorted_prev;
                        this->erase_chrono(itr);
                        delete itr.ptr_;
                        itr.ptr_ = temp.ptr_;
                        count = count - 1;
                        return itr;
                        
                    }
                }
                else
                {
                    cout<<"The Node that itr.ptr_ points to is not in the list."<<endl;
                    return itr;
                }
                
            }
        }
        else if(itr.type == "random")
        {
            if(count == 0)
            {
                cout<<"There is no elements in the list, nothing can be erased."<<endl;
                return itr;
            }
            else if(count == 1)
            {
                if(itr.ptr_ == random_head)
                {
                    chrono_head = NULL;
                    chrono_tail = NULL;
                    sorted_head = NULL;
                    sorted_tail = NULL;
                    random_head = NULL;
                    delete itr.ptr_;
                    count = count - 1;
                    itr.ptr_ = NULL;
                    return itr;
                }
                else
                {
                    cout<<"The Node that itr.ptr_ points to is not in the list."<<endl;
                    return itr;
                }
            }
            else if(count == 2)
            {
                if(itr.ptr_ == random_head || itr.ptr_ == random_head->random_next)
                {
                    if(itr.ptr_ == random_head)
                    {
                        random_head = itr.ptr_->random_next;
                    }
                    itr.ptr_->random_next->random_next = NULL;
                    this->erase_chrono(itr);
                    this->erase_sorted(itr);
                    delete itr.ptr_;
                    count = count - 1;
                    itr.ptr_ = random_head;
                    return itr;
                }
                else
                {
                    cout<<"The Node that itr.ptr_ points to is not in the list."<<endl;
                    return itr;
                }
            }
            else
            {
                iterator ite;
                ite = this->begin_chronological();
                bool is_in =false;
                while(ite != this->end_chronological() && !is_in)
                {
                    if(itr.ptr_ == ite.ptr_)
                    {
                        is_in = true;
                    }
                    else
                    {
                        ++ite;
                    }
                }
                if(is_in)
                {
                    if(itr.ptr_ == random_head)
                    {
                        random_head = itr.ptr_->random_next;
                    }
                    //Use a temp iterator to find the last node.
                    iterator temp;
                    temp = itr;
                    for(int i = 0 ; i< count - 1;i++)
                    {
                        temp.ptr_ = temp.ptr_->random_next;
                    }
                    temp.ptr_->random_next = itr.ptr_->random_next;
                    this->erase_chrono(itr);
                    this->erase_sorted(itr);
                    delete itr.ptr_;
                    count = count - 1;
                    itr.ptr_ = temp.ptr_->random_next;
                    return itr;
                }
                else
                {
                    cout<<"The Node that itr.ptr_ points to is not in the list."<<endl;
                    return itr;
                }
            }
        }
        else
        {
            cout<<"The iterator has wrong type"<<endl;
            return itr;
        }
    }
    
private:
    //private helper functions
    void copy_list(const MultiLL<T> & old)
    {
        if(old.count == 0)
        {
            count = 0;chrono_head = NULL;sorted_head = NULL;chrono_tail = NULL;sorted_tail = NULL;
        }
        else
        {
            iterator ite_chrono;
            ite_chrono = old.begin_chronological();
            while(ite_chrono != old.end_chronological())
            {
                this->add(*ite_chrono);
                ++ite_chrono;
            }
        }
    }
    void destroy_list()
    {
        while(chrono_head != NULL)
        {
            iterator ite_chrono;
            ite_chrono = this->begin_chronological();
            this->erase(ite_chrono);
        }
        
    }
    unsigned int count ;
    Node<T> *chrono_head;
    Node<T> *chrono_tail;
    Node<T> *sorted_head;
    Node<T> *sorted_tail;
    Node<T> *random_head;

};
#endif /* multi_linked_list_h */
