//Daniel Kobold
//CSCI362 PA1
//initEntry.cpp

#include "tour.hpp"
using namespace std;

//Initialize coordinate entry process
void initEntry()
{
	//Used for input and making the new node
	int x, y;
	
	//Used for confirmation of node to be created
	int confirm;
	
	//Enter x position
	cout<<"Enter initial X POSITION:\n";
	cin>>x;
	
	//Enter y position
	cout<<"Enter initial Y POSITION:\n";
	cin>>y;
	
	//Check if the entered coordinates are out of bounds of the board
	if(x > 7 || y > 7 || x < 0 || y < 0)
	{
		//Output error message, set confirm to 2 (cancels entry later)
		cout<<"Error: Invalid Location\n";
		confirm = 2;
	}
	else	//Otherwise, allow user to confirm this choice
	{
		//Display options and take input for confirmation
		cout<<"Confirm initial position:\n";
		cout<<"("<<x<<","<<y<<") (1)Yes or (2)No\n";
		cin>>confirm;	
	}
	
	//Do various exit task based on status of confirm
	if(confirm == 1)
	{
		//If confirm == 1, start the node addition process
		addNode(x,y);
	}
	else if(confirm == 2)	//Otherwise, the entry should be cancelled
		cout<<"Entry cancelled.\n";
	else					//OR something other than 1 or 2 was put in for confirmation
		cout<<"Invalid confirmation code.\n";
}

//Initialize coordinate deletion process
void delEntry()
{
	//Used for input and finding the node to be deleted
	int x, y;
	
	//Used for user confirmation of node to be deleted
	int confirm;
	int del = 0;
	
	//Enter x postion for deletion
	cout<<"Enter X POSITION of entry to be deleted:\n";
	cin>>x;
	
	//Enter y position for deletion
	cout<<"Enter Y POSITION of entry to be deleted:\n";
	cin>>y;
	
	//Check if the entered coordinates are out of bounds of the board
	if(x > 7 || y > 7 || x < 0 || y < 0)
	{
		//Specify error message
		confirm == 3;
	}
	else
	{
		//Otherwise allow user to confirm the coordinates to be deleted
		cout<<"Confirm entry to be deleted:\n";
		cout<<"("<<x<<","<<y<<") (1)Yes or (2)No\n";
		cin>>confirm;
	}
	
	//If confirm == 1 (node needs deleted)
	if(confirm == 1)
	{
		//Delete the node
		del = delNode(x,y);
		
		//If delNode returns 0, no matching coordinate was found
		if(del == 0)
			cout<<"No such entry exists.\n";
		else if(del == 2) 	//If del==2, another error occurred
			cout<<"Deletion error.\n";
		else				//Otherwise (del==1), node was deleted successfully
			cout<<"Entry deleted.\n";
	}
	else if(confirm == 2)	//Display message cancelling deletion if user chose against deleting node
		cout<<"Deletion cancelled.\n";
	else if(confirm == 3)	//Display error message explaining that invalid location was entered
		cout<<"Error: Invalid Location\n";
	else					//Display error messagfe explaining that invalid confirmation code was entered
		cout<<"Error: Invalid Confirmation Code\n";
}