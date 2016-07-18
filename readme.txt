Project 04 - Graphs
Programeers:  Manuel Martinez, John Santoro, and Jim Bui

The driver program, main.cpp, utilizes a menu program class(Menu_Program.h and Menu_Program.cpp) in order to display information about the Prim's Algorithm and Dijkstra’s algorithm.  The command processor requires the user to enter a numeric input in order to progress to the next menu or perform a certain function.  For example, 

  Main Menu

    1.  Prims Algorithm
    2.  Dijkstras Algorithm
    3.  Exit
  
> [A numeric value expected]

Typing in 1 and hitting enter on this menu will give the user access to all of the functions associated with the Prim's Algorithm structure.  This is the full menu layout, along with a description of what each of the functions accomplish:

1.  Prims Algorithm
--> Goes to
		1.  Create graph.
		2.  Check if graph is empty.
		3.  Returns the degree of the vertex inputed.
		4.  Returns the number of edges in the graph.
		5.  Determines if the graph is connected.
		6.  Returns the weight of the edge connecting two vertices.
		7.  Performs DFS traversal starting on vertex inputed.
		8.  Performs BFS traversal starting on vertex inputed.
		9.  Performs MST traversal starting on vertex inputed.
		10. Create graph from text file.
		11. Clear graph.
		12. Reset graph.
		13. Insert vertices into graph.
		14. Delete item from graph.
		15. Go back.
<-- Goes Back



2.  Dijkstra's Algorithm
--> Goes to
    	1.  Create graph.
		2.  Check if graph is empty.
		3.  Returns the indegree of the vertex inputed.
		4.  Returns the outdegree of the vertex inputed.
		5.  Returns the number of edges in the graph.
		6.  Returns the weight of the edge connecting two vertices.
		7.  Performs DFS traversal starting on vertex inputed.
		8.  Performs BFS traversal starting on vertex inputed.
		9.  Returns shortest path between two vertices.
		10. Returns shortest distance between two vertices.
		11. Create graph from text file.
		12. Clear graph.
		13. Reset graph.
		14. Inset vertices into graph.
		15. Delete item from graph.
		16. Go back.
<-- Goes Back


