#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include "SLinkedList.h"
#include "Edge.h"

using namespace std;

// static int numID = 0;

template<class T> class Vertex
{
private:
	// int id;
	bool visited;
	T data;
	Vertex<T> * parent;
	SLinkedList<Edge<T> * > adjacencyList;

	// int depth;
	template<class U> friend class Graph;

public:
	Vertex(const T & data) :visited(false), /*depth(0),*/ parent(0)
	{
		this->data = data;
		// id = numID++;
	}

	void visit()
	{
		cout << (this == nullptr ? "NULL" : this->data) << endl;
	}

	void visit(Vertex<T>* origin)
	{
		this->parent = origin;

		if (origin == nullptr) 
			this->depth = 0;
		else 
			this->depth = origin->depth + 1;
	}
};

#endif