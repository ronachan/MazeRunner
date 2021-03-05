#include <ics46/factory/DynamicFactory.hpp>
#include "MazeSolver.hpp"
#include "MazeSolution.hpp"
#include "Maze.hpp"
#include "GetOut.hpp"
#include <cstdlib>
ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, GetOut, "Get Out (Required)");

// Default Constructor
GetOut::GetOut()
{

}

// Destructor
GetOut::~GetOut()
{

}

void GetOut::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
	// Restart the maze solution
	mazeSolution.restart();

	// Initialize the vector to 0 to mark as unvisited 
	std::vector<std::vector<bool> > visitedSquare(maze.getHeight(), std::vector <bool>(maze.getWidth(), 0));

	// Initialize the Direction vector with all the directions that need to be checked
	std::vector<Direction> checkAllDir{Direction::down, Direction::right, Direction::up, Direction::left};

	// Call the recusive function
	recursiveSolve(maze, mazeSolution, visitedSquare, checkAllDir, mazeSolution.getStartingCell().first, mazeSolution.getStartingCell().second);

	//mazeSolution.getMovements();
}

bool GetOut::recursiveSolve(const Maze& maze, MazeSolution& mazeSolution, std::vector<std::vector<bool> > &visitedSquare, std::vector<Direction> &checkAllDir, int x, int y)
{
	std::pair<int, int> temp(x, y);

	// Base case: reach the end cell then the solution nis done
	if(mazeSolution.getCurrentCell() == mazeSolution.getEndingCell())
	{
		return true;
	}

	// Mark the cell as visited
	visitedSquare[x][y] = 1;

	for (int i = 0; i < 4; ++i)
	{
		temp = nextCell(maze, x, y, i);
		if(!maze.wallExists(x, y, checkAllDir.at(i)) && visitedSquare[temp.first][temp.second] != 1)
		{
			mazeSolution.extend(checkAllDir.at(i));
			if (recursiveSolve(maze, mazeSolution, visitedSquare, checkAllDir, temp.first, temp.second))
				return true;

		}
	}
	// Backs up if it hits a wall
	mazeSolution.backUp();
	return false;

}

// Returns a pair of ints according to the counter which is the position in the Direction vector
std::pair<int, int> GetOut::nextCell(const Maze& maze, int x, int y, int counter)
{

	if(counter == 0 && y < maze.getHeight()-1)
	{
		y +=1 ;
	}
	if(counter == 1 && x < maze.getWidth()-1)
	{
		x += 1;
	}
	if(counter == 2 && y > 0)
	{
		y -= 1;
	}
	if(counter == 3 && x > 0)
	{
		x -= 1;
	}
	std::pair<int, int> coor(x, y);
	return coor;
}
