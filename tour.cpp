//Daniel Kobold
//CSCI362 PA1
//tour.cpp

#include "tour.hpp"
using namespace std;

struct node *head = NULL;
struct node *current = NULL;
struct node *prev = NULL;

//Option arrays
struct option opts[8];
struct option opts2[8];
struct option opts3[8];
struct node *prob; //Keeps track of which knights tour problem is being solved					
int which[64];	//Keeps track of which choice was made for each move number
int over[64]; //Keep track of number of skips for each level
int getOut;		//Keeps track of if an emergency exit from program is needed
int levels;		//Keeps track of how many levels of push/pull are in progress
int detail;		//Keeps track of whether user wants to see all the details of the Knights Tour
struct answer ans[8][8];	//Holds all of the final answers

int main()
{
	int i, j;				//ints for position accessing each element
	int a = 0;				//Keeps track of when user is done inputting
	int w = 0;				//initial positions
	stack <struct node> s;	//The STACK used for storing and retrieving board statuses
	
	int choice = 0;			//Keeps track of what user is attempting to do
	getOut = 0;				//Set getOut to 0
	levels = 0;				//Set levels to 0
	detail = 0;				//Set detail to 0
	
	int v = 0;				//Helps with over changing
	
	cout<<"\nWelcome to KNIGHTS TOUR!\n"; //Welcome message

	//Stay in entry menu until 8 or 9 is inputted by user
	while(a != 9 && a != 8)
	{
		//Display a menu of options
		cout<<"\n__________________________________________\n";
		cout<<"INITIAL POSITION ENTRY MENU:\n";
		cout<<"(1) Add new entry\n";
		cout<<"(2) View current entries\n";
		cout<<"(3) Delete entry\n";
		cout<<"(4) Modify entry\n";
		cout<<"(8) Begin Knights Tour (no Detail)\n";
		cout<<"(9) Begin Knights Tour (w/ Detail)\n";
		
		//Take input and put in a
		cin>>a;
		
		//Do different things based on user input
		if(a==1)
			initEntry();			//Begin new node process
		else if(a == 2)
			printList();			//Print list of all current nodes
		else if(a == 3)
		{
			printList();			//Print list of all current nodes
			delEntry();				//THEN allow user to delete a node
		}
		else if(a == 4)
		{
			printList();			//Print list of all current nodes
			delEntry();				//THEN allow user to delete a node
			initEntry();			//THEN allow user to input a new node
		}
		else if(a == 8 || a == 9)	//Entry needs to stop, tour needs to begin
		{
			//Message
			cout<<"Entry process terminated\n";
			if(a==9)				//If requested, turn on details
				detail = 1;
		}
		else						//Otherwise, an invalid option was inputted
			cout<<"Invalid Choice\n";
		
	}
	
	//While prob is not pointing to NULL (meaning tours have not yet been completed for all initial positions)
	while(prob!=NULL)
	{
		//Set i and j to 0
		i = 0;
		j = 0;
		
		prob->initX = prob->xcord;
		prob->initY = prob->ycord;
		
		//Setting all places to -1 for solution move number and 1 for board validity code
		while(i<8)
		{
			//Set solution move number to -1 (for now)
			prob->sol[i][j]=-1;
			
			//Set board positions to 1 (making it a valid spot for guesses later)
			prob->board[i][j]=1;
			
			//Increment j
			j++;
			
			which[w]=0; //setting which array (keeps track of which option is being explored for each move)
			
			//Increment w
			w++;
			
			//If j == 8, increment i and set j back to 0
			if(j == 8)
			{
				j = 0;
				i++;
			}
		}
		
		//Reset i and j to 0
		i = 0;
		j = 0;
		
		//Set all which items to 0 and all over items to 0
		for(int q = 0; q<64; q++)
		{
			which[q] = 0;	//Keeps track of choices for each move
			over[q]=0;		//Keeps track of number of options to be skipped
		}
		
		//Knights Tour message
		cout<<"\n__________________________________________\n";
		
		//Set i an j to current (initial) coordinate of the knight for this problem
		i = prob->xcord;
		j = prob->ycord;
		
		//Message about starting position
		cout<<"KNIGHTS TOUR Starting at ("<<i<<","<<j<<")\n\n";
		
		//Set move for this position to 0, as this is the first space visited
		prob->sol[i][j]=0;
		
		//Increment move
		prob->move+=1;
		
		//While the Knights Tour has not been completed yet
		while(prob->move < 64)
		{
			//Used for reference
			if(detail==1)
				cout<<prob->move;
			
			//Set skip to the value of over for this move
			prob->skip = over[prob->move];
			
			//Push this problem onto the stack
			s.push(*prob);
			
			//Find the next move and complete the move
			nextMove(i,j,prob);
			
			//Set i and j to the new position
			i = prob->xcord;
			j = prob->ycord;
			
			//Find new options based on new position
			resetOptions(i,j);
			
			//If number of moves left == 0, but the tour isn't over
			if((numMoves(i,j,prob)-over[prob->move])==0 && prob->move <= 63)
			{
				//Used for reference
				if(detail == 1)
					cout<<"|^";
				
				//Set over for this move to 7
				over[prob->move]=7;
				
				//Increment over for the PREVIOUS move by 1
				over[prob->move - 1] += 1;
				
				//Used for reference
				if(detail==1)
					cout<<"|over ("<<prob->move<<")="<<over[prob->move];
				
				//Pop the top node off of stack (that is THIS node)
				s.pop();
				
				//Retrieve the NEXT NODE from the stack
				*prob = s.top();
				
				//Pop that node off the stack
				s.pop();
				
				//Set i and j to the new postions
				i = prob->xcord;
				j = prob->ycord;
				
				//Find new options for new position
				resetOptions(i,j);							
				
				//While number of available moves <= number of options to skip <= 7
				while(over[prob->move] <= 7 && over[prob->move] >= numMoves(i,j,prob) )
				{
					//Retrieve another node from top of the stack
					*prob = s.top();
					
					//Pop that node off the stack
					s.pop();
					
					//Set i and j to the new positions
					i = prob->xcord;
					j = prob->ycord;
					
					//Find new options for new position
					resetOptions(i,j);
					
					if(detail==1)
						cout<<"^"<<prob->move;
				}
			}
			else if(over[prob->move] > 7)			//Otherwise, if number of opts to be skipped is > 7
			{
				//Used for reference
				if(detail==1)
					cout<<"^b";
				
				//Pop another node off the top of the stack
				s.pop();
				
				//Retrieve another node from the top of the stack
				*prob = s.top();
				
				//Pop that node off the top of the stack
				s.pop();
				
				//While number of opts to skip >= number of available moves for this position and board state
				while(over[prob->move] >= numMoves(i,j,prob))
				{
					//Used for reference
					if(detail==1)
						cout<<"^"<<prob->move;
					
					//Retrieve node from top of stack
					*prob = s.top();
					
					//Pop that node off the top
					s.pop();
				}
			}
			
			//Used for reference
			if(detail==1)
				cout<<"\n";
			
			//Escape the program
			if(getOut == 1)
			{
				return 1;
			}
		
		
		}
		
		//Print the board since this tour is over
		printBoard(prob);
		
		//Copy all sol to ans
		for(int j = 0; j<8; j++)
		{
			for(int k = 0; k<8; k++)
			{
				ans[prob->initX][prob->initY].solution[j][k]=prob->sol[j][k];
			}
		}
		
		
		//Set prob to the next node
		prob=prob->next;
	}

	
}
