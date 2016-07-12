#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "HashTable.h"
#include "Vertex.h"
#include "Edge.h"

using namespace std;

template<class T> class Graph
{
private:
	HashTable<string, Vertex<T>*>* vertices;
	int sz;
	int edgeCount;

public:
	Graph(int Sz = 20) :sz(Sz)
	{
		vertices = new HashTable<string, Vertex<T>*>(sz, 0.5);

		// Test code...
		vertices->insert("V1", new Vertex<T>(44));
		vertices->insert("V2", new Vertex<T>(90));
		vertices->insert("V3", new Vertex<T>(46));
		vertices->insert("V4", new Vertex<T>(79));
	}

	~Graph()
	{
		delete vertices;
	}

	// Accessors --------------------------------------------------------------------------
	bool empty() const { return sz == 0; };

	// Returns the degree of the vertex stored at v in the hash table.  Can throw errors, so be sure to catch them...
	int degree(string v)
	{
		try
		{
			Vertex<T>* vertest = vertices->search(v);
			return vertest->adjacencyList->sz;
		}
		catch (const underflow_error& e)
		{
			throw invalid_argument("Vertex does not exist.");
		}
	}

	// Program this later... --> probably O(n^2).
	bool isConnected()
	{
		return false;
	}

	// Returns the number of edges in the graph
	int EdgeCount() const { return edgeCount; };

	// Determines the weight between two vertices.  Can throw errors, so be sure to catch them...  O(n)
	double adjacent(string u, string v)
	{
		try
		{
			// Get vertex u first; then check to see if v is adjacent to u
			Vertex<T>* uVertex = vertices->search(u);
			
			// The vertices are the same... (Note that the try-loop will handle all invalid arguments.)
			if (u == v)
				return 0;

			Node<Edge*>* edgeNode = uVertex->adjacencyList->head;

			// Return "infinity" because the vertices are not connected.
			if (edgeNode == nullptr)
				return 6.66 * pow(10, 66);

			// Return where the edge node's destination is v. (This is u <----> v.)
			while (edgeNode != nullptr)
			{
				if (v == edgeNode->data->GetDestination())
					return edgeNode->data->GetWeight();

				edgeNode = edgeNode->next;
			}

			// The edge was not found in the list.
			return 6.66 * pow(10, 66);
		}
		catch (const underflow_error& e)
		{
			throw invalid_argument("Either or both of the vertices do not exist.");
		}
	}

	// Mutators --------------------------------------------------------------------------
	void clear()  // O(n)
	{
		vertices->clear();
	}

	void reset()  // O(n)
	{
		for (int i = 0; i < vertices->arraySize; i++)
		{
			ChainNode<string, Vertex<T>*>* ptr = vertices->bucket[i].GetHead();

			while (ptr != nullptr)  // Checks each item in the chained hash table
			{
				Vertex<T>* current = ptr->Data();

				current->visited = false;
			}
		}
	}

	// Inserts a new edge into a graph with existing vertices.  O(n)
	void insert(string u, string v, double w)
	{
		// Checks to see whether the vertices are equal.
		if (u == v)
			throw invalid_argument("The vertices cannot be equal.");

		// Checks to see whether the weight is valid.
		if (w < 0 || w > pow(10, 10))
			throw invalid_argument("Invalid weight.  Valid values are between 0 and 10 ^ 10.");

		// Try loop is used to determine whether u and v exist...
		try
		{
			// If either one of these two lines fail, an underflow exception will be thrown. --> (uVertex != NULL && vVertex != NULL)
			Vertex<T>* uVertex = vertices->search(u);
			Vertex<T>* vVertex = vertices->search(v);

			// Check to see whether the edge already exists before inserting a new one...
			Node<Edge*>* listPtrU = uVertex->adjacencyList->head;
			Node<Edge*>* listPtrV = vVertex->adjacencyList->head;

			if (listPtrU == nullptr && listPtrV == nullptr && w > 0)  // insert the new item because one does not already exist
			{
				Edge* newEdgeUToV = new Edge(w, u, v);
				Edge* newEdgeVToU = new Edge(w, v, u);

				uVertex->adjacencyList->insert(newEdgeUToV);
				vVertex->adjacencyList->insert(newEdgeVToU);

				edgeCount++;
				return;
			}
			
			bool foundU = false;
			// Else, enter this while-loop and see if the edge already exists

			while (listPtrU != nullptr)
			{
				if (listPtrU->data->destinationName == v)  // The link exists; however, the other node must be found before the value can be modified.
				{
					foundU = true;

					// Delete link if the weight is equal to 0.
					if (w == 0)
						uVertex->adjacencyList->del(listPtrU->data);

					break;
				}

				listPtrU = listPtrU->next;
			}

			if (!foundU && w > 0)  // The edge does not exist, so a new one will be inserted.
			{
				Edge* newEdgeUToV = new Edge(w, u, v);
				Edge* newEdgeVToU = new Edge(w, v, u);

				uVertex->adjacencyList->insert(newEdgeUToV);
				vVertex->adjacencyList->insert(newEdgeVToU);

				edgeCount++;
				return;
			}

			// Else, enter this while-loop and get the other edge.  At this point, the only thing that will be modified is the edge's weight.
			while (listPtrV != nullptr)
			{
				if (listPtrV->data->destinationName == u)
				{
					if (w > 0)
					{
						listPtrU->data->weight = w;
						listPtrV->data->weight = w;
					}
					else  // Simply remove the other connection.
					{
						vVertex->adjacencyList->del(listPtrV->data);
					}

					return;
				}

				listPtrV = listPtrV->next;
			}
		}

		catch (const underflow_error& e)
		{
			throw invalid_argument("Either one or both of the vertices do not exist.");
		}
	}

	// Deletes a vertex and its corresponding links.  O(n^2)
	void del(string v)  // O(n^2) because all connecting vertices' edges must be traversed when the graph is tightly connected.
	{
		try
		{
			Vertex<T>* vVertex = vertices->search(v);  // Get the vertex to delete.

			Node<Edge*>* edgeNode = vVertex->adjacencyList->head;  // Gets the head vertex

			// Note that in a directed graph, one cannot simply traverse the connections and get those vertices' edges.
			// One must instead traverse all vertices and get all edges pointing to v.  This will correspond to a runtime of
			// O(n^2).

			// There must be no connecting links.  (Assumption valid for undirected graph only.)
			if (edgeNode == nullptr)
			{
				vertices->erase(v);  // Do not delete a vertex in the graph.  Delete it from the hash table.
				return;
			}

			// Search each connecting vertex for the link corresponding to v, and remove that link.
			while (edgeNode != nullptr)
			{
				// Get the destination vertex of the link...
				Vertex<T>* destinationVertex = vertices->search(edgeNode->data->destinationName);

				Node<Edge*>* edgeNodeDest = destinationVertex->adjacencyList->head;

				// By the rules of undirected graphs, edgeNodeDest will never be a nullptr.
				while (edgeNodeDest != nullptr)
				{
					if (edgeNodeDest->data->destinationName == v)  // Where these two conditions are equal, the edge will be removed.
					{
						// I'm feeling lazy.  Don't tell the instructor... --> Inefficient function.
						destinationVertex->adjacencyList->del(edgeNodeDest->data);
						edgeCount--;
						break;  // There will never be duplicate edges in the same list.
					}

					edgeNodeDest = edgeNodeDest->next;
				}

				edgeNode = edgeNode->next;
			}

			// Delete vertex out of hash table after all links to it have been removed.
			vertices->erase(v);
		}
		catch (const underflow_error& e)
		{
			cout << "This vertex does not exist, so it can't be deleted." << endl;
		}
	}

	// Debug --------------------------------------------------------------------------
	void DisplayAdjacencyList()
	{
		if (sz > 0) // How to get all of the vertices in the graph...
		{
			for (int i = 0; i < vertices->arraySize; i++)
			{
				ChainNode<string, Vertex<T>*>* ptr = vertices->bucket[i].GetHead();

				while (ptr != nullptr)  // Checks each item in the chained hash table
				{
					string vName = ptr->DataKey();
					Vertex<T>* current = ptr->Data();

					cout << "|" << vName << ":  " << current->GetData() << "| --> ";

					Node<Edge*>* edgePtr = current->adjacencyList->head;

					while (edgePtr != nullptr)
					{
						cout << edgePtr->data->GetDestination() << " (" << edgePtr->data->GetWeight() << ") --> ";
						edgePtr = edgePtr->next;
					}

					cout << "NULL" << endl;

					ptr = ptr->GetNext();
				}
			}
		}
		else
			cout << "The graph is empty." << endl;

		cout << endl;
	}
};


#endif
