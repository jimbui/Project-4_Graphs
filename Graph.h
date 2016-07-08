#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "HashTable.h"
#include "Edge.h"

using namespace std;

template<class T> class Graph
{
private:
	// HashTable<string, Vertex<T>*> vertices;
	int sz;

public:
	Graph(int Sz = 20) :sz(Sz)
	{}

};


#endif
