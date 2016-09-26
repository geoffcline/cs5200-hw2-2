// CS5200-A HW2
// 9/14/2016
// Geoffrey Cline
// Knight's Closed Tour

//include "stdafx.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <time.h>

using namespace std;

const int SZ = 8;
const int B_NEVER = -1;
const int MV_SZ = 8;

bool ktour();

//utility function for ktour()
//xMove[] and yMove[] are relative moves availalbe
//sol[] represents the board, with each location holding a move number
//        or -1 for not moved there yet
//x,y represent current knight location
//movei is the number of moves currently decided
//return true/false if solution possible based on board and location
bool ktour(const int x, const int y, const int movei, int sol[SZ][SZ], const int xMove[], const int yMove[]);

//Returns true if position x,y on the given board is a valid move
//Returns false if the position is off the board, or already taken
bool validmove(const int x, const int y, const int sol[SZ][SZ]);

//Return true if the position x,y is on the board, AND
//the position is the start position
bool finalmove(const int x, const int y, const int sol[SZ][SZ]);

//prints the board to COUT
void printboard(const int sol[SZ][SZ]);

//returns the number of possible moves from location x,y
//based on validmove()
int possiblemoves(const int x, const int y, const int sol[SZ][SZ]);

//returns an order of moves, based on the number of valid moves
//from the result location of all possible moves. The order
//is from least, to greatest, number of possible sub-moves
void moveorder(const int x, const int y, const int sol[SZ][SZ], int sorted[MV_SZ]);

int main()
{
  srand(time(NULL));
  
  ktour();

  cout << "Any input to quit..." << endl;
  char x;
  cin >> x;
  return 0;
}

bool validmove(const int x,const int y, const int sol[SZ][SZ])
{ 
  //check if in board bounds and not already moved
  return (x >= 0 && x < SZ && y >= 0 &&
	y < SZ && sol[x][y] == -1);
}

bool finalmove(const int x, const int y, const int sol[SZ][SZ])
{
  //check if in board bounds, and move is to start location
  return (x >= 0 && x < SZ && y >= 0 &&
	y < SZ && sol[x][y] == 0);
}

void printboard(const int sol[SZ][SZ])
{
  //for all x rows
  for (int x = 0; x < SZ; x++)
  {
	//for all positions in row
	for (int y = 0; y < SZ; y++)
	  printf(" %2d ", sol[x][y]);
	printf("\n");
  }
}

int possiblemoves(const int x, const int y,const int sol[SZ][SZ])
{
  int k;
  int next_x, next_y;
  int count = 0;

  //moves identified by index
  int xMove[SZ] = { 2, 1, -1, -2, -2, -1,  1,  2 };
  int yMove[SZ] = { 1, 2,  2,  1, -1, -2, -2, -1 };

  //for all possible moves
  for (k = 0; k < MV_SZ; k++)
  {
	next_x = x + xMove[k];
	next_y = y + yMove[k];
	if (validmove(next_x, next_y, sol))
	{
	  count++; 
	  //count number of moves to valid location
	}
  }

  return count;
}

void moveorder(const int x, const int y, const int sol[SZ][SZ], int sorted[MV_SZ])
{
  int k,j;
  int next_x, next_y;
  int count = 0;
  int result[MV_SZ];

  //moves identified by index
  int xMove[SZ] = { 2, 1, -1, -2, -2, -1,  1,  2 };
  int yMove[SZ] = { 1, 2,  2,  1, -1, -2, -2, -1 };

  //for all possible moves
  for (k = 0; k < MV_SZ; k++)
  {
	//simulate that move
	next_x = x + xMove[k];
	next_y = y + yMove[k];
	//record possible moves from that location
	result[k] = possiblemoves(next_x, next_y, sol);
  }

  int mini;
  int minv;

  //for all possible moves
  for (k = 0; k < MV_SZ; k++)
  {
	//move j to first element not == -1
	//that location basis for min element test
	j = 0;
	do
	{
	  mini = j;
	  minv = result[j];
	  j++;
	} while (minv == -1);
	
	//for remaining positions
	for (; j < MV_SZ; j++)
	{
	  //if position less than current min
	  if (result[j] < minv && result[j] != -1)
	  {
		//record value and location of new min
		minv = result[j];
		mini = j;
	  }
	}

	//record index of min
	sorted[k] = mini;
	//delete element
	result[mini] = -1;
  }

  //sorted[] should be indexes of result[] such that
  //result[] is sorted min to max based on possible moves

  //essentially, sorted[] is an order of the possible index
  //of the array of possible moves, such that all moves will be
  //attempted, but in order of fewest possible moves from that location

  return;
}

bool ktour()
{
  //setup board
  int sol[SZ][SZ];

  for (int x = 0; x < SZ; x++)
	for (int y = 0; y < SZ; y++)
	  sol[x][y] = B_NEVER;

  int xMove[SZ] = { 2, 1, -1, -2, -2, -1,  1,  2 };
  int yMove[SZ] = { 1, 2,  2,  1, -1, -2, -2, -1 };

  //random start location
  int kx = rand() % SZ;
  int ky = rand() % SZ;

  //knight at start location
  sol[kx][ky] = 0;

  //begin recursive calls
  if (ktour(kx, ky, 1, sol, xMove, yMove) == false)
  {
	printf("Solution does not exist");
	return false;
  }
  else
	printboard(sol);

  return true;
}

bool ktour(const int x, const int y, const int movei, int sol[SZ][SZ], const int xMove[SZ], const int yMove[SZ])
{
  int k, next_x, next_y;
  int om[MV_SZ];

  //if board full
  if (movei == SZ*SZ)
  {
	k = 0;
	bool res = false;
	
	//while a move to the start position has not been found
	//AND still move moves to test
	while (!res && k < MV_SZ)
	{
	  //simulate a move
	  next_x = x + xMove[k];
	  next_y = y + yMove[k];

	  //check if that move gets you to the start position
	  if (finalmove(next_x, next_y, sol))
	  {
		res = true;
	  }
	  k++;
	}

	//return true if at least one valid move gets to 
	//start position
	return res;
  }

  //order the possible moves from the current location
  //so move that leads to fewest sub-moves attempted first
  moveorder(x, y, sol, om);

  //for all moves from the location
  for (k = 0; k < MV_SZ; k++)
  {
	//simulate the move
	//om[k] gives the index of the move with the kth lowest
	//number of possible moves from the that location
	next_x = x + xMove[om[k]];
	next_y = y + yMove[om[k]];


	//if move actually valid
	if (validmove(next_x, next_y, sol))
	{
	  //mark the location with the move number
	  sol[next_x][next_y] = movei;
	  
	  //recursive call
	  if (ktour(next_x, next_y, movei + 1, sol,
		xMove, yMove) == true)
		return true;
	  else
		sol[next_x][next_y] = B_NEVER; //reset when backtracking
	}
  }

  return false;
}


