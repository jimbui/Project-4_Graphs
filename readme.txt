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
