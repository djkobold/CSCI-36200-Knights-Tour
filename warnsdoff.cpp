//Daniel Kobold
//CSCI362 PA1
//warnsdoff.cpp

#include "tour.hpp"
using namespace std;

//Returns "score" based on future possible moves
int warnsdoff(int i, int j, node *problem)
{
	//Used for looping through the opts2 array
	int p = 0;
	
	int xopt, yopt; //X and Y option variables
	
	int future; //Holds the score to be returned
	
	//Initialize future to 0
	future = 0;
	
	//Set up the options (same as resetOptions() but for opts2)
	opts2[0].xcord=i-2;
	opts2[0].ycord=j+1;
	opts2[1].xcord=i-1;
	opts2[1].ycord=j+2;
	opts2[2].xcord=i+1;
	opts2[2].ycord=j+2;
	opts2[3].xcord=i+2;
	opts2[3].ycord=j+1;
	opts2[4].xcord=i+2;
	opts2[4].ycord=j-1;
	opts2[5].xcord=i+1;
	opts2[5].ycord=j-2;
	opts2[6].xcord=i-1;
	opts2[6].ycord=j-2;
	opts2[7].xcord=i-2;
	opts2[7].ycord=j-1;
	
	//Go through the opts2 to determine which options are valid
	while(p<8)
	{
		//Set the position (not option coordinate) to the current position of the knight
		opts2[p].xpos = i;
		opts2[p].ypos = j;
		
		//Set xopt and yopt to the options to be examined in this iteration of loop
		xopt = opts2[p].xcord;
		yopt = opts2[p].ycord;
		
		//Check if option is out of bounds of the board
		if(xopt <= 7 && yopt <= 7 && xopt >= 0 && yopt >= 0)
		{
			//Check that the option is not the same as the current position
			if(xopt != i && yopt != j)
			{
				//Check that the current sol (move number) for that space is -1
				if(problem->sol[xopt][yopt]==-1)
					future += 10;
				else
					future+=1;
			}
			else
			{
				future+=1;
			}
		}
		else
		{
			future+=1;
		}
		p++;
	}
	
	//Every valid option -> future +10
	//Every invalid option -> future +1
	//Return future
	return future;
}

//Alternate version where the actual number of moves (rather than score) is returned
int numMoves(int i, int j, node * problem)
{
	//Used for looping through opts2 array
	int p = 0;
	int xopt, yopt; //X and Y option variables
	
	//Used to return number of moves
	int moves;
	
	//Initialize moves to 0
	moves = 0;
	
	//Set up the options (same as resetOptions() but for opts2)
	opts2[0].xcord=i-2;
	opts2[0].ycord=j+1;
	opts2[1].xcord=i-1;
	opts2[1].ycord=j+2;
	opts2[2].xcord=i+1;
	opts2[2].ycord=j+2;
	opts2[3].xcord=i+2;
	opts2[3].ycord=j+1;
	opts2[4].xcord=i+2;
	opts2[4].ycord=j-1;
	opts2[5].xcord=i+1;
	opts2[5].ycord=j-2;
	opts2[6].xcord=i-1;
	opts2[6].ycord=j-2;
	opts2[7].xcord=i-2;
	opts2[7].ycord=j-1;
	
	//Go through the opts2 to determine which options are valid
	while(p<8)
	{
		//Set the position (not option coordinate) to the current position of the knight
		opts2[p].xpos = i;
		opts2[p].ypos = j;
		
		//Set xopt and yopt to the options to be examined in this iteration of loop
		xopt = opts2[p].xcord;
		yopt = opts2[p].ycord;
		
		//Check if option is out of bounds of the board
		if(xopt < 8 && yopt < 8 && xopt >= 0 && yopt >= 0)
		{
			
			//Check that the option is not the same as the current position
			if(xopt != i && yopt != j)
			{
				//Check that the current sol (move number) for that space is -1
				if(problem->sol[xopt][yopt]==-1)
					moves += 1;
				else
					moves+=0;
			}
			else
			{
				moves+=0;
			}
		}
		else
		{
			moves+=0;
		}
		p++;
	}
	//Every valid option -> moves +1
	//Every invalid option -> moves +0
	//Return future
	return moves;
}