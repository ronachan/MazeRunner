#ifndef GETOUT_HPP
#define GETOUT_HPP
#include <iostream>
#include <vector>

class GetOut : public MazeSolver
{
	public:
		GetOut();
		virtual void solveMaze(const Maze& maze, MazeSolution& mazeSolution);
		virtual ~GetOut();
		bool recursiveSolve(const Maze& maze, MazeSolution& mazeSolution, std::vector<std::vector<bool> > &visitedSquare, std::vector<Direction> & checkAllDir, int x, int y);
		std::pair<int, int> nextCell(const Maze& maze, int x, int y, int counter);
};

#endif