//Daniel Kobold
//CSCI362 PA1
//nextMove.cpp

#include "tour.hpp"
using namespace std;

void nextMove(int i, int j, node *problem)
{
	//Used for looping through opts
	int o = 0;
	
	int xopt, yopt; //X and Y option variables
	
	//Keeps track of chosen option; keeps track of lowest move amount / score
	int choice, least;
	
	
	int a = 0;
	
	//Set choice to -1 to start
	choice = -1;
	
	//Set least to 0 to start
	least = 0;
	
	int guess; //Keep track of which skip we are on
	
	//Reset options before beginning
	resetOptions(i,j);
	
	//Set o to 0 to start looping from the beginning
	o=0;
	
	//If move < 32 (meaning Warnsdoff is used)
	if(problem->move < 32)
	{
		//While not all options have been analyzed yet
		while(o<8)
		{
			//Set the position to current position of the knight for this option
			opts[o].xpos = i;
			opts[o].ypos = j;
			
			//Set option variables to the option coordinate for this option
			xopt = opts[o].xcord;
			yopt = opts[o].ycord;
			
			//Check if the option is out of bounds of the board
			if(xopt > 7 || yopt > 7 || xopt < 0 || yopt < 0)
				opts[o].score=99;			//Invalid loc -> high score (bad)
			else if(problem->sol[xopt][yopt]!=-1)
				opts[o].score=99;			//Previously used loc -> high score (bad)
			else
				opts[o].score=numMoves(xopt, yopt, problem); //Otherwise, use the number of moves as the score

			//Increment o
			o++;
		}
		
		//Reset o to 0
		o = 0;
		
		//Reset choice to o (0)
		choice = o;
		
		//Set least to 99, so this will search for anything less than 99
		least = 99;
		
		//While not all options have been analyzed yet
		while(o<8)
		{
			//If this options score is less than the previously lowest score
			//AND o is greater than or equal to the previously recorded which value
			if(opts[o].score < least && o>=which[problem->move])
			{
				//Set choice to current o
				choice = o;
				
				//Set this which value to o
				which[problem->move]=o;
				
				//Set least to this option's score
				least = opts[o].score;
				
				//Increment o
				o++;
			}
			else
			{
				//Increment o
				o++;
			}
		}
		
		//Used for reference
		if(detail==1)
			cout<<"|"<<choice<<"|("<<opts[choice].xcord<<","<<opts[choice].ycord<<")";
		
		//Used for reference
		/*if(least == 99)
			cout << "\nERROR\n";
		else
		{
			cout << "\nChoice #"<<choice;
			cout << "\nxcord: "<<opts[choice].xcord;
			cout << "\nycord: "<<opts[choice].ycord;
			cout << "\nScore: "<<opts[choice].score<<"\n\n";
		}*/
		
		//Complete the move, given the current position, choice, and problem status
		move(i,j,choice,problem);
				
	}
	else			//Otherwise, Warnsdoff will NOT be used
	{		

		//While not all options have been analyzed yet
		while(o<8)
		{
			//Set positions to current knight position
			opts[o].xpos = i;
			opts[o].ypos = j;

			//Set option variables to this option's values
			xopt = opts[o].xcord;
			yopt = opts[o].ycord;
			
			//Check if this option is out of bounds of the board
			if(xopt > 7 || yopt > 7 || xopt < 0 || yopt < 0)
				opts[o].score=99;			//Invalid loc -> high score (bad)
			else if(problem->sol[xopt][yopt]!=-1)		//Check if this space has been visited already
				opts[o].score=99;			//Previously visited loc -> high score (bad)
			else
			{
				//Otherwise, set this option's score to 1
				//Doing so allows all valid locations to have EQUAL importance (score)
				opts[o].score = 1;
			}

			//Increment o
			o++;
		}
		
		//Reset o to 0
		o = 0;
		
		//Reset choice to o (0)
		choice = o;
		least = 99;
		
		//Set guess to 0
		guess = 0;
		
		//While not all options have been analyzed
		//AND the number of guesses does not exceed the number of options to be skipped
		//(skipped values determined elsewhere)
		while(o<8 && guess <= over[problem->move] )
		{
			//If this option's score is the lowest
			//AND this is the first option to not be skipped
			if(opts[o].score < least && guess==over[problem->move]) //
			{
				//Used for reference
				if(detail==1)
				{
					cout<<"|o="<<o;
					cout<<"|s="<<over[problem->move];
					cout<<"|mvs="<<numMoves(i,j,problem);
				}
				
				//Set choice to o
				choice = o;
				
				//Set which for this move to o
				which[problem->move]=o;
				
				//Set least to this option's score
				least = opts[o].score;
				
				//Increment o
				o++;
			}
			else if(opts[o].score < least && guess<over[problem->move]) //Same as above BUT this one needs to be skipped
			{
				//Increment guess and o
				guess++;
				o++;
			}
			else if(guess > 7)		//If guess exceeds the highest value it SHOULD reach, display error message if details are enabled
			{
				//Used for reference
				if(detail==1)
					cout << "|Oops...";
			}
			else
			{
				//Increment o
				o++;
			}
		}
		
		//If the least is still 99, meaning no better option was found
		if(least == 99)
		{
			//Used for reference
			if(detail==1)
				cout<<"|HELP|";
			
			//Set the choice option's score to 99
			opts[choice].score=99;
			
			//Add 1 to the amount of skipped options for the PREVIOUS LEVEL
			over[problem->move -1] += 1;
			
			//Reset the number of options to be skipped for THIS LEVEL
			over[problem->move] = 0;
			
			//EXPLANATION: This is using a "tree" structure
			//Setting up skip in this way allows us to check each valid option for each
			//different move number
			
			//If over (skip value) is higher than it SHOULD be, print error message if details are enabled
			if(over[problem->move] > 7)
			{
				//Used for reference
				if(detail==1)
					cout << ":(";
			}
			else if(opts[0].score == 99 && opts[1].score==99)		//Gradually check if ALL of the opts == 99
			{
				if(opts[2].score==99 && opts[3].score==99)
				{
					if(opts[4].score==99 && opts[5].score==99)
					{
						if(opts[6].score==99 && opts[7].score==99)
						{				
							//Used for reference
							if(detail == 1)
								cout<<"FAILURE.\n";
							
							//Set board of this space to 0, making it an invalid location for movement choice
							problem->board[i][j]=0;
						}
					}
				}
			}
		}
		else
		{
			//Otherwise, complete the movement since a better option was found
			move(i,j,choice,problem);
		}
		
	}


}

