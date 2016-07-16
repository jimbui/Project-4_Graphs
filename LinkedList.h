#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <cassert>
#include <iostream>
#include <stdexcept> 

#include "LinkedListNode.h"

using namespace std ;

template <class T> class LinkedList
{

public:

    LinkedListNode<T> *head ;
    int size ;

	// template<class U> friend class GenTreeNode ;

public:

    LinkedList():size(0) , head(NULL) {}
    bool isEmpty() {return head == NULL ;}
    int getSize() {return size ;}

    void insert(const T &data)
    {
        LinkedListNode<T> *tmp = new LinkedListNode<T>(data) ;

        if (head == NULL) head = tmp ;
    
        else
        {
            LinkedListNode<T> *ptr = head ;
            while(ptr->next != NULL) ptr = ptr->next ;
            ptr->next = tmp ;
        }

        size++ ;
    }

    void insert (const T &data , int pos)
    {
        if (pos <= 0)
        {
            LinkedListNode<T> *tmp = new LinkedListNode<T>(data , head) ;
            head = tmp ; 
            size++ ;
        }

        else if (pos >= size) insert(data) ;

        else
        {
            LinkedListNode<T> *ptr = head ;
            int k = 0 ;

            while(ptr->next != NULL)
            {
                if (k == pos - 1)
                {
                    LinkedListNode<T> *tmp = new LinkedListNode<T>(data) ;
                    tmp->next = ptr->next ;
                    ptr->next = tmp ;
                    size++ ;
                    break ;
                }

                else
                {
                    ptr = ptr->next ;
                    k++ ;
                }
            }
        }
    }

    void del(const T &data)
	{
        LinkedListNode<T> *ptr = head ;
        LinkedListNode<T> *prev = head ;

        if (this->isEmpty()) throw underflow_error("You cannot delete something when there's nothing to delete. Can you?") ;
    
        else
		{
            while (ptr->next != NULL)
			{
                if (ptr->data == data)
				{
                    if (ptr == head)
					{
                        head = head->next ;
                        delete prev ;
						size-- ;
						break ;
                    }

                    else
					{
                        LinkedListNode<T>* tmp = ptr->next ;
                        ptr->data = ptr->next->data ;
                        ptr->next = ptr->next->next ;
                        delete tmp ;
                        size-- ;
						break ;
                    }
                }

                prev = ptr ;
                ptr = ptr->next ;
            }

            if (ptr->data == data)
			{
                prev->next = NULL ;
                delete ptr ;
                size-- ;
            }
        }
    }
    
    void printList() const
    {
        LinkedListNode<T> *ptr = head ;

        std::cout << "  printList(): " ;

        if (size != 0)
        {
            while (true)
            {
                cout << ptr->data << " --> " ;

                if (ptr->next == NULL) 
                {
                    std::cout << "END \n\n" ;
                    return ;
                }

                ptr = ptr->next ;
            }
        }

        else std::cout << "There is nothing to display. \n\n" ;
    }

	T getData () 
    {
		if (this->head == NULL) return 0 ;
		else return this->head->data ;
	}

	T getNext () 
    {
		if (this->head->next == NULL) return 0 ;
		else return this->head->next->data ;
	}

	T getData (int pos) 
    {
		int count = 0 ;
		LinkedListNode<T> *ptr = head ;
		if (ptr == NULL) {throw underflow_error ("The list is empty") ;}
		
		while (ptr != NULL)
		{
			if (count == pos) return ptr->data ;
			ptr = ptr->next ;
			count++ ;
		}

		throw underflow_error ("The item was not found") ;
	}

	T PopFront () 
	{
		LinkedListNode <T> *tmp = head ;
		T data = head->data ;
		head = head->next ;
		delete tmp ;
		size-- ;	
		return data ;
	}
} ;

#endif
