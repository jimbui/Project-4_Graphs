#include <cassert>
#include <iostream>
#include <string>

#include "Menu_Program.h"

// main functions.

Menu_Program::Menu_Program()
{
	Clear() ;
	Greeting() ;
	Main_Loop() ;
}

void Menu_Program::Clear()
{
	for(int i = 0 ; i < 100 ; i++) std::cout << std::endl ;
}

void Menu_Program::Greeting()
{
	std::cout << std::endl << "Project 04 Program - Graphs" << std::endl ;
	std::cout << std::endl << "    by:  Manuel Martinez , John Santoro , and Jim Bui" << std::endl << std::endl ;
}

void Menu_Program::Main_Loop()
{
	int input = 0 ;

	while (true)
	{
		std::cout << "  Main Menu" << std::endl << std::endl ;
		std::cout << "    1.  Prims algorithm" << std::endl ;
		std::cout << "    2.  Dijkstras algorithm" << std::endl ;
		std::cout << "    3.  Exit" << std::endl <<std::endl ;

		std::cout << "  " ;
		std::cin >> input ; std::cin.clear() ; std::cin.ignore() ;

		if (input == 1)
		{
			Clear() ;
			Prim_Algorithm() ;		
		}

		else if (input == 2)
		{
			Clear() ;
			Dijkstra_Algorithm() ;
		}

		else if (input == 3)
		{
			std::cout << std::endl << "  Exiting program..." << std::endl << std::endl ;
			break ;
		}

		else
		{
			Clear() ;
			std::cout << std::endl << "  Invalid input." << std::endl << std::endl ;
		}
	}
}