//Completes the move
void move(int i, int j, int choice, node * problem)
{
	//Set the this problem's solution for the option space to the move number
	problem->sol[opts[choice].xcord][opts[choice].ycord]=problem->move;
	
	//Make sure this space isn't checked again
	problem->board[opts[choice].xcord][opts[choice].ycord]=0;
	
	//Set this problem's xcord and ycord to the new position
	problem->xcord=opts[which[problem->move]].xcord;
	problem->ycord=opts[which[problem->move]].ycord;
	
	//Increment move
	problem->move+=1;
	
	//Find new options for new coordinate and board conditions
	resetOptions(i,j);

}

//Find new options for board conditions
void resetOptions(int i, int j)
{
	//Find all possible moves and place in the opts array
	opts[0].xcord=i-2;
	opts[0].ycord=j+1;
	opts[1].xcord=i-1;
	opts[1].ycord=j+2;
	opts[2].xcord=i+1;
	opts[2].ycord=j+2;
	opts[3].xcord=i+2;
	opts[3].ycord=j+1;
	opts[4].xcord=i+2;
	opts[4].ycord=j-1;
	opts[5].xcord=i+1;
	opts[5].ycord=j-2;
	opts[6].xcord=i-1;
	opts[6].ycord=j-2;
	opts[7].xcord=i-2;
	opts[7].ycord=j-1;
	
	//Used for reference
	/*cout<<"Options for ("<<i<<","<<j<<"):  ";
	for(int r = 0; r < 8; r++)
	{
	cout<<"("<<opts[r].xcord<<","<<opts[r].ycord<<")";
	}
	cout<<"\n";*/
}