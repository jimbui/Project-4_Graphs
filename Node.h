#ifndef NODE
#define NODE

#include <iostream>

static int num = 1;

template<class type> class Node
{
public:
	type data;
	Node * next;
	int id;

	Node() :data(0), next(0)
	{
		id = num++;
	}

	Node(const type & data) :next(0)
	{
		this->data = data;
		id = num++;
	}

	Node(const type & data, Node * next)
	{
		this->data = data;
		this->next = next;
		id = num++;
	}

};
#endif
