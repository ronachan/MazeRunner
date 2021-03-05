#include <ics46/factory/DynamicFactory.hpp>
#include "MazeGenerator.hpp"
#include "Maze.hpp"
#include "MazeRunner.hpp"
#include "Direction.hpp"
#include <cstdlib>
#include <vector>
#include <random>
#include <utility>

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, MazeRunner, "My Maze Runner (Required)");

// Default Constructor
MazeRunner::MazeRunner()
{
	
}

// Destructor
MazeRunner::~MazeRunner()
{

}

void MazeRunner::generateMaze(Maze& maze)
{
	// add edges aka all the walls
	maze.addAllWalls();
	
	// a 2d vector to check if the coordinates have been visited. Every cell is not visited yet
	 std::vector<std::vector<bool> > visitedSquare(maze.getHeight(), std::vector <bool>(maze.getWidth(), 0));

	// vector that holds all direction possibilities
	std::vector<Direction> posDir{Direction::up, Direction::down, Direction::left, Direction::right};

	// call 
	recursiveDFS(maze, visitedSquare, 0, 0);

}

void MazeRunner::recursiveDFS(Maze& maze, std::vector<std::vector<bool> > &visitedSquare, int x, int y)
{
	Direction dir;

	std::pair<int, int> nums (x, y);

	std::pair<int, int> temp;

	// mark cell as visited
	visitedSquare[x][y] = 1;

	while((temp = adjCell(maze, visitedSquare, x, y, dir)) != nums)
	{
		maze.removeWall(x, y, dir);

		// run the function until visitedSquare is all true
		recursiveDFS(maze, visitedSquare, temp.first, temp.second);
	}
	
}

// returns a pair of ints aka coordinates to the adjacent cell of the current & track if visited or not
 std::pair<int, int> MazeRunner::adjCell(Maze& maze, std::vector<std::vector<bool> > &visitedSquare, int x, int y, Direction& dir)
 {
 	std::pair<int, int> cellCoor(x, y);

 	int counter = 0;
 	std::vector<Direction> directMe;

 	// Find all adjacent walls
 	// adjacent walls obtained by x+1, x-1, y +1, or y - 1
 	if(x+1 < maze.getWidth() && visitedSquare[x+1][y] != 1)
 	{
 		++counter;
 		directMe.push_back(Direction::right);

 	}
 	if(x-1 >= 0 && visitedSquare[x-1][y] != 1)
 	{
 		++counter;
 		directMe.push_back(Direction::left);
 	}
 	if(y+1 < maze.getHeight() && visitedSquare[x][y+1] != 1)
 	{
 		++counter;
 		directMe.push_back(Direction::down);
 	}
 	if(y-1 >= 0 && visitedSquare[x][y-1] != 1)
 	{
 		++counter;
 		directMe.push_back(Direction::up);
 	}


 	if(counter == 0)
 	{
 		return cellCoor;
 	}

 	dir = ranDir(directMe, counter);

 	// change coordinates according to the direction
 	switch(dir)
 	{
 		case Direction::right:
 			cellCoor.first = x+1;
 			cellCoor.second = y;
 			break;
 		case Direction::left:
 			cellCoor.first = x-1;
 			cellCoor.second = y;
 			break;
 		case Direction::down:
 			cellCoor.first = x;
 			cellCoor.second = y+1;
 			break;
 		case Direction::up:
 			cellCoor.first = x;
 			cellCoor.second = y-1;
 			break;
 	}
 	// REturn the pair of coordinates
 	return cellCoor;

 }

// returns a random Direction with the Direction vector and counter passed through
Direction MazeRunner::ranDir(std::vector<Direction> &posDir, int z)
{
	return posDir.at(rand() % z);

}
