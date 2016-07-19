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



int checker(string u , string v , bool path) // implementing djikstra's algorithm.
	{
		clear() ;
		BuildGraphNew() ;
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
				return 0 ; // exit function.
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

			if (path == false) 
			{
				int i = current->cheapestConnection ;
				clear() ;
				return i ;
			}

			else if (path == true) // this is for path retrieval.
			{
				std::cout << "\n  Shortest path: " ;

				while(current != nullptr)
				{	
					std::cout << current->name << " <- " ;
					current = current->parent ;
				}

				std::cout << "START \n\n" ;
				return 0 ;
			}
		}

		else std::cout << "  The graph is empty. \n" ; // if the graph is empty.
	}
