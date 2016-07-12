#ifndef EDGE_H
#define EDGE_H

// In order to determine the vertex the edge is storing, get the vertex and then 
// use the hash table to determine the remainder of the edges:
// Vertex<T>* v = hashBrown->search(key); --> this will always be the origin
// Vertex<T>* prev = v;
// In for-loop:
//		Edge<T>* e = currentVertex->adjacencyList->find(i);
// hashBrown->search(currentVertex->adjacencyList->find(i)->destinationName) will get the next vertex.

class Edge
{
private:
	double weight;

	string originName;
	string destinationName;

	template<class U> friend class Vertex;
	template<class U> friend class Graph;
	template<class U> friend class DirGraph;

public:
	Edge(double weight, string originName, string destinationName)
	{
		this->weight = weight;
		this->originName = originName;
		this->destinationName = destinationName;
	}

	double GetWeight() const { return weight; };

	string GetOrigin() const { return originName; };

	string GetDestination() const { return destinationName; };

	// Checks to see whether two edges are equal based on an undirected representation of a graph
	bool isUndirectedEqual(const Edge& other)
	{
		return (weight == other.weight && originName == other.destinationName && destinationName == other.originName);
	}

	bool operator>(const Edge& other)
	{
		return weight > other.weight;
	}

	bool operator<(const Edge& other)
	{
		return weight < other.weight;
	}

	~Edge() {}
};

#endif