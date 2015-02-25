all:	main game

main: main.o
	g++ main.o -o main

main.o: main.cpp 
	g++ -c main.cpp


game: game.o
	g++ game.o -o game

game.o: game.cpp 
	g++ -c game.cpp


clean:
	rm -f *.o main
	rm -f *.o game
