#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "path.h"
#include "solver.h"
#include <time.h>

int main(int argc, char ** argv){

	//argv[1] = maze dimensions
	//argv[2] = empty file that maze is printed to
	//argv[3] = output file that contains path

	if (argc != 4) {
		fprintf(stderr, "Wrong number of args\n");
		return EXIT_FAILURE;
	}

	//makes mazes completely random every run
	srand(time(NULL));
	

	//runs until a created maze is solvable
	bool solvable = false;
	Maze * m;
	char * path;
	while(!solvable){
		makeMaze(argv[1], argv[2]);

		m = readMaze(argv[2]);
	
		if (m == NULL){
			return EXIT_FAILURE;
		}

		path = solveMaze(m);
	
		if (writePath(argv[3], path)) {
			freeMaze(m);
			free(m);
			free(path);
			return EXIT_FAILURE;
		}

		freeMaze(m);
		free(m);
		free(path);

		m = readMaze(argv[2]);
		path = readPath(argv[3]);
		if (path == NULL) {
			freeMaze(m);
	 		free(m);
	 		return EXIT_FAILURE;
		}
	
		solvable = checkPath(m, path);

		if (solvable) {
	 		printf("Success!\n");
		} else {
	 		printf("Failure!\n");
		}

		freeMaze(m);
		free(m);
		free(path);
	}
	
	return EXIT_SUCCESS;
}
