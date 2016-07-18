/*

two classes.  done.

calculate running times and create a UML file.  ok.

// what is a priority queue?
	
	a priority queue is the same as a queue or a stack , however each item also has an associated 
	key.  the queue is then served in the order of priority of the key values.  if items have the 
	same key , they are then served by queue order.

a binary heap is then a particular implementation of the priority queue.  a heap is a complete 
binary tree (all levels are filled except for possibly the last level , where elements are stored 
from  left to right).  the entries in the binary tree also satisfy the heap property , where no 
child has a key that is greater than its parents key.

in this project , entries are stored in a dynamic array.  it follows the same resize rule as last
project.

*/

#ifndef MAXHEAPTREE_H
#define MAXHEAPTREE_H

#include <fstream>
#include <iostream>
#include <math.h>
#include <stdexcept>
#include <string>

#include "HeapTreeNode.h"

template <class type> class MaxHeapTree
{

private: 

	HeapTreeNode<type> *dynamic_array ;
	int array_size ; // size of the array.
	int initial_size ;
	int element_count ; // how many elements are in the array.

	/*

	there is an array starting with position 0.
	ignore position zero.  we start with 1.
	1 is the root.
	for any postion i , the two children of that node is 2i and 2i + 1.
	for any postion i except for the root , the parent is i / 2.

	this is a max heap , so the largest value goes to position 1.
	this is also has to be a complete binary tree , so the all levels must be complete with the 
	exception of the last level , which must be filled left to right.

	*/

public:

	MaxHeapTree(int n) // O(1).
	{
		if (n < 2) n = 2 ;
		dynamic_array = new HeapTreeNode<type>[n] ;
		array_size = n ;
		initial_size = n ;
		element_count = 0 ;
	}

	~MaxHeapTree(){} // O(1).

	type getMax() // O(1).
	{
		return dynamic_array[1].get_data() ;
	}

	int getSize() // returns number of elements in the tree. // O(1).
	{
		return element_count ;
	}

	int getHeight() // should be log_2(element_count) or something. // O(1).
	{	
		if (element_count == 0) return 0 ;
		else return log2(element_count) ;
	}

	bool empty() // O(1).
	{
		if (element_count == 0) return true ;
		else return false ;
	}

	int leaves() // returns the number of leaves in the tree. // O(1).
	{
		// the commented out equation was doing it the hard way.

		// int not_leaves = (pow(2 , ((int)this->getHeight() + 1)) - 1) - element_count ; 
		// return pow(2 , (int)this->getHeight()) - not_leaves + not_leaves / 2 ;

		// this was derived by looking at the tree.

		return (element_count + 1) / 2 ;
	}

	// accessors.

	void buildTreehouse(std::string path) // reads structure from a text file and builds a max heap.
	{
		std::string line ;
		std::ifstream myfile(path) ;

		if (myfile.is_open())
		{
			while (getline(myfile , line))
			{
				int pos = line.find('.') ;
				std::string key_in = line.substr(0 , pos) ;
				std::string data = line.substr(pos + 1) ;
				int key = stoi(key_in) ;
				this->insert(key , data) ;
			}

			myfile.close() ;
			std::cout << "  Tree has been build from text file. \n\n" ;
			return ;
		}

		else 
		{
			std::cout << "  File does not fuckin' exist. \n\n" ;
			return ;
		}
	}

	void clear() // O(1).
	{
		dynamic_array = new HeapTreeNode<type>[initial_size] ;
		array_size = initial_size ;
		element_count = 0 ;
		// std::cout << "  Tree cleared and reset. \n\n" ;
	}

	void insert(double key_in , type data_in) // satisfies the heap property. // worst case is that it has to go though all the levels to the root , making this O(log_2(n))
	{
		if (element_count + 1 == array_size) this->resize_up() ;

		HeapTreeNode<type> new_node(key_in , data_in) ;
		dynamic_array[element_count + 1] = new_node ;
		element_count++ ;

		insert_swap(element_count) ;
	}

	void insert(double key_in , type data_in , int weight_in) // satisfies the heap property. // worst case is that it has to go though all the levels to the root , making this O(log_2(n))
	{
		if (element_count + 1 == array_size) this->resize_up() ;

		HeapTreeNode<type> new_node(key_in , data_in , weight_in) ;
		dynamic_array[element_count + 1] = new_node ;
		element_count++ ;

		insert_swap(element_count) ;
	}

	std::string delMax() // worst case is that it has to go though all the levels to the end , making this O(log_2(n))
	{
		if (empty()) std::cout << "  There is nothing to delete in the tree. \n\n" ;
 
		else
		{	
			std::string thingy = dynamic_array[1].get_data() ;
			// std::cout << "1 \n" ;
			dynamic_array[1] = dynamic_array[element_count] ;
			// std::cout << "2 \n" ;
			HeapTreeNode<type> new_node(-1 , "NULL") ;
			// std::cout << "3 \n" ;
			dynamic_array[element_count] = new_node ; // just resets the last value.
			// std::cout << "4 \n" ;
			element_count-- ;
			// std::cout << "5 \n" ;
			delete_swap(1) ;
			// std::cout << "6 \n" ;

			if (element_count < array_size / 2 && array_size / 2 >= initial_size && array_size / 2 >= 2) this->resize_down() ;
			return thingy ;
		}
	}

	int return_weight()
	{
		return dynamic_array[1].get_weight() ;
	}

	void resize_up()
	{
		array_size = array_size * 2 ;

		HeapTreeNode<type> *temp_array = new HeapTreeNode<type>[array_size] ;
		int i = 1 ;

		while (i <= element_count)
		{
			temp_array[i] = dynamic_array[i] ;
			i++ ;
		}

		dynamic_array = temp_array ;
	}

	void resize_down()
	{
		array_size = array_size / 2 ;

		HeapTreeNode<type> *temp_array = new HeapTreeNode<type>[array_size] ;
		int i = 1 ;

		while (i <= element_count)
		{
			temp_array[i] = dynamic_array[i] ;
			i++ ;
		}

		dynamic_array = temp_array ;
	}

	// miscelleneous.

	void display()
	{
		int i = 0 ;

		while (i < array_size)
		{
			std::cout << "  dynamic_array[" << i << "]: " ;
			dynamic_array[i].display() ;
			i++ ;
		}

		std::cout << " \n" ;
	}

	void display_tree()
	{
		if (empty()) std::cout << "  The tree is empty. \n\n" ;

		else
		{
			display_recurse(1 , 0) ;
			std::cout << " \n" ;
		}
	}

	void display_recurse(int i , int j)
	{
		int k = 0 ;

		//if (j != 0)
		{
			while (k < j)
			{
				std::cout << "   |    " ;
				k++ ;
			}
		}

		dynamic_array[i].display() ;

		if (dynamic_array[i * 2].get_key() != -1 && i * 2 <= element_count)
		{
			display_recurse(i * 2 , j + 1) ;
		}

		if (dynamic_array[i * 2 + 1].get_key() != -1 && i * 2 + 1 <= element_count)
		{
			display_recurse(i * 2 + 1 , j + 1) ;
		}
	} 

	void insert_swap(int index) // recusively check if the parent is smaller.
	{
		if (index == 1)
		{
			return ; // this is now the max value.
		}

		else if (dynamic_array[index].get_key() > dynamic_array[index / 2].get_key()) // if element is larger than it's parent , swap.
		{
			HeapTreeNode<type> temp_node(dynamic_array[index].get_key() , dynamic_array[index].get_data()) ; // hold current array.
			dynamic_array[index] = dynamic_array[index / 2] ;
			dynamic_array[index / 2] = temp_node ;
			insert_swap(index / 2) ;
		}

		else
		{
			return ;
		}
	}

	void delete_swap(int index)
	{
		if (element_count == 1 || element_count == 0) return ; // if empty or just one element , nothing to swap.

		else
		{
			int larger_key ;

			if (index * 2 + 1 < array_size)
			{
				if (dynamic_array[index * 2].get_key() >= dynamic_array[index * 2 + 1].get_key()) larger_key = index * 2 ;
				else larger_key = index * 2 + 1 ;
			}

			else if (index * 2 < array_size)
			{
				larger_key = index * 2 ; 
			}

			else return ;

			if (dynamic_array[index].get_key() <= dynamic_array[larger_key].get_key())
			{
				HeapTreeNode<type> temp_node(dynamic_array[index].get_key() , dynamic_array[index].get_data()) ; // hold current array.
				dynamic_array[index] = dynamic_array[larger_key] ;
				dynamic_array[larger_key] = temp_node ;
				delete_swap(larger_key) ;
			}

			else return ;
		}
	}

} ;

#endif

