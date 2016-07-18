#ifndef HEAPTREENODE_H
#define HEAPTREENODE_H

#include <iostream>

template<class type> class HeapTreeNode
{

private:

	double key_element ;
	type data_element ;
	int weight_element ;

public:

	HeapTreeNode()
	{
		key_element = -1 ;
		data_element = "NULL" ;
	}

	HeapTreeNode(double key_in ,  type data_in)
	{
		key_element = key_in ;
		data_element = data_in ;
		// weight_element = 0 ;
	}

	HeapTreeNode(double key_in ,  type data_in , int weight_in)
	{
		key_element = key_in ;
		data_element = data_in ;
		weight_element = weight_in ;
	}

	double get_key(){return key_element ;}
	type get_data(){return data_element ;}
	int get_weight(){return weight_element ;}
	void display(){std::cout << "  [" << this->get_key() << " , " << this->get_data() << " , " << this->get_weight() << "] \n" ;}
} ;

#endif