void Menu_Program::Prim_Algorithm()
{
	int input = 0 ;
	Graph<double>* undirectedGraph = new Graph<double>(23);

	while (true)
	{
		std::cout << "  Prim Algorithm Menu" << std::endl << std::endl ;
		std::cout << "    1.  Create graph." << std::endl ;
		std::cout << "    2.  Check if graph is empty." << std::endl ;
		std::cout << "    3.  Returns the degree of the vertex inputed." << std::endl ;
		std::cout << "    4.  Returns the number of edges in the graph." << std::endl ;
		std::cout << "    5.  Determines if the graph is connected." << std::endl ;
		std::cout << "    6.  Returns the weight of the edge connecting two vertices." << std::endl ;
		std::cout << "    7.  Performs DFS traversal starting on vertex inputed." << std::endl ;
		std::cout << "    8.  Performs BFS traversal starting on vertex inputed." << std::endl ;
		std::cout << "    9.  Performs MST traversal starting on vertex inputed." << std::endl ;
		std::cout << "    10. Create graph from text file." << std::endl ;
		std::cout << "    11. Clear graph." << std::endl ;
		std::cout << "    12. Reset graph." << std::endl ;
		std::cout << "    13. Insert edge into graph." << std::endl ;
		std::cout << "    14. Delete vertex from graph." << std::endl ;
		std::cout << "    15. Go back." << std::endl << std::endl ;

		std::cout << "  " ;
		std::cin >> input ; std::cin.clear() ; std::cin.ignore() ;

		if (input == 1)
		{
			Clear() ;

			std::cout << "  The graph has been created. " << " \n\n" ;
		}

		else if (input == 2)
		{
			Clear() ;

			if (undirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
			else std::cout << "  The graph is not empty " << " \n\n" ;
		}

		else if (input == 3)
		{
			Clear() ;

			string vertex;

			if (undirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
			else {
				std::cout << "  Input a vertex: " ;
				std::cin >> vertex;
				std::cout << "  Degree of vertex " << vertex << ": " << undirectedGraph->degree(vertex) << " \n\n";
				}
		}

		else if (input == 4)
		{
			Clear() ;

			if (undirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
			else std::cout << "  The number of edges in the graph are: " << undirectedGraph->EdgeCount() << " \n\n" ;
		}

		else if (input == 5)
		{
			Clear() ;

			if (undirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
			else std::cout << "Is the graph connected ? "<< (undirectedGraph->isConnected()?"Yes":"No") << " \n\n" ;

		}

		else if (input == 6)
		{
			Clear() ;
			
			string vertex1;
			string vertex2;

			if (undirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
			else {
				std::cout << "  Enter first vertex: ";
				std::cin >> vertex1;
				std::cout << "  Enter second vertex: ";
				std::cin >> vertex2;

				std::cout << "  The weight of the edge between vetices " << vertex1 << " and " << vertex2 << " is: " 
					<< undirectedGraph->adjacent(vertex1, vertex2) << " \n\n";
				}
		}

		else if (input == 7)
		{
			Clear() ;

			string vertex;

			if (undirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
			else {
				std::cout << "  Input a vertex:  " ;
				std::cin >> vertex;

				std::cout << "DFS Traversal: " << " \n" ;
					try
					{
						undirectedGraph->DFS(vertex);
					}
					catch (const invalid_argument& e)
					{
						cerr << e.what() << endl;
					}
				}

		}

		else if (input == 8)
		{
			Clear() ;

			string vertex;

			if (undirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
			else {
				std::cout << "  Input a vertex:  " ;
				std::cin >> vertex;

				std::cout << "BFS Traversal: " << " \n" ;
					try
					{
						undirectedGraph->BFS(vertex);
					}
					catch (const invalid_argument& e)
					{
						cerr << e.what() << endl;
					}
				}
		}

		else if (input == 9)
		{
			Clear() ;

			string vertex;
			Graph<double> *mst = new Graph<double>(undirectedGraph->vertices->NumberOfBuckets());

			if (undirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
			else {
				std::cout << "  Input a vertex:  " ;
				std::cin >> vertex;

				std::cout << "BFS Traversal of MST: " << " \n" ;
					try
					{
						mst = undirectedGraph->MST(vertex);
						mst->BFS(vertex);
					}
					catch (const invalid_argument& e)
					{
						cerr << e.what() << endl;
					}
				}
		}

		else if (input == 10)
		{
			Clear() ;

			if (undirectedGraph->empty()) {
				undirectedGraph->BuildGraphNew();
				std::cout << "  The graph was created from the text file. \n\n" ;
			}
			else std::cout << "  The graph was already created. " << " \n\n" ;
		}


		else if (input == 11)
		{
			Clear() ;

			if (undirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
			else {

				undirectedGraph->clear();
				std::cout << "  The graph was cleared. " << " \n\n" ;

				}
		}

		else if (input == 12)
		{
			Clear() ;

			if (undirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
			else {
				
				undirectedGraph->reset();
				std::cout << "  The graph was reset. " << " \n\n" ;

				}
		}
		
		else if (input == 13)
		{
			Clear() ;

			string input1;
			string input2;
			double weight;

			if (undirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
			else {
				
				std::cout << "  Enter first vertex: ";
				std::cin >> input1;
				std::cout << "  Enter second vertex: ";
				std::cin >> input2;
				std::cout << "  Enter weight: ";
				std::cin >> weight;

				try
				{
					undirectedGraph->insert(input1, input2, weight);
					std::cout << "  Element was inserted. " << " \n\n ";
				}
				catch (const invalid_argument& e)
				{
					cerr << e.what() << endl;
				}

			}
		}

		else if (input == 14)
		{
			Clear() ;

			string vertex;

			if (undirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
			else {
				
				std::cout << "  Enter vertex to be deleted: ";
				std::cin >> vertex;

				try
				{
					undirectedGraph->del(vertex);
				}
				catch (const invalid_argument& e)
				{
					cerr << e.what() << endl;
				}
				
				//std::cout << "Vertex " << vertex << " was deleted and connections were updated. " << " \n\n";
				}	
		}

		else if (input == 15)
		{
			Clear() ;
			break;
		}

		else
		{
			Clear() ;
			std::cout << std::endl << "  Invalid input." << std::endl << std::endl ;
		}
	}
}


void Menu_Program::Dijkstra_Algorithm()
{
	int input = 0;
	DirGraph<double>* DirectedGraph = new DirGraph<double>(23);

	while (true)
	{
		std::cout << "  Dijkstra Algorithm Menu" << std::endl << std::endl ;
		std::cout << "    1.  Create graph." << std::endl ; // what is the difference betweent this and 11?
		std::cout << "    2.  Check if graph is empty." << std::endl ;
		std::cout << "    3.  Returns the indegree of the vertex inputed." << std::endl ;
		std::cout << "    4.  Returns the outdegree of the vertex inputed." << std::endl ;
		std::cout << "    5.  Returns the number of edges in the graph." << std::endl ;
		std::cout << "    6.  Returns the weight of the edge connecting two vertices." << std::endl ;
		std::cout << "    7.  Performs DFS traversal starting on vertex inputed." << std::endl ;
		std::cout << "    8.  Performs BFS traversal starting on vertex inputed." << std::endl ;
		std::cout << "    9.  Returns shortest distance between two vertices." << std::endl ;
		std::cout << "    10. Returns shortest path between two vertices." << std::endl ;
		std::cout << "    11. Create graph from text file." << std::endl ; // what is the difference betweent this and 1?
		std::cout << "    12. Clear graph." << std::endl ;
		std::cout << "    13. Reset graph." << std::endl ;
		std::cout << "    14. Insert edge into graph." << std::endl ;
		std::cout << "    15. Delete vertex from graph." << std::endl ;
		std::cout << "    16. Go back." << std::endl << std::endl ;

		std::cout << "  ";
		std::cin >> input; std::cin.clear(); std::cin.ignore();

		if (input == 1) // this does nothing.
		{
			Clear() ;
			std::cout << "  The graph has been created. " << " \n\n" ;
		}

		else if (input == 2)
		{
			Clear() ;

			if (DirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
			else std::cout << "  The graph is not empty " << " \n\n" ;
		}

		else if (input == 3)
		{
			Clear() ;

			string vertex;

			if (DirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
			else {
				std::cout << "  Input a vertex: " ;
				std::cin >> vertex;
				std::cout << "  In degree of vertex " << vertex << ": " << DirectedGraph->indegree(vertex) << " \n\n";
				}
		}

		else if (input == 4)
		{
			Clear() ;

			string vertex;

			if (DirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
			else {
				std::cout << "  Input a vertex: " ;
				std::cin >> vertex;
				std::cout << "  Out degree of vertex " << vertex << ": " << DirectedGraph->outdegree(vertex) << " \n\n";
				}
		}

		else if (input == 5)
		{
			Clear() ;

			if (DirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
			else std::cout << "  The number of edges in the graph are: " << DirectedGraph->EdgeCount() << " \n\n" ;

		}

		else if (input == 6)
		{
			Clear() ;
			
			string vertex1;
			string vertex2;

			if (DirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
			else {
				std::cout << "  Enter first vertex: ";
				std::cin >> vertex1;
				std::cout << "  Enter second vertex: ";
				std::cin >> vertex2;

				std::cout << "  The weight of the edge between vetices " << vertex1 << " and " << vertex2 << " is: " 
					<< DirectedGraph->adjacent(vertex1, vertex2) << " \n\n";
				}
		}

		else if (input == 7)
		{
			Clear() ;

			string vertex;

			if (DirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
			else {
				std::cout << "  Input a vertex:  " ;
				std::cin >> vertex;
				Clear() ;

				try
				{
					std::cout << "  DFS Traversal: " << " \n\n" ;
					DirectedGraph->DFS(vertex);
					DirectedGraph->reset() ;
					std::cout << "\n" ;
				}
				catch (const invalid_argument& e)
				{
					cerr << e.what() << endl;
				}

				}

		}

		else if (input == 8)
		{
			Clear() ;

			string vertex;

			if (DirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;

			else 
			{
				std::cout << "  Input a vertex:  " ;
				std::cin >> vertex;
				Clear() ;

				try
				{
					std::cout << "  BFS Traversal: " << " \n\n" ;
					DirectedGraph->BFS(vertex);
					DirectedGraph->reset() ;
					std::cout << "\n" ;
				}
				catch (const invalid_argument& e)
				{
					cerr << e.what() << endl;
				}
	
			}
		}

		else if (input == 9)
		{
			Clear() ;

			string start_vertex ;
			string end_vertex ;

			if (DirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;

			else 
			{
				std::cout << "  Enter starting vertex: ";
				std::cin >> start_vertex;
				Clear() ;
				std::cout << "  Enter ending vertex: ";
				std::cin >> end_vertex;
				Clear() ;

				try
				{
					DirectedGraph->shortPath(start_vertex , end_vertex , false) ;
				}
				catch (const invalid_argument& e)
				{
					cerr << e.what() << endl;
				}
				
			}
		}

		else if (input == 10)
		{
			Clear() ;

			string start_vertex ;
			string end_vertex ;

			if (DirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;

			else 
			{
				std::cout << "  Enter starting vertex: ";
				std::cin >> start_vertex;
				Clear() ;
				std::cout << "  Enter ending vertex: ";
				std::cin >> end_vertex;
				Clear() ;

				try
				{
					DirectedGraph->shortPath(start_vertex , end_vertex , true) ;
				}
				catch (const invalid_argument& e)
				{
					cerr << e.what() << endl;
				}
			}
		}


		else if (input == 11) // can only build if it is empty.
		{
			Clear() ;

			if (DirectedGraph->empty()) 
			{
				DirectedGraph->BuildGraphNew();
				std::cout << "  The graph was created from the text file. \n\n" ;
			}
			else std::cout << "  The graph was already created. " << " \n\n" ;
		}

		else if (input == 12)
		{
			Clear() ;

			if (DirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
			else {

				DirectedGraph->clear();
				std::cout << "  The graph was cleared. " << " \n\n" ;

				}
		}

		else if (input == 13)
		{
			Clear() ;

			if (DirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
			else {
				
				DirectedGraph->reset();
				std::cout << "  The graph was reset. " << " \n\n" ;

				}
		}
		
		else if (input == 14)
		{
			Clear() ;

			string input1;
			string input2;
			double weight;

			if (DirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
			else {
				
				std::cout << "  Enter first vertex: ";
				std::cin >> input1;
				std::cout << "  Enter second vertex: ";
				std::cin >> input2;
				std::cout << "  Enter weight: ";
				std::cin >> weight;

				try
				{
					DirectedGraph->insert(input1, input2, weight);
					std::cout << "  Element was inserted. " << " \n\n ";
				}
				catch (const invalid_argument& e)
				{
					cerr << e.what() << endl;
				}

			}
		}

		else if (input == 15)
		{
			Clear() ;

			string vertex;

			if (DirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
			else {
				
				std::cout << "  Enter vertex to be deleted: ";
				std::cin >> vertex;

				try
				{
					DirectedGraph->del(vertex);
				}
				catch (const invalid_argument& e)
				{
					cerr << e.what() << endl;
				}
				
				//std::cout << "Vertex " << vertex << " was deleted and connections were updated. " << " \n\n";
				}	
		}
		else if (input == 16)
		{
			Clear();
			break;
		}
		else if (input == 17)
		{
			Clear();
			DirectedGraph->DisplayAdjacencyList() ;
			if(DirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
		}
		else if (input == 18)
		{
 			Clear() ;
 			// std::cout << DirectedGraph->checker("A" , "F" , false) << " \n\n" ;
 			if (DirectedGraph->checker("A" , "F" , false) == 3)
 			{
 			std::cout << " I AM WORKING AND I DON'T KNOW WHY. \n\n" ;
 			}
 			else std::cout << " I AM NOT WORKING AND I DON'T KNOW WHY. \n\n" ;
 			
		}
		else
		{
			Clear();
			std::cout << std::endl << "  Invalid input." << std::endl << std::endl;
		}
	}
}
