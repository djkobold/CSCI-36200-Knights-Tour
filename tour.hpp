//Daniel Kobold
//CSCI362 PA1
//tour.hpp

#ifndef	TOUR_H
#define	TOUR_H

#include <iostream>
#include <stack>

//Answer Struct (for putting all answers in one array)
struct answer{
	int solution[8][8];
};

//Option Struct
struct option{
	int xcord, ycord;	//The potential new position for this option
	int xpos, ypos;		//The current position being moved from
	int score;			//The "score" to help make the choice
};

//Node Struct
struct node{
	int initX, initY;	//Initial positions from beginning of problem
	int xcord, ycord;	//Current position of the knight in this problem
	int sol[8][8];		//Solution to the Knights Tour problem
	int board[8][8];	//Board multidimensional array to keep track of open spaces
	int skip, sk;		//Skipping variables
	int move;			//Keeps track of which move the knight is on
	struct node * next;	//Link to the next Knights Tour problem
};



int main(void);											//tour.cpp - highest level of program
void initEntry(void);									//initEntry.cpp - begin node entry process
void delEntry(void);									//initEntry.cpp - begin node deletion process
void addNode(int x, int y);								//node.cpp - add node for given coordinates
int delNode(int x, int y);								//node.cpp - delete node for given coordinates
void printList(void);									//node.cpp - print list of current initial positions
void printBoard(struct node * problem);					//node.cpp - print entire (solution) board for this problem
void insertFirst(int x, int y);							//node.cpp - insert new node as head
void insertAfter(int x, int y);							//node.cpp - insert node at end of linked list
void nextMove(int i, int j, struct node * problem);		//nextMove.cpp - determine options and select best option for next move
void move(int i, int j, int choice, node * problem);	//nextMove.cpp - complete the move given initial position, destination, and board state
void resetOptions(int i, int j);						//nextMove.cpp - find new options based on given position
int warnsdoff(int i, int j, struct node * problem);		//warnsdoff.cpp - find Warnsdoff score based on future moves (numMoves used instead)
int numMoves(int i, int j, node * problem);				//warnsdoff.cpp - find number of potential moves based on given position and board state
int stackguess(int i, int j, struct node * problem);	//stackguess.cpp - NO LONGER USED
extern std::stack <struct node> s;						//The stack used in this project

extern struct node *head;		//Used in entry and deletion, keeps track of head node
extern struct node *current;	//Used to keep track of current node, prob is used instead
extern struct node *prev;	//Used in entry and deletion
extern struct node *prob; //Keeps track of which knights tour problem is being solved					

extern struct option opts[8];		//Options #1
extern struct option opts2[8];		//Options #2
extern struct option opts3[8];		//Options #3
extern int which[64];				//Keeps track of which choice was chosen for each move
extern int over[64];				//Keeps track of number of options to be skipped
extern int getOut;					//Keep track of if emergency exit is needed
extern int detail;					//Keeps track of if user wants to see all details of Knights Tour	
extern int levels;					//Keeps track of number of levels of push/pull being used now (stack)
extern struct answer ans[8][8];			//FINAL ANSWER ARRAY (indices are initial position)

#endif