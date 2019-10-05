#Daniel Kobold
#CSCI362 PA1
#Makefile

all: tour

clean:
	rm tour

tour: tour.hpp tour.cpp node.cpp nextMove.cpp warnsdoff.cpp initEntry.cpp stackguess.cpp
	g++ -o tour tour.hpp tour.cpp node.cpp nextMove.cpp warnsdoff.cpp initEntry.cpp stackguess.cpp
	
debug: tour.hpp tour.cpp node.cpp nextMove.cpp warnsdoff.cpp initEntry.cpp stackguess.cpp
	g++ -g -o tour tour.hpp tour.cpp node.cpp nextMove.cpp warnsdoff.cpp initEntry.cpp stackguess.cpp