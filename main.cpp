#include "HashTable.h"
#include "Graph.h"
#include "DirGraph.h"

int main()
{
	cout << "4 tcejorP maeT" << endl << endl;  // Insert new edge is the only algorithm for insertion required.  Hash table can cause collisions.

	//test buildgraph for Directed Graph
	DirGraph<double>* GraphTest = new DirGraph<double>(23);
	GraphTest->buildGraph();
	GraphTest->DisplayAdjacencyList();

	//test buildgraph for UnDirected Graph
	Graph<double>* UnGraphTest = new Graph<double>(23);
	UnGraphTest->buildGraph();
	UnGraphTest->DisplayAdjacencyList();

	// Get name --> vertex
	// Method --> Reset sets each vertex object flag to false.
	// Vertex contains linked list of edges... (edge->start = vertex)

	/*Edge e1(10, "Duh", "Barf");
	Edge e2(14, "Barf", "Duh");

	bool duhr = e1 < e2;

	bool areEdgesEqual = e1.isUndirectedEqual(e2);

	DirGraph<double>* calculator = new DirGraph<double>(23);

	calculator->DisplayAdjacencyList();

	try
	{
		cout << "In-Degree of V1:  " << calculator->indegree("V1") << endl;
	}
	catch (const invalid_argument& e)
	{
		cerr << e.what() << endl;
	}

	try
	{
		cout << "Edge:  V1 <----> V2 = " << calculator->adjacent("V1", "V2") << endl;
	}
	catch (const invalid_argument& e)
	{
		cerr << e.what() << endl;
	}*/

	// Perform multiple insertions/deletions...
	/*while (true)
	{
		calculator->DisplayAdjacencyList();

		cout << "Use 'd' to delete and 'i' to insert:  ";
		char deleteOrInsert;
		cin >> deleteOrInsert;
		cin.ignore();

		if (deleteOrInsert == 'd')
		{
			string v;

			cout << "Enter vertex to delete:  ";
			cin >> v;
			cin.ignore();

			calculator->del(v);
		}
		else if (deleteOrInsert == 'i')
		{
			string u, v;
			double w;

			cout << "Enter Starting Vertex:  ";
			cin >> u;
			cin.ignore();
			cout << "Enter Destination Vertex:  ";
			cin >> v;
			cin.ignore();
			cout << "Enter Desired Weight:  ";
			cin >> w;
			cin.ignore();

			cout << endl;

			try
			{
				calculator->insert(u, v, w);
			}
			catch (const invalid_argument& e)
			{
				cerr << e.what() << endl;
			}
		}
		else
			cout << "Invalid input." << endl;

		cout << endl;
	}

	delete calculator;*/

	//HashTable<string, int>* hashBrown = new HashTable<string, int>(29, 0.5);

	//hashBrown->insert("V1", 10);
	//hashBrown->insert("V2", 20);

	//// int val1 = hashBrown["V1"];

	//hashBrown->DisplayElementList();

	//hashBrown->clear();

	//hashBrown->DisplayElementList();

	cin.get();
	return 0;
}