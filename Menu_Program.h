#ifndef MENU_PROGRAM_H
#define MENU_PROGRAM_H

#include <cassert>
#include <iostream>
#include <string>

#include "Graph.h"
#include "DirGraph.h"
#include "Menu_Program.h"
// #include "PrintingPress.h"


class Menu_Program
{

public:

	Menu_Program() ;

private:

	void Clear() ;
	void Greeting() ;
	void Main_Loop() ;

	void Prim_Algorithm() ;
	void Dijkstra_Algorithm() ;
} ;

#endif
