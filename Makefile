CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
TESTFLAGS = 
GCC = gcc $(CFLAGS) $(TESTFLAGS)
EXEC = main
OBJS =  main.o maze.o mazehelper.o path.o solver.o
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose

$(EXEC): $(OBJS) solver.h
	$(GCC) $(OBJS) -o $(EXEC) 

test: $(EXEC)
	./$(EXEC) testcases/maze1 mazes/maze1 solution1
	./$(EXEC) testcases/maze2 mazes/maze2 solution2
	./$(EXEC) testcases/maze3 mazes/maze3 solution3

memory: $(EXEC)
	$(VALGRIND) --log-file=log1 ./$(EXEC) testcases/maze1 mazes/maze1 solution1
	$(VALGRIND) --log-file=log2 ./$(EXEC) testcases/maze2 mazes/maze2 solution2
	$(VALGRIND) --log-file=log3 ./$(EXEC) testcases/maze3 mazes/maze3 solution3

%.o : %.c
	$(GCC) -c $< 

clean:
	rm -f $(OBJS)
	rm -f $(EXEC)
	rm -f expected? log?
	rm -f solution*
	rm -f mazes/maze*