#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    cout << "Add your own tests here! Modify main.cpp" << endl;
    //PNG output;
	//output.readFromFile(filename);
	SquareMaze maze;
    PNG * actualOutput = maze.drawMazeCreative();
    actualOutput->writeToFile("creative"+string(".png"));
    return 0;
}
