FLAGS = -pedantic-errors -std=c++11

all: game_loop

game_loop.o: game_loop.cpp rooms.h
	g++ $(FLAGS) -c game_loop.cpp

game_loop: game_loop.o 
	g++ $(FLAGS) game_loop.o -o game_loop

clean:
	rm -f game_loop game_loop.o rooms.o 

.PHONY: clean