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
		std::cout << "    13. Insert vertices into graph." << std::endl ;
		std::cout << "    14. Delete item from graph." << std::endl ;
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
				undirectedGraph->DFS(vertex);
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
				undirectedGraph->BFS(vertex);
				}
		}

		else if (input == 9)
		{
			Clear() ;

			/*string vertex;

			if (undirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
			else {
				std::cout << "  Input a vertex:  " ;
				std::cin >> vertex;

				std::cout << "MST Traversal: " << " \n" ;
				undirectedGraph->MST(vertex);
				}*/
		}

		else if (input == 10)
		{
			Clear() ;

			if (undirectedGraph->empty()) {
				undirectedGraph->BuildGraph();
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
				
				std::cout << "  Enter first edge: ";
				std::cin >> input1;
				std::cout << "  Enter second edge: ";
				std::cin >> input2;
				std::cout << "  Enter weight: ";
				std::cin >> weight;

				undirectedGraph->insert(input1, input2, weight);

				std::cout << "  Element was inserted. " << " \n\n ";
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

				undirectedGraph->del(vertex);
				
				std::cout << "Vertex " << vertex << " was deleted and connections were updated. " << " \n\n";
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
		std::cout << "    9.  Returns shortest path between two vertices." << std::endl ;
		std::cout << "    10. Returns shortest distance between two vertices." << std::endl ;
		std::cout << "    11. Create graph from text file." << std::endl ; // what is the difference betweent this and 1?
		std::cout << "    12. Clear graph." << std::endl ;
		std::cout << "    13. Reset graph." << std::endl ;
		std::cout << "    14. Inset vertices into graph." << std::endl ;
		std::cout << "    15. Delete item from graph." << std::endl ;
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

				std::cout << "  DFS Traversal: " << " \n\n" ;
				DirectedGraph->DFS(vertex);
				DirectedGraph->reset() ;
				std::cout << "\n" ;
				}

		}

		else if (input == 8)
		{
			Clear() ;

			string vertex;

			if (DirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
			else {
				std::cout << "  Input a vertex:  " ;
				std::cin >> vertex;
				Clear() ;

				std::cout << "  BFS Traversal: " << " \n\n" ;
				DirectedGraph->BFS(vertex);
				DirectedGraph->reset() ;
				std::cout << "\n" ;
				}
		}

		else if (input == 9)
		{
			Clear() ;

			/*string vertex1;
			string vertex2;

			if (DirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
			else {
				std::cout << "  Enter first vertex: ";
				std::cin >> vertex1;
				std::cout << "  Enter second vertex: ";
				std::cin >> vertex2;

				}*/
		}

		else if (input == 10)
		{
			Clear() ;

			/*string vertex1;
			string vertex2;

			if (DirectedGraph->empty()) std::cout << "  The graph is empty. \n\n" ;
			else {
				std::cout << "  Enter first vertex: ";
				std::cin >> vertex1;
				std::cout << "  Enter second vertex: ";
				std::cin >> vertex2;

				}*/
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
				
				std::cout << "  Enter first edge: ";
				std::cin >> input1;
				std::cout << "  Enter second edge: ";
				std::cin >> input2;
				std::cout << "  Enter weight: ";
				std::cin >> weight;

				DirectedGraph->insert(input1, input2, weight);

				std::cout << "  Element was inserted. " << " \n\n ";
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

				DirectedGraph->del(vertex);
				
				std::cout << "Vertex " << vertex << " was deleted and connections were updated. " << " \n\n";
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
		else
		{
			Clear();
			std::cout << std::endl << "  Invalid input." << std::endl << std::endl;
		}
	}
}
