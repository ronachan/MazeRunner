#ifndef MAZERUNNER_HPP
#define MAZERUNNER_HPP

#include <iostream>
#include <vector>

class MazeRunner : public MazeGenerator
{
	public:
		MazeRunner();
		virtual void generateMaze(Maze& maze);
		virtual ~MazeRunner();
		void recursiveDFS(Maze& maze, std::vector<std::vector<bool> > &visitedSquare, int x, int y);
		Direction ranDir(std::vector<Direction> &posDir, int z);
		std::pair<int, int> adjCell(Maze& maze, std::vector<std::vector<bool> > &visitedSquare, int x, int y, Direction& dir);
	
		
};

#endif