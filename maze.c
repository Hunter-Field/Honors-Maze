#include <stdlib.h>
#include <stdio.h>
#include "maze.h"

void makeMaze(char * sizeFilename, char * mazeFilename){
	//opens the maze dimension file
	FILE * fptr1 = fopen(sizeFilename, "r");
	if (fptr1 == NULL) {
		fprintf(stderr, "Could not open size file for reading\n");
		exit(1);
	}

	//opens empty file to print maze to
	FILE * fptr2 = fopen(mazeFilename, "w");
	if (fptr2 == NULL) {
		fprintf(stderr, "Could not open maze file for reading\n");
		exit(1);
	}
		
	//scans maze dimensions
	int height;
	int width;
	if(fscanf(fptr1, "%d %d\n", &height, &width) != 2) {
		fprintf(stderr, "Cannot get maze dimensions\n");
		return;
	}

	//prints maze dimensions to file
	fprintf(fptr2, "%d %d\n", height, width);


	//makes a array to contain a character path
	char ** maze = malloc(height * sizeof(MazeSquare *));
	for (int i = 0; i < width; i++) {
		maze[i] = malloc(width * sizeof(MazeSquare));
	}

	//fills maze with open spaces
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			maze[i][j] = '.';
		}
	}

	//adds random walls throughout maze
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			if(rand() % 3 == 0){
				maze[i][j] = '#';
			}
		}
	}

	//creates the start and end point at designated location
	maze[0][0] = 's';
	maze[width - 1][height - 1] = 'e';

	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			fprintf(fptr2, "%c", maze[i][j]);
		}
		fprintf(fptr2, "\n");
	}


	//frees the 2D maze array
	for(int i = 0; i < height; i++){
		free(maze[i]);
	}
	free(maze);

	//closes both files
	fclose(fptr1);
	fclose(fptr2);
}

Maze * readMaze(char * mazeFilename){
	FILE * inMaze = fopen(mazeFilename, "r");

	if (inMaze == NULL) {
		fprintf(stderr, "Could not open maze file for reading\n");
		exit(1);
	}
		
	//Allocate Maze structure
	Maze * m = malloc(sizeof(Maze));


	//Read in the dimensions of the maze
	if (fscanf(inMaze, "%d %d\n", &(m->height), &(m->width)) != 2){
		printf("%d %d\n", m->height, m->width);
		fprintf(stderr, "Malfored input: can't get maze dimensions\n");
		free(m);
		return NULL;
	}
	
	//Allocate the 2D array in m
	m->maze = malloc(m->height * sizeof(MazeSquare *));
	for (int i = 0; i < m->width; i++) {
		m->maze[i] = malloc(m->width * sizeof(MazeSquare));
	}
	
	//Read in the maze -- assume that it is well formatted
	for (int i = 0; i < m->height; i++) {
		for (int j = 0; j < m->width; j++) {
			int val = fgetc(inMaze);

			m->maze[i][j].type = val;
			m->maze[i][j].visited = false;

			if (val == END) {
				m->end.xpos = j;
				m->end.ypos = i;
			} else if (val == START) {
				m->start.xpos = j;
				m->start.ypos = i;
			}
		}
		//consume extra \n
		int c = fgetc(inMaze);
		//Error check: c had better be a \n:
		if (c != '\n') {
			fprintf(stderr, "Malformed input\n");
			freeMaze(m);
			free(m);
			return NULL;
		}
	}
	
	//close the file
	if (fclose(inMaze)) {
		fprintf(stderr, "Error closing file\n");
		freeMaze(m);
		free(m);
		return NULL;
	}
	
	return m;
}
void freeMaze(Maze * m) {
	//1. Free each of the "rows" of the maze
	for (int i = 0; i < m->height; i++) {
		free(m->maze[i]);
	}
	
	//2. Free the "spine" of the array
	free(m->maze);
}
