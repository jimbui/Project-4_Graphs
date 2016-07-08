#ifndef EDGE_H
#define EDGE_H

#include "Vertex.h"

template<class T> class Edge
{
private:
	double weight;

	Vertex<T>* origin;
	Vertex<T>* destination;

	// template<class U> friend class Vertex;

public:
	Edge(double weight, Vertex<T>* origin, Vertex<T>* destination)
	{
		this->weight = weight;
		this->origin = origin;
		this->destination = destination;
	}

	double GetWeight() const { return weight; };

	~Edge() {}
};

#endif