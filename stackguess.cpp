//Daniel Kobold
//CSCI362 PA1
//stackguess.cpp

#include "tour.hpp"
using namespace std;

int stackguess(int i, int j, node *problem)
{
	int check = 0;
	int xopt, yopt;
	int p = 0;
	
	//Set up the options (same as resetOptions() but for opts3)
	opts3[0].xcord=i-2;
	opts3[0].ycord=j+1;
	opts3[1].xcord=i-1;
	opts3[1].ycord=j+2;
	opts3[2].xcord=i+1;
	opts3[2].ycord=j+2;
	opts3[3].xcord=i+2;
	opts3[3].ycord=j+1;
	opts3[4].xcord=i+2;
	opts3[4].ycord=j-1;
	opts3[5].xcord=i+1;
	opts3[5].ycord=j-2;
	opts3[6].xcord=i-1;
	opts3[6].ycord=j-2;
	opts3[7].xcord=i-2;
	opts3[7].ycord=j-1;
	
	while(p<8)
	{
		//Set position (not option coordinate) to the current position of the knight
		opts3[p].xpos = i;
		opts3[p].ypos = j;
		
		//Set option variables to the option to be analyzed for this iteration of loop
		xopt = opts3[p].xcord;
		yopt = opts3[p].ycord;
		
		//Check if the option is out of bounds of the board
		if(xopt <= 7 && yopt <= 7 && xopt >= 0 && yopt >= 0)
		{
			//Check if board space is still valid, and move number is -1
			if(problem->board[xopt][yopt]==1 && problem->sol[xopt][yopt]==-1)
			{
				if(detail==1)
					cout<<"|Check+";
				
				//Increment check and p
				check += 1;
				p++;
			}
			else
			{
				p++;
			}
		}
		else
		{
			p++;
		}
	}
	
	//Return check
	return check;
	
}

