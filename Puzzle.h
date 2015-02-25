//Nathan Kowaleski
//Lab 5 Part 1
//Sudoku puzzle
//Puzzle class .h file
// 02-24-15

#ifndef PUZZLE_H
#define PUZZLE_H
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

template <typename T>
class Puzzle
{

public:

  Puzzle(string, int);
  void print();
  int check(int, int, T);
  void set(int, int, T);
  int isComplete();
private:

  int size;
  vector < vector < T > >puz;

};

template <typename T>
Puzzle <T>::Puzzle(string s, int n)
{
  size = n;
  ifstream f;
  f.open(s.c_str());
  T x;				//int reading to from file
  int i;			//for loop counter
  int j;			//for loop counter
  for(i = 0; i < size; i++)
    {
      puz.push_back(vector < T > ());	//fill one vector with vectors
      for(j = 0; j < size; j++)
	{
	  f >> x;
	  puz[i].push_back(x);	//fill in the vectors with values from file
	}
    }
  f.close ();
}

//print function
template <typename T>
void Puzzle <T>::print()
{
  cout << endl;
  typename vector < vector < T > >::iterator row;
  typename vector < T >::iterator col;
  for (row = puz.begin (); row != puz.end (); row++)
    {
      for (col = row->begin (); col != row->end (); col++)
	{
	  cout << *col << " ";	//for all positions print out the value and a space
	}
      cout << endl;
    }
  cout << endl;
}

//check to make sure placement is valid
template <typename T>
int Puzzle <T>::check(int x, int y, T t)
{
  int xstart;			//place in sector
  int ystart;			//place in sector
  int z;			//for checking in row and column
  int i;			//for loop variable
  int j;			//for loop variable
  if (puz[x][y] != 0)		//if the space isn't empty not valid
    return 0;
  for (z = 0; z < size; z++)
    {
      if (puz[x][z] == t || puz[z][y] == t)
	return 0;		//if same value in a row or column then not valid
    }
  if (size == 4)		//check to see which of the 4by4 sectors its in
    {
      if (x < 2)
	xstart = 0;
      else
	xstart = 2;
      if (y < 2)
	ystart = 0;
      else
	ystart = 2;
      if (t == puz[xstart][ystart] || t == puz[xstart + 1][ystart]
	  || t == puz[xstart][ystart + 1] || t == puz[xstart + 1][ystart + 1])
	return 0;		//if same value already exists in sector then not valid
    }

  if (size == 9)		//check to see which of the 9by9 sectors it's in 
    {
      if (x < 3)
	xstart = 0;
      if (x > 5)
	xstart = 6;
      if (x > 2 && x < 6)
	xstart = 3;

      if (y < 3)
	ystart = 0;
      if (y > 5)
	ystart = 6;
      if (y > 2 && y < 6)
	ystart = 3;

      for (i = xstart; i < xstart + 3; i++)
	{
	  for (j = ystart; j < ystart + 3; j++)
	    {
	      if (t == puz[i][j])
		return 0;	//if the value already exists in the sector then not a valid placement
	    }
	}
    }

  return 1;
}

//check to see if puzzle is complete
template <typename T>
int Puzzle <T>::isComplete()
{
  int x;
  int y;
  for (x = 0; x < size; x++)
    {
      for (y = 0; y < size; y++)
	{
	  if (puz[x][y] == 0)
	    return 0;		//if any of the spaces are 0 then the puzzle is not complete
	}
    }
  return 1;
}

//set space x,y equal to value t
template <typename T>
void Puzzle <T>::set(int x, int y, T t)
{
  puz[x][y] = t;
}

#endif
