// path finder - finds a path through a digital map read from a text file using a graph representation and breadth-first search
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "glut.h"	// GLUT Library (for graphics and user interaction)
#include "graph.h" // graph class

// Global constants 
const int LAND = 0;
const int WATER = 1;
const int MAXSIZE = 50;

// Global variables
int NUMROWS;
int NUMCOLS;
int cellsCount;  // total number of cells (rows*cols)
// add addtional variables here (mapGraph & mapArray) as mentioned in the assignment
graph mapGraph;
// mapArray stores the map in an array as 0 and 1 from a given file that was given by the user
int mapArray[50][50];


// forward declaration - function called by graphics code included below
void findAndPrintPath();

#include "graphics.h" // application-specific graphics functions, uses global vars defined above

void createGraphFromMapFile() // reads the map file and initializes all global variables      
{ 
	cout << "Type in the name of the file that has the map you want! " << flush;
	string filename;
	cin >> filename;

	ifstream inFile;
	inFile.open(filename);

	if (inFile.fail())
	{
		cout << "Error: couldn't open that file. \nPress enter to abort." << flush;
		cin.get();
		exit(EXIT_FAILURE);
	}
	
	inFile >> NUMROWS;
	inFile >> NUMCOLS;
	cellsCount = NUMROWS*NUMCOLS;

	for (int r = 0; r < NUMROWS; ++r)
	{
		for (int c = 0; c < NUMCOLS; ++c)
		{
			inFile >> mapArray[r][c];
			mapGraph.addVertex();
		}
	}

	/*
		These for loops will run there the two-dim array
		Checks if the position next to it is a valid 
		position to create a neighbor / edge
	*/
	for (int r = 0; r < NUMROWS; ++r)
	{
		for (int c = 0; c < NUMCOLS; ++c)
		{
			if (mapArray[r][c] == 0)
			{
				//UP
				if (r - 1 >= 0 && mapArray[r - 1][c] == 0)
					mapGraph.addEdge((r*NUMCOLS) + c, ((r*NUMCOLS) - NUMCOLS) + c);

				//DOWN
				if (r + 1 < NUMROWS && mapArray[r + 1][c] == 0)
					mapGraph.addEdge((r*NUMCOLS) + c, ((r*NUMCOLS) + NUMCOLS) + c);

				//LEFT
				if (c - 1 >= 0 && mapArray[r][c - 1] == 0)
					mapGraph.addEdge((r*NUMCOLS) + c, ((r*NUMCOLS) + (c - 1)));

				//RIGHT
				if (c + 1 < NUMCOLS && mapArray[r][c + 1] == 0)
					mapGraph.addEdge((r*NUMCOLS) + c, ((r*NUMCOLS) + (c + 1)));

				//DOWN - RIGHT
				if ((r + 1 < NUMROWS && c + 1 < NUMCOLS) && mapArray[r + 1][c + 1] == 0)
					mapGraph.addEdge((r*NUMCOLS) + c, ((r*NUMCOLS) + NUMCOLS) + (c + 1));

				//Up - LEFT
				if ((r - 1 >= 0 && c - 1 >= 0) && (mapArray[r - 1][c - 1] == 0))
					mapGraph.addEdge((r*NUMCOLS) + c, ((r*NUMCOLS) - NUMCOLS) + (c - 1));

				//UP - RIGHT
				if ((r - 1 >= 0 && c + 1 < NUMCOLS) && (mapArray[r - 1][c + 1] == 0))
					mapGraph.addEdge((r*NUMCOLS) + c, ((r*NUMCOLS) - NUMCOLS) + (c + 1));

				//DOWN - LEFT
				if ((r + 1 < NUMROWS && c - 1 >= 0) && mapArray[r + 1][c - 1] == 0)
					mapGraph.addEdge((r*NUMCOLS) + c, ((r*NUMCOLS) + NUMCOLS) + (c - 1));		
			}

		}
	}

}  

void findAndPrintPath()
{
	mapGraph.breadthFirst(0);
	mapGraph.printPath(cellsCount-1);

}

int main(int argc, char** argv)
{
	createGraphFromMapFile();
	findAndPrintPath();
	startGraphicsLoop(argc, argv);
   
    return 0;
}



