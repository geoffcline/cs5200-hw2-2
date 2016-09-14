// cs5200-hw2-2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <iostream>

using namespace std;

const int SZ = 8;
const int B_NEVER = -1;

int ktour(int x, int y, int movei, int sol[SZ][SZ], int xMove[], int yMove[]);

bool validmove(int x, int y, int sol[SZ][SZ])
{
  return (x >= 0 && x < SZ && y >= 0 &&
	y < SZ && sol[x][y] == -1);
}

bool finalmove(int x, int y, int sol[SZ][SZ])
{
  return (x >= 0 && x < SZ && y >= 0 &&
	y < SZ && sol[x][y] == 0);
}

void printboard(int sol[SZ][SZ])
{
  for (int x = 0; x < SZ; x++)
  {
	for (int y = 0; y < SZ; y++)
	  printf(" %2d ", sol[x][y]);
	printf("\n");
  }
}

int possiblemoves(int x, int y, int sol[SZ][SZ])
{
  int k;
  int next_x, next_y;
  int count = 0;

  int xMove[SZ] = { 2, 1, -1, -2, -2, -1,  1,  2 };
  int yMove[SZ] = { 1, 2,  2,  1, -1, -2, -2, -1 };

  for (k = 0; k < 8; k++)
  {
	next_x = x + xMove[k];
	next_y = y + yMove[k];
	if (validmove(next_x, next_y, sol))
	{
	  count++;
	}
  }

  return count;
}

void moveorder(int x, int y, int sol[SZ][SZ], int sorted[8])
{
  int k,j;
  int next_x, next_y;
  int count = 0;
  int result[8];

  int xMove[SZ] = { 2, 1, -1, -2, -2, -1,  1,  2 };
  int yMove[SZ] = { 1, 2,  2,  1, -1, -2, -2, -1 };

  for (k = 0; k < 8; k++)
  {
	next_x = x + xMove[k];
	next_y = y + yMove[k];
	result[k] = possiblemoves(next_x, next_y, sol);
  }

  int mini;
  int minv;

  for (k = 0; k < 8; k++)
  {
	j = 0;
	do
	{
	  mini = j;
	  minv = result[j];
	  j++;
	} while (minv == -1);
	
	for (; j < 8; j++)
	{
	  if (result[j] < minv && result[j] != -1)
	  {
		minv = result[j];
		mini = j;
	  }
	}

	sorted[k] = mini;
	result[mini] = -1;
  }


  return;
}

bool ktour()
{
  int sol[SZ][SZ];

  for (int x = 0; x < SZ; x++)
	for (int y = 0; y < SZ; y++)
	  sol[x][y] = B_NEVER;

  int xMove[SZ] = { 2, 1, -1, -2, -2, -1,  1,  2 };
  int yMove[SZ] = { 1, 2,  2,  1, -1, -2, -2, -1 };

  int kx = rand() % SZ;
  int ky = rand() % SZ;

  ky = 0;
  kx = 0;

  cout << kx << "," << ky << endl;

  sol[kx][ky] = 0;

  if (ktour(kx, ky, 1, sol, xMove, yMove) == false)
  {
	printf("Solution does not exist");
	return false;
  }
  else
	printboard(sol);

  return true;
}

int ktour(int x, int y, int movei, int sol[SZ][SZ],
  int xMove[SZ], int yMove[SZ])
{
  int k, next_x, next_y;
  int om[8];

  if (movei == SZ*SZ)
  {
	k = 0;
	bool res = false;
	while (!res && k < 8)
	{
	  next_x = x + xMove[k];
	  next_y = y + yMove[k];
	  if (finalmove(next_x, next_y, sol))
	  {
		res = true;
	  }
	  k++;
	}
	return res;
  }

  printboard(sol);

  moveorder(x, y, sol, om);


  for (k = 0; k < 8; k++)
  {
	next_x = x + xMove[om[k]];
	next_y = y + yMove[om[k]];


	if (validmove(next_x, next_y, sol))
	{
	  sol[next_x][next_y] = movei;
	  if (ktour(next_x, next_y, movei + 1, sol,
		xMove, yMove) == true)
		return true;
	  else
		sol[next_x][next_y] = B_NEVER;
	}
  }

  return false;
}
int main()
{
  char x;
  ktour();

  cin >> x;
  return 0;
}

