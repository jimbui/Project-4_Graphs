#ifndef DIRGRAPH_H
#define DIRGRAPH_H

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
#include "MaxHeapTree.h"

using namespace std;

template<class T> class DirGraph
{
private:
	HashTable<string, Vertex<T>*>* vertices;
	int sz;
	int edgeCount;

public:
	DirGraph(int Sz = 20) :sz(Sz), edgeCount(0)
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

	// Accessors --------------------------------------------------------------------------
	bool empty() const { return vertices->numElements == 0; };

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
	
	void shortPath(string u , string v , bool path) // implementing djikstra's algorithm.
	{
		if (sz > 0) // check to see if the graph is empty or not.
		{
			Vertex<T>* current ;

			try // see if nodes exist.
			{
				current = vertices->search(v) ;
				current = vertices->search(u) ; // current is now the starting node.
			}

			catch (const underflow_error& e) // if nodes do not exist.
			{
				std::cout << "  The node(s) do(es) not exist. \n\n" ;
				return ; // exit function.
			}

			// the start node is now initialized.

			djikstras_initialize() ; // makes all nodes unvisited and infinity distance away.
			current->cheapestConnection = 0 ; // the starting node willk have a distance of zero from itself.
			current->name = u ;
			MaxHeapTree<std::string> edge_weight_tree(sz) ; // this will store nodes by key value , with smallest at the top.
			MaxHeapTree<std::string> visit_tree(sz) ; // these are the nodes to visit.

			// go to current node (which starts as first node in the beginning).  fill tree with adjacency list , update 
			// distance , and set them to visited.  set current to visited.  set current to least value in heap tree.  repeat 
			// until the heap tree is empty.

			bool flag = true ;

			while(flag == true)
			{
				// std::cout << "\nthis loop? \n" ;
				Node<Edge*>* edgePtr = current->adjacencyList->head ; // finds the first value in the adjacency list.

				while (edgePtr != NULL) // fills the max heap tree with edges from node , with lowest edge as the max.
				{   
					edge_weight_tree.insert((double)1 / (double)edgePtr->data->GetWeight() , edgePtr->data->GetDestination() , edgePtr->data->GetWeight()) ;
					std::cout << "\n  inserting: " << edgePtr->data->GetDestination() << " \n" ;
					// previous line inserts the node and edge to the heap tree.  since this is technically a max heap tree ,
					// we use the inverse value as a key to create a "min" heap tree.
					edgePtr = edgePtr->next ; // go to next value.
				}

				current->visited = true ; 
				edge_weight_tree.display_tree() ;

				// now visit each node in the heap tree by distance , and update the distance.  add new nodes as necessary.

				while (!edge_weight_tree.empty()) // while this tree still has elements.
				{
					int weight_temp = edge_weight_tree.return_weight() ; // weight of the first item in the heap.
					string name_temp = edge_weight_tree.delMax() ; // deletes first item and stores the name.
					Vertex<T>* next = vertices->search(name_temp) ; // goes to node that was just deleted.
					next->name = name_temp ;

					if (current->cheapestConnection + weight_temp < next->cheapestConnection) // if the newly calculated distance is smaller.
					{   // also update the parent for tracking purposes.
						// std::cout << "\ncurrent->GetData() = " << current->GetData() << " \n" ;
						std::cout << "next->GetData() = " << next->GetData() << " \n" ;
						// std::cout << current->cheapestConnection << " " << weight_temp << " < " << next->cheapestConnection << "   " << current->cheapestConnection + weight_temp << " \n\n" ;
						next->cheapestConnection = current->cheapestConnection + weight_temp ; // set new shortest distance.
						next->parent = current ;
					}

					if (next->visited != true) // if the next node has yet to be visited , throw it into the heap tree.
					{
						std::cout << "\n  inserting: " << name_temp << " \n" ;
						visit_tree.insert((double)1 / (double)next->cheapestConnection , name_temp , next->cheapestConnection) ;
						next->visited = true ; // don't want to add the same node multiple times.
					}
				}

				// edge_weight_tree.clear() ;

				if (visit_tree.empty()) 
				{
					flag = false ;
				}

				else 
				{
					current = vertices->search(visit_tree.getMax()) ;
					visit_tree.delMax() ;
				}
			}

			current  = vertices->search(v) ;
			// djikstras_display() ;
			for (int i = 0 ; i < 200 ; i++) std::cout << "\n\n" ;
			// djikstras_display() ;

			if (path == false) std::cout << "\n  Distance to " << v << " is " << current->cheapestConnection << ". \n\n" ;

			else if (path == true) // this is for path retrieval.
			{
				std::cout << "\n  Shortest path: " ;

				while(current != nullptr)
				{	
					std::cout << current->name << " <- " ;
					current = current->parent ;
				}

				std::cout << "START \n\n" ;
			}
		}

		else std::cout << "  The graph is empty. \n" ; // if the graph is empty.
	}
	
	void djikstras_initialize()  // O(n)
	{
		for (int i = 0; i < vertices->arraySize; i++)
		{
			ChainNode<string, Vertex<T>*>* ptr = vertices->bucket[i].GetHead();

			while (ptr != nullptr)  // Checks each item in the chained hash table
			{
				Vertex<T>* current = ptr->Data();

				current->visited = false;
				current->cheapestConnection = 9001 * 9001 ; // over 9000.
				ptr = ptr->GetNext() ;
			}
		}
	}

	void djikstras_display()  // O(n)
	{
		for (int i = 0; i < vertices->arraySize; i++)
		{
			ChainNode<string, Vertex<T>*>* ptr = vertices->bucket[i].GetHead();

			while (ptr != nullptr)  // Checks each item in the chained hash table
			{
				Vertex<T>* current = ptr->Data();
				std::cout << "  " << current->data << " = " << current->cheapestConnection << "\n" ;
				ptr = ptr->GetNext() ;
			}
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

				//cout << "vname: " << vname << endl;

				str = str.substr(str.find_first_of(' ') + 1, str.length());
				string data(str.substr(0, str.find_first_of(' ')));

				//cout << "vname data: " << data << endl;

				//vertices = new HashTable<string, Vertex<T>*>(sz, 0.5);

				vertices->insert(vname, new Vertex<T>(stoi(data)));
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

					insert(vnamefore, ename, stoi(weight));
				}
			}
			myfile.close();
		}
		else 
			cout << "Unable to open file";
	}

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
			// Node<Edge*>* listPtrV = vVertex->adjacencyList->head;

			if (listPtrU == nullptr /*&& listPtrV == nullptr*/)  // insert the new item because one does not already exist
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

					listPtrU->data->weight = w;
					return;
					// break;
				}

				listPtrU = listPtrU->next;
			}

			// Else, enter this while-loop and get the other edge.  At this point, the only thing that will be modified is the edge's weight.
			//while (listPtrV != nullptr)
			//{
			//	if (listPtrV->data->destinationName == u)  // In this case, there is already an existing edge.
			//	{
			//		if (!foundU)
			//		{
			//			Edge* newEdgeUToV = new Edge(w, u, v);
			//			uVertex->adjacencyList->insert(newEdgeUToV);
			//		}
			//		else
			//			listPtrU->data->weight = w;

			//		listPtrV->data->weight = w;

			//		//}
			//		//else  // Simply remove the other connection.
			//		//{
			//		//	vVertex->adjacencyList->del(listPtrV->data);
			//		//}

			//		edgeCount++;
			//		return;
			//	}

			//	listPtrV = listPtrV->next;
			//}

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
								edgeCount--;
								break;
							}

							edgePtr = edgePtr->next;
						}
					}

					ptr = ptr->GetNext();
				}
			}

			// Delete vertex out of hash table after all links to it have been removed.
			vertices->erase(v);
		}
		catch (const underflow_error& e)
		{
			cout << "This vertex does not exist, so it can't be deleted." << endl;
		}
	}
	
	void BuildGraphNew()
	{
		vertices->insert("A", new Vertex<T>(1)) ;
		vertices->insert("B", new Vertex<T>(2)) ;
		vertices->insert("C", new Vertex<T>(3)) ;
		vertices->insert("D", new Vertex<T>(4)) ;
		vertices->insert("E", new Vertex<T>(5)) ;
		vertices->insert("F", new Vertex<T>(6)) ;

		insert("A", "B", 1);
		insert("A", "C", 4);
		insert("B", "C", 1);
		insert("B", "D", 1);
		insert("B", "E", 2);
		insert("C", "E", 3);
		insert("D", "F", 1);
		insert("E", "D", 3);
		insert("E", "F", 2);
		insert("F" , "A" , 99) ;
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
