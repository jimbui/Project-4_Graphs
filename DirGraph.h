#ifndef DIRGRAPH_H
#define DIRGRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <map>
#include "HashTable.h"
#include "Vertex.h"
#include "Edge.h"
#include "mQueue.h"

using namespace std;

template<class T> class DirGraph
{
private:
	HashTable<string, Vertex<T>*>* vertices;
	int sz;
	int edgeCount;

public:
	DirGraph(int Sz = 20) :sz(Sz)
	{
		vertices = new HashTable<string, Vertex<T>*>(sz, 0.5);

		// Test code...
		/*vertices->insert("V1", new Vertex<T>(44));
		vertices->insert("V2", new Vertex<T>(90));
		vertices->insert("V3", new Vertex<T>(46));
		vertices->insert("V4", new Vertex<T>(79));

		insert("V2", "V1", 10);
		insert("V3", "V1", 10);
		insert("V1", "V3", 20);*/

		// Note that unlike in the case of an undirected graph,
		// directed graphs can contain edges not pointing in both
		// directions (to either vertex).
	}

	~DirGraph()
	{
		delete vertices;
	}

	void buildGraph(){
        string line;
        ifstream myfile ("DirGraph.txt");
        if (myfile.is_open())
        {
            // Building array of vertices
            while(getline(myfile,line)){
                
				string str(line);
				string vname(str.substr(0, str.find_first_of(' ')));

				//cout << "vname: " << vname << endl;

				str = str.substr(str.find_first_of(' ') + 1, str.length());
				string data(str.substr(0, str.find_first_of(' ')));

				//cout << "vname data: " << data << endl;

				//vertices = new HashTable<string, Vertex<T>*>(sz, 0.5);
				vertices->insert(vname, new Vertex<T>(stoi(data)));
            }

			myfile.clear();
            myfile.seekg(0, ios::beg);

            while(getline(myfile,line)){

				string str(line);
				string vnamefore(str.substr(0, str.find_first_of(' ')));
				int StartPos = str.find_first_of('!');
				string linein(str.substr(StartPos+1, ' '));
                
				mQueue<string> Q;
				stringstream ss(linein);
				string linedata;
				while (getline(ss, linedata, ' ')) {
					Q.enqueue(linedata);
				}
                while (!Q.isEmpty()){
                    string ename = Q.dequeue();
					string weight = Q.dequeue();
					
					insert(vnamefore, ename, stoi(weight));
				}
			}

            myfile.close();
        }
        else cout << "Unable to open file";
    }

	// Accessors --------------------------------------------------------------------------
	bool empty() const { return sz == 0; };

	// Returns the out-degree of the vertex stored at v in the hash table.  Can throw errors, so be sure to catch them...  O(1)
	int outdegree(string v)
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

	// O(n^2) because # edges can be n^2 max
	int indegree(string v)
	{
		try
		{
			Vertex<T>* vertest = vertices->search(v);  // This line of code will throw an error if execution is unsuccessful.
			int innDegree = 0;

			// Get the rest of the vertices...
			for (int i = 0; i < vertices->arraySize; i++)
			{
				ChainNode<string, Vertex<T>*>* ptr = vertices->bucket[i].GetHead();

				// If the bucket is empty, nothing happens in this loop.
				while (ptr != nullptr)
				{
					Vertex<T>* current = ptr->Data();

					// Ensure that current != vertex at v
					if (current != vertest)
					{
						Node<Edge*>* edgePtr = current->adjacencyList->head;

						// Check each edge in each vertex
						while (edgePtr != nullptr)
						{
							// If the edge's destination is the vertex being searched, increment in-degree and break.
							if (edgePtr->data->destinationName == v)
							{
								innDegree++;
								break;
							}

							edgePtr = edgePtr->next;
						}
					}

					ptr = ptr->GetNext();
				}
			}

			return innDegree;
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

			// Return where the edge node's destination is v. (This is u --> v.)
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
		edgeCount = 0;
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
		if (w <= 0 || w > pow(10, 10))
			throw invalid_argument("Invalid weight.  Valid values are between 0 and 10 ^ 10 - 1.");

		// Try loop is used to determine whether u and v exist...
		try
		{
			// If either one of these two lines fail, an underflow exception will be thrown. --> (uVertex != NULL && vVertex != NULL)
			Vertex<T>* uVertex = vertices->search(u);
			Vertex<T>* vVertex = vertices->search(v);

			// Check to see whether the edge already exists before inserting a new one...
			Node<Edge*>* listPtrU = uVertex->adjacencyList->head;
			Node<Edge*>* listPtrV = vVertex->adjacencyList->head;

			if (listPtrU == nullptr && listPtrV == nullptr)  // insert the new item because one does not already exist
			{
				// In a directed graph, only one edge is inserted.
				Edge* newEdgeUToV = new Edge(w, u, v);

				uVertex->adjacencyList->insert(newEdgeUToV);

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

					// Weight cannot equal 0.  This throws an illegal argument exception.
					/*if (w == 0)
						uVertex->adjacencyList->del(listPtrU->data);*/

					break;
				}

				listPtrU = listPtrU->next;
			}

			// Else, enter this while-loop and get the other edge.  At this point, the only thing that will be modified is the edge's weight.
			while (listPtrV != nullptr)
			{
				if (listPtrV->data->destinationName == u)  // In this case, there is already an existing edge.
				{
					if (!foundU)
					{
						Edge* newEdgeUToV = new Edge(w, u, v);
						uVertex->adjacencyList->insert(newEdgeUToV);
					}
					else
						listPtrU->data->weight = w;

					listPtrV->data->weight = w;

					//}
					//else  // Simply remove the other connection.
					//{
					//	vVertex->adjacencyList->del(listPtrV->data);
					//}

					edgeCount++;
					return;
				}

				listPtrV = listPtrV->next;
			}

			// Insertion is okay.
			edgeCount++;
			Edge* newEdgeUToV = new Edge(w, u, v);
			uVertex->adjacencyList->insert(newEdgeUToV);
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

			vVertex->adjacencyList->clear();  // Clears the entire adjacency list

			// Note that in a directed graph, one cannot simply traverse the connections and get those vertices' edges.
			// One must instead traverse all vertices and get all edges pointing to v.  This will correspond to a runtime of
			// O(n^2).

			// Finds and deletes every edge in the hash table whose edge's destination = v.
			for (int i = 0; i < vertices->arraySize; i++)
			{
				ChainNode<string, Vertex<T>*>* ptr = vertices->bucket[i].GetHead();

				while (ptr != nullptr)
				{
					Vertex<T>* current = ptr->Data();

					if (current != vVertex)
					{
						Node<Edge*>* edgePtr = current->adjacencyList->head;

						while (edgePtr != nullptr)
						{
							if (edgePtr->data->destinationName == v)
							{
								current->adjacencyList->del(edgePtr->data);
								break;
							}

							edgePtr = edgePtr->next;
						}
					}

					ptr = ptr->GetNext();
				}
			}

			// Delete vertex out of hash table after all links to it have been removed.
			edgeCount--;
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