3. Exit 




































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

			else 
			{
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
				DirectedGraph->shortPath(start_vertex , end_vertex) ;
			}
		}

		else if (input == 10)
		{
			Clear() ;
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



void shortPath(string u , string v)
	{
		if (sz > 0)
		{
			MaxHeapTree<std::string> why_is_the_rum_gone(sz) ; // this is the tree compare edge weights , will be reset many times.
			MaxHeapTree<std::string> no_really_why(sz) ; // this is the path of least resistance.
			int i = 0 ;

			try
			{
				Vertex<T>* current = vertices->search(v) ; // just to see if this exists.
				current = vertices->search(u) ; // start at this node.
				// Node<Edge*>* edgePtr = current->adjacencyList->head ; // get adjacency list.
				djikstras() ; // sets distance to over 9000 (infinity).
				current->cheapestConnection = 0 ; // except this one , this be zed.
				no_really_why.insert(0 , u , 0) ;
				bool flag = true ;

				while (!no_really_why.empty())
				{
					std::cout << "\nTHIS IS FROM: " << current->GetData() << " XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx\n\n" ;
					Node<Edge*>* edgePtr = current->adjacencyList->head ;
					// std::cout << "1 \n\n" ;

					while (edgePtr != NULL) // fills the max heap tree with edges from first node , with lowest edge as the max.
					{
						int i = edgePtr->data->GetWeight() ;
						cout << edgePtr->data->GetDestination() << " (" << edgePtr->data->GetWeight() << ") --> NULL \n";
						why_is_the_rum_gone.insert((double)1 / (double)edgePtr->data->GetWeight() , edgePtr->data->GetDestination() , i) ;
						// why_is_the_rum_gone.insert(key_in , data_in) ;
						
						// if (current->cheapestConnection + )
						edgePtr = edgePtr->next ;
					}

					why_is_the_rum_gone.display_tree() ;

					while (!why_is_the_rum_gone.empty())
					{
						int weight_temp = why_is_the_rum_gone.return_weight() ;
						std::cout << "return_weight(): " << return_weight() ;
						string name_temp = why_is_the_rum_gone.delMax() ;
						Vertex<T>* next = vertices->search(name_temp) ;

						if (current->cheapestConnection + weight_temp < next->cheapestConnection)
						{
							std::cout << "\ncurrent->GetData() = " << current->GetData() << " \n" ;
							std::cout << "next->GetData() = " << next->GetData() << " \n" ;
							std::cout << current->cheapestConnection << " " << weight_temp << " < " << next->cheapestConnection << "   " << current->cheapestConnection + weight_temp << " \n\n" ;
							next->cheapestConnection = current->cheapestConnection + weight_temp ;
						}

						if (next->visited != true) 
						{
							// std::cout << "2: " << (double)1 / (double)next->cheapestConnection << "   " << name_temp << "   " << next->cheapestConnection << " \n\n" ;
							no_really_why.insert((double)1 / (double)next->cheapestConnection , name_temp , next->cheapestConnection) ;
							next->visited = true ;
							std::cout << "INSERTED " << name_temp << "\n" ;
						}
					}

					current->visited = true ;
					// no_really_why.display_tree() ;


					// if (flag == true)
					// {
					// 	flag = false ;
					// 	no_really_why.delMax() ;
					// 	no_really_why.delMax() ;
					// }

					// no_really_why.display_tree() ;
					current = vertices->search(no_really_why.getMax()) ;
					no_really_why.delMax() ;
				}

				djikstras_display() ;

				current  = vertices->search(v) ;
				std::cout << "  Distance to " << v << " is " << current->cheapestConnection << ". \n\n" ;
				// djikstras_display() ;

				// why_is_the_rum_gone.display_tree() ;
				// std::cout << why_is_the_rum_gone.delMax() << "\n" ;
				// why_is_the_rum_gone.display_tree() ;
				std::cout << "\n" ;

				// std::cout << "  double: " << (double)1 / (double)64 << " \n\n" ;


				// std::cout << "this is getdata(): " << start->GetData() << "\n\n" ; // this gives the value of the node... which does literally nothing.
				// std::cout << "this is start->data: " << start->data << " \n\n" ;
				// ChainNode<string, Vertex<T>*>* ptr = vertices->bucket[i].GetHead();
				// no_really_why.insert()
				// why_is_the_rum_gone.insert(key_in , data_in) ;
				reset() ;
			}

			catch (const underflow_error& e)
			{
				// std::cout << "  The vertex or vertices do not exist. \n\n" ;
				Vertex<T>* current  = vertices->search(v) ;
				std::cout << "  Distance to " << v << " is " << current->cheapestConnection << ". \n\n" ;
				djikstras_display() ;
			}
		}

		else std::cout << "  The graph is empty. \n" ;

		/*if (sz > 0) // How to get all of the vertices in the graph...
		{
			for (int i = 0; i < vertices->arraySize; i++)
			{
				ChainNode<string, Vertex<T>*>* ptr = vertices->bucket[i].GetHead();

				while (ptr != nullptr)  // Checks each item in the chained hash table
				{
					string vName = ptr->DataKey();
					Vertex<T>* current = ptr->Data();

					cout << "  |" << vName << ":  " << current->GetData() << "| --> ";

					Node<Edge*>* edgePtr = current->adjacencyList->head;

					while (edgePtr != nullptr)
					{
						cout << edgePtr->data->GetDestination() << " (" << edgePtr->data->GetWeight() << ") --> ";
						edgePtr = edgePtr->next;
					}

					cout << "NULL" << endl; // marks the end of one set of edges.

					ptr = ptr->GetNext();
				}
			}
		}
		else
			cout << "The graph is empty." << endl;

		cout << endl;*/
	}
	
	
	
	void djikstras()  // O(n)
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
