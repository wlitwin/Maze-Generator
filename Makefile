main:
	g++ -o maze main.cpp Maze.cpp -lGL -lglut -lGLU

clean:
	/bin/rm maze
