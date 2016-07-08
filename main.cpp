#include "HashTable.h"
#include "Graph.h"

int main()
{
	cout << "4 tcejorP maeT" << endl << endl;  // Insert new edge is the only algorithm for insertion required.  Hash table can cause collisions.

	// Get name --> vertex
	// Method --> Reset sets each vertex object flag to false.
	// Vertex contains linked list of edges... (edge->start = vertex)

	Graph<double>* calculator = new Graph<double>(23);

	HashTable<string, int>* hashBrown = new HashTable<string, int>(29, 0.5);

	hashBrown->insert("V1", 10);
	hashBrown->insert("V2", 20);

	// int val1 = hashBrown["V1"];

	hashBrown->DisplayElementList();

	hashBrown->clear();

	hashBrown->DisplayElementList();

	cin.get();
	return 0;
}