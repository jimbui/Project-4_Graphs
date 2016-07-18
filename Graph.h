#ifndef GRAPH_H
#define GRAPH_H


#include <math.h> 
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <sstream>
#include "HashTable.h"
#include "mQueue.h"
#include "Vertex.h"
#include "Edge.h"

using namespace std;

template<class T> class Graph
{
private:
	HashTable<string, Vertex<T>*>* vertices;
	int sz;
	int edgeCount;

	// Helper method for MST.  Gets a set of connected vertices.
	HashTable<string, Vertex<T>*>* BFSGetVertices(string v)
	{
		HashTable<string, Vertex<T>*>* verticesInBFS = new HashTable<string, Vertex<T>*>(sz, 0.5);

		Vertex<T>* start = vertices->search(v);
		// cout << v << ":  " << start->data << endl;
		start->visited = true;
		verticesInBFS->insert(v, start);

		mQueue<Vertex<T>*> Q;
		Q.enqueue(start);

		while (!Q.isEmpty())
		{
			Vertex<T>* vVertex = Q.dequeue();

			Node<Edge*>* edgePtr = vVertex->adjacencyList->head;

			while (edgePtr != nullptr)
			{
				string w = edgePtr->data->destinationName;
				Vertex<T>* wVertex = vertices->search(w);

				if (!wVertex->visited)
				{
					// cout << w << ":  " << wVertex->data << endl;
					wVertex->visited = true;
					verticesInBFS->insert(w, wVertex);

					Q.enqueue(wVertex);
				}

				edgePtr = edgePtr->next;
			}
		}

		reset();
		return verticesInBFS;
	}

	// Resets everything after a call to MST(...)
	void ResetForPrimsAlgorithm()
	{
		for (int i = 0; i < vertices->arraySize; i++)
		{
			ChainNode<string, Vertex<T>*>* ptr = vertices->bucket[i].GetHead();

			while (ptr != nullptr)  // Checks each item in the chained hash table
			{
				Vertex<T>* current = ptr->Data();

				current->visited = false;
				current->parent = nullptr;
				current->edgePointer = nullptr;

				// Reset cheapest connection to infinity after call to mst...
				current->cheapestConnection = 6.66 * pow(10, 66);

				Node<Edge*>* edgePtr = current->adjacencyList->head;

				while (edgePtr != nullptr)
				{
					edgePtr->data->edgeConnectingVToOtherVertex = false;

					edgePtr = edgePtr->next;
				}

				ptr = ptr->GetNext();
			}
		}
	}

public:
	Graph(int Sz = 20) :sz(Sz), edgeCount(0)
	{
		vertices = new HashTable<string, Vertex<T>*>(sz, 0.5);

		// Test code...
		/*vertices->insert("V1", new Vertex<T>(44));
		vertices->insert("V2", new Vertex<T>(90));
		vertices->insert("V3", new Vertex<T>(46));
		vertices->insert("V4", new Vertex<T>(79));

		insert("V1", "V3", 10);
		insert("V1", "V4", 10);*/
		// insert("V4", "V2", 10);
		// insert("V2", "V3", 10);
	}

	~Graph()
	{
		delete vertices;
	}

	// Accessors --------------------------------------------------------------------------
	bool empty() const { return vertices->numElements == 0; };

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

	// Checks to see if the graph is connected by performing a BFS on 1 vertex and ensuring that all vertices are visited afterward.  O(n^2).
	// Note that this function automatically resets the graph, but BFS and DFS don't.
	bool isConnected()
	{
		if (sz > 0)
		{
			int numVerticesVisited = 0;
			Vertex<T>* start;

			// Get the starting vertex
			for (int i = 0; i < vertices->arraySize; i++)
			{
				ChainNode<string, Vertex<T>*>* ptr = vertices->bucket[i].GetHead();

				bool breakThis = false;

				while (ptr != nullptr)
				{
					start = ptr->Data();
					breakThis = true;
					break;
				}

				if (breakThis)
					break;
			}

			
			// cout << v << ":  " << start->data << endl;
			start->visited = true;
			numVerticesVisited++;

			mQueue<Vertex<T>*> Q;
			Q.enqueue(start);

			while (!Q.isEmpty())
			{
				Vertex<T>* vVertex = Q.dequeue();

				Node<Edge*>* edgePtr = vVertex->adjacencyList->head;

				while (edgePtr != nullptr)
				{
					string w = edgePtr->data->destinationName;
					Vertex<T>* wVertex = vertices->search(w);

					if (!wVertex->visited)
					{
						// cout << w << ":  " << wVertex->data << endl;
						wVertex->visited = true;
						numVerticesVisited++;

						Q.enqueue(wVertex);
					}

					edgePtr = edgePtr->next;
				}
			}

			reset();
			return (numVerticesVisited == vertices->numElements);
		}
		else
			return false;  // Should probably throw an error.
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

	// Performs depth-first search on vertex v.  
	void DFS(string v)
	{
		try
		{
			Vertex<T>* current = vertices->search(v);
			cout << v << ":  " << current->data << endl;
			current->visited = true;

			Node<Edge*>* edgePtr = current->adjacencyList->head;

			while (edgePtr != nullptr)
			{
				string w = edgePtr->data->destinationName;
				
				// The next vertex will always exist as long as insertion/deletion was done properly.
				Vertex<T>* nextVertex = vertices->search(w);

				if (!nextVertex->visited)
					DFS(w);

				edgePtr = edgePtr->next;
			}
		}
		catch (const underflow_error& e)
		{
			throw invalid_argument("Vertex does not exist.  Have a nice day.");
		}
	}

	// Performs a breadth-first search on vertex v.
	void BFS(string v)
	{
		try
		{
			Vertex<T>* start = vertices->search(v);
			cout << v << ":  " << start->data << endl;
			start->visited = true;

			mQueue<Vertex<T>*> Q;
			Q.enqueue(start);

			while (!Q.isEmpty())
			{
				Vertex<T>* vVertex = Q.dequeue();

				Node<Edge*>* edgePtr = vVertex->adjacencyList->head;

				while (edgePtr != nullptr)
				{
					string w = edgePtr->data->destinationName;
					Vertex<T>* wVertex = vertices->search(w);

					if (!wVertex->visited)
					{
						cout << w << ":  " << wVertex->data << endl;
						wVertex->visited = true;

						Q.enqueue(wVertex);
					}

					edgePtr = edgePtr->next;
				}
			}
		}
		catch (const underflow_error& e)
		{
			throw invalid_argument("Vertex does not exist.  Have a nice day.");
		}
	}

	// Creates the MST of an undirected graph.  Simple Prim's algorithm results in O(n^2) running time.
	Graph<T>* MST(string v)
	{
		try
		{
			// Immediately throw error if vertex v is not in graph.
			Vertex<T>* vVertex = vertices->search(v);

			// Contains only the vertices in the MST --> see 1 ---------------------------------------------------------------
			HashTable<string, Vertex<T>*>* mstVertices = BFSGetVertices(v);
			// End 1 ---------------------------------------------------------------------------------------------------------
			
			int vertexCount = mstVertices->numElements;

			// If there is only one vertex, return a new graph containing that vertex.
			if (vertexCount == 1)
			{
				Graph<T>* newGraph = new Graph<T>(sz);
				newGraph->vertices->insert(v, vVertex);

				return newGraph;
			}

			// Gets the number of vertices to iterate through. --> see 2 -----------------------------------------------------
			string* vertexKeys = new string[vertexCount];
			bool* isVertexUsed = new bool[vertexCount];

			// Gets all vertices and stores them in an array.  Note that the key to each vertex is kept for reference later.
			// Note that since all of the vertices will exist in the MST, they will be added here.
			int currentVertex = 0;
			Graph<T>* mst = new Graph<T>(sz);

			for (int i = 0; i < mstVertices->arraySize; i++)
			{
				ChainNode<string, Vertex<T>*>* ptr = vertices->bucket[i].GetHead();

				while (ptr != nullptr)  // Checks each item in the chained hash table
				{
					Vertex<T>* current = ptr->Data();

					vertexKeys[currentVertex] = current->adjacencyList->head->data->originName;
					isVertexUsed[currentVertex] = false;

					mst->vertices->insert(vertexKeys[currentVertex], current->GetPureVertex());

					ptr = ptr->GetNext();
					currentVertex++;
				}
			}
			
			// Initialize one mst vertex so that the algorithm will run from that point
			// Vertex<T>* vVertex = mstVertices->search(v);

			vVertex->cheapestConnection = 0;
			vVertex->parent = nullptr;
			
			// While the element list is not empty, build the MST
			int numElementsRemaining = vertexCount;
			// End 2 ---------------------------------------------------------------------------------------------------------

			while (numElementsRemaining > 0)
			{
				// Finds and removes vertex with least possible cost --> see 3A ----------------------------------------------
				double minCost = 6.66 * pow(10, 66);
				int mindex = 0;

				// Find the vertex with the lowest possible key value --> key = connection with least weight
				for (int i = 0; i < vertexCount; i++)
				{
					if (!isVertexUsed[i])
					{
						Vertex<T>* current = mstVertices->search(vertexKeys[i]);

						if (minCost > current->cheapestConnection)
						{
							mindex = i;
							minCost = current->cheapestConnection;
						}
					}
				}

				// Remove that vertex from the hash table
				Vertex<T>* duhVertex = mstVertices->Remove(vertexKeys[mindex]);
				numElementsRemaining--;
				isVertexUsed[mindex] = true;
				// End 3A ----------------------------------------------------------------------------------------------------

				// Get the cheapest connection
				/*Node<Edge*>* edgePtr = duhVertex->adjacencyList->head;
				double minWeight = 6.66 * pow(10, 66);
				Edge* cheapShot = nullptr;

				while (edgePtr != nullptr)
				{
					if (minWeight > edgePtr->data->weight)
					{
						cheapShot = edgePtr->data;
						minWeight = cheapShot->weight;
					}

					edgePtr = edgePtr->next;
				}*/

				// Add duh vertex to the MST, and add the first edge who's not a part of the graph already...
				// mst->vertices->insert(vertexKeys[mindex], duhVertex->GetPureVertex());

				// Add an edge if its minimum weight is not equal to the flag value --> see 3B -------------------------------
				if (duhVertex->edgePointer != nullptr && !duhVertex->edgePointer->edgeConnectingVToOtherVertex)
				{
					// duhVertex->edgePointer->edgeConnectingVToOtherVertex = true;
					// duhVertex->edgePointer = cheapShot;  // Make E[v] point to edge of least cost

					// duhVertex->cheapestConnection = cheapShot->weight;
					mst->insert(duhVertex->edgePointer->originName, duhVertex->edgePointer->destinationName, duhVertex->edgePointer->weight);
				}
				// End 3B ----------------------------------------------------------------------------------------------------
			
				// Begin 3C --------------------------------------------------------------------------------------------------
				// Loop over all other edges.  If the edge's destination vertex is in the hash table (see new method)...
				Node<Edge*>* edgePtr = duhVertex->adjacencyList->head;

				while (edgePtr != nullptr)
				{
					// Replace edge wherever it is necessary
					Edge* currentEdge = edgePtr->data;

					if (mstVertices->CheckExistenceOf(currentEdge->destinationName) &&
						edgePtr->data->weight < mstVertices->search(currentEdge->destinationName)->cheapestConnection)
					{
						Vertex<T>* wVertex = mstVertices->search(currentEdge->destinationName);
						wVertex->cheapestConnection = currentEdge->weight;
						wVertex->edgePointer = currentEdge;
					}

					edgePtr = edgePtr->next;
				}
				// End 3C ----------------------------------------------------------------------------------------------------

				int blub = 0;
			}

			// O(|E| + |V|)
			ResetForPrimsAlgorithm();
			return mst;
		}
		catch (const underflow_error& e)
		{
			throw invalid_argument("Vertex in argument does not exist.");
		}
	}

	// Mutators --------------------------------------------------------------------------
	void BuildGraph()
	{
		string line;
		ifstream myfile("DirGraph.txt");

		if (myfile.is_open())
		{
			// Building array of vertices

			while (getline(myfile, line))
			{
				string str(line);
				string vname(str.substr(0, str.find_first_of(' ')));

				str = str.substr(str.find_first_of(' ') + 1, str.length());
				string data(str.substr(0, str.find_first_of(' ')));

				vertices->insert(vname, new Vertex<T>(stod(data)));
			}

			myfile.clear();
			myfile.seekg(0, ios::beg);

			while (getline(myfile, line))
			{
				string str(line);
				string vnamefore(str.substr(0, str.find_first_of(' ')));

				int StartPos = str.find_first_of('!');
				string linein(str.substr(StartPos + 1, ' '));

				mQueue<string> Q;
				stringstream ss(linein);
				string linedata;

				while (getline(ss, linedata, ' '))
				{
					Q.enqueue(linedata);
				}

				while (!Q.isEmpty())
				{
					string ename = Q.dequeue();
					string weight = Q.dequeue();

					insert(vnamefore, ename, stod(weight));
				}
			}
			myfile.close();
		}
		else
			cout << "Unable to open file";
	}

	void clear()  // O(n)
	{
		vertices->clear();
		sz = 0;
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
				current->parent = nullptr;

				// Reset cheapest connection to infinity after call to mst...
				current->cheapestConnection = 6.66 * pow(10, 66);

				ptr = ptr->GetNext();
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
			int numEdgesDeleted = 0;

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
						numEdgesDeleted++;
						break;  // There will never be duplicate edges in the same list.
					}

					edgeNodeDest = edgeNodeDest->next;
				}

				edgeNode = edgeNode->next;
			}

			// Delete vertex out of hash table after all links to it have been removed.
			edgeCount -= numEdgesDeleted / 2;
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
