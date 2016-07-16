#ifndef LINKEDLISTNODE_H
#define LINKEDLISTNODE_H

#include <iostream>

using namespace std ;

template<class type> class LinkedListNode
{

public:

    type data ;
    LinkedListNode *next ;
    
	LinkedListNode():data(0) , next(0){}
	LinkedListNode(const type &data):next(0){this->data = data ;}

    LinkedListNode(const type &data , LinkedListNode *next)
    {
        this->data = data ;
        this->next = next ;
    }
} ;

#endif