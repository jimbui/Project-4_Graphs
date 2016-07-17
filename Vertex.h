#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <stdexcept>
#include "SLinkedList.h"
#include "Edge.h"
#include <math.h>

using namespace std;

// static int numID = 0;

template<class T> class Vertex
{
private:
	// int id;
	bool visited;
	T data;
	Vertex<T>* parent;
	SLinkedList<Edge*>* adjacencyList;

	// For Prim's algorithm...
	double cheapestConnection;
	Edge* edgePointer;
	// string name;

	// int depth;
	template<class U> friend class Graph;
	template<class U> friend class DirGraph;

public:
	Vertex() :visited(false), parent(0), cheapestConnection(6.66 * pow(10, 66)), data(0), edgePointer(nullptr)
	{
		adjacencyList = new SLinkedList<Edge*>();
	}

	Vertex(const T& data) :visited(false), parent(0), cheapestConnection(6.66 * pow(10, 66)), edgePointer(nullptr)
	{
		this->data = data;
		adjacencyList = new SLinkedList<Edge*>();
	}

	Vertex(const T& data, const string& name) :visited(false), parent(0), cheapestConnection(6.66 * pow(10, 66)), edgePointer(nullptr)
	{

	}

	Vertex(const T& data, const double& cheapestConnection) :visited(false), parent(0), edgePointer(nullptr)
	{
		this->data = data;
		this->cheapestConnection = cheapestConnection;
		adjacencyList = new SLinkedList<Edge*>();
	}

	~Vertex()
	{
		adjacencyList->clear();

		delete adjacencyList;
	}

	T GetData() const { return data; };

	// Creates a new vertex identical to the original, except without edges.
	Vertex* GetPureVertex() { return new Vertex(data, cheapestConnection); };

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

	friend ostream& operator<<(ostream& os, const Vertex& v)
	{
		os << v.GetData();

		return os;
	}
};

#endif