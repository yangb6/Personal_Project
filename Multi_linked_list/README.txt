HOMEWORK 5: MULTI LINKED LISTS


NAME:  Bing Yang


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

First, I asked my classmates Yushi Xiao and Zhuoyi Li for some problem about homework_5.
Second, in the lab class, Charles and Youssef give me some helpful suggestions and help me to solve some problems about the homework_5. I feel grateful for their job. Thanks.
Third, I used the google to search some information about the pointer and list.
Fourth, I found some information about merge sort on the:http://www.geeksforgeeks.org/merge-sort-for-doubly-linked-list/.
Finally, I also use the website cplusplus.com for some information.


Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  20 hours.



TESTING & DEBUGGING STRATEGY:
Please be concise!  
1.I test them for another data type to make sure that template class work.
2.I test each function by general case.
3.I test each function by ¡°Coner case¡±.
4.When I found bugs.I would firstly check the logic of the code and draw a draft.
5.Then I would use drmitory to see where the program crash and fix it.


ORDER NOTATION of the member functions of MultiLL?
(in terms of n, the number of elements currently in the list)

default constructor
1.It just need to initialize the value of the member variables which needs constant time.¡ª>O(1).

copy constructor
1.Since it use the add function. So if we want to copy the old list which has n nodes,it needs (1+n)*n/2.
So the order notation is O(n^2).

assignment operator
1. When we use assignment operator, actually we use copy_list function, so the order notation is O(n^2).

destructor
1.Its order notation is the same as the destroy_list function.
2.At destroy_list function, every time I erase the first node.¡ª>O(1)
So erase n nodes need n times erase operation. Total order notation is ¡ª>O(n).

size
1.It just need return the the value of the count which need constant time.¡ª>O(1).

empty
1.It just compare member variable count==0 which need constant time. ¡ª>O(1).

clear
1.Its order notation is the same as the destroy_list function.
2.At destroy_list function, every time I erase the first node.¡ª>O(1)
So erase n nodes need n times erase operation. Total order notation is ¡ª>O(n).

add
1.Add the new Node to the end of the chronological list and reset related pointers 
only need constant time.¡ª>O(1)
2.The worse situation about adding new Node to the end of the sorted list and reset related pointers is 
that traversing  all nodes in the list.¡ª>O(n).
So the total order notation is (n).

erase
1.The worse situation is that I have to traversal the whole list to find if the Node we want to erase is in 
the list or not.¡ª->O(n).
2.Reset the pointer only need constant time¡ª>O(1).
3.So the total order notation is O(n).

begin_chronological
constant time:O(1)

end_chronological
constant time:O(1)

begin_sorted
constant time:O(1)

end_sorted
constant time:O(1)

begin_random
1. Reset all random_next¡ª->O(n).
2.Find the next random Node and set it n(n+1)/2 ¡ª->O(n^2)
3.Actually, the worse situation is that the random number continuously do not meet the requirement and It would loop infinitely.But at this situation, I really don¡¯t know how to calculate the order notation¡­¡­¡­¡­
4.So,without considering the random number, totally order notation: O(n^2)

ITERATOR INVALIDATION:
In what cases will iterators of the MultiLL be invalidated?  Justify
the need for each of the restrictions placed on your implementation.
1.If an iterator equal to end_chronological() or end_sorted(), when we use post-decrement, pre-decrement,post-increment and pre-increment,it would be useless and show some wrong information, such as segmentation fault.

2.If an iterator equal to the begin_chronological() or begin_sorted().When we use post-decrement, pre-decrement, it would be useless and show some wrong information, such as segmentation fault.

3.If we use pre-decrement and post-increment for a ¡°random¡± type iterator, it would also show some wrong information.

4.Once we use the begin_random() function, all random next pointer would be reset.So all iterator about the random list would be invalidated.Although it still point to a Node.

5.If we delete a node use an iterator, another iterator points to this node would be invalidated.

EXTRA CREDIT: 
Which function in your implementation can be improved by a
non-insertion sort sorting method?  Describe.

In my copy_list function, it would use the add function. In add function, every node we add is new, so we have to compare it with the node in the list before.So the order notation is O(n^2). However, in copy_list function, we do not need to add new node, but just need to sort the list. So I decide to use merge sort to sort the list and the order notation would be O(nlogn).

But there is still some problems with my code and I can¡¯t fix it in a short time.If you know where it is wrong, could you please email me? I know it is hard for me to get extra credit, but I really want to know how to reduce the order notation.
The code is:

    //Helper Function to split the the list. 
   Node<T> *split(Node<T> *sorted_head)
    {
        Node<T> *fast = sorted_head;
        Node<T> *slow = sorted_head;
        while(fast->sorted_next && fast->sorted_next->sorted_next)
        {
            fast = fast->sorted_next->sorted_next;
            slow = slow->sorted_next;
        }
        Node<T> *temp = slow->sorted_next;
        slow->sorted_next = NULL;
        return temp;
    }
    
    Node<T> *merge(Node<T> *first, Node<T>* second)
    {
        if(first == NULL)
            return second;
        if(second == NULL)
            return first;
        if(first->value < second->value)
        {
            first->sorted_next = merge(first->sorted_next,second);
            first->sorted_next->sorted_prev = first;
            first->sorted_prev = NULL;
            return first;
        }
        else
        {
            second->sorted_next = merge(first,second->sorted_next);
            second->sorted_next->sorted_prev = second;
            second->sorted_prev = NULL;
            return second;
        }
    }
    
    Node<T> *mergesort(Node<T> *sorted_head)
    {
        if(count ==0 || count == 1)
        {
            return sorted_head;
        }
        else
        {
            Node<T> *second = split(sorted_head);
            sorted_head = mergesort(sorted_head);
            second = mergesort(second);
            return merge(sorted_head,second);
        }
    }
    void copy_list(const MultiLL<T> & old)
    {
        iterator ite_chrono = old.begin_chronological();
        iterator temp_chrono;
        iterator temp_sorted;
	//First, we should initialise the chronological list and sorted list.
	//I set the sorted list the same as the chronological order and then sort it.
        if(old.count != 0)
        {
            while (ite_chrono!= old.end_chronological())
            {
                Node<T> *new_node = new Node<T>(*ite_chrono);
                if(count == 0)
                {
                    chrono_head = new_node;
                    sorted_head = new_node;
                    temp_chrono.ptr_ = new_node;
                    count = count + 1;
                }
                else
                {
                    temp_chrono.ptr_->chrono_next = new_node;
                    temp_chrono.ptr_->sorted_next = new_node;
                    temp_chrono.ptr_ = new_node;
                    count = count + 1;
                    
                }
                ite_chrono++;
            }
            chrono_tail = temp_chrono.ptr_;
            sorted_tail = temp_chrono.ptr_;
        }
        mergesort(this->sorted_head);
        
    }







MISC. COMMENTS TO GRADER:  
Optional, please be concise!


