//Daniel Kobold
//CSCI362 PA1
//node.cpp

#include "tour.hpp"
using namespace std;

//Add Node
void addNode(int x, int y)
{
	//If head doesn't exist, make a new first node
	//Otherwise, insert the node afterwards
	if(head == NULL)
		insertFirst(x,y);
	else
		insertAfter(x,y);
}

//Delete Node
int delNode(int x, int y)
{
	//find helps locate the node needing to be deleted
	struct node *find = head;
	
	//Previous for find (used in deletion)
	struct node *findPrev = head;
	
	//Keeps track of where the node needs to be deleted from
	int yep = 0;
	
	//While find is not at the end of the node list
	while(find != NULL)
	{
		//If the x or y coordinate doesn't match, move findPrev and find to next node
		if(find->xcord != x)
		{
			findPrev = find;
			find=find->next;
		}
		else if(find->ycord != y)
		{
			findPrev = find;
			find=find->next;
		}
		else		//Otherwise, the coordinates match and this should be deleted
		{
			if(find == findPrev) //Delete from start
				yep = 1;
			else if(find->next == NULL) //Delete from end
				yep = 3;
			else	//Delete somewhere else
				yep = 2;
				
			break;
		}
	}
	
	if(yep == 0)	//Point not found
		return 0;
	else if(yep == 1)	//Delete from start
	{
		struct node *temp = new node;			//Used for proper linking
		temp = head;							//Start temp at head
		head=head->next;						//The node after head is the new head
		delete temp;							//Delete temp
		prev = NULL;							//Set prev to NULL
		return 1;								//Return 1 (successful deletion)
	}
	else if(yep == 2)	//Delete in middle
	{
		findPrev->next=find->next;				//Link previous node to node after this node
		delete find;							//Delete node in the middle
		return 1;								//Return 1 (successful deletion)
	}
	else if(yep ==3)	//Delete at end
	{
		//Currently:
		//find->next=NULL
		//findPrev->next=find
		
		findPrev->next=NULL; //Set up previous next as null
		delete find;	//Delete last node
		return 1;		//Return 1 (successful deletion)
		
	}
	else				//Some error occurred
		return 2;
	
}

//Print the list of nodes, from the beginning
void printList()
{
	//Set pointer to head
	struct node *ptr = head;
	
	//Message
	cout<<"Initial Locations Entered:\n";
	
	//While ptr has not reached the end of the list
	while(ptr != NULL)
	{
		//Display the coordinates of the initial position being pointed at by ptr
		cout<<"("<<ptr->xcord<<","<<ptr->ycord<<")\n";
		
		//Set ptr to the next node
		ptr = ptr->next;
	}
}

//Print entire board, using move numbers
void printBoard(struct node * problem)
{
	//[00][00][00][00][00][00][00][00]
	
	//For formatting purposes
	cout<<"\n";
	
	//Loop through all parts of sol multidimensional array in pattern sol[a][b]
	for(int a = 0; a<8; a++)
	{
		for(int b = 0; b<8; b++)
		{
			if(problem->sol[a][b]==-1)					//Display -1
				cout<<"["<<problem->sol[a][b]<<"]";
			else if(problem->sol[a][b]<10)				//Display a position < 10
				cout<<"[0"<<problem->sol[a][b]<<"]";
			else										//Display a position >= 10
				cout<<"["<<problem->sol[a][b]<<"]";
		}
		
		//For formatting purposes
		cout<<"\n";
	}
}

void insertFirst(int x, int y)
{
	//Make new head node
	struct node *first = new node;
	
	//Assign x and y coordinates to new node
	first->xcord=x;
	first->ycord=y;
	
	//Point head to NULL
	first->next=NULL;
	
	//Set head to the new head node
	head = first;
	
	//Set this node as the new prev node
	prev = first;
	
	//Set current problem to the first node
	prob = first;
	
	//Set first to NULL (because this is the first node)
	first = NULL;
}

void insertAfter(int x, int y)
{
	//Make a new node
	struct node *newNode = new node;
	
	//Assign x/y coordinates to new node and set next to null
	newNode->xcord=x;
	newNode->ycord=y;
	newNode->next=NULL;
	
	//Set previous node's next node to this new node
	prev->next=newNode;
	
	//Set this node as the new prev node
	prev=newNode;	
}