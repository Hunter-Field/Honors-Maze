#ifndef _MAZE_H_
#define _MAZE_H_

#include <stdbool.h>

//Enum for maze square type
typedef enum SquareType {
	WALL = '#',
	SPACE = '.',
	START = 's',
	END = 'e'
} SquareType;

//Maze square
typedef struct MazeSquare {
	SquareType type;
	bool visited;
} MazeSquare;

//Maze position
typedef struct MazePos {
	int xpos;
	int ypos;
} MazePos;

//Maze structure
typedef struct Maze {
	MazeSquare * * maze; //2D array holding maze
	int width; //Number of columns in maze
	int height; //Number of rows in maze
	MazePos start; //Location of 's'
	MazePos end; //Location of 'e'
} Maze;
 
void makeMaze(char * sizeFilename, char * mazeFilename);
Maze * readMaze(char * mazeFilename);

void freeMaze(Maze * m);

#endif
